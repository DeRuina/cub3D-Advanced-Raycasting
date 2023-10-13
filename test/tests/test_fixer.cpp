#include <fcntl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int fix_test(char *path)
{
	string path1 = path;
	ifstream fileIn(path1);
	if (!fileIn.is_open())
	{
		cout << "Error: failed to open input file" << endl;
		return (3);
	}
	std::ofstream outFile((path1 + ".replace").c_str());

	for (string line; getline(fileIn, line);)
	{
		if (line.find("SO") != string::npos && line.find("SO") == 0 && line[line.find("SO") + 4] != ' ' )
			line.replace(line.find("SO") + 3, line.length() - 3,  "textures/test/SO.png");
		if (line.find("NO") != string::npos && line.find("NO") == 0 && line[line.find("NO") + 4] != ' ' )
			line.replace(line.find("NO") + 3, line.length() - 3,  "textures/test/NO.png");
		if (line.find("WE") != string::npos && line.find("WE") == 0 && line[line.find("WE") + 4] != ' ' )
			line.replace(line.find("WE") + 3, line.length() - 3,  "textures/test/WE.png");
		if (line.find("EA") != string::npos && line.find("EA") == 0 && line[line.find("EA") + 4] != ' ' )
			line.replace(line.find("EA") + 3, line.length() - 3,  "textures/test/EA.png");
		outFile << line << std::endl;
	}


	return (0);
}
