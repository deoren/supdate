// Notes: This will not compile using DevCPP, as
//          I don't have compatible libraries.

// These includes are used for testing purposes.  When full
// program has been developed, these can either be removed
// or commented out.

// #include <fstream>  // this OR iostream IS NEEDED for namespace std
#include <iostream> 
#include <windows.h> 
#include <stdlib.h>

// #include <urlmon.h> // for URLDownloadToFile function
// Was able to use urlmon.lib within the linker specs instead of above
// header file. 

using namespace std;


// prototype functions here
// This (or these) will need to either be moved to core.cpp or
// moved to a protype.h file.
bool DownloadFile(LPCTSTR URL , LPCTSTR LocalFilename);
// main will need to be removed.
int main()
{

	// this variable type like to have driven me nuts:LPCTSTR

	// ... returns a string of type LPCTSTR, 
	// that is, an unmanaged type

	// Purposely BAD Url for testing
	//LPCTSTR URL = "http://www.bobsapples.com/index.html";

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
	system("pause");
	return (0);

}  // end main function


// API Function for downloading files with no dialog boxes, 
// which is good for background downloading

// all original variable names have been kept intact, including
// capitalization

bool DownloadFile(LPCTSTR URL , LPCTSTR LocalFilename) 
{        
    // initialize variables    
    long lngRetVal;  // may initialize to something !0 
    
    
    // execute function and save results in variable
    lngRetVal = URLDownloadToFileA(0, URL, LocalFilename, 0, 0); 
    
	// RETURN VALUES:
    // S_OK               Operation Succeeded
    // E_OUTOFMEMORY      The buffer length is invalid or there was 
    // 			  insufficient memory to complete the operation.

	if (lngRetVal==S_OK)
	{
		return (true); // file successfully retrieved
	} 
	else
	{
		return (false); 
	}
        
} // end of DownloadFile Function

/* VB Example - may give ideas

Private Declare Function URLDownloadToFile Lib "urlmon" Alias _ 
"URLDownloadToFileA" (ByVal pCaller As Long, ByVal szURL As String, _
 ByVal szFileName As String, ByVal dwReserved As Long, ByVal lpfnCB _
 As Long) As Long

Public Function DownloadFile(URL As String, LocalFilename As String) _ 
As Boolean
    
    Dim lngRetVal As Long
    lngRetVal = URLDownloadToFile(0, URL, LocalFilename, 0, 0)
    If lngRetVal = 0 Then DownloadFile = True
End Function

Private Sub Form_Load()
    'example by Matthew Gates (Puff0rz@hotmail.com)
    DownloadFile "http://www.allapi.net", "c:\allapi.htm"
End Sub
*/
