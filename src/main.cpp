#include <string.h>
#include <string>
using std::to_string;

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "Shapes.h"
#include "Polygon.h"

#include <ncurses.h>
#include <cstdlib>
using std::exit;

void parseUserChoice(string menuSelection);
void printMenu(WINDOW * menuWindow, int highlight, vector<string> & options);
void interactive(vector<Shape>& shapes, vector<string> menuOptions);
string fileName = "main.ps";

vector<string> currentMenu;
vector<string> mainMenuOptions = { "Draw shape",
				"Specify output file",
				"Save to file",
				"About",
				"Exit"};

vector<string> baseShapes = {"Star",
				"Polygon",
				"Square",
				"Circle",
				"Triangle",
				"Rectangle",
				"Spacer",
				"None"};
	
vector<string> shapeArrangements = {"Layered",
				"Vertical",
				"Horizontal",
				"None"};

vector<string> shapeModOptions = {"Color",
				"Scaled",
				"Rotated",
				"None"};

vector<Shape> shapes;
int startx = 0;
int starty = 0;


vector<Shape> handleArgs(int numberOfArgs, char* args[]);
void initInterface();
void interactive(vector<Shape>& shapes);

int main(int argc, char* args[])
{
	string programName = args[0];

	vector<Shape> shapes = handleArgs(argc, args);

	for ( auto i : shapes) {
		i.textToFile("main.ps");
	}

}

vector<Shape> handleArgs(int numberOfArgs, char* args[])
{

	for (int ii = 1; ii < numberOfArgs; ++ii) {
		if (strcmp(args[ii], "polygon") == 0) {
			
			int numSides = atoi(args[++ii]);
			int sideLength = atoi(args[++ii]);

			Polygon poly(numSides, sideLength);
			shapes.push_back(poly);

		} else if (strcmp(args[ii], "circle") == 0) {

			double radius = atoi(args[++ii]);

			Circle c(radius);
			shapes.push_back(c);
			
		} else if (strcmp(args[ii], "square") == 0) {

			double side = atoi(args[++ii]);

			Square s(side);
			shapes.push_back(s);

		} else if (strcmp(args[ii], "star") == 0) {
			
			int sideLength = atoi(args[++ii]);

			Star s(sideLength);
			shapes.push_back(s);

		} else if (strcmp(args[ii], "rectangle") == 0) {
			
			double width = atoi(args[++ii]);
			double height = atoi(args[++ii]);

			Rectangle r(width, height);
			shapes.push_back(r);

		} else if (strcmp(args[ii], "spacer") == 0) {

			double width = atoi(args[++ii]);
			double height = atoi(args[++ii]);

			Spacer c(width, height);
			shapes.push_back(c);

		} else if (strcmp(args[ii], "-I") == 0) {

			initInterface();
			currentMenu = mainMenuOptions;
			interactive(shapes, currentMenu);

		} else {

			cout << "BAD ARG" << endl;

		}
	}

	return shapes;
}


void initInterface()
{
	initscr();
	noecho();
	cbreak();
	raw();
	keypad(stdscr, TRUE);
}

void interactive(vector<Shape>& shapes, vector<string> menuOptions)
{
	int userInputCharValue = 0;
	const int WIDTH = 30;
	const int HEIGHT = 10;
	int choice = -1;
	int highlight = 1;
	WINDOW *menuWindow;

	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	



	do {
		erase();
		int numOfChoices = currentMenu.size();

		menuWindow = newwin(numOfChoices + 4, WIDTH, starty, startx);
		keypad(menuWindow, TRUE);


		mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
		refresh();

		printMenu(menuWindow, highlight, currentMenu);
		userInputCharValue = wgetch(menuWindow);
		switch(userInputCharValue) {
		case KEY_UP:
			if(highlight == 1)
				highlight = numOfChoices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if(highlight == numOfChoices)
				highlight = 1;
			else 
				++highlight;
			break;
		case 10:			//pressed enter key
			choice = highlight - 1; //want to be albe to align with menu
			break;
		default:
			refresh();
			choice = -1;
			break;
		}

		printMenu(menuWindow, highlight, mainMenuOptions);

		if (choice > -1) {	/* User made choice come out of the infinite loop */
			erase();
			parseUserChoice(currentMenu[choice]);
			refresh();
			choice = -1;
			delwin(menuWindow);
			highlight = 1;
		}

	} while(true);
}

string getFileName()
{
	return "";
}

void parseUserChoice(string menuSelection)
{

		if (menuSelection == "Specify output file") {
			echo();
			printw("Enter file name to save to.\n");
			refresh();

			char tempName[80];
			scanw("%89s", tempName);

			fileName = tempName;
			fileName += ".ps";
			erase();
		}

		if (menuSelection == "Save to file") {

			printw("Saved file");
			refresh();

			for ( auto i : shapes) {
				i.textToFile(fileName);
			}
		}

		if (menuSelection == "Draw shape") {
			printw("Drawing Shape");
			refresh();
			currentMenu = shapeArrangements;
			refresh();
		}

		if (menuSelection == "About") {
			printw("hey");
			refresh();
		}

		if (menuSelection == "None") {
			if(currentMenu == baseShapes) {
				currentMenu = mainMenuOptions;
			} else if (currentMenu == shapeArrangements) {
				currentMenu = shapeModOptions;
			} else if (currentMenu == shapeModOptions) {
				currentMenu = baseShapes;
			}
		}

		if (menuSelection == "Exit") {
			endwin();
			exit(1);
		} 		
		
		if (menuSelection == "Polygon") {
			int numSides = 0;
			int sideLength = 0;

			printw("Enter number of sides:\n");
			refresh();
			scanw("%d", &numSides);

			printw("Enter the side length in pixels:\n");
			refresh();
			scanw("%d", &sideLength);

			Polygon poly(numSides, sideLength);
			shapes.push_back(poly);

		} else if (menuSelection == "Circle") {
			double radius = 0;

			printw("Enter radius of circle in pixels\n");
			refresh();

			scanw("%lf", &radius);

			Circle c(radius);
			shapes.push_back(c);
			
		} else if (menuSelection == "Square") {
			double side = 0;

			printw("Ender side length in pixels\n");
			refresh();

			scanw("%lf", &side);

			Square s(side);
			shapes.push_back(s);

		} else if (menuSelection == "Star") {
			int sideLength = 0; 
			
			printw("Ender height in pixels\n");
			refresh();

			scanw("%lf", &sideLength);


			Star s(sideLength);
			shapes.push_back(s);

		} else if (menuSelection == "Rectangle") {
			double width = 0;
			double height = 0;

			printw("Ender width in pixels\n");
			refresh();

			scanw("%lf", &width);

			printw("Ender height in pixels\n");
			refresh();

			scanw("%lf", &height);

			Rectangle r(width, height);
			shapes.push_back(r);

		} else if (menuSelection == "Spacer") {
			double width = 0;
			double height = 0;

			printw("Ender width in pixels\n");
			refresh();

			scanw("%lf", &width);

			printw("Ender height in pixels\n");
			refresh();

			scanw("%lf", &height);


			Spacer c(width, height);
			shapes.push_back(c);
		}

		if (menuSelection == "Layered") {
			//TODO	
		}
		
		if (menuSelection == "Color") {
			int red = 0;
			int green = 0;
			int blue = 0;

			printw("Enter a value for red, green, and blue\n");
			refresh();

			scanw("%d %d %d", &red, &green, &blue);

			Colored coloredObject(shapes.back(), red, green, blue);
			shapes.push_back(coloredObject);
		}
		if (menuSelection == "Scaled") {
			double xScaleFactor = 1;
			double yScaleFactor = 1;

			printw("Enter x and y scaling factors\n");
			refresh();

			scanw("%lf %lf", &xScaleFactor, &yScaleFactor);

			Scaled scaledObject(shapes.back(), xScaleFactor, yScaleFactor);
			shapes.push_back(scaledObject);
		}
		if (menuSelection == "Rotated") {
			RotationAngle rotationAngle;

			printw("Enter either, 90, 180, or 270 for rotation angle\n");
			refresh();

			scanw("%d", &rotationAngle);

			Rotated rotatedObject(shapes.back(), rotationAngle);
			shapes.push_back(rotatedObject);
		}

}

void printMenu(WINDOW * menuWindow, int highlight, vector<string> & options)
{
	int xCoord = 2;
	int yCoord = 2;

	box(menuWindow, 0, 0);

	for (int ii = 0; ii < options.size(); ++ii) {
		if (highlight == ii + 1) {
			wattron(menuWindow, A_REVERSE); 
			mvwprintw(menuWindow, yCoord, xCoord, "%s", options[ii].c_str());
			wattroff(menuWindow, A_REVERSE);
		} else {
			mvwprintw(menuWindow, yCoord, xCoord, "%s", options[ii].c_str());
		}
		++yCoord;
		wrefresh(menuWindow);
	}

}
