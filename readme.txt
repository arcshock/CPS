		C++ To PostScript
Authors:
		Paul Gentemann
		Bucky Frost
		Erik Talvi

Structure:
	CPS:
		LICENSE - Rude License
		TODO - Overview of Game Plan
		Makefile - Make file
		README.md - made with git
		build:
			debug:
				cps-build.out - main build
				cps-test.out - test build
			release:
		doc:
			grammar.txt - Explanation of Grammar
		include:
			Arrangements.h - Describes Shape Decorators that deal with arrangment of multiple shape objects. Cannot exist without concrete shape objects.
			CompoundShapes.h - Describes Shapes that are not as simple as primitives but can exist on their own and be decorated by any decorator
			Polygon.h - Describes general regular polygon shapes and specific instances of Triangle and Square. Can exist on their own. Can be decorated by any decorator.
			Primitives.h - Describes primitive Shape objects that can exist on their own or be decorated by any decorator.
			Shapes.h - Describes the Base Shapes class that all other classes in this spec derive from. 
			Transformations.h - Describes all shape decorators that deal with changing a single shape object. Cannot exist without concrete shape objects.
			cps.hpp - "needs to delete"
		src:
			bubbles.ps - testing poscript file
			main.cpp - Main file
		testing:
			catch.hpp - provides Catch Test support
			correctPS.ps - comparison file for textToPSFile function
			cps.cpp - Testing File
			filecomp.sh - shell script that allows testing of textToPSFile function
			masterShapes.ps - contains correct output postscript
			testing.ps - textToPSFile function output file 

