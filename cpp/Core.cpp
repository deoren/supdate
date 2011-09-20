Attribute VB_Name = "Core"
'   GENERAL NOTES ABOUT PROGRAM
'   See "Notes.bas" for info
Option Explicit

Sub Main()

'This section of code prevents more than one instance from running
If App.PrevInstance Then
    'This bit of code below came from "Hardcore Visual Basic"
    Dim sTitle As String
    'Save my title
    sTitle = sUpdate.Caption
    'Change my title bar so I won't activate myself
    sUpdate.Caption = Hex$(sUpdate.hWnd)
    'Activate other instance
    AppActivate sTitle
    'Terminate myself
    End
    End If
   

'Dim DatURL As String, DatFolder As String
'Dim URL_Location As Boolean, Dat_Location As Boolean

'URL_Location = Get_McAfeeURL(DatURL) 'Get Download Location
'MsgBox DatURL, vbOKOnly, "Contents of DatURL"
'If URL_Location = False Then
'Dim ini_McafeeURL_Error As Boolean
'ini_McafeeURL_Error = True
'GoTo EndOfProgram
'End If

'Dat_Location = Get_DatFolder(DatFolder)
'If Dat_Location = False Then
'Dim ini_DatFolder_Error As Boolean
'ini_DatFolder_Error = True
'GoTo EndOfProgram
'End If


' *****************************************************************************
Dim sFile As String, FileList As String
Dim ret As Long
Dim Temp As String * 50 'This is the returned string

' Get update.ini off of McAfee's FTP Server
FileList = DownloadFile("ftp://ftp.mcafee.com/pub/datfiles/english/update.ini", _
           "C:\updates\Mcafee\update.ini") = True
If FileList = False Then
'MsgBox Err.LastDllError, vbCritical, "DownloadFile Update.ini" 'Uncomment for troubleshooting
Dim iniDownloadError As Boolean
iniDownloadError = True 'This lets the error handler know that the ini file download _
                        had errors
GoTo EndOfProgram
End If
'*******************************************************************************


' Create Variables for iniAccess Functions to use
'Dim lpAppName As String, DatKeyName As String, lpDefault As String, lpFileName As String
Dim ini_McAfee_Error As Boolean, Version As String
Dim ini_zipdat_Error As Boolean, ini_sdat_Error As Boolean

ini_McAfee_Error = Get_Version(Version)
'MsgBox Version, vbOKOnly, "Version Variable Contents"

'MsgBox ini_McAfee_Error, vbOKOnly, "ini_McAfee_Error Contents"
If ini_McAfee_Error = True Then 'Which means Function didn't work
' What is this really asking?  Is this asking "If the Function doesn't work, or does work?
' If a function is called, and completed, it is true, right? TRUE
GoTo EndOfProgram
End If

ini_sdat_Error = Get_sdatPrefix()
'MsgBox ini_sdat_Error, vbOKOnly, "Checking Get_sdatPrefix Function Calls"
If ini_sdat_Error = True Then 'Which means Function didn't work
GoTo EndOfProgram
End If

ini_zipdat_Error = Get_zipdatPrefix()
'MsgBox ini_zipdat_Error, vbOKOnly, "Checking Get_zipdatPrefix Function Calls"
If ini_zipdat_Error = True Then 'Which means Function didn't work
GoTo EndOfProgram
End If

'MsgBox Version, vbInformation, "Version Contents" 'Added for troubleshooting
'*********************************************************************************************

'MsgBox sdatPrefix.Caption, vbCritical, "Check sdatPrefix"  'Troubleshooting Line



'MsgBox zipdatPrefix.Caption, vbCritical, "zipdatPrefix"  'Troubleshooting
'******************************************************************************************

'-------------------------------------------------------------------------------------------------
Dim sdatverAlt1 As String, sdatverAlt2 As String, zipdatverAlt1 As String, zipdatverAlt2 As String
Dim sdatverAlt3 As String, sdatverAlt4 As String, zipdatverAlt3 As String, zipdatverAlt4 As String
Dim Box As Integer
Box = Version 'This works because the "Version" string holds an integer equivalent value
sdatverAlt1 = sUpdate.sdatPrefix.Caption & Box + 2 & ".exe"
sdatverAlt2 = sUpdate.sdatPrefix.Caption & Box + 1 & ".exe" 'Alternate Files; Counting Up
sdatverAlt3 = sUpdate.sdatPrefix.Caption & Box - 1 & ".exe"
sdatverAlt4 = sUpdate.sdatPrefix.Caption & Box - 2 & ".exe" 'Alternate Files for download if McAfee
zipdatverAlt1 = sUpdate.zipdatPrefix.Caption & Box + 2 & ".zip"
zipdatverAlt2 = sUpdate.zipdatPrefix.Caption & Box + 1 & ".zip" 'doesn'thave their .ini file
zipdatverAlt3 = sUpdate.zipdatPrefix.Caption & Box - 1 & ".zip" 'updated with their correct
zipdatverAlt4 = sUpdate.zipdatPrefix.Caption & Box - 2 & ".zip" 'available dats
'sdatverAlt1 = "sdat" & Box - 1 & ".exe"
'sdatverAlt2 = "sdat" & Box - 2 & ".exe"
'zipdatverAlt1 = "dat-" & Box - 1 & ".zip"
'zipdatverAlt2 = "dat-" & Box - 2 & ".zip"
'-------------------------------------------------------------------------------------------------
'MsgBox sdatverAlt1, vbCritical, "sdatverAlt1"
'MsgBox sdatverAlt2, vbCritical, "sdatverAlt2"
'MsgBox sdatverAlt3, vbCritical, "sdatverAlt3"
'MsgBox sdatverAlt4, vbCritical, "sdatverAlt4"
'MsgBox zipdatverAlt1, vbCritical, "zipdatverAlt1"     'These are added here for troubleshooting
'MsgBox zipdatverAlt2, vbCritical, "zipdatverAlt2"
'MsgBox zipdatverAlt3, vbCritical, "zipdatverAlt3"
'MsgBox zipdatverAlt4, vbCritical, "zipdatverAlt4"
Dim sdatVer  As String
sdatVer = sUpdate.sdatPrefix.Caption & Box & ".exe"
'sdatVer = "sdat" & Box & ".exe"

'MsgBox sdatVer, vbInformation, "sdatVer Variable Contents" 'Uncomment this line for debugging

SdatCheck:
Dim sdatNew As String, sdatExist As String
'Tests for the T/F condition of "Is the sdat file on file current with website?"
sdatNew = Dir("C:\updates\McAfee\" & sdatVer)

If sdatNew = "" Then
'Get rid of all old sdat files
sdatExist = Dir("C:\updates\McAfee\sdat*.exe")
End If

If sdatExist <> "" Then
Kill "C:\updates\McAfee\sdat*.exe"
'THEN DOWNLOAD NEW VERSION
End If

If sdatNew = sdatVer Then
GoTo ZipDatCheck
End If

SdatDownload:
'DOWNLOADS LATEST SUPERDAT
Dim sdatFile As Boolean
sdatFile = DownloadFile("ftp://ftp.mcafee.com/pub/antivirus/superdat/intel/" & sdatVer, _
    "C:\updates\McAfee\" & sdatVer) = True

'############################################################################
sdatErrorHandler:
If sdatFile = False Then
Dim sdatFile2 As Boolean, sdatFile3 As Boolean
Dim sdatFile4 As Boolean, sdatFile5 As Boolean
'If first try failed, then...
'MsgBox Err.LastDllError, vbCritical, "DownloadFile sdatFile" 'LastDLLError is used because of API

'Here is the first Alternate attempt
sdatFile2 = DownloadFile("ftp://ftp.mcafee.com/pub/antivirus/superdat/intel/" & sdatverAlt1, _
    "C:\updates\McAfee\" & sdatverAlt1) = True
Else

GoTo ZipDatCheck 'If first Sdat download was successful on first try, then go try the dat-41xx.zip
End If

If sdatFile2 = False Then 'If the first Alternate download attempt failed...

sdatFile3 = DownloadFile("ftp://ftp.mcafee.com/pub/antivirus/superdat/intel/" & sdatverAlt2, _
    "C:\updates\McAfee\" & sdatverAlt2) = True
Else

GoTo ZipDatCheck
End If

If sdatFile3 = False Then 'If the second Alternate download attempt failed...
sdatFile4 = DownloadFile("ftp://ftp.mcafee.com/pub/antivirus/superdat/intel/" & sdatverAlt3, _
    "C:\updates\McAfee\" & sdatverAlt3) = True
Else
GoTo ZipDatCheck
End If

If sdatFile4 = False Then 'If the third Alternate download attempt failed...
sdatFile5 = DownloadFile("ftp://ftp.mcafee.com/pub/antivirus/superdat/intel/" & sdatverAlt4, _
    "C:\updates\McAfee\" & sdatverAlt4) = True
Else

GoTo ZipDatCheck
End If

If sdatFile5 = False Then
Dim sdatError As Boolean
sdatError = True

GoTo EndOfProgram
End If
'############################################################################

ZipDatCheck:
Dim ZipdatVer As String
ZipdatVer = sUpdate.zipdatPrefix.Caption & Box & ".zip"
'ZipdatVer = "dat-" & Box & ".zip"
'MsgBox ZipdatVer, vbInformation, "ZipdatVer Variable Contents" Uncomment for debugging

Dim zipdatNew As String, zipdatExist As String
'Tests for the T/F condition of "Are there .zip (dat-41xx.zip) files here?"
zipdatNew = Dir$("C:\updates\McAfee\" & ZipdatVer) '= True
If zipdatNew = "" Then
zipdatExist = Dir$("C:\updates\McAfee\*.zip")
End If

If zipdatExist <> "" Then
'Get rid of all old sdat files
Kill "C:\updates\McAfee\*.zip"
End If

If zipdatNew = ZipdatVer Then
GoTo EndOfProgram
End If


ZipdatDownload:
Dim ZipdatFile As Boolean
ZipdatFile = DownloadFile("ftp://ftp.mcafee.com/pub/datfiles/english/" & ZipdatVer, _
"C:\updates\McAfee\" & ZipdatVer) = True

'############################################################################
ZipdatErrorHandler:
If ZipdatFile = False Then 'If first try failed, then...
Dim ZipdatFile2 As Boolean, ZipdatFile3 As Boolean
Dim ZipdatFile4 As Boolean, ZipdatFile5 As Boolean
'MsgBox Err.LastDllError, vbCritical, "DownloadFile ZipdatFile" 'Uncomment for debugging

'Here is the first Alternate attempt
ZipdatFile2 = DownloadFile("ftp://ftp.mcafee.com/pub/datfiles/english/" & zipdatverAlt1, _
"C:\updates\McAfee\" & zipdatverAlt1) = True
Else

GoTo EndOfProgram 'If first Sdat download was successful on first try, then end
End If

If ZipdatFile2 = False Then 'If the first Alternate download attempt failed...

ZipdatFile3 = DownloadFile("ftp://ftp.mcafee.com/pub/datfiles/english/" & zipdatverAlt2, _
"C:\updates\McAfee\" & zipdatverAlt2) = True
Else

GoTo EndOfProgram
End If

If ZipdatFile3 = False Then 'If the 2nd Alternate download attempt failed...

ZipdatFile4 = DownloadFile("ftp://ftp.mcafee.com/pub/datfiles/english/" & zipdatverAlt3, _
"C:\updates\McAfee\" & zipdatverAlt3) = True
Else

GoTo EndOfProgram
End If

If ZipdatFile4 = False Then 'If the 3rd Alternate download attempt failed...

ZipdatFile5 = DownloadFile("ftp://ftp.mcafee.com/pub/datfiles/english/" & zipdatverAlt4, _
"C:\updates\McAfee\" & zipdatverAlt4) = True
Else

GoTo EndOfProgram
End If

If ZipdatFile5 = False Then

Dim zipdatError As Boolean
zipdatError = True
End If

'############################################################################


EndOfProgram:

'This was added to provide functionality for logging errors.
'WHEN A METHOD IS FOUND TO DO SO, EXPORT THIS SECTION TO A MODULE
Dim LoggingFunction As Boolean
LoggingFunction = AddtoLogFile(zipdatError, sdatError, iniDownloadError, _
                  ini_McAfee_Error, ini_sdat_Error, ini_zipdat_Error)

If LoggingFunction = False Then
sUpdate.Show
sUpdate.Label1.Caption = "Error adding to Log File."
End If

' This is looking for False return values for the functions.
If ini_McAfee_Error = True Or ini_sdat_Error = True Or ini_zipdat_Error = True Then
'Or ini_DatFolder_Error = True Or ini_McafeeURL_Error = True Then
sUpdate.Label1.Caption = "Check file list to verify all required files are present"
sUpdate.Label2.Caption = "Errors have occured: Check (""Program Files\Dst\Log.txt"")"
sUpdate.BackColor = &HC0C0&
End If


'If ini_McAfee_Error = False And ini_sdat_Error = False And ini_zipdat_Error = False _
'And iniDownloadError = False And zipdatError = False And sdatError = False Then
'MsgBox "Everything works great!", vbExclamation, " Success!"
'End If

' These are actual errors if any of these variables contain "True"
If iniDownloadError = True Or zipdatError = True Or sdatError = True Then
sUpdate.Show
sUpdate.Label1.Caption = "Check internet connection to FTP.NAI.COM"
sUpdate.Label2.Caption = "Errors have occured:Check (""Program Files\Dst\Log.txt"")"
sUpdate.BackColor = &H80&
End If
Sleep 6000
TheEnd:

Unload sUpdate 'Unload the form
End Sub

