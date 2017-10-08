#pragma once

#include <string>
using namespace std;

class Webpage {
public:
    Webpage();
    Webpage(const string& webpageURL, const time_t& timeVisited);
    string getURL();
    time_t getTime();

private:
   string webAddress;
   time_t timeVisited;
};
