#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Shapes.h"
#include "Polygon.h"
#include "Arrangements.h"
#include "Transformations.h"
#include "CompoundShapes.h"
#include "Primitives.h"
#include "LookupTable.h"
#include <fstream>
#include <map>
#include <vector>

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
Horizontal horizontal4({redScaledStar, scaledStar, redScaledStar});
Vertical vertical1({horizontal2, horizontal2, horizontal2, spacer, horizontal3});
Vertical vertical2({horizontal4, horizontal3, horizontal4});

std::vector<string> testShapeNames  = 
	{ "printRectangle1", "printSquare", "printHexagon", "printPentagon", "printCircle", 
	"printScaledSquare", "Rotated", "RedScaled Star", "Octagon", "Gon-19", "Triangle"};

std::map<string,LineRange> lookup = 
	generateLookupTable(testShapeNames);

TEST_CASE( "To File" ) {
	REQUIRE( vertical2.textToFile("testing/testing.ps") == "I" );
}
TEST_CASE( "Rectangles" ) {
	LineRange rect1 = lookup[testShapeNames[0]];
	REQUIRE( rectangle.draw() == getLinesFromMasterShapesFile(rect1) );
}
TEST_CASE( "Regular Polygons" ) {
	LineRange hex = lookup[testShapeNames[2]];
	REQUIRE( hexagon.draw() == getLinesFromMasterShapesFile(hex) );
	LineRange penta = lookup[testShapeNames[3]];
	REQUIRE( pentagon.draw() == getLinesFromMasterShapesFile(penta) );
	LineRange octa = lookup[testShapeNames[8]];
	REQUIRE( octogon.draw() == getLinesFromMasterShapesFile(octa) );
	LineRange nineteen = lookup[testShapeNames[9]];
	REQUIRE( gon19.draw() == getLinesFromMasterShapesFile(nineteen) );
	LineRange tri = lookup[testShapeNames[10]];
	REQUIRE( triangle.draw() == getLinesFromMasterShapesFile(tri) );
	LineRange sq = lookup[testShapeNames[1]];
	REQUIRE( square.draw() == getLinesFromMasterShapesFile(sq) );
}
TEST_CASE( "Circle" ) {
	LineRange circ = lookup[testShapeNames[4]];
	REQUIRE( circle.draw() == getLinesFromMasterShapesFile(circ) );
}
TEST_CASE( "Scaled" ) {
	LineRange scalesq = lookup[testShapeNames[5]];
	REQUIRE( scaledSquare.draw() == getLinesFromMasterShapesFile(scalesq) );
}
TEST_CASE( "Rotated" ) {
	LineRange rot = lookup[testShapeNames[6]];
	REQUIRE( rotatedTriangle.draw() == getLinesFromMasterShapesFile(rot));
}
TEST_CASE( "Colored" ) {
	LineRange color = lookup[testShapeNames[7]];
	REQUIRE( redScaledStar.draw() == getLinesFromMasterShapesFile(color) );
}
