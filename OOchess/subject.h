#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
#include <vector>

class Subject {
  // list of observers
  std::vector<Observer*> observers;
  public:
  // add observer to the subject's observers list
    void attach(Observer* ob);
  // remove observer from the subject's observers list
    void detach(Observer* ob);
  // notify the observer in the observers list
    void notify() ;
  // virtual destructor
    virtual ~Subject() = 0;
};
#endif

