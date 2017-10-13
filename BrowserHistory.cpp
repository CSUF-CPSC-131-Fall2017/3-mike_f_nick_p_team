
#include "BrowserHistory.h"

//default constructor
BrowserHistory::BrowserHistory() {
	numVisited = 0;
	head= tail;
	tail= head;
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
	head->next = tail;
	tail->prev = head;
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
		numVisited++;
		return;
	}

	//cursor at the end (nonempty)
	else if ((cursor == tail) && (head != NULL)) {
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
		numVisited++;
		return;
	}

	//somewhere else
	else
	{
		//delete all next elements
		Webpage *r = cursor;
		Webpage *delCursor = tail;
		while (delCursor != cursor) {
			Webpage *temp = delCursor;
			delCursor = delCursor->prev;
			delete temp;
			numVisited--;
		}
		r->next = new Webpage;
		cursor = r->next;
		cursor->next = NULL;
		numVisited++;
		
		//sets information for next site
		//need to check to make easier to understand
		r = r->next;
		r->setInfo(newSite);
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
	//giving error when cursor is a null pointer
	if (cursor != head) {
		cursor = cursor->prev;
		return cursor->url;
	}
	//comes here if going back points to NULL or if cursor is null
	else {
		return "Cursor is at First element already!";
	}
}

//move cursor forward
string BrowserHistory::forward() {
	if (cursor != tail) {
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

	//open the file
	ifstream myFile;
	myFile.open(fileName);

	//for some reason, not going into while loop to read the file data


	if (myFile.is_open()) {
		cout << "Successfully opened file: " << fileName << endl << endl;
		//input variables to read into here
		//for the mobileinput.txt, order goes
		//we know commands, so we can read as string
		//string is array of characters and each command has different first character
		//use first character in the string to determine command
		string command;
		
			
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
			else if (command[0] == 'n' || command[0] == 'N') {
				string url;
				time_t timeVisited;
				//new site is visited if first character of string in n as in New
				//only then will url and time show up on the txt file, else they won't exist on the line
				myFile >> url >> timeVisited;
				cout << "It works" << endl;
				Webpage newVisit(url, timeVisited);
				cout << "So does this" << endl;
				visitSite(newVisit);
				cout << "Then why does it break?" << endl;
			}
		}
	}
	myFile.close();
}



//does not need to access full history
void BrowserHistory::printBackSites() {
	// cannot be done recursively due to lack of parameters
	/*for (Webpage *dispCursor = head; dispCursor->next = cursor; dispCursor = dispCursor->next) {
	cout << "Site URL: " << dispCursor->url << endl << "Time Visited: " << dispCursor->time << endl << endl;
	}*/

	Webpage *dispCursor = head;
	//need to add case if dispCursor starts as equal to the cursor so the single node data is printed
	//only changing it to a do-while won't work, because dispCursor might try to access NULL->next
	while (dispCursor != cursor) {

		cout << "Site URL: " << dispCursor->url << endl << "Time Visited: " << dispCursor->time << endl << endl;
		dispCursor = dispCursor->next;
	}
}

//does not need to access full history
void BrowserHistory::printForwardSites() {
	//start at current site and end once reached end of browsing history
	/*for (Webpage *dispCursor = cursor; dispCursor->next = NULL; dispCursor = dispCursor->next) {
	cout << "Site URL: " << dispCursor->url << endl << "Time Visited: " << dispCursor->time << endl << endl;
	}*/


	Webpage *dispCursor = tail;
	while (dispCursor != cursor->prev) {

		cout << "Site URL: " << dispCursor->url << endl << "Time Visited: " << dispCursor->time << endl << endl;
		dispCursor = dispCursor->prev;
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
