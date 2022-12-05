#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Subject;

class Observer {
 public:
  virtual void notify() = 0; //virtual void function
  virtual int pickMove() = 0; // virtual int function
  virtual ~Observer() = default;
};

#endif
