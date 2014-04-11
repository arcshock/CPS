#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
	public:
		Rectangle(double length, double width) : _length(length), _width(width) 
		{}
		double width()
		{
			return _width;
		}
		double length()
		{
			return _length;
		}

	private:
		double _length;
		double _width;
};

#endif

#ifndef SQUARE_H
#define SQUARE_H

class Square : public Rectangle
{
	public:
		Square(double side) : Rectangle(side, side) {}
};

#endif

