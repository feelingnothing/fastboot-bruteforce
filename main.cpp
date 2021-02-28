#include <iostream>
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
	string cmd = "fastboot oem unlock ";
	unsigned long long int i = 1000000000000000;
	while(true)
	{
		string command = cmd + to_string(i);
		string out = exec(command);
		system("cls");
		cout << to_string(i) + "\n";
		i += 30050100187;
		if (out.find("wrong") != string::npos) { continue; }
		break;
	}
	cout << "FOUND IT > " + to_string(i) + "\n";
	cin.get();
}
