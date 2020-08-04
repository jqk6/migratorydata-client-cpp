This is an example of a C++ client application using MigratoryData Client C++ API.

This C++ example application connects to the MigratoryData Server running at 
"127.0.0.1:8080", subscribes to the subject "/server/status" and displays
the messages received from the MigratoryData server. Also, it publishes messages
on the same subject.

You can edit the source code of this example application to connect to your instance 
of MigratoryData Server and subscribe / publish to your subjects. Then, use the build 
script "build.bat" to (re)compile the example application. 

REQUIREMENTS
------------

1. You need to have installed Visual Studio 2019 with C++ development

2. You might need to adapt the value of the variable "CC_DIR" of the script "build.bat" to reflect your setup

STRUCTURE
---------

The delivery package of this example has the following structure:

    - "lib" :
        The folder which contains the MigratoryData Client C++ API library.

    - "include" :
        The folder which contains the headers files of MigratoryData Client C++ API.

    - "build.bat" :
        The build script which is used to compile this example application on Windows.

    - "main.cpp"
    	The source code of this example application.
    	                 	                     
    - "README" :
        This file.
        	   
MODIFYING AND (RE)BUILDING THE SOURCE CODE
------------------------------------------

	1. Edit the source code file
	
	2. Run the "build.bat" to rebuild the source code for Windows
	
	3. Run the executable produced at Step 2.

