#include <string.h>
#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "Shapes.h"
#include "Polygon.h"


vector<Shape> handleArgs(int numberOfArgs, char* args[]);
void interactive(vector<Shape>& shapes);

int main(int argc, char* args[])
{
	string programName = args[0];

	vector<Shape> shapes = handleArgs(argc, args);

	for ( auto i : shapes) {
		i.textToFile("main.ps");
	}

}

vector<Shape> handleArgs(int numberOfArgs, char* args[])
{
	vector<Shape> shapes;

	for (int ii = 1; ii < numberOfArgs; ++ii) {
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

		} else if (strcmp(args[ii], "-I") == 0) {

			interactive(shapes);

		} else {

			cout << "BAD ARG" << endl;

		}
	}

	return shapes;
}

void interactive(vector<Shape>& shapes)
{
	cout << "Welcome to the C++ to PostScript Library" << endl;
}
