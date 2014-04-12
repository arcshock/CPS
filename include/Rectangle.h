#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <string>
using std::string;
using std::to_string;

class Rectangle
{
	public:
		Rectangle(double length, double width) : _length(length), _width(width) 
		{}
		double width()
		{
			return _width;
		}
		double length()
		{
			return _length;
		}
		string print()
		{
			string toPS = to_string(_width / 2.0) + " inch " + to_string(_length / 2.0) +
					" inch rmoveto\n" + 
					 "-" + to_string(_width) + " inch 0 inch rlineto\n"
					 "0 inch -" + to_string(_length) + " inch rlineto\n" +
					 to_string(_width) + " inch 0 inch rlineto\n"
					 "0 inch " + to_string(_length) + " inch rlineto\n"
					 "stroke\n";
			return toPS;


		}

	private:
		double _length;
		double _width;
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

