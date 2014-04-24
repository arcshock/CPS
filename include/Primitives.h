#ifndef PRIMITIVES_H
#define PRIMITIVES_H
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
		Star(int starRadius) : _radius(starRadius / 72.0)
		{
			setBoundingBox();
			_tempPSText = 
				"% Star\n"
				"\t180 rotate\n"
				"\t-" + toString(_width / 2.0) + " inch -" + 
				toString(getPentagonDownPoint()) + " inch rmoveto\n"
				"\t5 {\n"
				"\t\t" + toString(getPentagonSideLength()) + " inch 0 inch rlineto\n"
				"\t\t144 rotate\n"
				"\t} repeat\n"
				"\tstroke\n";
		}

		double getPentagonDownPoint()
		{
			double down = 0.5 * sqrt(0.2 * (5 - 2 * sqrt(5)));
			return getPentagonSideLength() * down;
		}

		double getPentagonSideLength()
		{
			return _radius / sqrt(.1 * (5 - sqrt(5)));
		}

		double getPentagonHeight()
		{
			double radical = (25.0 - 11.0 * sqrt(5.0));
			double circumRadiusInnerPentagon = sqrt(0.1 * radical);
			double verticaldistance = 0.5 * sqrt(0.5 * radical);
			return (_radius + circumRadiusInnerPentagon + verticaldistance) * sqrt(getPentagonSideLength());
		}


		virtual void setBoundingBox()
		{
			_width = getPentagonSideLength();
			_height = getPentagonHeight();
		}

		double _radius;
};

#endif /* PRIMITIVES_H */

