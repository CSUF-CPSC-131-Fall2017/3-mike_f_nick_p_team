#pragma once

#include <string>
using namespace std;

class Webpage {
public:
	Webpage();
	//took out all reference operators to try fix... PUT THEM BACK IF IT BREAKS
	Webpage(const string& webpageURL, const time_t& timeVisited);
	string getURL();
	time_t getTime();
	void setInfo(const Webpage&);
	void setURL(string newURL);
	void setTime(time_t newTime);

private:
	// Add private member variables for your class along with any
	// other variables required to implement the public member functions
	// TO BE COMPLETED
	time_t time;
	string url;

	// adds functionality of webpage as a node
	Webpage* next;
	Webpage* prev;
	friend class BrowserHistory;
};

