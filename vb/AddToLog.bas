Attribute VB_Name = "AddtoLog"
'This was added to provide functionality for logging errors.
'WHEN A METHOD IS FOUND TO DO SO, EXPORT THIS SECTION TO A MODULE
Public Function AddtoLogFile(zipdatError As Boolean, sdatError As Boolean, _
iniDownloadError As Boolean, ini_McAfee_Error As Boolean, ini_sdat_Error As Boolean, ini_zipdat_Error) As Boolean
On Error GoTo Prob
Dim Logfile As String ' This is the error report
Logfile = "C:\progra~1\dst\log.txt"
Open Logfile For Append As #1
Print #1, "...................................................."
'Print #1, "If you see nothing True under 'Errors... :' then everthing is working normally"
Print #1, "Update Server Version:   1.3.0.15"
Print #1, "Revision Date:           03-13-02"
Print #1, "Time: " & Format(Time, "hh:mm a/p")
Print #1, "Date: " & Date$
Print #1, "Error Downloading zipfile    : " & zipdatError
Print #1, "Error Downloading sdatfile   : " & sdatError
Print #1, "Error Downloading iniFile    : " & iniDownloadError
Print #1, "Error Accessing Update.ini   : " & ini_McAfee_Error
Print #1, "Error Accessing settings.ini : " & ini_zipdat_Error
Close
AddtoLogFile = True
GoTo EndOfFunction

Prob: ' This will only be assigned if there are problems
AddtoLogFile = False

EndOfFunction:
End Function

