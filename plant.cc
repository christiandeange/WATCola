#include "plant.h"
#include "truck.h"
#include "MPRNG.h"

using namespace std;

BottlingPlant::BottlingPlant( 
  Printer &prt, 
  NameServer &nameServer, 
  unsigned int numVendingMachines,
  unsigned int maxShippedPerFlavour, 
  unsigned int maxStockPerFlavour,
  unsigned int timeBetweenShipments ) 
: mPrinter( prt ),
  mNameServer( nameServer ),
  mNumVendingMachines( numVendingMachines ),
  mMaxShippedPerFlavour( maxShippedPerFlavour ),
  mMaxStockPerFlavour( maxStockPerFlavour ),
  mTimeBetweenShipments( timeBetweenShipments ) {

  shutdown = false;
  mPrinter.print( Printer::BottlingPlant,
                  Starting );
}

BottlingPlant::~BottlingPlant() {
  mPrinter.print( Printer::BottlingPlant,
                  Finished );
}

void BottlingPlant::getShipment( unsigned int cargo[] ) {
  _Accept( ~BottlingPlant ) {
    uRendezvousAcceptor();
    throw Shutdown();
  } _Else {
    mPrinter.print( Printer::BottlingPlant,
                   Pickup );
    unsigned int total = 0;
    for( int i = 0; i < VendingMachine::FlavoursCount; i++ ) {
      cargo[i] = RAND(mMaxShippedPerFlavour);
      total += cargo[i];
    }
    mPrinter.print( Printer::BottlingPlant,
                    (char)Generating,
                    total );
  }
}

void BottlingPlant::main() {
  Truck truck( mPrinter, 
               mNameServer, 
               (*this),
               mNumVendingMachines,
               mMaxStockPerFlavour );
  
  while( true ) {
    yield(mTimeBetweenShipments);
    _Accept( getShipment ) {}
    
    if ( shutdown ) break;
  }

}