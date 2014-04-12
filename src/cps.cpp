#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Rectangle.h"
#include <string>
using std::string;

string printSquare = "0.500000 inch 0.500000 inch rmoveto\n"
					 "-1.000000 inch 0 inch rlineto\n"
					 "0 inch -1.000000 inch rlineto\n"
					 "1.000000 inch 0 inch rlineto\n"
					 "0 inch 1.000000 inch rlineto\n"
					 "stroke\n";
string printTestangle = "2.000000 inch 1.500000 inch rmoveto\n"
					 "-4.000000 inch 0 inch rlineto\n"
					 "0 inch -3.000000 inch rlineto\n"
					 "4.000000 inch 0 inch rlineto\n"
					 "0 inch 3.000000 inch rlineto\n"
					 "stroke\n";

Rectangle square(1,1);
Rectangle testangle(4,3);

TEST_CASE( "square"){
	REQUIRE( square.width() == 1);
	REQUIRE( square.height() == 1);
	REQUIRE( square.print() == printSquare);

	REQUIRE( testangle.width() == 4);
	REQUIRE( testangle.height() == 3);
	REQUIRE( testangle.print() == printTestangle);
}
