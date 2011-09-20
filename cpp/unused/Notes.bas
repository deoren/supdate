Attribute VB_Name = "GeneralNotes"
' All old update files are deleted every time this is ran.  Current ones are left
' Log File Function has been added [10-23-01]
' Functions have been added; cleaned up code [10-23-01]
' Add the 'Hiding your program in the ctrl-Alt-Del list' function
' Add function to empty Temporary Internet Files everytime program is run
           
' *** CODE WIDTH FOR PRINTOUTS ARE 100 CHARACTERS WIDE MAX *** (For neatness)
'               This line shows max width                                                          #
'FOR THE FIRST IMPLEMENTED LAB TESTING, TWO LABELS HAVE BEEN ADDED _
 NAMED zipdatPrefix & sdatPrefix, to replace the variables that will not accept _
 a value without quotation marks [""]

' Original code used in form, before ported to Sub Main and modified
'If App.PrevInstance Then
    'This bit of code below came from "Hardcore Visual Basic"
   ' Dim sTitle As String
    'Save my title
    'sTitle = Me.Caption
    'Change my title bar so I won't activate myself
    'Me.Caption = Hex$(Me.hWnd)
    'Activate other instance
    'AppActivate sTitle
    'Terminate myself
    'End
    'End If
