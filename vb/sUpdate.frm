VERSION 5.00
Begin VB.Form sUpdate 
   BackColor       =   &H00000000&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Update Server [Build 013]"
   ClientHeight    =   1860
   ClientLeft      =   15
   ClientTop       =   4140
   ClientWidth     =   4755
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   Icon            =   "sUpdate.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   MousePointer    =   3  'I-Beam
   Moveable        =   0   'False
   ScaleHeight     =   0
   ScaleWidth      =   0
   ShowInTaskbar   =   0   'False
   Visible         =   0   'False
   Begin VB.Label zipdatPrefix 
      BackStyle       =   0  'Transparent
      Caption         =   "ZipdatPrefix"
      ForeColor       =   &H0000C000&
      Height          =   495
      Left            =   2160
      MousePointer    =   2  'Cross
      TabIndex        =   3
      Top             =   840
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.Label sdatPrefix 
      BackStyle       =   0  'Transparent
      Caption         =   "sdatPrefix"
      ForeColor       =   &H00FF0000&
      Height          =   495
      Left            =   2160
      MousePointer    =   2  'Cross
      TabIndex        =   2
      Top             =   360
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Status"
      ForeColor       =   &H00FFFFFF&
      Height          =   195
      Left            =   120
      MousePointer    =   2  'Cross
      TabIndex        =   1
      Top             =   960
      Width           =   450
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "DST Consulting Services"
      ForeColor       =   &H00FFFFFF&
      Height          =   195
      Left            =   120
      MousePointer    =   2  'Cross
      TabIndex        =   0
      Top             =   480
      Width           =   1770
   End
End
Attribute VB_Name = "sUpdate"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Contents of sUpdate

