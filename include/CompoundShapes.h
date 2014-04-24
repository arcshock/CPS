#ifndef FLAGS_H
#define FLAGS_H

#include "Shapes.h"
#include "Primitives.h"
#include "Transformations.h"
#include "Arrangements.h"

// Note flag term canton - that's the blue rectangle area that holds the stars.
class Flag : public Shape
{
	public:
		Flag(int height) 
		{
			_height = 1.0 * height;
			_width = 1.9 * height * 2;

			Rectangle field(getCantonWidth(), getCantonHeight());
			Colored fieldOfBlue(field, 0, 0, 1);
			Spacer topCorner(0, _height * 6.0 / 13.0);
			Vertical placedField({ topCorner, fieldOfBlue });

			Star starShape(getStarRadius() ); 
			Scaled fudgeStar(starShape, 1.05, .9);
			Colored star(fudgeStar, 1, 1, 1);
			Spacer s(getSpacerWidth() / 2.0 + 1, getSpacerHeight());
			Spacer h(getSpacerWidth() / 4.0 + 1, getSpacerHeight());
			Spacer starFieldHeight(0, _height * 6.0 / 13.0 );
			Spacer bump(4, 5);
			Horizontal even({bump, h, star, s, star, s, star, s, star, s, star, s, star});
			Horizontal odd({bump, h, s, star, s, star, s, star, s, star, s, star});
			Vertical starSpangled({bump, starFieldHeight, even, odd, even, odd, even, odd, even, odd, even});

			Rectangle stripe(getBigStripeWidth(), getStripeHeight());
			Colored red(stripe, 1, 0, 0);
			Colored white(stripe, 1, 1, 1);
			Vertical stripes({red, white, red, white, red, white, 
					red, white, red, white, red, white, red});

			Layered flag({stripes, placedField, starSpangled});
			_tempPSText = flag.draw() ;
		}

	protected:
		double getCantonHeight()
		{
			return _height * 7.0 / 13.0 * .995;
		}

		double getCantonWidth()
		{
			return _width * 2.0 / 5.0; 
		}

		double getBigStripeWidth()
		{
			return _width;
		}

		double getSmallStripeWidthScale()
		{
			return 3.0 / 5.0;
		}

		double getStripeHeight()
		{
			return _height / 13.0;
		}

		double getStarRadius()
		{
			return .5 * getStripeHeight() * 4.0 / 5.0;
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

