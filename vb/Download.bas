Attribute VB_Name = "Download"
'API Function for downloading files with no dialog boxes, which is good for background downloading
Public Function DownloadFile(URL As String, _
    LocalFilename As String) As Boolean
        
    Dim lngRetVal As Long
    
    lngRetVal = URLDownloadToFile(0, URL, LocalFilename, 0, 0)
    
    If lngRetVal = 0 Then DownloadFile = True
    'RETURN VALUES:
    'S_OK               Operation Succeeded
    'E_OUTOFMEMORY      The buffer length is invalid or there was insufficient memory _
                        to complete the operation.
End Function

