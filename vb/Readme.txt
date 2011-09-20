Oct5th, 2k1


Make sure to Read the DATVersion Key for the newest version, load that key value into an 
integer variable, - 1 (to get version of old dats) and check for that dat file.  If it is
found, then delete it, otherwise continue on.


Also, when creating the Config.exe program, make sure to include the option for adding
"Del C:\windows\tempor~1\*.*"

This can be done by appending to Autoexec.bat or by adding a small program to the "RUN"
section of the Registry.  The likely solution is by adding the prog. to the RUN section.