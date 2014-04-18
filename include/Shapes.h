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


class Shape
{
	public:
		string draw()
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
			_tempPSText = "\t0 0 " + to_string(_radius) + " inch 0 360 arc\n"
				"\tclosepath\n"
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
		Rotated(Shape shape, double angle)
		{
			_tempPSText = "\t" + to_string(angle) +
							" rotate\n" +
							shape.getTempPostScriptText();
		}
};

/*
class Layered : public Shape
{
	public:
		Layered(Shape shape ...)
};*/
#endif /* SHAPES_H */
