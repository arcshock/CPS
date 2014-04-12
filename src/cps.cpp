#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Rectangle.h"
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


Rectangle rectangle1(1,2);
Rectangle rectangle2(4,3);
Square square(3);

TEST_CASE( "rectangle1"){
	REQUIRE( rectangle1.width() == 1);
	REQUIRE( rectangle1.height() == 2);
	REQUIRE( rectangle1.print() == printRectangle1);

	REQUIRE( rectangle2.width() == 4);
	REQUIRE( rectangle2.height() == 3);
	REQUIRE( rectangle2.print() == printRectangle2);

	REQUIRE( square.width() == 3);
	REQUIRE( square.height() == 3);
	REQUIRE( square.print() == printSquare);
}
