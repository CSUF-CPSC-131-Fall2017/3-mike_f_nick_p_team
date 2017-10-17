#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>
#include "Webpage.h"
using namespace std;


//BrowserHistory acts as a doubly linked list class.
class BrowserHistory { 
public:
	BrowserHistory();
	~BrowserHistory();
	void visitSite(Webpage newSite);
	string back();
	string forward();
	void readHistory(string filename);
	string getURL();
	size_t getNavSize();
	void printBackSites();
	void printForwardSites();
	void printFullHistory();

private:
	int numVisited;
	Webpage *head;
	Webpage *tail;
	list<Webpage> fullHistory; //Will hold every website visited ordered by time visited. Will never need to remove elements.
	Webpage *cursor; //Used to keep track of location within the browsing history list.
};
