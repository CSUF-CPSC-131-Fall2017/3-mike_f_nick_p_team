#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>
#include "Webpage.h"
using namespace std;

class Node{
	public:
		Node(Webpage elem = Webpage(), Node* link1 = NULL, Node* link2 = NULL):site(elem), next(link1), prev(link2){};
	private:
		Webpage site;
		Node* next;
		Node* prev;
		friend class BrowserHistory;
	};


//In this case, BrowserHistory is the DLinkedList class
class BrowserHistory {
public:
	BrowserHistory();
	~BrowserHistory();

	void visitSite(Webpage newSite);
	string back();
	string forward();

	void readHistory(string fileName);

	string getURL();
	size_t getNavSize();

	void printBackSites();
	void printForwardSites();
	void printFullHistory();
	

private:
	// Add private member variables for your class along with any
	// other variables required to implement the public member functions
	// TO BE COMPLETED
	int numVisited;
	
	//Webpage *head;
	//Webpage *tail;
	
	//this list stores the full UNALTERED browser history based solely on time accessed
	list<Webpage> fullHistory;
	// full history will not delete elements, only add and does not need a cursor to change
	

	//cursor will be used with the navigation functions of back and forward to keep track of the current location
	//LOOK AT CURSOR WITH REGARDS TO NECESSARY FUNCTIONALITY NEEDED
	//Webpage *cursor;
	
	Node *cursor;
	Node* head;
	Node* tail;
};
