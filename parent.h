#ifndef PARENT_H_
#define PARENT_H_

_Task Parent {
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );

    enum State {
      Starting = 'S', 
      Deposit  = 'D', 
      Finished = 'F'
    };
};

#endif