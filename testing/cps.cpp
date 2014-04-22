#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Shapes.h"
#include "Polygon.h"
#include "Arrangements.h"
#include "Transformations.h"
#include "Primitives.h"
using std::ifstream;

const int RECTANGLE1 = 14;
const int SQUARE = RECTANGLE1 + 16;
const int HEXAGON = SQUARE + 16;
const int PENTAGON = HEXAGON + 16;
const int CIRCLE = PENTAGON + 13;
const int SCALED = CIRCLE + 16;
const int ROTATED = SCALED + 16;
const int RED = ROTATED + 27;
const int OCTOGON = RED + 15;
const int GON19 = OCTOGON + 15;
const int TRIANGLE = GON19 + 15;

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

Spacer spacer(4, 31);
Rectangle rectangle(49, 92);
Square square(69);
Polygon hexagon(6, 72);
Polygon pentagon(5, 72);
Polygon octogon(8, 50);
Polygon gon19(19,30);
Triangle triangle(72);
Circle circle(72);
Star star(72);
Scaled scaledStar(star, 0.4, 0.4);
Scaled scaledSquare(square, 2, 2);
Rotated rotatedTriangle(triangle, LEFT);
Colored blueSquare(square, 0, 0, 1);
Colored redScaledStar(scaledStar, 1, 0, 0);
Layered layered({star, circle});
Horizontal horizontal0({blueSquare, spacer, hexagon, blueSquare, redScaledStar}); 
Horizontal horizontal1({circle, layered, pentagon}); 
Horizontal horizontal2({pentagon, pentagon, pentagon}); 
Horizontal horizontal3({blueSquare,blueSquare,blueSquare,rotatedTriangle,blueSquare,blueSquare,blueSquare,blueSquare,blueSquare,blueSquare,blueSquare,blueSquare,blueSquare,blueSquare});
Vertical vertical({horizontal2, horizontal2, horizontal2, spacer, horizontal3});

TEST_CASE( "To File" ) {
	REQUIRE( vertical.textToFile("testing/testing.ps") == "I" );
}
TEST_CASE( "Rectangles" ) {
	REQUIRE( rectangle.draw() == getLinesFromMasterShapesFile(RECTANGLE1 - 8, RECTANGLE1) );
}
TEST_CASE( "Regular Polygons" ) {
	REQUIRE( hexagon.draw() == getLinesFromMasterShapesFile(HEXAGON - 8, HEXAGON) );
	REQUIRE( pentagon.draw() == getLinesFromMasterShapesFile(PENTAGON - 8, PENTAGON) );
	REQUIRE( octogon.draw() == getLinesFromMasterShapesFile(OCTOGON -8, OCTOGON) );
	REQUIRE( gon19.draw() == getLinesFromMasterShapesFile(GON19 - 8, GON19) );
	REQUIRE( triangle.draw() == getLinesFromMasterShapesFile(TRIANGLE - 8, TRIANGLE) );
	REQUIRE( square.draw() == getLinesFromMasterShapesFile(SQUARE - 8, SQUARE) );
}
TEST_CASE( "Circle" ) {
	REQUIRE( circle.draw() == getLinesFromMasterShapesFile(CIRCLE - 5, CIRCLE) );
}
TEST_CASE( "Scaled" ) {
	REQUIRE( scaledSquare.draw() == getLinesFromMasterShapesFile(SCALED - 9, SCALED) );
}
TEST_CASE( "Rotated" ) {
	REQUIRE( rotatedTriangle.draw() == getLinesFromMasterShapesFile(ROTATED - 9, 
											ROTATED) );
}
TEST_CASE( "Colored" ) {
	REQUIRE( redScaledStar.draw() == getLinesFromMasterShapesFile(RED - 20, RED) );
}
