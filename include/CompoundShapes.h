#ifndef FLAGS_H
#define FLAGS_H

#include "Shapes.h"
#include "Transformations.h"
#include "Arrangements.h"

class Flag : public Shape
{
	public:
		Flag() : _height(1), _width(1.9)
		{
			Star baseStar()
		}
	protected:
		double _cantonHeight; 
		double _cantonWidth;


};

#endif

