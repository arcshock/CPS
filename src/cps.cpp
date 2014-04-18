#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Shapes.h"
#include "Polygon.h"
#include <string>
using std::string;

string printRectangle1 = 
	"\t0.500000 inch 1.000000 inch rmoveto\n"
	"\t-1.000000 inch 0 inch rlineto\n"
	"\t0 inch -2.000000 inch rlineto\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\t0 inch 2.000000 inch rlineto\n"
	"\tstroke\n"
"grestore\n";
string printRectangle2 =
	"\t2.000000 inch 1.500000 inch rmoveto\n"
	"\t-4.000000 inch 0 inch rlineto\n"
	"\t0 inch -3.000000 inch rlineto\n"
	"\t4.000000 inch 0 inch rlineto\n"
	"\t0 inch 3.000000 inch rlineto\n"
	"\tstroke\n"
"grestore\n";
string printSquare = 
	"\t1.500000 inch 1.500000 inch rmoveto\n"
	"\t-3.000000 inch 0 inch rlineto\n"
	"\t0 inch -3.000000 inch rlineto\n"
	"\t3.000000 inch 0 inch rlineto\n"
	"\t0 inch 3.000000 inch rlineto\n"
	"\tstroke\n"
"grestore\n";
string printSpacer = 
	"\t1.000000 inch 0.500000 inch rmoveto\n"
	"\t-2.000000 inch 0 inch rlineto\n"
	"\t0 inch -1.000000 inch rlineto\n"
	"\t2.000000 inch 0 inch rlineto\n"
	"\t0 inch 1.000000 inch rlineto\n"
"grestore\n";
string printHexagon =
	"\t0.500000 inch 0.866025 inch rmoveto\n"
	"\t60.000000 rotate\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\t60.000000 rotate\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\t60.000000 rotate\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\t60.000000 rotate\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\t60.000000 rotate\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\t60.000000 rotate\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\tstroke\n"
"grestore\n";
string printPentagon = 
	"\t0.000000 inch 0.769421 inch rmoveto\n"
	"\t72.000000 rotate\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\t72.000000 rotate\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\t72.000000 rotate\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\t72.000000 rotate\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\t72.000000 rotate\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\tstroke\n"
"grestore\n";
string printCircle =
	"\t0 0 1.000000 inch 0 360 arc\n"
	"\tclosepath\n"
	"\tstroke\n"
"grestore\n";

string scaledPrefix = "\t2.000000 2.000000 scale\n";

string rotatedPrefix = "\t60.000000 rotate\n";


Rectangle rectangle1(1 * 72,2 * 72);
Rectangle rectangle2(4 * 72 ,3 * 72);
Square square(3 * 72);
Spacer spacer(2 * 72,1 * 72);
Polygon hexagon(6, 72);
Polygon pentagon(5, 72);
Polygon elevengon(11, 72);
Circle circle(72);
Scaled scaledSquare(square, 2, 2);
Rotated rotatedScaledSquare(scaledSquare, 60.0);

TEST_CASE( "Rectangles" ) {
	REQUIRE( rectangle1.draw() == "gsave\n" + printRectangle1 );
	REQUIRE( rectangle2.draw() == "gsave\n" + printRectangle2 );
}
TEST_CASE( "Squares" ) {
	REQUIRE( square.draw() == "gsave\n" + printSquare );
	REQUIRE( spacer.draw() == "gsave\n" + printSpacer );
}
TEST_CASE( "Polygons" ) {
	REQUIRE( hexagon.draw() == "gsave\n" + printHexagon );
	REQUIRE( pentagon.draw() == "gsave\n" + printPentagon );
}
TEST_CASE( "Circle" ) {
	REQUIRE( circle.draw() =="gsave\n" +  printCircle );
}
TEST_CASE( "Scaled" ) {
	REQUIRE( scaledSquare.draw() == "gsave\n" + scaledPrefix + printSquare );
}
TEST_CASE( "Rotated" ) {
	REQUIRE( rotatedScaledSquare.draw() == "gsave\n" + rotatedPrefix + scaledPrefix + printSquare );
}
