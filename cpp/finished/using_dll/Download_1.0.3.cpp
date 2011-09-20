/*
	Filename:	download.cpp
	 Version:	1.0.3
	Modified:	March 10, 2003	
	
	 Purpose:	Testing a "module" of code
			    belonging to a larger program.

	   Notes:	***PROBLEM FIXED***
				see explanation at bottom of code
	   
				This code below was pulled from many
			   	sources, and as such, I don't fully
				understand all of it.  I have made
			    various comments throughout the code
			    about what I may, and what I may not
			    understand.  PLEASE feel free to respond
			    with any explanations you wish to give.

                This code however, after MANY hours of 
			    picking through, WILL compile on both
			    MS VC++ 6.0 and DevCPP 4 & beta 5.

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
bool DownloadFile(LPCTSTR URL , LPCTSTR LocalFilename); // makes sense

// URLDownloadToFile requires a long return value

// -----------------------------------------------------
// typedef seems to be needed here for defining MYPROC 
// as a long pointer
// -----------------------------------------------------

// actually, I believe MYPROC is returning a long ?

// in most examples I find, you don't need to declare
// all of the arguments like I've done here.
// However without this, it won't compile. 

// __stdcall is the calling convention, which is #define d as
// WINAPI.  Most (if not all) Win32 APIs use __stdcall
// as the convention, whereas C functions use __cdecl by
// default.  (perhaps MOST compilers)


typedef long (WINAPI * MYPROC)(long,LPCTSTR,LPCTSTR,DWORD,long);

int main()
{
	// I didn't realize this variable type existed: LPCTSTR
	// Took awhile ...

	// Purposely BAD Url for testing
	// LPCTSTR URL = "http://www.bobsapples.com/index.html";

	// Good Url
    LPCTSTR URL = "http://www.geocities.com/deoren/index.html";
	LPCTSTR LocalFilename = "D:\\index.html";

    // Called here with these values for testing purposes.
	bool success;
	success = DownloadFile(URL ,LocalFilename);
	if (success == false)
	{
		cout << "There is a problem with your url" << endl;
	}
	else
	{
		cout << "It works" << endl;
	}

	// #include d stdlib.h for this function
	// VC++ 6 would automatically add any includes
	// for functions that I implicitly called
	// but that is not good programming practice
    system("pause"); 
					 
	return (0);

}  // end main function //WinMain

// start DownloadFile function

// this function simplifies passing parameters to 
// the Win32 API, URLDownloadToFile
bool DownloadFile(LPCTSTR URL , LPCTSTR LocalFilename) 
{        
    // initialize variables    
    long lngRetVal;  // may initialize to something !0 
    
    // Where do these variable types come from?  Windows.h?
    // HINSTANCE hinstLib;
	HMODULE hinstLib;
    MYPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

	// get urlmon dll
	// see LoadLibrary reference for how the function checks
	// the path
	hinstLib = LoadLibrary("urlmon.dll");

  // If the handle is valid, try to get the function address.
  if(hinstLib != NULL)
  { 
  
    // This is one part (below) that I MAJORLY suspect of causing the ESP
    // problem mentioned at the beginning of this file.

	// actually the problem (ESP) was that GetProcAddress was expecting
	// a WINAPI (or __stdcall) calling convention, whereas it was
	// receiving a __cdecl convention.  See bottom of code for more info.
    
	// get pointer to URLDownloadToFile
	ProcAdd = (MYPROC) GetProcAddress(hinstLib, "URLDownloadToFileA");
	
		
	   if (NULL != ProcAdd) 
	   {  // If the function address is valid ...
            fRunTimeLinkSuccess = TRUE;

	    	cout << "Value of URL: " << URL << endl;
			cout << "Value of LocalFilename: " << LocalFilename << endl;

			//  ... (cont') call the function.

			// Here is where the program bombs out.  I hope this
			// is obvious to somebody... certainly not to me.
			
			// BTW, the values "0, URL, LocalFilename, 0, 0"
			// used below are correct.  That much I'm confident of.

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
    
    // I'm assuming the values above are of type long, as that's
    // what VB uses as a return value when using that API call.

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
*/
