Attribute VB_Name = "sUpdateAPIs"
Public Declare Function URLDownloadToFile Lib "urlmon" Alias _
    "URLDownloadToFileA" (ByVal pCaller As Long, _
    ByVal szURL As String, _
    ByVal szFileName As String, _
    ByVal dwReserved As Long, _
    ByVal lpfnCB As Long) As Long


Public Declare Function WritePrivateProfileString Lib "Kernel32" Alias _
    "WritePrivateProfileStringA" (ByVal lpApplicationname As String, _
    ByVal lpKeyName As Any, _
    ByVal lsString As Any, _
    ByVal lplFilename _
    As String) As Long

'Public Declare Function GetPrivateProfileInt Lib "kernel32" Alias "GetPriviteProfileIntA" _
'(ByVal lpApplicationname As String, ByVal lpKeyName As String, ByVal nDefault As Long, ByVal _
'lpFileName As String) As Long

Public Declare Function GetPrivateProfileString Lib "Kernel32" _
Alias "GetPrivateProfileStringA" (ByVal lpApplicationname As String, _
ByVal lpKeyName As String, _
ByVal lpDefault As String, _
ByVal lpReturnedString As String, _
ByVal nSize As Long, _
ByVal lpFileName As String) As Long

'Public Const RSP_SIMPLE_SERVICE = 1
'Public Const RSP_UNREGISTER_SERVICE = 0
'Public Declare Function GetCurrentProcessId Lib "kernel32" () As Long
'Public Declare Function RegisterServiceProcess Lib "kernel32" _
(ByVal dwProcessID As Long, ByVal dwT) As Long

Public Declare Sub Sleep Lib "Kernel32" (ByVal dwMilliseconds As Long)


