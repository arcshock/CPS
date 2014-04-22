#ifndef SHAPES_H
#define SHAPES_H
#include <string>
using std::string;
using std::to_string;
#include <cmath>
using std::sin;
using std::cos;
#include <utility>
#include <initializer_list>
using std::initializer_list;
#include <fstream>

const double PI = 3.14159265358979;

class Shape
{
	public:
		virtual ~Shape() {}
		virtual string draw()
		{
			return "gsave\n" + _tempPSText + "grestore\n";
		}

		double toInches(int value)
		{
			return value / 72.0;
		}

		void setBoundingBox(int height, int width)
		{
			_height = toInches(height);
			_width = toInches(width);
		}

		string getTempPostScriptText()
		{
			return _tempPSText;
		}

		string toString(double number)
		{
			string str = to_string(number);
			str.erase( str.find_last_not_of('0') + 1, string::npos );
			if (str.back() == '.')
				str.pop_back();
			return str;
		}

		virtual string textToFile(string fileName)
		{
			std::ofstream outputPSFile;
			outputPSFile.open(fileName, std::ios::binary);
			outputPSFile << "%!\n/inch { 72 mul } def\n"
				"3 inch 3 inch moveto\n" << draw() << "\n\nshowpage";
			outputPSFile.close();

			return "I";
		}

		double getHeight()
		{
			return _height;
		}

		double getWidth()
		{
			return _width;
		}	

	protected:
		double _height;
		double _width;
		string _tempPSText;
};

#endif /* SHAPES_H */

