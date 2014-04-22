#ifndef COMPOUND_SHAPES_H
#define COMPOUND_SHAPES_H

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
			std::cout << getHeight() << "\n";
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

#endif

