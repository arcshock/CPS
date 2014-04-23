#ifndef POLYGON_H
#define POLYGON_H
#include "Shapes.h"
using std::pair;
using std::make_pair;

class Polygon : public Shape 
{
	typedef pair<double, double> coordinate; 
	public:
	Polygon(int numSides, double sideLength):
		_numSides(numSides), _degreesPerSide(360.0 / numSides)
	{
		_sideLength = toInches(sideLength);
		updateHeight();
		updateWidth();
		updatePSText();
	}
	private:
	bool isNumSidesOdd()
	{
		return _numSides % 2;
	}

	void updateHeight()
	{
		double angle = PI / _numSides;
		if (isNumSidesOdd()) {
			_height = _sideLength * (1 + cos(angle)) / (2 * sin(angle));
		}
		else {
			_height = _sideLength * cos(angle) / sin(angle);
		}

	}

	void updateWidth()
	{
		double angle = PI / _numSides;
		if (isNumSidesOdd()) {
			_width = (_sideLength * sin(angle * (_numSides - 1) / 2))  / sin(angle);
		}
		else {
			_width = _sideLength / sin(angle);
			if (sidesDivisibleByFour()) {
				_width *= cos(angle);
			}
		}
	}

	bool sidesNotDivisibleByFour()
	{
		return !sidesDivisibleByFour();
	}

	bool sidesDivisibleByFour()
	{
		return (_numSides % 4 == 0);
	}

	void updatePSText()
	{
		coordinate start = initializeStartingPoint();
		_tempPSText = 
			"% " + toString(_numSides) + "-gon Side=" + toString(_sideLength) +
			"\n"
			"\t" + toString(start.first) + " inch "  
			"-" + toString(start.second) + " inch rmoveto\n"
			"\t" +  toString(_numSides) + " {\n"
			"\t\t" + toString(_degreesPerSide) + " rotate\n"
			"\t\t" + toString(_sideLength) + " inch 0 inch rlineto\n"
			"\t} repeat\n"
			"\tstroke\n";
	}

	coordinate initializeStartingPoint()
	{
		coordinate startingPoint = make_pair(_sideLength / 2.0, _height / 2.0);
		return startingPoint;
	}

	int _numSides;
	double _sideLength;
	double _degreesPerSide;
};

class Square : public Polygon
{
	public:
		Square(double side) : Polygon (4, side) {}
};

class Triangle : public Polygon
{
	public:
		Triangle(double sideLength) : Polygon (3, sideLength) {}
};

#endif /* POLYGON_H */
