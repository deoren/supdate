/*
	Filename:	download.cpp
	 Version:	1.0.4
	Modified:	March 14, 2003	
	
	 Purpose:	Testing a "module" of code
			    belonging to a larger program.

	   Notes:	***PROBLEM FIXED***
				see explanation at bottom of code
	   
				Compiles on both MS VC++ 6.0 and DevCPP 4 & beta 5.
			    Quite possibly most Win32 capable compilers.
			    Unfortunately, I don't have many compilers to test
			    this on.

	Problems:	Whenever the executable compiled from VC++
			    is run, I get the following error:
			    
-----------------------------------------------------
The value of ESP was not properly saved across a 
function call.  This is usually a result of calling
a function declared with one calling convention with
a function pointer declared with a different calling 
convention.
-----------------------------------------------------

   *** PROBLEM FIXED ***
   see explanation at bottom of code

*/

// These includes are used for testing purposes.  When full
// program has been developed, these can either be removed
// or commented out.

#define WIN32_LEAN_AND_MEAN
// #include <fstream>  // this OR iostream IS NEEDED for namespace std
#include <iostream> 
#include <windows.h> 
#include <stdlib.h>   // without this DevCPP complains "implicit declaration"

/* 
// #include <urlmon.h> // for URLDownloadToFile function

This version uses LoadLibrary to obtain the functions from a dll
instead of compiling with urlmon.lib.  This allows compiling
without either the sdk and with an alternate (devcpp) compiler !(VC++6).
*/

using namespace std;

// prototype functions here
// This (or these) will need to either be moved to core.cpp or
// moved to a protype.h file.
bool DownloadFile(LPCTSTR URL , LPCTSTR LocalFilename); 

// -----------------------------------------------------
// typedef seems to be needed here for defining MYPROC 
// as a long pointer
// -----------------------------------------------------

// no, it's actually a function-pointer using stdcall or __stdcall
// as it's calling convention that returns a long (value)
// which accepts the argument(s) (types) declared below.

// URLDownloadToFile requires a long return value
typedef long (WINAPI * MYPROC)(long,LPCTSTR,LPCTSTR,DWORD,long);
// same as typedef long (__stdcall * MYPROC)(long,LPCTSTR,LPCTSTR,DWORD,long);


int main()
{
	// I didn't realize this variable type existed: LPCTSTR
	// Took awhile ...
	
	// It is defined within windef.h  I'd suggest printing a 
	// copy to have around as a reference.

	// Purposely BAD Url for testing
	// LPCTSTR URL = "http://www.bobsapples.com/index.html";

	// Good Url
    LPCTSTR URL = "http://www.geocities.com/deoren/index.html";
	LPCTSTR LocalFilename = "D:\\index.html";

    // Called here with these values for testing purposes.
	bool success;
	
	// pass above values
	success = DownloadFile(URL ,LocalFilename); 
	if (success == false)
	{
		cout << "There is a problem with your url" << endl;
	}
	else
	{
		cout << "It works" << endl;
	}

	// #include <--(d) stdlib.h for this function
	// VC++ 6 would automatically add any includes
	// for functions that I implicitly called
	// but that is not good programming practice
	
    system("pause");  // hold window open so user can see output
					 
	return (0);

}  // end main function 

// start DownloadFile function
// this function simplifies passing parameters to 
// the Win32 API, URLDownloadToFile
bool DownloadFile(LPCTSTR URL , LPCTSTR LocalFilename) 
{        
    
    
    // Where do these variable types come from?  Windows.h?
    
    // depending on what compiler you have much of them are added by #define
    // or typedef in windef.h, though I've seen *nix ports defining HANDLE 
    // in windows.h
   
   // INITIALIZE VARIABLES  
/*****************************************************************************/
     // receives return value of download function 
    long lngRetVal; 
    
    // HMODULE is the same thing as HINSTANCE,
	// which happens to be a void pointer                
	HMODULE hinstLib; 
	
	// We're declaring ProcAdd to be of the type specified at the top
	// of the code.  ProcAdd will be our function pointer to URLDownloadToFileA
    MYPROC ProcAdd;
    
    // results of checks to make sure functions executed properly                                      
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;
/*****************************************************************************/
	
    // get .dll for URLDownloadToFile function
	// see Win32API reference for how LoadLibrary checks the path
	hinstLib = LoadLibrary("urlmon.dll");

  // If the handle is valid, try to get the function address.
  if(hinstLib != NULL)
  { 
  
    // This is one part (below) that I suspected of causing the ESP
    // problem mentioned at the beginning of this file.

	// However, the problem (ESP) was that GetProcAddress was expecting
	// a WINAPI (or __stdcall) calling convention, whereas it was
	// receiving a __cdecl convention.  See bottom of code for more info.
    
	// get pointer to URLDownloadToFile
	ProcAdd = (MYPROC) GetProcAddress(hinstLib, "URLDownloadToFileA");
	
		
	   if (NULL != ProcAdd) 
	   {  // If the function address is valid ...
            fRunTimeLinkSuccess = TRUE;

            // ... Show the user what we're trying to get then ...
	    	cout << "Value of URL: " << URL << endl;
			cout << "Value of LocalFilename: " << LocalFilename << endl;

			//  ... call the function.

			// Here is where the program would bomb out (doesn't now).  This is 
			// explained very well by Fordy in the bottom section of this code
			
			// Calls the function and passes in the expected parameters
			// saving results in lngRetVal
			
		    lngRetVal = ProcAdd(0, URL, LocalFilename, 0, 0);

			// Free the DLL module.
		    fFreeResult = FreeLibrary(hinstLib);

		}	
  }

	/*
     RETURN VALUES:
     S_OK               Operation Succeeded
     E_OUTOFMEMORY      The buffer length is invalid or there was 
                        insufficient memory to complete the operation.
    */                   

    // now that function has been called, let's see what
    // it returned...
    
    // The values above are of type long, as that's
    // what this API call expects.

    // It works, because it'll tell you if the URL is unreachable.
        
	if (lngRetVal==S_OK)
	{
		return (true); // file successfully retrieved
	} 
	else
	{
		return (false); 
	}
		        
} // end of DownloadFile Function


/* 
  SOLUTION TO PROBLEM MENTIONED AT BEGINNING OF FILE
  --------------------------------------------------
  
  The following comments from the posters on http://cboard.cprogramming.com
  have been unedited, and have been included entirely as posted.  I deeply
  appreciate posts from both of these people.  It is people like them that
  make the difference
  
  // begin posts:

  Try changing this:


code:--------------------------------------------------------------------------
(*MYPROC)(long,LPCTSTR,LPCTSTR,DWORD,long);
-------------------------------------------------------------------------------


to this...

code:--------------------------------------------------------------------------
(__stdcall * MYPROC)(long,LPCTSTR,LPCTSTR,DWORD,long);
-------------------------------------------------------------------------------


From what I've been able to find out about that error, the calling
convention of your function-pointer doesn't match the calling
convention of the function you're assigning to it... FARPROC GetProcAddress();

FARPROC, I think, is defined as WINAPI (which is __stdcall. And
with VC++, __cdecl is the default calling convention.)

I don't know much, though. I'm probably wrong, and not making
much sense. Keep in mind, I had no idea what the heck a
calling-convention was before I decided to reply to your thread.

But when you change it to __stdcall, the error doesn't appear.
And that's what matters.. 

  - ethic : http://cboard.cprogramming.com



Windows APIs almost all use STDCALL......but C compilers default to 
the C calling convention..

When you call a function, the params are copied to the stack......
The main difference between the conventions is that with STDCALL, the 
called function wipes them off the stack....but with the C convention, 
the code that called the function does this right after the function 
returns.....so in your case, the called function didnt clean up, neither 
did the calling code, therefore the stack still had the params on it
.....the debug version of your code checks to see that the stack is in 
the state it should be, and as it isnt, it asserts - creating the error

   - Fordy : http://cboard.cprogramming.com
   
The following is a code snippet posted by Fordy to illustrate what's 
going on at an assembly level.  The assembly syntax used is for Intel
Assembly compatible compilers.  The same example using AT&T notation
(and slightly different coding conventions) can be found as a file 
called callgcc.cpp at the same place you found this file.


#include <iostream>


void _cdecl Hello1(const char* szBuff)
//force C calling convention
{
	std::cout << szBuff << std::endl;
}

void _stdcall Hello2(const char* szBuff)
//force STDCALL calling convention
{
	std::cout << szBuff << std::endl;
}

int main()
{
	const char* szBuff = "Hello World";

	__asm
	{
		push szBuff //push the param onto the stack
		call Hello1 //call the function
		add esp,4 //restore the stack to previous state

		push szBuff //push the param onto the stack
		call Hello2 //call the function
		//dont restore stack as Hello2 will do that
	}
	
	return 0;
}
   
*/

/*
Ok...in my code above I push a 4 byte value 
(actually a 32bit pointer to a string) onto the stack....
the stack pointer is held in the ESP register for Intel type chips...
tht register is decreased 4 bytes as you have added 4 bytes to the 
stack....after this param is no longer needed, the ADD instruction 
increases the ESP register by 4 (bytes) therefore returning the stack 
position to the same place before the CALL
*/


