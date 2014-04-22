#ifndef FLAGS_H
#define FLAGS_H

#include "Shapes.h"
#include "Primitives.h"
#include "Transformations.h"
#include "Arrangements.h"

class Flag : public Shape
{
	public:
		Flag() 
		{
			_height = 1.0;
			_width = 1.9;
			Star baseStar(3.0);
		}

	protected:
		double getCantonHeight()
		{
			return _height * 7.0 / 13.0;
		}

		double getCantonWidth()
		{
			return _width * 2.0 / 5.0; 
		}

		double getStripeWidth()
		{
			return _height / 13.0;
		}

		double getStarDiameter()
		{
			return getStripeWidth() * 4.0 / 5.0;
		}
		
		double getSpacerHeight()
		{
			return getCantonHeight() * 1.0 / 10.0;
		}

		double getSpacerWidth()
		{
			return getCantonWidth() * 1.0 / 12.0;
		}


};

#endif

