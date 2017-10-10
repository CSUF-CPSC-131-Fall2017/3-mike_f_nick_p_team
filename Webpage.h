#pragma once

#include <string>
using namespace std;

class Webpage {
public:
    Webpage();
    Webpage(const string& webpageURL, const time_t& timeVisited);
    Webpage(&Webpage);
    operator=(&Webpage);
    string getURL();
    time_t getTime();

private:
   string url;
   time_t time;
   Webpage* next;
   Webpage* prev;
   friend class BrowserHistory;
};
