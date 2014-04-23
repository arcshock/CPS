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
		readme.txt - THIS FILE
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
			testStrategy.txt - text explaining our testing strategy 

Use:
	The program is built by invoking "make build". Then it is used by invoking "make run". A gui will open that gives the user options and the program is used by selecting options and following the directions of the prompts. 

Intersting Aspects:
	Everything is a string. The Shape objects exist in as much as it creates the PostScript String. We allow colors by our colorize function but that will only color non-colored objects. Also instead of points we use inches and so the generated Post Script can be parsed as inches rather than in points. We tried to make the output Post Script as clean as possible.

	Several of our classes are empty as they inherit from other classes. Also we have implemented the decarator design pattern with respect to the classes in the Arragement.h and Transformation.h. 

Critique:
	The language is expressive enough to create interesting drawings, assuming you like the outline of arranged regular polygons and rectangles. The shape abstractions are not well designed as there is a cleaner way to pass parameters. They make rotated or scaled regular polygons or rectangles easy to create, but anything beyond that (even arragements of those shapes are difficult). 

	If we were to design this language from scratch we would have passed bounding boxes as parameters, made clear what rotationAngle needed to be (and why), and add a way besides arragements and spacer to move around PostScript file.

