Attribute VB_Name = "iniAccess"
Public Function Get_Version(Version As String) As Boolean
Dim ret As Long
Dim Temp As String * 50 'This is the returned string

Dim lpAppName As String, DatKeyName As String, lpDefault As String, lpFileName As String
lpAppName = "SuperDat-IA32" 'Section Name to search
DatKeyName = "DATVersion" 'KeyName
lpDefault = vbNullString 'Returned value if it cannot find key
lpFileName = "C:\updates\mcafee\update.ini" 'Where to get (read) the .ini file

'MsgBox lpAppName, vbOKOnly, "lpAppName"
'MsgBox DatKeyName, vbOKOnly, "DatKeyName"
'MsgBox lpDefault, vbOKOnly, "lpDefault"
'MsgBox lpFileName, vbOKOnly, "lpFileName"


' Read Update.ini with above search guidelines; used to get Version Variable
ret = GetPrivateProfileString(lpAppName, DatKeyName, lpDefault, Temp, Len(Temp), lpFileName)
'MsgBox ret, vbOKOnly, "Contents of ini Reading"
If ret = 0 Then
 MsgBox Err.LastDllError, vbCritical, "Sdat .ini file access" 'Uncomment for debugging
   
   Get_Version = True 'Errors have occured, set status to Error=True
     
Else
 'This variable plays a big part in this program; read closely...
  Version = Trim(Temp)
  Get_Version = False 'Errors did not occur
  'MsgBox Version, vbOKOnly, "Inside of Version Assignment"
End If

End Function


Public Function Get_sdatPrefix() As Boolean


'THIS SECTION OF CODE DEFINES THE PREFIX FOR SDAT41xx.EXE FILE

Dim ret As Long
Dim Temp As String * 50 'This is the returned string

Dim lpAppName As String, DatKeyName As String, lpDefault As String, lpFileName As String
lpAppName = "SDAT" 'Section Name to search
DatKeyName = "Prefix" 'KeyName
lpDefault = vbNullString 'Returned value if it cannot find key
lpFileName = "C:\progra~1\dst\config\settings.ini" 'Where to get (read) the .ini file

' Read Update.ini with above search guidelines; used to get sdatPrefix Variable
ret = GetPrivateProfileString(lpAppName, DatKeyName, lpDefault, Temp, Len(Temp), lpFileName)

If ret = 0 Then
  'MsgBox Err.LastDllError, vbCritical, "Sdat Prefix .ini file access"
  
  Get_sdatPrefix = True 'Errors have occured, set status to Error=True

Else
  sUpdate.sdatPrefix.Caption = Trim(Temp)
  Get_sdatPrefix = False
End If

End Function

Public Function Get_zipdatPrefix() As Boolean

'THIS SECTION OF CODE DEFINES THE PREFIX FOR DAT-41xx.ZIP FILE

Dim ret As Long
Dim Temp As String * 50 'This is the returned string

Dim lpAppName As String, DatKeyName As String, lpDefault As String, lpFileName As String
lpAppName = "ZIP" 'Section Name to search
DatKeyName = "Prefix" 'KeyName
lpDefault = vbNullString 'Returned value if it cannot find key
lpFileName = "C:\progra~1\dst\config\settings.ini" 'Where to get (read) the .ini file

' Read Update.ini with above search guidelines; used to get zipdatPrefix Value
ret = GetPrivateProfileString(lpAppName, DatKeyName, lpDefault, Temp, Len(Temp), lpFileName)
If ret = 0 Then
 'MsgBox Err.LastDllError, vbCritical, "zipdat Prefix .ini file access" 'Uncomment for debugging
 
 Get_zipdatPrefix = True 'Errors have occured, set status to Error=True
 
Else
  'Dim zipdatPrefix As String
  sUpdate.zipdatPrefix.Caption = Trim(Temp)
  Get_zipdatPrefix = False 'Free of errors
End If

End Function

Public Function Get_McAfeeURL(DatURL As String) As Boolean

'THIS SECTION OF CODE OBTAINS THE URL FOR REMOTE UPDATE FILES

Dim ret As Long
Dim Temp As String * 50 'This is the returned string

Dim lpAppName As String, DatKeyName As String, lpDefault As String, lpFileName As String
lpAppName = "Dats" 'Section Name to search
DatKeyName = "McAfeeURL" 'KeyName
lpDefault = vbNullString 'Returned value if it cannot find key
lpFileName = "C:\progra~1\dst\config\settings.ini" 'Where to get (read) the .ini file

' Read Update.ini with above search guidelines; used to get sdatPrefix Variable
ret = GetPrivateProfileString(lpAppName, DatKeyName, lpDefault, Temp, Len(Temp), lpFileName)

If ret = 0 Then
  'MsgBox Err.LastDllError, vbCritical, "Sdat Prefix .ini file access"
  Get_McAfeeURL = True 'Errors have occured, set status to Error=True

Else
  DatURL = Trim(Temp)
  Get_McAfeeURL = False
End If

End Function


Public Function Get_DatFolder(DatFolder As String) As Boolean

'THIS SECTION OF CODE OBTAINS THE LOCATION FOR DOWNLOADED UPDATE FILES

Dim ret As Long
Dim Temp As String * 50 'This is the returned string

Dim lpAppName As String, DatKeyName As String, lpDefault As String, lpFileName As String
lpAppName = "Dats" 'Section Name to search
DatKeyName = "DatFolder" 'KeyName
lpDefault = vbNullString 'Returned value if it cannot find key
lpFileName = "..\settings.ini" 'Where to get (read) the .ini file

' Read Update.ini with above search guidelines; used to get sdatPrefix Variable
ret = GetPrivateProfileString(lpAppName, DatKeyName, lpDefault, Temp, Len(Temp), lpFileName)

If ret = 0 Then
  'MsgBox Err.LastDllError, vbCritical, "Sdat Prefix .ini file access"
  Get_DatFolder = True 'Errors have occured, set status to Error=True

Else
  DatURL = Trim(Temp)
  Get_DatFolder = False
End If

End Function



