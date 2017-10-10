#include "BrowserHistory.h"

//default constructor
BrowserHistory::BrowserHistory() {
	// TO BE COMPLETED
	head = NULL;
	tail = NULL;
	cursor = head;
	// add full browser history stack 
	// full history will not delete elements, only add
}

//destructor must delete every node in the browser history
BrowserHistory::~BrowserHistory() {
	for (Webpage *delCursor = head; delCursor->next == NULL; delCursor = delCursor->next) {
		//remove the elements 
		// also needs to change previous and next pointers
		Webpage *p = delCursor -> next;
		Webpage *q = delCursor -> prev;
		p -> prev = q;
		q -> next = p;
		delete delCursor;
	}
}

//THIS FUNCTION IS VERY MESSED UP
//WORK ON IT


//add node to linked list
void BrowserHistory::visitSite(Webpage newSite) {
	// TO BE COMPLETED
	// adds new node into the list at the end
	// also needs to add the webpage to the stack of webpages that will remain imperfect
	
	//THIS ONLY WORKS IF THE CURSOR IS AT THE END

	//create new node with pointer p
	Webpage *p;
	p = new Webpage;
	p->setInfo(newSite);
	//find old final node with pointer q

	//need case if this is first webpage and tail is a pointer to null
	if ((head == NULL) && (tail == NULL)) {
		head = p;
		tail = p;
		//NULL pointers at both ends of the list
		p->next = NULL;
		p->prev = NULL;
		cursor = p;
	}

	//if new site is not the first visited and cursor is at the end of the list
	else if((tail -> next == NULL) && (head != NULL) && (cursor->next == NULL)){
		Webpage *q;
		q = tail;
		//make q point to p
		q->next = p;
		//make tail point to p
		tail = p;
		//make p point to null as it is last in the list
		p->next = NULL;
		p->prev = q;
		//set cursor to be on current new site
		cursor = p;
	}

	//if new site is not the first visited and cursor is not at the end of the list
	else if ((cursor->next != NULL) && (head != NULL) && (tail != NULL)) {
		// q will be previous node
		// r will be next node
		Webpage *q;
		Webpage *r;

		q = cursor->prev;
		r = cursor->next;

		p->next = r;
		p->prev = q;

		cursor = p;
	}
}

//get url from current cursor position
string BrowserHistory::getURL() {
	// TO BE COMPLETED
	//only works if cursor is set at a node
	if (numVisited==0) {
		return "No Sites Visited\n";
	}
	return (cursor->url);
}

size_t BrowserHistory::getNavSize() {
	return numVisited;
}

//move cursor back
string BrowserHistory::back() {
	cursor = cursor->prev;
	return cursor->url;
}

//move cursor forward
string BrowserHistory::forward() {
	cursor = cursor->next;
	return cursor->url;
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
