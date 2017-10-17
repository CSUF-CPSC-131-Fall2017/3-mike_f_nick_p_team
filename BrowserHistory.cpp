#include "BrowserHistory.h"


//Default constructor.
BrowserHistory::BrowserHistory() {
	numVisited = 0;
	head = new Webpage;
	tail = new Webpage;
	head->next = tail;
	head->prev = nullptr;
	tail->prev = head;
	tail->next = nullptr;
	cursor = head;
}

//Destructor deletes list by deallocating memory.
BrowserHistory::~BrowserHistory() {
	//We must deallocate memory from browser history doubly linked list
	Webpage *delCursor = tail->prev;
	while (delCursor != head) {
		Webpage *p = delCursor->prev;
		delete delCursor;
		delCursor = p;
	}
	delete head;
	delete tail;

	//The full history linked list implements its own destructor that will deallocate its memory.
}


//Adds a node to full history and browser history lists.
void BrowserHistory::visitSite(Webpage newSite) {
	//Adds new site visited to the full website history. Repeats allowed, but will have different times visited.
	fullHistory.push_front(newSite);

	//First webpage visited.
	if (head->next == tail) {
		Webpage *p = new Webpage;	 //Create new node with pointer p
		p->setInfo(newSite);
		head->next = p;				 //Insert new node into list between head and tail.
		p->prev = head;				 //Set link between new node and sentinels.
		p->next = tail;
		tail->prev = p;
		cursor = p;					 //Update cursor.	
		numVisited++;
		return;
	}

	//Cursor at the end of list.
	else if (cursor->next == tail) {
		Webpage *p = new Webpage;	//Create new node with pointer p.
		p->setInfo(newSite);
		p->next = tail;
		tail->prev = p;
		p->prev = cursor;
		cursor->next = p;
		cursor = p;
		numVisited++;
		return;
	}


	//In the middle of list.
	else
	{
		//Delete all of the previous forward history.
		Webpage *delCursor = tail->prev;			//Start from tail and remove in reverse.
		while (delCursor != cursor) {		//Until the cursor is reached.
			Webpage *temp = delCursor;		//Store link to be deleted.
			delCursor = delCursor->prev;	//Move deleting cursor back one link.
			delete temp;					//Remove link from list.
			numVisited--;					//Need to decrement for every item deleted.
		}
		
		Webpage *p = new Webpage;		//Create new node with pointer p.
		p->setInfo(newSite);				
		cursor->next = p;				//Insert new node after cursor.
		p->prev = cursor;
		p->next = tail;
		tail->prev = p;					//Set link between new node and tail.
		cursor = p;						//Update cursor.
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
	if (cursor->prev == head) //If the cursor is at the beggining link.
		throw invalid_argument("Cursor already at the beginning of the list.\n");
	cursor = cursor->prev;	  //Move the cursor back one link (head and tail unchanged).
	return cursor->url;
}


//Move cursor forward one link.
string BrowserHistory::forward() {
	if (cursor->next == tail) //If the cursor is at the final link.
		throw invalid_argument("Cursor already at the end of the list.\n");
	cursor = cursor->next;		 //Move the cursor forward one link (head and tail unchanged).
	return cursor->url;
}


void BrowserHistory::readHistory(string fileName) {
	ifstream myFile(fileName);
	if (myFile.fail())
	throw invalid_argument("Failed to open file.\n");

	//Variables to store file data and insert them into nodes in list.
	string command;
	string url = "";
	time_t timeVisited = 0;

	while (myFile >> command) {		//Until end of file is reached.
		if (command[0] == 'f' || command[0] == 'F') //If command is forward.
			forward();
		else if (command[0] == 'b' || command[0] == 'B') //If command is back.
			back();
		else if (command[0] == 'n' || command[0] == 'N') { //If command is new site.
			myFile >> url >> timeVisited;	 //Only then will url and time be read from text file.
			Webpage p(url, timeVisited);
			visitSite(p);
		}
	}
	myFile.close();
}


//Prints sites from beggining of browser up to (but not including) the current page.
void BrowserHistory::printBackSites() {
	if (head->next == tail)
		throw invalid_argument("There are no items in the browser history.\n");
	Webpage *dispCursor = head;
	while (dispCursor->next != cursor) {
		if (dispCursor == head)
			cout << "---Start List--- \n\n";
		else {
			cout << "Site URL: " << dispCursor->url << endl;
			cout << "Time Visited: " << dispCursor->time << endl << endl;
		}
		dispCursor = dispCursor->next;		//Move cursor forward one link.
	}
}

//Does not need to access full history
void BrowserHistory::printForwardSites() {
	if (head->next == tail)
		throw invalid_argument("There are no items in the browser history.\n");
	Webpage* dispCursor = cursor;
	while (dispCursor->next != tail) {
		cout << "Site URL: " << dispCursor->url << endl;
		cout << "Time Visited: " << dispCursor->time << endl << endl;
		dispCursor = dispCursor->next;		//Move cursor forward one link.
	}
	cout << "---End List---\n";
}


//Prints the web browsing history.
void BrowserHistory::printFullHistory() {
	cout << "---Start List--- \n\n";
	for (list<Webpage>::iterator i = fullHistory.begin(); i != fullHistory.end(); i++) {
		cout << "Site URL: " << (*i).getURL() << endl;
		cout << "Time Visited: " << (*i).getTime() << endl << endl;
	}
	cout << "---End List--- \n\n";

	for (list<Webpage>::iterator i = fullHistory.begin(); i != fullHistory.end(); ++i) {
		cout << "Site URL: " << (*i).getURL() << endl << "Time Visited: " << (*i).getTime() << endl;
	}
}
