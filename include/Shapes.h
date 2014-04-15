#ifndef SHAPES_H
#define SHAPES_H
#include <string>
using std::string;
using std::to_string;

#include <utility>
using std::pair;
using std::make_pair;

class Polygon 
{
	typedef pair<double, double> coordinate; 

	public:
		Polygon(int numSides, double sideLength):_numSides(numSides), _sideLength(sideLength)
		{
			setHeight();
			setWidth();
			initializeStartingPoint();
		}

		coordinate initializeStartingPoint()
		{
			if (isOdd()) {
				return make_pair(0.0, (_height / 2.0) / 72.0);
			} else {
				return make_pair((_sideLength/2.0) / 72.0, (_height / 2.0) / 72.0);
			}
		}

		void drawPolygon()
		{
			for (int ii = 0; ii < _numSides; ++ii) {
				_outputToPostScript += ""; // PS to draw the lines of side length
				_outputToPostScript += ""; // PS to rotate by 360/numSides
			}
			_outputToPostScript += "Stroke\n";
		}
	private:

		bool isOdd()
		{
			return _numSides%2;
		}
		
		bool isEven()
		{
			return !isOdd();
		}

		void setHeight()
		{
			// TODO
		}

		void setWidth()
		{
			// TODO
		}

		string _outputToPostScript;
		int _numSides;
		double _sideLength;
		double _height;
		double _width;
};

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

