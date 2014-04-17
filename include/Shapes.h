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

const double PI = 3.14159265358979;

class Polygon 
{
	typedef pair<double, double> coordinate; 

	public:
		Polygon(int numSides, double sideLength):
			_numSides(numSides), _sideLength(sideLength / 72.0), _degrees(360 / numSides)
		{
			setHeight();
			setWidth();
			coordinate startingPoint = initializeStartingPoint();
			_outputToPostScript = "\t" + to_string(startingPoint.first) + " inch " + 
								  to_string(startingPoint.second) + " inch rmoveto\n";

			for (int side = 0; side < _numSides; ++side)
			{
				_outputToPostScript += "\t" + to_string(_degrees) + " rotate\n" +
					"\t" + to_string(_sideLength) + " inch 0 inch rlineto\n";
			}
			_outputToPostScript += "\tstroke\n";
			_outputToPostScript = "gsave\n" + _outputToPostScript + "grestore\n";
		}

		coordinate initializeStartingPoint()
		{
			coordinate startingPoint = make_pair(0.0, _height / 2.0);
			if (isNumSidesEven()) {
				startingPoint.first = _sideLength / 2.0;
			}
			return startingPoint;
		}

		string draw()
		{

			return _outputToPostScript;
		}
	private:

		bool isNumSidesOdd()
		{
			return _numSides % 2;
		}
		
		bool isNumSidesEven()
		{
			return !isNumSidesOdd();
		}
		
		bool sidesDivisibleByFour()
		{
			return (_numSides % 4 == 0);
		}
		bool sidesNotDivisibleByFour()
		{
			return !sidesDivisibleByFour();
		}
		
		void setHeight()
		{
			double angle = PI / _numSides;
			if (isNumSidesOdd()) {
				_height = _sideLength * (1 + cos(angle)) / (2 * sin(angle));
			}
			else {
				_height = _sideLength * cos(angle) / sin(angle);
			}

		}

		void setWidth()
		{
			double angle = PI / _numSides;
			if (isNumSidesOdd()) {
				_width = (_sideLength * sin(angle * (_numSides - 1) / 2))  / sin(angle);
			}
			else {
				_width = _sideLength / sin(angle);
				if (sidesNotDivisibleByFour()) {
					_width *= cos(angle);
				}
			}
		}

		string _outputToPostScript;
		int _numSides;
		double _sideLength;
		double _degrees;
		double _height;
		double _width;
};

class Spacer
{
	public:
		Spacer(double width, double height): _width(width / 72.), _height(height / 72.)
		{
			_outputToPostScript = 
					"\t" + to_string(_width / 2.0) + " inch " + to_string(_height / 2.0) +
					" inch rmoveto\n" + 
					"\t-" + to_string(_width) + " inch 0 inch rlineto\n"
					"\t0 inch -" + to_string(_height) + " inch rlineto\n" +
					"\t" + to_string(_width) + " inch 0 inch rlineto\n"
					"\t0 inch " + to_string(_height) + " inch rlineto\n";
		}
		virtual string draw()
		{
			return "gsave\n" + _outputToPostScript + "grestore\n";
		}

	protected:
		string _outputToPostScript;
		double _width;
		double _height;
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

class Circle
{
	public:
		Circle(double radius) : _radius(radius / 72.)
		{
			_outputToPostScript = "\t0 0 " + to_string(_radius) + " inch 0 360 arc\n"
				"\tclosepath\n"
				"\tstroke\n";
		}			

		string draw()
		{
			return "gsave\n" + _outputToPostScript + "grestore\n";
		}

	private: 
		double _radius;
		string _outputToPostScript;

};
#endif

