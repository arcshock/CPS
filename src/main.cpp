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
			
		} else {
			cout << "BAD ARG" << endl;
		}
	}

	for ( auto i : shapes) {
		i.textToFile();
	}
}
