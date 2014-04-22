#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Shapes.h"
#include "Polygon.h"
#include <string>
using std::string;
using std::ifstream;

string getLinesFromMasterShapesFile(int startLine, int endLine)
{
    ifstream infile("testing/masterShapes.ps");
    string line;
    string compPSText;
    int count = 0;

    while(std::getline(infile, line))
    {
        ++count;
        if (count > endLine)
            break;
        if (count < startLine)
            continue;

        compPSText += line + "\n";
    }

    return compPSText;
}

string outputShape(string shape)
{
	return "gsave\n" + shape;
}

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
Star star(72);
Scaled sStar(star, .2, .2);
Colored bcolored(square, 0, 0, 1);
Colored rcolored(gon8, 1, 0, 0);
Horizontal layeredShapes0({bcolored, hexagon, rcolored}); 
Horizontal layeredShapes1({circle, bcolored, pentagon}); 
Horizontal layeredShapes2({rcolored, rotatedScaledSquare, circle}); 
Vertical layeredShapes({layeredShapes0, layeredShapes1, layeredShapes2, star});

TEST_CASE( "To File" ) {
	REQUIRE( layeredShapes.textToFile("testing/testing.ps") == "I" );
}
TEST_CASE( "Rectangles" ) {
	REQUIRE( rectangle.draw() == getLinesFromMasterShapesFile(6, 13) );
}
TEST_CASE( "Squares" ) {
	REQUIRE( square.draw() == getLinesFromMasterShapesFile(21, 28) );
}
TEST_CASE( "Polygons" ) {
	REQUIRE( hexagon.draw() == getLinesFromMasterShapesFile(36, 51) );
	REQUIRE( pentagon.draw() == getLinesFromMasterShapesFile(59, 72) );
}
TEST_CASE( "Circle" ) {
	REQUIRE( circle.draw() == getLinesFromMasterShapesFile(80, 84) );
}
TEST_CASE( "Scaled" ) {
	REQUIRE( scaledSquare.draw() == getLinesFromMasterShapesFile(90, 98) );
}
TEST_CASE( "Rotated" ) {
	REQUIRE( rotatedScaledSquare.draw() == getLinesFromMasterShapesFile(105, 114) );
}
