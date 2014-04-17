#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Shapes.h"
#include <string>
using std::string;

string printRectangle1 = 
"gsave\n"					
	"\t0.500000 inch 1.000000 inch rmoveto\n"
 	"\t-1.000000 inch 0 inch rlineto\n"
	 "\t0 inch -2.000000 inch rlineto\n"
	 "\t1.000000 inch 0 inch rlineto\n"
	 "\t0 inch 2.000000 inch rlineto\n"
	 "\tstroke\n"
"grestore\n";
string printRectangle2 =
"gsave\n"
	 "\t2.000000 inch 1.500000 inch rmoveto\n"
	 "\t-4.000000 inch 0 inch rlineto\n"
	 "\t0 inch -3.000000 inch rlineto\n"
	 "\t4.000000 inch 0 inch rlineto\n"
	 "\t0 inch 3.000000 inch rlineto\n"
	 "\tstroke\n"
"grestore\n";
string printSquare = 
"gsave\n"
	"\t1.500000 inch 1.500000 inch rmoveto\n"
	"\t-3.000000 inch 0 inch rlineto\n"
	"\t0 inch -3.000000 inch rlineto\n"
	"\t3.000000 inch 0 inch rlineto\n"
	"\t0 inch 3.000000 inch rlineto\n"
	"\tstroke\n"
"grestore\n";
string printSpacer = 
"gsave\n"
	"\t1.000000 inch 0.500000 inch rmoveto\n"
	"\t-2.000000 inch 0 inch rlineto\n"
	"\t0 inch -1.000000 inch rlineto\n"
	"\t2.000000 inch 0 inch rlineto\n"
	"\t0 inch 1.000000 inch rlineto\n"
"grestore\n";
string printHexagon =
"gsave\n"
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
"gsave\n"
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
"gsave\n"
	"\t0 0 1.000000 inch 0 360 arc\n"
	"\tclosepath\n"
	"\tstroke\n"
"grestore\n";

Rectangle rectangle1(1 * 72,2 * 72);
Rectangle rectangle2(4 * 72 ,3 * 72);
Square square(3 * 72);
Spacer spacer(2 * 72,1 * 72);
Polygon hexagon(6, 72);
Polygon pentagon(5, 72);
Polygon elevengon(11, 72);
Circle circle(72);

TEST_CASE( "Rectangles"){
	REQUIRE( rectangle1.draw() == printRectangle1);
	REQUIRE( rectangle2.draw() == printRectangle2);
}
TEST_CASE( "Squares") {
	REQUIRE( square.draw() == printSquare);
	REQUIRE( spacer.draw() == printSpacer);
}
TEST_CASE( "Polygons") {
	REQUIRE( hexagon.draw() == printHexagon);
	REQUIRE( pentagon.draw() == printPentagon);
	REQUIRE( elevengon.draw() == printPentagon); 
}
TEST_CASE( "Circle") {
	REQUIRE( circle.draw() == printCircle);
}
