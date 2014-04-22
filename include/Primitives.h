#ifndef PRIMITIVES_H
#define PRIMITIVES_H

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
		Star(int innerPentagonSideLength) 
		{
			const double PHI = 1.618034;
			double inchInnerPentagonSideLength = toInches(innerPentagonSideLength);
			double isocelesLeg = (inchInnerPentagonSideLength * PHI);
			setBoundingBox(inchInnerPentagonSideLength, isocelesLeg);
			_tempPSText = 
				"% Star\n"
				"\t180 rotate\n"  
				"\t" + toString(inchInnerPentagonSideLength / 2.0 ) + " inch -" 
				+ toString(inchInnerPentagonSideLength * 0.769421) + " inch rmoveto\n"
				"\t5 {\n"
				"\tgsave\n"
				"\t\t" + toString(isocelesLeg) + " inch 0 inch rlineto\n"
				"\t\t144 rotate\n"
				"\t\t" + toString(isocelesLeg) + " inch 0 inch rlineto\n"
				"\t\tstroke\n"
				"\tgrestore\n"
				"\t" + toString(72.0) + " rotate\n"
				"\t" + toString(inchInnerPentagonSideLength) + " inch 0 inch rlineto\n" 
				"\t} repeat\n"
				"\tstroke\n";
		}

		virtual void setBoundingBox(double innerPentagonSideLength, double isocelesLeg)
		{
			_width = innerPentagonSideLength + (2 * isocelesLeg);
			_height = _width * sin(72*PI/180); 
		}
};

#endif /* PRIMITIVES_H */

