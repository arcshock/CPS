#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Shapes.h"
#include "Polygon.h"
#include <string>
using std::string;


string outputShape(string shape)
{
	return "gsave\n" + shape;
}

string printRectangle1 = 
	"\t0.500000 inch 1.000000 inch rmoveto\n"
	"\t-1.000000 inch 0 inch rlineto\n"
	"\t0 inch -2.000000 inch rlineto\n"
	"\t1.000000 inch 0 inch rlineto\n"
	"\t0 inch 2.000000 inch rlineto\n"
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
string printHexagon =
	"\t0.500000 inch -0.866025 inch rmoveto\n"
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
	"\t0.500000 inch -0.769421 inch rmoveto\n"
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
	"\tcurrentpoint 1.000000 inch add moveto\n"
	"\tcurrentpoint 1.000000 inch sub 1.000000 inch -270 360 arc\n"
	"\tstroke\n"
"grestore\n";



string scaledPrefix = "\t2.000000 2.000000 scale\n";
string rotatedPrefix = "\t90 rotate\n";
string listShapes = printSquare + "\n\n" + outputShape(printCircle) + "\n\n" +
						outputShape(printHexagon) + "\n\n" + outputShape(printPentagon) + "\n";

Rectangle rectangle(1 * 72,2 * 72);
Square square(3 * 72);
Polygon hexagon(6, 72);
Polygon pentagon(5, 72);
Polygon gon4(4, 72);
Polygon gon8(8, 72);
Polygon gon3(3,72);
Circle circle(72);
Scaled scaledSquare(square, 2, 2);
Rotated rotatedScaledSquare(scaledSquare, LEFT);
//Vertical layeredShapes0({square, hexagon, pentagon, gon4, gon3, circle});
//Vertical layeredShapes1({pentagon, pentagon, pentagon, pentagon, pentagon});
//Vertical layeredShapes2({hexagon, hexagon, hexagon, hexagon, hexagon});
//Vertical layeredShapes3({gon4, gon4, gon4, gon4, gon4});
Star star(72);
Scaled sStar(star, .2, .2);
Horizontal layeredShapes0({sStar, sStar, sStar}); 
Horizontal layeredShapes1({sStar, sStar, sStar}); 
Horizontal layeredShapes2({sStar, sStar, sStar}); 
Vertical layeredShapes({layeredShapes0, layeredShapes1, layeredShapes2});
Colored colored( layeredShapes, 0, 1, 1);
TEST_CASE( "To File" ) {
	REQUIRE( colored.textToFile() == "I" );
}
TEST_CASE( "Rectangles" ) {
	REQUIRE( rectangle.draw() == outputShape(printRectangle1) );
}
TEST_CASE( "Squares" ) {
	REQUIRE( square.draw() == outputShape(printSquare) );
}
TEST_CASE( "Polygons" ) {
	REQUIRE( hexagon.draw() == outputShape(printHexagon) );
	REQUIRE( pentagon.draw() == outputShape(printPentagon) );
}
TEST_CASE( "Circle" ) {
	REQUIRE( circle.draw() == outputShape(printCircle) );
}
TEST_CASE( "Scaled" ) {
	REQUIRE( scaledSquare.draw() == outputShape(scaledPrefix) + printSquare );
}
TEST_CASE( "Rotated" ) {
	REQUIRE( rotatedScaledSquare.draw() == outputShape(rotatedPrefix) + 
											scaledPrefix + printSquare );
}
//TEST_CASE( "Layered" ) {
//	REQUIRE( layeredShapes.draw() == "\n" "gsave\n" + listShapes );
//}
