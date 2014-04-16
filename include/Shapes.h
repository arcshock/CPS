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

class Polygon 
{
	typedef pair<double, double> coordinate; 

	public:
		Polygon(int numSides, double sideLength):_numSides(numSides / 72.0), _sideLength(sideLength / 72.0)
		{
			setHeightAndWidth();
			coordinate startingPoint = initializeStartingPoint();
		}

		coordinate initializeStartingPoint()
		{
			coordinate startingPoint = make_pair(0.0, _height / 2.0);
			if (isNumSidesEven()) {
				startingPoint.first = _sideLength/2.0;
			}
			return startingPoint;
		}

		void draw()
		{
			for (int ii = 0; ii < _numSides; ++ii) {
				_outputToPostScript += ""; // PS to draw the lines of side length
				_outputToPostScript += ""; // PS to rotate by 360/numSides
			}
			_outputToPostScript += "Stroke\n";
		}
	private:

		bool isNumSidesOdd()
		{
			return _numSides%2;
		}
		
		bool isNumSidesEven()
		{
			return !isNumSidesOdd();
		}
		
		bool isNotDivisibleByFour(int numSides)
		{
			return (numSides%4==0);
		}

		void setHeightandWidth()
		{
			const double PI = 3.14159265358979;
			const double ANGLE = PI / _numSides;
			if (isNumSidesOdd()) {
				_height = _sideLength * (1 + cos(ANGLE)) / 2 * ANGLE;
				_width = _sideLength * sin(ANGLE * (_numSides - 1) / 2);
			}
			else {
				_height = _sideLength * cos(ANGLE) / sin(ANGLE);
				_width = _sideLength / sin(ANGLE);
				if (isNotDivisibleByFour(_numSides)) {
					_width *= cos(ANGLE);
				}
			}
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
					"\t" + to_string(width / 2.0) + " inch " + to_string(height / 2.0) +
					" inch rmoveto\n" + 
					"\t-" + to_string(width) + " inch 0 inch rlineto\n"
					"\t0 inch -" + to_string(height) + " inch rlineto\n" +
					"\t" + to_string(width) + " inch 0 inch rlineto\n"
					"\t0 inch " + to_string(height) + " inch rlineto\n";
		}
		virtual string draw()
		{
			return "gsave\n" + _outputToPostScript + "grestore\n";
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

