#include "Webpage.h"

//default constructor
Webpage::Webpage() {
	url = "www.---------.com";
	time = 0;
}

//initialized constructor
Webpage::Webpage(const string& webpageURL, const time_t& timeVisited) {
	url = webpageURL;
	time = timeVisited;
}

string Webpage::getURL() {
	return url;
}

time_t Webpage::getTime() {
	return time;
}

//Setter function to be used when creating a new node
void Webpage::setInfo(const Webpage &newSite) {
	url = newSite.url;
	time = newSite.time;
}
