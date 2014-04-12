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
					"gsave\n" 
					"\t" + to_string(width / 2.0) + " inch " + to_string(height / 2.0) +
					" inch rmoveto\n" + 
					"\t-" + to_string(width) + " inch 0 inch rlineto\n"
					"\t0 inch -" + to_string(height) + " inch rlineto\n" +
					"\t" + to_string(width) + " inch 0 inch rlineto\n"
					"\t0 inch " + to_string(height) + " inch rlineto\n";
		}
		virtual string print()
		{
			return _outputToPostScript + "grestore\n";
		}

	protected:
		string _outputToPostScript;
};

class Rectangle : public Spacer
{
	public:
		Rectangle(double width, double height) : Spacer(width, height) 
		{
			_outputToPostScript += "\tstroke\n";
		}

};

class Square : public Rectangle
{
	public:
		Square(double side) : Rectangle(side, side) {}
};

/*
class Circle
{
	public:
		Circle(double radius)
		{
			_outputToPostScript =
					"
				
};
*/
#endif

