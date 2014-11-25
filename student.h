#ifndef STUDENT_H_
#define STUDENT_H_


_Task Student {

    void main();

  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );

    enum State {
      Starting  = 'S', 
      Selecting = 'V', 
      Buying    = 'B', 
      Lost      = 'L', 
      Finished  = 'F'
    };

};

#endif