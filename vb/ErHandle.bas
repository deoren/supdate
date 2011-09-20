Attribute VB_Name = "DatErrorHandler"
Public Function sdatErrorHandle()

If sdatFile = False Then 'If first try failed, then...
MsgBox Err.LastDllError, vbCritical, "DownloadFile sdatFile" 'LastDLLError is used because of API
Label1.Caption = "Trying Alternate sdat File: " & sdatverAlt1
'Here is the first Alternate attempt
sdatFile2 = DownloadFile("ftp://ftp.mcafee.com/pub/antivirus/superdat/intel/" & sdatverAlt1, _
    "C:\updates\McAfee\" & sdatverAlt1) = True
Else
Label1.Caption = "Sdat File Download Successful"
GoTo ZipDatCheck 'If first Sdat download was successful on first try, then go try the dat-41xx.zip
End If

If sdatFile2 = False Then 'If the first Alternate download attempt failed...
Label1.Caption = "Trying Alternate sdatFile #2: " & sdatverAlt2
sdatFile3 = DownloadFile("ftp://ftp.mcafee.com/pub/antivirus/superdat/intel/" & sdatverAlt2, _
    "C:\updates\McAfee\" & sdatverAlt2) = True
Else
Label1.Caption = "Alternate Download Was Successful"
GoTo ZipDatCheck
End If

If sdatFile3 = False Then
Label1.Caption = "Trying Alternate sdatFile #3: " & sdatverAlt3
sdatFile4 = DownloadFile("ftp://ftp.mcafee.com/pub/antivirus/superdat/intel/" & sdatverAlt3, _
    "C:\updates\McAfee\" & sdatverAlt3) = True
Else
Label1.Caption = "Alternate Download Was Successful"
GoTo ZipDatCheck
End If

If sdatFile4 = False Then
Label1.Caption = "Trying Alternate sdatFile #4: " & sdatverAlt3
sdatFile5 = DownloadFile("ftp://ftp.mcafee.com/pub/antivirus/superdat/intel/" & sdatverAlt4, _
    "C:\updates\McAfee\" & sdatverAlt4) = True
Else
Label1.Caption = "Alternate Download Was Successful"
GoTo ZipDatCheck
End If

If sdatFile5 = False Then
Label1.Caption = "Alternate Download Attempts Could Not Be Completed"
'Dim sdatError As Boolean
sdatError = True
Sleep 3000 'Pauses program execution for 3000 milliSeconds
GoTo EndOfProgram
End If

End Function

Public Function zipdatErrorHandle()
If ZipdatFile = False Then 'If first try failed, then...
MsgBox Err.LastDllError, vbCritical, "DownloadFile ZipdatFile"
Label1.Caption = "Trying Alternate Zipdat File: " & zipdatverAlt1
'Here is the first Alternate attempt
ZipdatFile2 = DownloadFile("ftp://ftp.mcafee.com/pub/datfiles/english/" & zipdatverAlt1, _
"C:\updates\McAfee\" & zipdatverAlt1) = True
Else
Label1.Caption = "Zipdat File Download Successful"
GoTo EndOfProgram 'If first Sdat download was successful on first try, then end
End If

If ZipdatFile2 = False Then 'If the first Alternate download attempt failed...
Label1.Caption = "Trying 2nd Alternate Zipdat File: " & zipdatverAlt2
ZipdatFile3 = DownloadFile("ftp://ftp.mcafee.com/pub/datfiles/english/" & zipdatverAlt2, _
"C:\updates\McAfee\" & zipdatverAlt2) = True
Else
Label1.Caption = "Alternate Download Was Successful"
GoTo EndOfProgram
End If


If ZipdatFile3 = False Then 'If the 2nd Alternate download attempt failed...
Label1.Caption = "Trying 3rd Alternate Zipdat File: " & zipdatverAlt3
ZipdatFile4 = DownloadFile("ftp://ftp.mcafee.com/pub/datfiles/english/" & zipdatverAlt3, _
"C:\updates\McAfee\" & zipdatverAlt3) = True
Else
Label1.Caption = "Alternate Download Was Successful"
GoTo EndOfProgram
End If

If ZipdatFile4 = False Then 'If the 3rd Alternate download attempt failed...
Label1.Caption = "Trying 4th Alternate Zipdat File: " & zipdatverAlt4
ZipdatFile5 = DownloadFile("ftp://ftp.mcafee.com/pub/datfiles/english/" & zipdatverAlt4, _
"C:\updates\McAfee\" & zipdatverAlt4) = True
Else
Label1.Caption = "Alternate Download Was Successful"
GoTo EndOfProgram
End If

If ZipdatFile5 = False Then
Label1.Caption = "Zipdat File Download Could Not Be Completed"
'Dim zipdatError As Boolean
zipdatError = True
End If
Sleep 3000
End Function



