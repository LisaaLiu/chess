#ifndef OBSERVER_H
#define OBSERVER_H

// observer abstract class
class Observer {
  public:
    // re-render when subject is changed
    virtual void notify() = 0;
    // virtual destructor
    virtual ~Observer() {};
};

#endif
