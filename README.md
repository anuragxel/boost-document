boost-generic-document-library
------------------------------

This is not a source for an official boost library and is
not reviewed, however meant as a prototype to be exhibit 
as a proof of concept to the community hoping to develop and submit
a final library to formal review for inclusion.

To install this library, you need to perform the following steps -

On Linux
--------

1.  sudo apt-get install libreoffice-dev

2.  cd /usr/lib/libreoffice/sdk

3.  source setsdkenv\_unix.sh       # This sets the appropriate environment variables

4.  cd ~/libreoffice\_sdk           # The folder name may vary

5.  cppumaker -Gc -O"$OO\_SDK\_OUT/include/" /usr/lib/ure/share/misc/types.rdb /usr/lib/libreoffice/program/types/offapi.rdb /usr/lib/libreoffice/program/types/oovbaapi.rdb         # Add -BUCR after -Gc if neccessary. You can also run an example in sdk directory for the same effect.

6.  cd boost\_1\_57\_0/libs/ 	# The folder name may vary, it is your boost directory which you downloaded from sourceforge.

7.  git clone https://github.com/anuragxel/boost-generic-document-library.git document

8.  cd document/build

9.  ../../../b2 cxxflags="-I$OO\_SDK\_OUT/include/"

10. cd ../test

11. chmod 000 Test3.ods #This is just to make tests run effectively

12. soffice "--accept=socket,host=localhost,port=2083;urp;StarOffice.ServiceManager" &  #Running the libreoffice server instance

13. ../../../b2 cxxflags="-I$OO\_SDK\_OUT/include/"   # This will run the test

On Windows
----------

1. Install both LibreOffice 4.4 and LibreOffice 4.4 SDK by downloading them from the official website.

2. Open Your Command Prompt, go to C:\\Program Files (x86)\\LibreOffice 4\\sdk and run setsdkenv_windows.bat and provide the necessary paths. Install cat, sed, zip, 

3. Add C:\\Program Files (x86)\\LibreOffice 4\\URE\\bin to the system PATH

4. Go to C:\\Program Files (x86)\\LibreOffice 4\\sdk\\bin and run the following command to generate the includes,
   cppumaker.exe -Gc -O"$OO_SDK_OUT\\include" "C:\\Program Files (x86)\\LibreOffice 4\\URE\\misc\\types.rdb" "C:\\Program Files (x86)\\LibreOffice 4\\program\\types\\oovbaapi.rdb" "C:\\Program Files (x86)\\Libreoffice 4\\program\\types\\offapi.rdb"

5. Change directory to the boost libs directory (assuming you have already run bootstrap.bat, else run it now)

6. Open a Git Bash instance and clone 
	git clone https://github.com/anuragxel/boost-generic-document-library.git document 

7. In the cmd instance, cd document/build

8. Run Commands nearly same as linux. :) However, you might need to start the soffice server manually. 