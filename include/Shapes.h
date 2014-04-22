#ifndef SHAPES_H
#define SHAPES_H
#include <string>
using std::string;
using std::to_string;
#include <cmath>
using std::sin;
using std::cos;
using std::sqrt;
#include <utility>
#include <initializer_list>
using std::initializer_list;
#include <fstream>

const double PI = 3.14159265358979;
const double PHI = 1.618034;
enum RotationAngle { LEFT = 90, RIGHT = 270, INVERT = 180 };

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

class Spacer : public Shape
{
	public:
		Spacer(double width, double height)
		{
			_width = toInches(width);
			_height = toInches(height);
		}
};

class Rectangle : public Spacer
{
	public:
		Rectangle(double width, double height) : Spacer(width, height) 
	{
		_tempPSText = 
			"% Rectangle Width=" + toString(_width) + " Height=" +
			toString(_height) + "\n"
			"\t" + toString(_width / 2.0) + " inch " +
			toString(_height / 2.0) + " inch rmoveto\n" + 
			"\t-" + toString(_width) + " inch 0 inch rlineto\n"
			"\t0 inch -" + toString(_height) + " inch rlineto\n" +
			"\t" + toString(_width) + " inch 0 inch rlineto\n"
			"\t0 inch " + toString(_height) + " inch rlineto\n"
			"\tstroke\n";
	}
};

class Circle : public Shape
{
	public:
		Circle(double radius) : _radius(radius / 72.)
	{
		setBoundingBox(radius * 2, radius * 2);
		_tempPSText =
			"% Circle Radius=" + toString(_radius) + "\n" 
			"\tcurrentpoint " + toString(_radius) + " inch add moveto\n"
			"\tcurrentpoint " + toString(_radius) + " inch sub " +
			toString(_radius) + " inch -270 360 arc\n"
			"\tstroke\n";
	}			
	private: 
		double _radius;
};

class Star : public Shape
{
	public:
		Star(int innerPentagonSideLength) 
		{
			const double PHI = 1.618034;
			double inchInnerPentagonSideLength = toInches(innerPentagonSideLength);
			double isocelesLeg = (inchInnerPentagonSideLength * PHI);
			setBoundingBox(inchInnerPentagonSideLength, isocelesLeg);
			_tempPSText = 
				"% Star \n"
				"\t180 rotate\n"  
				"\t" + toString(inchInnerPentagonSideLength / 2.0 ) + " inch -" 
				+ toString(inchInnerPentagonSideLength * 0.769421) + " inch rmoveto\n"
				"\t5 {\n"
				"\tgsave\n"
				"\t\t" + toString(isocelesLeg) + " inch 0 inch rlineto\n"
				"\t\t144 rotate\n"
				"\t\t" + toString(isocelesLeg) + " inch 0 inch rlineto\n"
				"\t\tstroke\n"
				"\tgrestore\n"
				"\t" + toString(72.0) + " rotate\n"
				"\t" + toString(inchInnerPentagonSideLength) + " inch 0 inch rlineto\n" 
				"\t} repeat\n"
				"\tstroke\n";
		}

		Star(double starRadius) : _radius(starRadius)
		{
			double innerPentagonSideLength = getPentagonSideLength();
			double inchInnerPentagonSideLength = toInches(innerPentagonSideLength);
			double isocelesLeg = (inchInnerPentagonSideLength * PHI);
			setBoundingBox(inchInnerPentagonSideLength, isocelesLeg);
			_tempPSText = 
				"% Star \n"

				"\t" + toString(inchInnerPentagonSideLength / 2.0 ) + " inch -" 
				+ toString(inchInnerPentagonSideLength * 0.769421) + " inch rmoveto\n"
				"\t5 {\n"
				"\tgsave\n"
				"\t\t" + toString(isocelesLeg) + " inch 0 inch rlineto\n"
				"\t\t144 rotate\n"
				"\t\t" + toString(isocelesLeg) + " inch 0 inch rlineto\n"
				"\t\tstroke\n"
				"\tgrestore\n"
				"\t" + toString(72.0) + " rotate\n"
				"\t" + toString(inchInnerPentagonSideLength) + " inch 0 inch rlineto\n" 
				"\t} repeat\n"
				"\tstroke\n";
		}

		double getPentagonSideLength()
		{
			const double PHISQ = PHI * PHI;
			double numerator = 
				PHISQ + PHI - (2 * _radius * PHISQ) - (_radius / 2) + .25;
			double denominator =
				(PHISQ * PHISQ) - PHISQ / 2 + .0625;
			return sqrt(numerator / denominator);
		}

		virtual void setBoundingBox(double innerPentagonSideLength, double isocelesLeg)
		{
			_width = innerPentagonSideLength + (2 * isocelesLeg);
			_height = _width * sin(72*PI/180); 
		}

		double _radius;

};

#endif /* SHAPES_H */

