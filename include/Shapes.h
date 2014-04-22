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
#include <initializer_list>
using std::initializer_list;
#include <fstream>
using std::ofstream;
using std::ios;

const double PI = 3.14159265358979;
enum RotationAngle { LEFT = 90, RIGHT = 270, INVERT = 180 };

class Shape
{
	public:
		virtual ~Shape() {}
		virtual string draw()
		{
			return "gsave\n" + _tempPSText + "grestore\n";
		}

		double toInches(int value)
		{
			return value / 72.0;
		}
		
		void setBoundingBox(int height, int width)
		{
			_height = toInches(height);
			_width = toInches(width);
		}

		string getTempPostScriptText()
		{
			return _tempPSText;
		}
		
		string toString(double number)
		{
			string str = to_string(number);
			str.erase( str.find_last_not_of('0') + 1, string::npos );
			return str;
		}

		virtual string textToFile(string fileName)
		{
			ofstream outputPSFile;
			outputPSFile.open(fileName, ios::binary);
			outputPSFile << "%!\n/inch { 72 mul } def\n"
							"3 inch 3 inch moveto\n" << draw() << "\n\nshowpage";
			outputPSFile.close();

			return "I";
		}

		double getHeight()
		{
			return _height;
		}
	
		double getWidth()
		{
			return _width;
		}	

	protected:
		double _height;
		double _width;
		string _tempPSText;
};

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

class Scaled : public Shape
{
	public:
		Scaled(Shape shape, double xScaleFactor, double yScaleFactor)
		{
			_height = shape.getHeight() * yScaleFactor;
			_width = shape.getWidth() * xScaleFactor;
			_tempPSText = "\t" + toString(xScaleFactor) + 
								  " " + toString(yScaleFactor) + 
								  " scale\n" +
								  shape.getTempPostScriptText();
		}
};

class Rotated : public Shape
{
	public:
		Rotated(Shape shape, RotationAngle angle)
		{
			setBoundingBox(shape, angle);
			_tempPSText = "\t" + to_string(angle) +
							" rotate\n" +
							shape.getTempPostScriptText();
		}

		virtual void setBoundingBox(Shape shape, RotationAngle angle)
		{
			if (angle == INVERT)
			{
				_width = shape.getWidth();
				_height = shape.getHeight();
			}
			_width = shape.getWidth();
			_height = shape.getHeight();
		}	
};

class Layered : public Shape
{
	public:
		Layered(initializer_list<Shape> shapes)
		{
			_height = 0;
		 	_width = 0;
			_tempPSText = "% Layered Shapes Start\n";

			for (auto shape : shapes)
			{	
				setBoundingBox(shape);
				drawConsecutiveShapes(shape);
			}
		}

		virtual void setBoundingBox(Shape shape)
		{
				if (shape.getHeight() > _height)
					_height = shape.getHeight();
				if (shape.getWidth() > _width)
					_width = shape.getWidth();
		}	

		virtual void drawConsecutiveShapes(Shape shape)
		{
			_tempPSText += "\n" + shape.draw() + "\n";
		}

		virtual string draw() override
		{
			return  _tempPSText;
		}
};

class Vertical : public Shape
{
	public:
		Vertical(initializer_list<Shape> shapes)
		{
			_height = 0;
		 	_width = 0;
			_tempPSText = "% Vertical Shapes Start\n";

			for (auto shape : shapes)
			{	
				setBoundingBox(shape);
				drawConsecutiveShapes(shape);
			}
		}
	protected:
		virtual void setBoundingBox(Shape shape)
		{
				if (shape.getWidth() > _width)
					_width = shape.getWidth();
				_height += shape.getHeight();
		}	

		virtual void drawConsecutiveShapes(Shape shape)
		{
			_tempPSText += "0 " + toString(shape.getHeight() / 2) + " inch rmoveto\n" + 
						shape.draw() + "\n\n0 " +  toString(shape.getHeight() / 2) + 
						" inch rmoveto\n";
		}
};

class Horizontal : public Shape
{
	public:
		Horizontal(initializer_list<Shape> shapes)
		{
			_height = 0;
		 	_width = 0;
			_tempPSText = "% Horizontal Shapes Start\n";

			for (auto shape : shapes)
			{	
				setBoundingBox(shape);
				drawConsecutiveShapes(shape);
			}
		}
	protected:
		virtual void setBoundingBox(Shape shape)
		{
				if (shape.getHeight() > _height)
					_height = shape.getHeight();
				_width += shape.getWidth();
		}	

		virtual void drawConsecutiveShapes(Shape shape)
		{
			_tempPSText += toString(shape.getWidth() / 2) + " inch 0 rmoveto\n" + 
						shape.draw() + "\n\n" +  toString(shape.getWidth() / 2) + 
						" inch 0 rmoveto\n";
		}	

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
				"% Star \n"
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

class Colored : public Shape
{
	public:
	Colored(Shape shape, int red, int green, int blue)
	{
		_height = shape.getHeight();
		_width = shape.getWidth();

		string colorizePS = "colorize" + toString(red) + toString(green) + toString(blue);
		string definePSColor = "/" + colorizePS + " {" + toString(red) + " " + toString(green) +
								" " + toString(blue) + " setrgbcolor fill} def";
		
		_tempPSText = shape.draw();
		replaceStrokeWithColorize(colorizePS);
		_tempPSText = definePSColor + "\n\n" + _tempPSText;
	}

	void replaceStrokeWithColorize(string colorize)
	{
		std::size_t foundPoint = _tempPSText.find("stroke"); 
		while (foundPoint != string::npos)
		{
			_tempPSText.replace(foundPoint, 6, colorize);
			foundPoint = _tempPSText.find("stroke");
		}
	}
};

#endif /* SHAPES_H */
