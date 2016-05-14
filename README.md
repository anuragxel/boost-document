document-library
=================

This is not a source for an official boost library and is
not reviewed, however meant as a prototype to be exhibit
as a proof of concept to the community hoping to develop and submit
a final library to formal review for inclusion.

Documentation will be updated at the following link

http://anuragxel.github.io/boost-document/

Test results
============

@               | Build         | Tests coverage
----------------|-------------- | --------------
Master branch:  | [![Build Status](https://travis-ci.org/anuragxel/boost-document.svg?branch=master)](https://travis-ci.org/anuragxel/boost-document)  | [![Coverage Status](https://coveralls.io/repos/anuragxel/boost-document/badge.png?branch=master)](https://coveralls.io/r/anuragxel/boost-document?branch=master)


For Libre Office Users
======================

Compilers tested on - MSVC 12.0 and GCC 4.6.\*

To install this library, you need to perform the following steps -

On Linux
--------
```
	sudo apt-get install libreoffice-dev

	cd /usr/lib/libreoffice/sdk

	source setsdkenv_unix.sh       # This sets the appropriate environment variables

	cd ~/libreoffice_sdk           # The folder name may vary

	# types.rdb was earlier available in /usr/lib/ure/share/misc/types.rdb (pre-libreoffice 5)
	cppumaker -Gc -O"$OO_SDK_OUT/include/" /usr/lib/libreoffice/program/types.rdb /usr/lib/libreoffice/program/types/offapi.rdb /usr/lib/libreoffice/program/types/oovbaapi.rdb   # Add -BUCR after -Gc if neccessary. You can also run an example in sdk directory for the same effect.

	cd boost_1_57_0/libs/ 	# The folder name may vary, it is your boost directory which you downloaded from sourceforge.

	git clone https://github.com/anuragxel/boost-generic-document-library.git document

	cd document/build

	../../../b2

	cd ../test

	chmod 000 Test3.ods #This is just to make tests run effectively

	soffice "--accept=socket,host=localhost,port=2083;urp;StarOffice.ServiceManager" &  #Running the libreoffice server instance

	../../../b2   # This will run the test
```

On Windows
----------

1. Install both LibreOffice 4.4 and LibreOffice 4.4 SDK by downloading them from the official website.

2. Open Your Command Prompt, go to C:\Program Files (x86)\LibreOffice 4\sdk and run setsdkenv_windows.bat and provide the necessary paths. Install cat, sed, zip,

3. Add
	`C:\Program Files (x86)\LibreOffice 4\URE\bin`
   to the system PATH

4. Go to C:\Program Files (x86)\LibreOffice 4\sdk\bin and run the following command to generate the includes,
   `cppumaker.exe -Gc -O"$OO_SDK_OUT\include" "C:\Program Files (x86)\LibreOffice 4\URE\misc\types.rdb" "C:\Program Files (x86)\LibreOffice 4\program\types\oovbaapi.rdb" "C:\Program Files (x86)\Libreoffice 4\program\types\offapi.rdb"`

5. Change directory to the boost libs directory (assuming you have already run bootstrap.bat, else run it now)

6. Open a Git Bash instance and clone

	`git clone https://github.com/anuragxel/boost-generic-document-library.git document`

7. In the cmd instance,

	`cd document\build`

8. Run Commands nearly same as linux. :) However, you might need to start the soffice server manually.


For Micrsoft Office Users
=========================

**ONLY SUPPORTED IN WINDOWS**

You would need to have MSVC 12.0 (or higher) on your Windows Installation. (Untested on GCC or Clang).

1. Open a Git Bash instance and clone

	`git clone https://github.com/anuragxel/boost-generic-document-library.git document` at `$lib_path\libs`

2. In the bash instance,

	`cd $lib_path/libs/document/build`

3. run '../../../b2'

4. You may run the tests in `test` folder now using the same command as above.
