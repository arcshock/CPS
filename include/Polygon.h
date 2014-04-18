#ifndef POLYGON_H
#define POLYGON_H

#include "Shapes.h"

const double PI = 3.14159265358979;

class Polygon : public Shape 
{
	typedef pair<double, double> coordinate; 

	public:
		Polygon(int numSides, double sideLength):
			_numSides(numSides), _degrees(360 / numSides)
		{
			_sideLength = toInches(sideLength);
			setHeight();
			setWidth();
			coordinate startingPoint = initializeStartingPoint();

			_tempPSText = "\t" + to_string(startingPoint.first) + " inch -" + 
								  to_string(startingPoint.second) + " inch rmoveto\n";

			for (int side = 0; side < _numSides; ++side)
			{
				_tempPSText += "\t" + to_string(_degrees) + " rotate\n" +
					"\t" + to_string(_sideLength) + " inch 0 inch rlineto\n";
			}
			_tempPSText += "\tstroke\n";
		}

		coordinate initializeStartingPoint()
		{
			coordinate startingPoint = make_pair(_sideLength / 2.0, _height / 2.0);
			return startingPoint;
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

		int _numSides;
		double _sideLength;
		double _degrees;
};

#endif /* POLYGON_H */
