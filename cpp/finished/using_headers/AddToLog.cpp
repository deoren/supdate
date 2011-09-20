// This was added to provide functionality for logging errors.


// These includes are used for testing purposes.  When full
// program has been developed, these can either be removed
// or commented out.

#include <fstream>
// #include <iostream> // Is this needed?
#include <windows.h>

using namespace std;


// prototype functions here
// This will need to either be moved to core.cpp or
// moved to a protype.h file.
bool AddtoLogFile(
    bool zipdatError, 
    bool sdatError, 
    bool iniDownloadError, 
    bool ini_McAfee_Error, 
    bool ini_sdat_Error, 
    bool ini_zipdat_Error);

// main will need to be removed.
int main()
{
    // Called here with these values for testing purposes.
    // Does bool need to be added in front of AddtoLogFile for 
    // further compliance with ISO C++ 98?
    
    // no, it is already prototyped above, and this is merely a function call
    // it's return value is already defined, and return 0 handles that.
	AddtoLogFile(false,false,false,false,false,false);
	return (0);
}

bool AddtoLogFile( // start of AddtoLogFile function
	bool zipdatError, 
	bool sdatError, 
	bool iniDownloadError, 
	bool ini_McAfee_Error, 
	bool ini_sdat_Error, 
	bool ini_zipdat_Error)
{  
  
   
  // Create a structure variable of type SYSTEMTIME
  SYSTEMTIME systemtime;

  // get current local time, duh?
  GetLocalTime(&systemtime 	// address of system time structure  
   );

  // declare output file
  ofstream logfile;

  // open logfile in local directory, in append mode
  logfile.open("log.txt",ios::app);
  
  // add logfile header
  logfile << "...................................................." 
	      << endl;
  logfile << "...................................................." 
	      << endl;
  	      
  logfile << "Update Server Version:   1.4.1" << endl;
  logfile << "Original Concept Date:   x-x-2001" << endl;
  logfile << "        Revision Date:   03-08-03" << endl;
  logfile << "        Major Changes:   ";
  logfile << "Translated from VB to C++" << endl;
  
  // log run time
  logfile << "Time: " << systemtime.wHour 
          << ":" << systemtime.wMinute << endl;

  logfile << "Date: " << systemtime.wMonth << "-" << systemtime.wDay
                      << "-" << systemtime.wYear << endl 
                      
                      // add extra line to make section below stand out
                      << endl;
                      
  logfile << "***************************************************"
          << endl;
  logfile << "How to read this logfile:" << endl;
  logfile << "-------------------------" << endl;
  logfile << "0 indicates success, 1 indicates failure"
          << endl;
  logfile << "***************************************************"
          << endl;        
          
          
          // log errors, or lack of...
  logfile << "Error Downloading zipfile    : " << zipdatError << endl;
  logfile << "Error Downloading sdatfile   : " << sdatError << endl;
  logfile << "Error Downloading iniFile    : " << iniDownloadError 
		  << endl;
  logfile << "Error Accessing Update.ini   : " << ini_McAfee_Error 
	      << endl;
  logfile << "Error Accessing settings.ini : " << ini_zipdat_Error 
	      << endl << endl;
  
  logfile.close(); // just what it looks like

  return (true); 

} // end of AddtoLogFile function
