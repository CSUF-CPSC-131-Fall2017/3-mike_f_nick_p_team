#include "BrowserHistory.h"

//default constructor
BrowserHistory::BrowserHistory() {
	// TO BE COMPLETED
	head = NULL;
	tail = NULL;
	cursor = head;
}

//destructor must delete every node in the browser history
BrowserHistory::~BrowserHistory() {
	for (Webpage *delCursor = head; delCursor->next == NULL; delCursor = delCursor->next) {
		//remove the elements 
		delete delCursor;
	}
}

//add node to linked list
void BrowserHistory::visitSite(Webpage newSite) {
	// TO BE COMPLETED
	// adds new node into the list at the end

	//create new node with pointer p
	Webpage *p;
	p = new Webpage;
	//find old final node with pointer q
	Webpage *q;
	q = tail->next;
	//make q point to p
	q->next = p;
	//make tail point to p
	tail->next = p;
	//make p point to null
	p->next = NULL;

	//store data in new node
	//FIGURE THIS OUT
	time_t tempVisit;

}

//get url from current cursor position
string BrowserHistory::getURL() {
	// TO BE COMPLETED
	//only works if cursor is set at a node
	if (numVisited==0) {
		cout << "No sites visited\n";
		return;
	}
	return (cursor->url);
}

size_t BrowserHistory::getNavSize() {
	return numVisited;
}

//move cursor back
string BrowserHistory::back() {
	cursor = cursor->prev;
}

//move cursor forward
string BrowserHistory::forward() {
	cursor = cursor->next;
}

void BrowserHistory::readHistory(string fileName) {
	// TO BE COMPLETED
}

void BrowserHistory::printBackSites() {
	// TO BE COMPLETED
	// cannot be done recursively due to lack of parameters
	for (Webpage *dispCursor = head; dispCursor->next = cursor; dispCursor = dispCursor->next) {
		cout << "Site URL: " << dispCursor->url << endl << "Time Visited: " << dispCursor->time << endl << endl;
	}
}

void BrowserHistory::printForwardSites() {
	// TO BE COMPLETED
	//start at current site and end once reached end of browsing history
	for (Webpage *dispCursor = cursor; dispCursor->next = NULL; dispCursor = dispCursor->next) {
		cout << "Site URL: " << dispCursor->url << endl << "Time Visited: " << dispCursor->time << endl << endl;
	}
}

void BrowserHistory::printFullHistory() {
	// TO BE COMPLETED
	for (Webpage *dispCursor = head; dispCursor->next = NULL; dispCursor = dispCursor->next) {
		cout << "Site URL: " << dispCursor->url << endl << "Time Visited: " << dispCursor->time << endl << endl;
	}
}
