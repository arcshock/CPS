#ifndef SHAPES_H
#define SHAPES_H
#include <string>
using std::string;
using std::to_string;
#include <cmath>
using std::sin;
using std::cos;
#include <utility>
using std::pair;
using std::make_pair;
#include <initializer_list>
using std::initializer_list;
#include <fstream>
using std::ofstream;

enum RotationAngle { LEFT = 90, RIGHT = 270, INVERT = 180 };

class Shape
{
	public:
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

		string textToFile()
		{
			ofstream outputPSFile;
			outputPSFile.open("testing.ps");
			outputPSFile << "%!\n/inch { 72 mul } def\n3 inch 3 inch moveto\n" << draw() 
						 << "\n\nshowpage";
			outputPSFile.close();

			return "I";
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

			_tempPSText = 
					"\t" + to_string(_width / 2.0) + " inch " + to_string(_height / 2.0) +
					" inch rmoveto\n" + 
					"\t-" + to_string(_width) + " inch 0 inch rlineto\n"
					"\t0 inch -" + to_string(_height) + " inch rlineto\n" +
					"\t" + to_string(_width) + " inch 0 inch rlineto\n"
					"\t0 inch " + to_string(_height) + " inch rlineto\n";
		}

		virtual string draw()
		{
			return "gsave\n" + _tempPSText + "grestore\n";
		}

	protected:
};

class Rectangle : public Spacer
{
	public:
		Rectangle(double width, double height) : Spacer(width, height) 
		{
			_tempPSText += "\tstroke\n";
		}

};

class Square : public Rectangle
{
	public:
		Square(double side) : Rectangle(side, side) {}
};

class Circle : public Shape
{
	public:
		Circle(double radius) : _radius(radius / 72.)
		{
			setBoundingBox(radius * 2, radius * 2);
			_tempPSText = "\tcurrentpoint " + to_string(_radius) + " inch add moveto\n"
						"\tcurrentpoint " + to_string(_radius) + " inch sub " +
						to_string(_radius) + " inch -270 360 arc\n"
						"\tstroke\n";
		}			

	private: 
		double _radius;

};


class Scaled : public Shape
{
	public:
		Scaled(Shape shape, double xScaleFactor, double yScaleFactor)
		{
			_tempPSText = "\t" + to_string(xScaleFactor) + 
								  " " + to_string(yScaleFactor) + 
								  " scale\n" +
								  shape.getTempPostScriptText();
		}
};

class Rotated : public Shape
{
	public:
		Rotated(Shape shape, RotationAngle angle)
		{
			_tempPSText = "\t" + to_string(angle) +
							" rotate\n" +
							shape.getTempPostScriptText();
		}
};

class Layered : public Shape
{
	public:
		Layered(initializer_list<Shape> shapes)
		{
			for (auto shape : shapes)
			{	
				_tempPSText += "\n" + shape.draw() + "\n";
			}
		}

		virtual string draw() override
		{
			return  _tempPSText;
		}


};

#endif /* SHAPES_H */
