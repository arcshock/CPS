#ifndef SHAPES_H
#define SHAPES_H
#include <string>
using std::string;
using std::to_string;

class Spacer
{
	public:
		Spacer(double width, double height)   
		{
			_outputToPostScript = 
					to_string(width / 2.0) + " inch " + to_string(height / 2.0) +
					" inch rmoveto\n" + 
					 "-" + to_string(width) + " inch 0 inch rlineto\n"
					 "0 inch -" + to_string(height) + " inch rlineto\n" +
					 to_string(width) + " inch 0 inch rlineto\n"
					 "0 inch " + to_string(height) + " inch rlineto\n";
		}
		virtual string print()
		{
			return _outputToPostScript;
		}

	protected:
		string _outputToPostScript;
};

class Rectangle : public Spacer
{
	public:
		Rectangle(double width, double height) : Spacer(width, height) 
		{
			_outputToPostScript += "stroke\n";
		}

};

class Square : public Rectangle
{
	public:
		Square(double side) : Rectangle(side, side) {}
};

#endif

