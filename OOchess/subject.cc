#include "subject.h"
#include <iostream>
#include <algorithm>

// add observer to the subject's observers list
void Subject::attach(Observer* ob){ 
    observers.emplace_back(ob); 
}
// remove observer from the subject's observers list
void Subject::detach(Observer* ob) { 
  auto it = std::find(observers.begin(), observers.end(), ob);
  if (it != observers.end()) {
    observers.erase(it);
  }
}
// notify the observer in the observers list
void Subject::notify() {
      for (auto ob: observers) {
        ob->notify();}
    }
 //destructor
Subject::~Subject() {}
