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
		//remove all the elements from visible browser history 
		// also needs to change previous and next pointers
		Webpage *p = delCursor->next;
		Webpage *q = delCursor->prev;
		p->prev = q;
		q->next = p;
		delete delCursor;
	}
	head = NULL;
	tail = NULL;
}

//THIS FUNCTION IS VERY MESSED UP
//WORK ON IT

//add node to linked list
void BrowserHistory::visitSite(Webpage newSite) {
	// TO BE COMPLETED

	//adds new site visited to the list which stores full history
	fullHistory.push_front(newSite);

	//create new node with pointer p
	Webpage *p = new Webpage;
	p->setInfo(newSite);
	//find old final node with pointer q

	//4 Cases for adding sites
	//first webpage visited
	//cursor is at the end
	//cursor at beginning (nonempty)
	//cursor not at beginning (nonempty)

	//first webpage visited 
	if ((head == NULL) && (tail == NULL)) {
		head = p;
		tail = p;
		//NULL pointers at both ends of the list
		p->next = NULL;
		p->prev = NULL;
		cursor = p;
	}

	//cursor at the end (nonempty)
	else if ((cursor->next == NULL) && (head != NULL)) {
		Webpage *q;
		//q is a pointer to the last node in the list
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

	//cursor not at beginning (nonempty)
	else if ((cursor->next != NULL) && (head != NULL)) {
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
	//cursor at beginning (nonempty)
	else if ((cursor->next != NULL) && (cursor->prev == NULL)) {
		//put code here
		// CHECK THE ARGUMENTS AND SEE IF PREVIOUS NODE IS SET TO NULL BY DEFAULT
		Webpage *q;
		q = cursor->next;


		p->next = q;
		//allows this statement to run 
		p->prev = NULL;
	}

}

//get url from current cursor position
string BrowserHistory::getURL() {
	// TO BE COMPLETED
	//only works if cursor is set at a node
	if (numVisited == 0) {
		return "No Sites Visited\n";
	}
	return (cursor->url);
}

size_t BrowserHistory::getNavSize() {
	return numVisited;
}

//move cursor back
string BrowserHistory::back() {
	if (cursor->prev != NULL) {
		cursor = cursor->prev;
		return cursor->url;
	}
	//comes here if going back points to NULL
	return "Cursor is at First element already!";
}

//move cursor forward
string BrowserHistory::forward() {
	if (cursor->next != NULL) {
		cursor = cursor->next;
		return cursor->url;
	}
	//comes here if going forward points to NULL
	return "Cursor as at Last element already!";
}


void BrowserHistory::readHistory(string fileName) {
	// TO BE COMPLETED
	//read in from a file
	//MUST BE ABLE TO READ FORWARD AND BACK COMMANDS AS WELL AS NEW SITES VISITED

	//get file
	//open as ifstream
	//read url & time
	//ensure it can read forward and back commands


	ifstream myFile(fileName);

	if (myFile.is_open()) {
		cout << "Successfully opened file: " << fileName << endl << endl;
		//input variables to read into here
		//for the mobileinput.txt, order goes
		//we know commands, so we can read as string
			//string is array of characters and each command has different first character
			//use first character in the string to determine command
		string command;
		string url;
		time_t timeVisited;

		//while loop won't work as some statements contain only commands
		while (myFile >> command) {
			//code goes here
			//need way to find command from text file
				//3 commands
					//new
					//back
					//forward
			if (command[0] == 'f' || command[0] == 'F') {
				//forward command
				forward();
			}
			else if (command[0] == 'b' || command[0] == 'B') {
				//back command
				back();
			}
			else if (command[0] == 'n' || command [0] == 'N') {
				//new site is visited if first character of string in n as in New
				//only then will url and time show up on the txt file, else they won't exist on the line
				myFile >> url >> timeVisited;
				visitSite(Webpage(url, timeVisited));
			}
		}
	}
}



//does not need to access full history
void BrowserHistory::printBackSites() {
	// cannot be done recursively due to lack of parameters
	for (Webpage *dispCursor = head; dispCursor->next = cursor; dispCursor = dispCursor->next) {
		cout << "Site URL: " << dispCursor->url << endl << "Time Visited: " << dispCursor->time << endl << endl;
	}
}
//does not need to access full history
void BrowserHistory::printForwardSites() {
	//start at current site and end once reached end of browsing history
	for (Webpage *dispCursor = cursor; dispCursor->next = NULL; dispCursor = dispCursor->next) {
		cout << "Site URL: " << dispCursor->url << endl << "Time Visited: " << dispCursor->time << endl << endl;
	}
}

//printFullHistory should be reading in from the stack method of browser history which stores all sites regardless of deletion
void BrowserHistory::printFullHistory() {
	// TO BE COMPLETED

	//head will point to first element in forward list
	//rest is okay
	// make the iterator work to do this
	for (list<Webpage>::iterator i = fullHistory.begin(); i != fullHistory.end(); ++i) {
		cout << "Site URL: " << (*i).getURL() << endl << "Time Visited: " << (*i).getTime() << endl;
	}
}
