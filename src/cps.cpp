#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Rectangle.h"

TEST_CASE( "square"){
	Rectangle a(1,1);
	REQUIRE( a.width() == 1);
	REQUIRE( a.length() == 1);

}
