#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Shapes.h"
#include "Polygon.h"
#include "CompoundShapes.h"
#include <string>
using std::string;
using std::ifstream;

const int RECTANGLE1 = 13;
const int SQUARE = RECTANGLE1 + 15;
const int HEXAGON = SQUARE + 15;
const int PENTAGON = HEXAGON + 15;
const int CIRCLE = PENTAGON + 12;
const int SCALED = CIRCLE + 15;
const int ROTATED = SCALED + 16;

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

Rectangle rectangle(72, 72);
Square square(216);
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
Triangle triangle(72);

TEST_CASE( "To File" ) {
	REQUIRE( layeredShapes.textToFile("testing/testing.ps") == "I" );
}
TEST_CASE( "Rectangles" ) {
	REQUIRE( rectangle.draw() == getLinesFromMasterShapesFile(RECTANGLE1 - 7, RECTANGLE1) );
}
TEST_CASE( "Squares" ) {
	REQUIRE( square.draw() == getLinesFromMasterShapesFile(SQUARE - 7, SQUARE) );
}
TEST_CASE( "Polygons" ) {
	REQUIRE( hexagon.draw() == getLinesFromMasterShapesFile(HEXAGON - 7, HEXAGON) );
	REQUIRE( pentagon.draw() == getLinesFromMasterShapesFile(PENTAGON - 7, PENTAGON) );
}
TEST_CASE( "Circle" ) {
	REQUIRE( circle.draw() == getLinesFromMasterShapesFile(CIRCLE - 4, CIRCLE) );
}
TEST_CASE( "Scaled" ) {
	REQUIRE( scaledSquare.draw() == getLinesFromMasterShapesFile(SCALED - 8, SCALED) );
}
TEST_CASE( "Rotated" ) {
	REQUIRE( rotatedScaledSquare.draw() == getLinesFromMasterShapesFile(ROTATED - 9, 
											ROTATED) );
}
