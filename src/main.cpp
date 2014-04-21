#include <string.h>
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

void printMenu(WINDOW * menuWindow, int highlight);
vector<char *> choices = { "Draw a shape",
				   "Specify output file",
				   "randomness",
				   "About",
				   "Exit" };

int startx = 0;
int starty = 0;



vector<Shape> handleArgs(int numberOfArgs, char* args[]);
void interactive(vector<Shape>& shapes);

int main(int argc, char* args[])
{
	string programName = args[0];

	vector<Shape> shapes = handleArgs(argc, args);

	for ( auto i : shapes) {
		i.textToFile();
	}

}

vector<Shape> handleArgs(int numberOfArgs, char* args[])
{
	vector<Shape> shapes;

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

			interactive(shapes);

		} else {

			cout << "BAD ARG" << endl;

		}
	}

	return shapes;
}

void interactive(vector<Shape>& shapes)
{
	int userInputCharacter = 0;
	int highlight = 1;
	const int WIDTH = 30;
	const int HEIGHT = 10;
	int choice = 0;
	int c = 0;
	WINDOW *menuWindow;


	int numOfChoices = choices.size();

	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	menuWindow = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menuWindow, TRUE);

	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
	printMenu(menuWindow, highlight);

	while(1) {
		c = wgetch(menuWindow);
		switch(c) {
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
		case 10:
			choice = highlight;
			break;
		default:
			mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
			refresh();
			break;
		}

		printMenu(menuWindow, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	
	printw("Welcome to the C++ to PostScript Library\n");
	refresh();
	
	userInputCharacter = getch();
	
	if (userInputCharacter == '1') {
		attron(A_BOLD);
		printw("Drawing polygon");
		refresh();
	}

	getch();
	endwin();
}

void printMenu(WINDOW * menuWindow, int highlight)
{
	int x, y, index;

	x = 2;
	y = 2;

	box(menuWindow, 0, 0);

	for (int ii = 0; ii < choices.size(); ++ii) {
		if (highlight == ii + 1) {
			wattron(menuWindow, A_REVERSE); 
			mvwprintw(menuWindow, y, x, "%s", choices[ii]);
			wattroff(menuWindow, A_REVERSE);
		} else {
			mvwprintw(menuWindow, y, x, "%s", choices[ii]);
		}
		++y;
		wrefresh(menuWindow);
	}

}
