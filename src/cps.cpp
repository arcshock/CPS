#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Shapes.h"
#include <string>
using std::string;

string printRectangle1 = "0.500000 inch 1.000000 inch rmoveto\n"
					 "-1.000000 inch 0 inch rlineto\n"
					 "0 inch -2.000000 inch rlineto\n"
					 "1.000000 inch 0 inch rlineto\n"
					 "0 inch 2.000000 inch rlineto\n"
					 "stroke\n";
string printRectangle2 = "2.000000 inch 1.500000 inch rmoveto\n"
					 "-4.000000 inch 0 inch rlineto\n"
					 "0 inch -3.000000 inch rlineto\n"
					 "4.000000 inch 0 inch rlineto\n"
					 "0 inch 3.000000 inch rlineto\n"
					 "stroke\n";
string printSquare = "1.500000 inch 1.500000 inch rmoveto\n"
					 "-3.000000 inch 0 inch rlineto\n"
					 "0 inch -3.000000 inch rlineto\n"
					 "3.000000 inch 0 inch rlineto\n"
					 "0 inch 3.000000 inch rlineto\n"
					 "stroke\n";
string printSpacer = "1.000000 inch 0.500000 inch rmoveto\n"
					 "-2.000000 inch 0 inch rlineto\n"
					 "0 inch -1.000000 inch rlineto\n"
					 "2.000000 inch 0 inch rlineto\n"
					 "0 inch 1.000000 inch rlineto\n";



Rectangle rectangle1(1,2);
Rectangle rectangle2(4,3);
Square square(3);
Spacer spacer(2,1);

TEST_CASE( "shapes"){
	REQUIRE( rectangle1.print() == printRectangle1);
	REQUIRE( rectangle2.print() == printRectangle2);
	REQUIRE( square.print() == printSquare);
	REQUIRE( spacer.print() == printSpacer);
}
