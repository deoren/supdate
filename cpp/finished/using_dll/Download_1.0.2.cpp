/*
	Filename:	download.cpp
	 Version:	1.0.2
	Modified:	March 09, 2003	
	
	 Purpose:	Testing a "module" of code
			    belonging to a larger program.

	   Notes:	This code below was pulled from many
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

The value of ESP was not properly saved across a 
function call.  This is usually a result of calling
a function declared with one calling convention with
a function pointer declared with a different calling
convention.


PLEASE feel free to let me know what you think it could be. I've
search all over the net and haven't really come up with much.
I don't know enough to tell where the problem lies in my code, so
I'm relying on you.  Thanks.

*/

// These includes are used for testing purposes.  When full
// program has been developed, these can either be removed
// or commented out.

#define WIN32_LEAN_AND_MEAN
// #include <fstream>  // this OR iostream IS NEEDED for namespace std
#include <iostream> 
#include <windows.h> 
#include <stdlib.h>

/* 
// #include <urlmon.h> // for URLDownloadToFile function

This version uses LoadLibrary to obtain the functions from a dll
instead of compiling with urlmon.lib.  This allows compiling
without either the sdk and with an alternate compiler !(VC++6).
*/

using namespace std;


// prototype functions here
// This (or these) will need to either be moved to core.cpp or
// moved to a protype.h file.
bool DownloadFile(LPCTSTR URL , LPCTSTR LocalFilename); // makes sense

// URLDownloadToFile requires a long return value

// typedef seems to be needed here for defining MYPROC 
// as a long pointer

// in most examples I find, you don't need to declare
// all of the arguments like I've done here.
// However without this, it won't compile. 

// 
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
	system("pause"); // DevCPP complains about implicit
	                    // declaration
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
	hinstLib = LoadLibrary("urlmon.dll");

  // If the handle is valid, try to get the function address.
  if(hinstLib != NULL)
  { 
  
    // This is one part that I MAJORLY suspect of causing the ESP
    // problem mentioned at the beginning of this file.
    
	// get pointer to URLDownloadToFile
	ProcAdd = (MYPROC) GetProcAddress(hinstLib, "URLDownloadToFileA");
	
		// If the function address is valid, call the function.

	   if (NULL != ProcAdd) 
        {
            fRunTimeLinkSuccess = TRUE;

	    
			cout << "Value of URL: " << URL << endl;
			cout << "Value of LocalFilename: " << LocalFilename << endl;


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

	// RETURN VALUES:
    // S_OK               Operation Succeeded
    // E_OUTOFMEMORY      The buffer length is invalid or there was insufficient memory _
    //                    to complete the operation.

    // now that function has been called, let's see what
    // it returned...
    
    // I'm assuming the values above are of type long, as that's
    // what VB uses as a return value when using that API call.

    // It works, because it'll tell you if the URL is unreachable.
    // Even if it bombs out right afterwords...
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

  Solution to problem mentioned in beginning of code

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

*/
