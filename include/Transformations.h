#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "Shapes.h"

enum RotationAngle { LEFT = 90, RIGHT = 270, INVERT = 180 };

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
			_tempPSText = "\t" + toString(angle) +
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
			_height = shape.getWidth();
			_width = shape.getHeight();
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

#endif

