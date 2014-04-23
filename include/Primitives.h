#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include "Shapes.h"
#include <cmath>
using std::sin;
using std::cos;
using std::sqrt;

const double PHI = 1.618034;

class Spacer : public Shape
{
	public:
		Spacer(double width, double height)
		{
			_width = toInches(width);
			_height = toInches(height);
		}
};

class Rectangle : public Spacer
{
	public:
		Rectangle(double width, double height) : Spacer(width, height) 
	{
		_tempPSText = 
			"% Rectangle Width=" + toString(_width) + " Height=" +
			toString(_height) + "\n"
			"\t" + toString(_width / 2.0) + " inch " +
			toString(_height / 2.0) + " inch rmoveto\n" + 
			"\t-" + toString(_width) + " inch 0 inch rlineto\n"
			"\t0 inch -" + toString(_height) + " inch rlineto\n" +
			"\t" + toString(_width) + " inch 0 inch rlineto\n"
			"\t0 inch " + toString(_height) + " inch rlineto\n"
			"\tstroke\n";
	}
};

class Circle : public Shape
{
	public:
		Circle(double radius) : _radius(radius / 72.)
	{
		setBoundingBox(radius * 2, radius * 2);
		_tempPSText =
			"% Circle Radius=" + toString(_radius) + "\n" 
			"\tcurrentpoint " + toString(_radius) + " inch add moveto\n"
			"\tcurrentpoint " + toString(_radius) + " inch sub " +
			toString(_radius) + " inch -270 360 arc\n"
			"\tstroke\n";
	}			
	private: 
		double _radius;
};

class Star : public Shape
{
	public:
		Star(double sideLength)
		{
			sideLength = toInches(sideLength);
			double isocelesLeg = (sideLength/(2*PHI +1));
			double innerPentagonSideLength = isocelesLeg/PHI;
			double outerPentagonSideLength = isocelesLeg + innerPentagonSideLength;
			setBoundingBox(sideLength);
			_tempPSText = 
				"% Star\n"
				"\t -180 rotate\n"
				"\t" + toString((innerPentagonSideLength + isocelesLeg) / 2 ) + " inch -" + toString(_height / 2) + " inch rmoveto\n"
				"\t1 1 5 {\n"
				"\tpop\n"
				"\t\t144 rotate\n"
				"\t\t" + toString(_width) + " inch 0 rlineto\n"
				"\t} for\n"
				"\tstroke\n";
		}

		double getPentagonSideLength()
		{
			const double PHISQ = PHI * PHI;
			double numerator = 
				-(PHISQ + PHI - (2 * _radius * PHISQ) - (_radius / 2) + .25);
			double denominator =
				(PHISQ * PHISQ) - PHISQ / 2 + .0625;
			return sqrt(numerator / denominator);
		}

		virtual void setBoundingBox(double sideLength)
		{
			double angle = PI / 5;
			_width = sideLength;//xinnerPentagonSideLength + (2 * isocelesLeg);
			_height = sideLength;//(_width - isocelesLeg) * (1 + cos(angle)) / (2 * sin(angle));
		}

		double _radius;
};

#endif /* PRIMITIVES_H */

