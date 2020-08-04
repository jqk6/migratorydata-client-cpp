set MD_FLAGS=/DSSL_DISABLED
@echo off

set CC_DIR="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC"

if not defined DevEnvDir (
    call %CC_DIR%\Auxiliary\Build\vcvars32.bat
)

set EX_LIBS=ws2_32.lib gdi32.lib advapi32.lib crypt32.lib user32.lib

%CC_DIR%\Tools\MSVC\14.26.28801\bin\Hostx86\x86\cl.exe %MD_FLAGS% /EHsc /I include /MD main.cpp %EX_LIBS% migratorydata-client-cpp-i586.lib /link /LIBPATH:lib\Release
