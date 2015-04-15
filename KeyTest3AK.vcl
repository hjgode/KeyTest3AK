<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: KeyTest3AK - Win32 (WCE ARMV4) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"ARMV4Rel/KeyTest3AK.res" /d UNDER_CE=420 /d _WIN32_WCE=420 /d "NDEBUG" /d "UNICODE" /d "_UNICODE" /d "WIN32_PLATFORM_PSPC=400" /d "ARM" /d "_ARM_" /d "ARMV4" /r "D:\C-Source\Active\KeyTest3AK\KeyTest3AK.rc"" 
Creating temporary file "C:\Temp\RSP368.tmp" with contents
[
/nologo /W3 /Oxs /D _WIN32_WCE=420 /D "WIN32_PLATFORM_PSPC=400" /D "ARM" /D "_ARM_" /D "ARMV4" /D UNDER_CE=420 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /FR"ARMV4Rel/" /Fo"ARMV4Rel/" /Gs8192 /GF /c 
"D:\C-Source\Active\KeyTest3AK\init.cpp"
"D:\C-Source\Active\KeyTest3AK\KeyTest3AK.cpp"
"D:\C-Source\Active\KeyTest3AK\listview.cpp"
"D:\C-Source\Active\KeyTest3AK\stdafx.cpp"
]
Creating command line "clarm.exe @C:\Temp\RSP368.tmp" 
Creating temporary file "C:\Temp\RSP369.tmp" with contents
[
corelibc.lib commctrl.lib coredll.lib aygshell.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:no /pdb:"ARMV4Rel/KeyTest3AK.pdb" /nodefaultlib:"libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib" /out:"ARMV4Rel/KeyTest3AK.exe" /subsystem:windowsce,4.20 /MACHINE:ARM 
".\ARMV4Rel\init.obj"
".\ARMV4Rel\KeyTest3AK.obj"
".\ARMV4Rel\listview.obj"
".\ARMV4Rel\stdafx.obj"
".\ARMV4Rel\KeyTest3AK.res"
]
Creating command line "link.exe @C:\Temp\RSP369.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
Command line warning D4002 : ignoring unknown option '/Gs8192'
init.cpp
KeyTest3AK.cpp
listview.cpp
stdafx.cpp
Generating Code...
Linking...




<h3>Results</h3>
KeyTest3AK.exe - 0 error(s), 1 warning(s)
</pre>
</body>
</html>
