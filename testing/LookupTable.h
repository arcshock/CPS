#ifndef LOOKUP_TABLE_H
#define LOOKUP_TABLE_H

#include <utility>
using std::pair;
#include <map>
using std::map;
#include <vector>
using std::vector;

typedef pair<int,int> LineRange;
map<string,LineRange> generateLookupTable(vector<string> testShapeNames)
{
	std::ifstream infile("testing/masterShapes.ps");
	map<string, LineRange> masterShapeLines;

	for (auto name : testShapeNames) 
		masterShapeLines.insert( pair<string,LineRange> (name, make_pair(-1,-1)));

	string line;
	string currentName;
	int lineNumber = 0;
	int programDepth = 0;

	while(std::getline(infile, line)) {
		++lineNumber;
		if (programDepth == 0 && line[0] != '%')
			continue;

		for (auto name : testShapeNames) {
			if (line.find(name) == string::npos) 
				continue;
			else {
				if (masterShapeLines[name].first == -1) {
					masterShapeLines[name].first = lineNumber + 1;
					currentName = name;
					programDepth = 1;
					break;
				}
			}
		}

		if (programDepth > 0)
		{
			if (line.find("gsave") != string::npos) {
				++programDepth;
			}
			if (line.find("grestore") != string::npos) {
				--programDepth;
				if (programDepth == 1) {
					masterShapeLines[currentName].second = lineNumber;
					programDepth = 0;
					continue;
				}
			}
		}
	}
	return masterShapeLines;
}

string getLinesFromMasterShapesFile(LineRange lines)
{
	std::ifstream infile("testing/masterShapes.ps");
    string line;
    string compPSText;
    int count = 0;

    while(std::getline(infile, line))
    {
        ++count;
        if (count > lines.second)
            break;
        if (count < lines.first)
            continue;
        compPSText += line + "\n";
    }
    return compPSText;
}

#endif

