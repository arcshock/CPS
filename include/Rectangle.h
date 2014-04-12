#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <string>
using std::string;
using std::to_string;

class Rectangle
{
	public:
		Rectangle(double width, double height) : _width(width), _height(height) 
		{}
		double height()
		{
			return _height;
		}
		double width()
		{
			return _width;
		}
		string print()
		{
			string toPS = to_string(_width / 2.0) + " inch " + to_string(_height / 2.0) +
					" inch rmoveto\n" + 
					 "-" + to_string(_width) + " inch 0 inch rlineto\n"
					 "0 inch -" + to_string(_height) + " inch rlineto\n" +
					 to_string(_width) + " inch 0 inch rlineto\n"
					 "0 inch " + to_string(_height) + " inch rlineto\n"
					 "stroke\n";
			return toPS;


		}

	private:
		double _width;
		double _height;
};

#endif

#ifndef SQUARE_H
#define SQUARE_H

class Square : public Rectangle
{
	public:
		Square(double side) : Rectangle(side, side) {}
};

#endif

