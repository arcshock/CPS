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
