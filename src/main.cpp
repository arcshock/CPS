#include <string.h>
#include <vector>
using std::vector;


#include <iostream>
using std::cout;
using std::endl;

#include "Shapes.h"
#include "Polygon.h"

int main(int argc, char* args[])
{
	string programName = args[0];

	cout << args[0] << endl;
	cout << args[1] << endl;
	cout << args[2] << endl;
	
	vector<Shape> shapes;

	for (int ii = 1; ii < argc; ++ii) {
		if (strcmp(args[ii], "polygon") == 0) {
			
			int numSides = atoi(args[++ii]);
			int sideLength = atoi(args[++ii]);

			Polygon poly(numSides, sideLength);
			shapes.push_back(poly);

		} else if (strcmp(args[ii], "circle") == 0) {

			double radius = atoi(args[++ii]);

			Circle c(radius);
			shapes.push_back(c);
			
		} else if (strcmp(args[ii], "square") == 0) {

			double side = atoi(args[++ii]);

			Square s(side);
			shapes.push_back(s);

		} else if (strcmp(args[ii], "star") == 0) {
			
			int sideLength = atoi(args[++ii]);

			Star s(sideLength);
			shapes.push_back(s);

		} else if (strcmp(args[ii], "rectangle") == 0) {
			
			double width = atoi(args[++ii]);
			double height = atoi(args[++ii]);

			Rectangle r(width, height);
			shapes.push_back(r);

		} else if (strcmp(args[ii], "spacer") == 0) {

			double width = atoi(args[++ii]);
			double height = atoi(args[++ii]);

			Spacer c(width, height);
			shapes.push_back(c);

		} else {

			cout << "BAD ARG" << endl;

		}
	}

	for ( auto i : shapes) {
		i.textToFile();
	}

}
