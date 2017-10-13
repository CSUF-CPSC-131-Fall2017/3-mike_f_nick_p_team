#include "BrowserHistory.h"

//Default constructor.
BrowserHistory::BrowserHistory() {
	numVisited = 0;
	head->next = tail;
	head->prev = nullptr;
	tail->prev = head;
	tail->next = nullptr;
	cursor = head;
}

//Destructor deletes list by deallocating memory.
BrowserHistory::~BrowserHistory() {
	//We must deallocate memory from browHistory doubly linked list
	Webpage *delCursor = tail;
	while (delCursor->prev != head) {
		Webpage *p = delCursor->prev;
		delete delCursor;
		delCursor = p;
	}
	head->next = tail;
	head->prev = nullptr;
	tail->prev = head;
	tail->next = nullptr;

	//The full history linked list implements its own destructor that will deallocate its memory.
}


//Adds a node to full history and browser history lists.
void BrowserHistory::visitSite(Webpage newSite) {
	//Adds new site visited to the full website history. Repeats allowed, but will have different times visited.
	fullHistory.push_front(newSite);

	//First webpage visited.
	if (head->next == tail->prev) {
		Webpage *p = new Webpage;	 //Create new node with pointer p
		p->setInfo(newSite);
		head = p;					 //Insert new node into list between head and tail.
		cursor = p;					 //Update cursor.
		cursor->next = nullptr;
		cursor->prev = nullptr;
		tail = cursor;				 //Set link between new node and tail.
		numVisited++;
		return;
	}

	//Cursor at the end of list.
	else if (cursor->next == nullptr) {
		Webpage *p = new Webpage;	//Create new node with pointer p.
		p->setInfo(newSite);
		cursor->next = p;			//Insert new node after cursor.
		cursor = p;					//Update cursor.
		cursor->next = nullptr;
		tail = cursor;				//Set link between new node and tail.
		numVisited++;
		return;
	}

	//In the middle of list.
	else
	{
		//Delete all of the previous forward history.
		Webpage *delCursor = tail;			//Start from tail and remove in reverse.
		while (delCursor != cursor) {		//Until the cursor is reached.
			Webpage *temp = delCursor;		//Store link to be deleted.
			delCursor = delCursor->prev;	//Move deleting cursor back one link.
			delete temp;					//Remove link from list.
			numVisited--;					//Need to decrement for every item deleted.
		}

		Webpage *p = new Webpage;		//Create new node with pointer p.
		p->setInfo(newSite);				
		cursor->next = p;				//Insert new node after cursor.
		cursor = p;						//Update cursor.
		cursor->next = nullptr;			
		tail = cursor;					//Set link between new node and tail.
		numVisited++;
	}
}

//Get url from current cursor position.
string BrowserHistory::getURL() {
	if (numVisited == 0)
		throw invalid_argument("No sites visited\n");
	return (cursor->url);
}


//Returns the number of sites currently in the browser history.
size_t BrowserHistory::getNavSize() {
	return numVisited;
}


//Move cursor back one link.
string BrowserHistory::back() {
	if (cursor->prev == nullptr) //If the cursor is at the beggining link.
		throw invalid_argument("Cursor already at the beggining of the list.\n");
	cursor = cursor->prev;		 //Move the cursor back one link (head and tail unchanged).
	return cursor->url;
}


//Move cursor forward one link.
string BrowserHistory::forward() {
	if (cursor->next == nullptr) //If the cursor is at the final link.
		throw invalid_argument("Cursor already at the end of the list.\n");
	cursor = cursor->next;		 //Move the cursor forward one link (head and tail unchanged).
	return cursor->url;
}


void BrowserHistory::readHistory(string fileName) {
	ifstream myFile(fileName);
	if (myFile.fail())
		throw "Failed to open file.\n";

	//Variables to store file data and insert them into nodes in list.
	string command;
	string url;
	time_t timeVisited;

	while (myFile >> command) { //Until end of file is reached.
		if (command[0] == 'f' || command[0] == 'F') //If command is forward.
			forward();
		else if (command[0] == 'b' || command[0] == 'B') //If command is back.
			back();
		else if (command[0] == 'n' || command[0] == 'N') { //If command is new site.
			myFile >> url >> timeVisited;	 //Only then will url and time be read from text file.
			visitSite(Webpage(url, timeVisited));
			fullHistory.push_front(Webpage(url, timeVisited));
		}
	}
}


//Prints sites from beggining of browser up to (but not including) the current page.
void BrowserHistory::printBackSites() {
	if (head->next == tail->prev)
		throw invalid_argument("There are no items in the browser history.\n");
	Webpage *dispCursor = head;
	while (dispCursor->next != cursor) {
		cout << "Site URL: " << dispCursor->url << endl;
		cout << "Time Visited: " << dispCursor->time << endl << endl;
		dispCursor = dispCursor->next;		//Move cursor forward one link.
	}
}

//Does not need to access full history
void BrowserHistory::printForwardSites() {
	if (head->next == tail->prev)
		throw invalid_argument("There are no items in the browser history.\n");
	Webpage* dispCursor = cursor;
	while (dispCursor->next != nullptr) {
		cout << "Site URL: " << dispCursor->url << endl;
		cout << "Time Visited: " << dispCursor->time << endl << endl;
		dispCursor = dispCursor->prev;		//Move cursor forward one link.
	}
}


//Prints the web browsing history.
void BrowserHistory::printFullHistory() {
	for (list<Webpage>::iterator i = fullHistory.begin(); i != fullHistory.end(); ++i) {
		cout << "Site URL: " << (*i).getURL() << endl;
		cout << "Time Visited: " << (*i).getTime() << endl;
	}
}
