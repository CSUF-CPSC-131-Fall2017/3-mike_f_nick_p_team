#include "BrowserHistory.h"

BrowserHistory::BrowserHistory() {
    // TO BE COMPLETED
}

BrowserHistory::~BrowserHistory() {
    //delete each list
}

void BrowserHistory::visitSite(Webpage newSite) {
    if (browHistory.empty)
        browHistory.push_back(newSite);
    
    //if browHistory is empty
    //if cursor is at end
    //if cursor is in middle, delete everything after using tail and going backwards, then cursor next
}

string BrowserHistory::getURL() {
    // TO BE COMPLETED
}

size_t BrowserHistory::getNavSize() {
    // TO BE COMPLETED
}

string BrowserHistory::back() {
    // TO BE COMPLETED
}

string BrowserHistory::forward() {
    // TO BE COMPLETED
}

void BrowserHistory::readHistory(string fileName) {
    // TO BE COMPLETED
}

void BrowserHistory::printBackSites() {
    // TO BE COMPLETED
}

void BrowserHistory::printForwardSites() {
    // TO BE COMPLETED
}

void BrowserHistory::printFullHistory() {
    // TO BE COMPLETED
}
