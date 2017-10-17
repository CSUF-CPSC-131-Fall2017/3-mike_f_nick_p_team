#pragma once

#include <string>
#include <exception>
using namespace std;

class Webpage {
public:
	Webpage();
	Webpage(const string& webpageURL, const time_t& timeVisited);
	string getURL();
	time_t getTime();
	void setInfo(const Webpage&);

private:
	time_t time;
	string url;
	Webpage* next;	//Converts Webpage into a doubly linked list node class.
	Webpage* prev;
	friend class BrowserHistory;
};
