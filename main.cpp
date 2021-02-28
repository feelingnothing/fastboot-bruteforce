#include <iostream>
#include <math.h>
#include <string>

using namespace std;

string exec(string cmd) {
    char buffer[128];
    string result = "";
	cmd = cmd + " 2>&1";
    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) throw runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        _pclose(pipe);
        throw;
    }
    _pclose(pipe);
    return result;
}

int main()
{
	// set them if you dont want to enter imei and start every time and compile it
	const unsigned long long int static_start = 0;
	const int static_imei = 0;

	int imei;
	unsigned long long int start;
	string cmd = "fastboot oem unlock ";
	cout << "Hi? So, this script support only devices that are not being reloaded after some tries, this is IMPORTANT\n";
	cout << "script doesn't handle this stuff\n";
	cout << "Requirements!!: Have adb.exe, fastboot.exe and all dependencies in same folder as this executable\n";

	if (static_imei == 0) {
		cout << "\n\nEnter your IMEI\n";
		cin >> imei;
	}

	if (static_start == 0) {
		cout << "If yout want to start from custom position - enter it, if not - enter 0\n";
		cin >> start;
	}

	if (static_imei != 0) { imei = static_imei; }
	if (static_start != 0 ) { start = static_start; }

	unsigned long long int i = 1000000000000000;
	int step = sqrt(imei) * 14;
	if (start != 0) { i = start; }
	while(true)
	{
		string command = cmd + to_string(i);
		string out = exec(command);
		cout << to_string(i) + "\n";
		i += step;
		if (out.find("wrong") != string::npos) { continue; }
		break;
	}
	cout << "FOUND IT > " + to_string(i) + "\n";
	cin.get();
}
