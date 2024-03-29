#include <iostream>
#include <fstream>
#include <limits>					// numeric_limits

#include "config.h"

using namespace std;


static bool comments( ifstream &in, string &name ) {
    for ( ;; ) {
	in >> name;
      if ( in.fail() ) return true;
      if ( name.substr(0,1) != "#" ) break;
	in.ignore( numeric_limits<int>::max(), '\n' ); // ignore remainder of line
    } // for
    return false;
} // comments

// Process the configuration file to set the parameters of the simulation.
void processConfigFile( const char *configFile, ConfigParams &cParams ) {
    const unsigned int Parmnum = 9;
    struct {
        const char *name;				// configuration name
        bool used;					// already supplied ?
        unsigned int &value;				// location to put configuration value
    } static Params[Parmnum] = {
        { "SodaCost", false, cParams.sodaCost },
        { "NumStudents", false, cParams.numStudents },
        { "MaxPurchases", false, cParams.maxPurchases },
        { "NumVendingMachines", false, cParams.numVendingMachines },
        { "MaxStockPerFlavour", false, cParams.maxStockPerFlavour },
        { "MaxShippedPerFlavour", false, cParams.maxShippedPerFlavour },
        { "TimeBetweenShipments", false, cParams.timeBetweenShipments },
        { "ParentalDelay", false, cParams.parentalDelay },
        { "NumCouriers", false, cParams.numCouriers },
    };
    string name;
    int value;
    unsigned int cnt, posn;
    unsigned int numOfParm = 0;

    try {
        ifstream in( configFile );			// open the configuration file for input

	for ( cnt = 0 ; cnt < Parmnum; cnt += 1 ) {	// parameter names can appear in any order
	  if ( comments( in, name ) ) break;		// eof ?
	    for ( posn = 0; posn < Parmnum && name != Params[posn].name; posn += 1 ); // linear search
	  if ( posn == Parmnum ) break;			// configuration not found ?
	  if ( Params[posn].used ) break;		// duplicate configuration ?
	    in >> value;
	    if ( value <= 0 ) {
		cerr << "Error: file \"" << configFile << "\" parameter " << name
		     << " value " << value << " must be positive." << endl;
		exit( EXIT_FAILURE );
	    } // if
	  if ( in.fail() ) break;
	    in.ignore( numeric_limits<int>::max(), '\n' ); // ignore remainder of line
	    numOfParm += 1;
	    Params[posn].used = true;
	    Params[posn].value = value;
	} // for

	if ( numOfParm != Parmnum ) {
	    cerr << "Error: file \"" << configFile << "\" is corrupt." << endl;
	    exit( EXIT_FAILURE );
	} // if
	if ( ! comments( in, name ) ) {			// ! eof ?
	    cerr << "Error: file \"" << configFile << "\" has extraneous data." << endl;
	    exit( EXIT_FAILURE );
	} // if
    } catch( uFile::Failure ) {
        cerr << "Error: could not open input file \"" << configFile << "\"" << endl;
        exit( EXIT_FAILURE );    
    } // try
} // processConfigFile

// Local Variables: //
// compile-command: "make" //
// End: //
