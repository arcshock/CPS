#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
	public:
		Rectangle(double length, double width) : _length(length), _width(width) 
		{}
		double width()
		{
			return 0;
		}

	private:
		double _length;
		double _width;
};

#endif

