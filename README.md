boost-generic-document-library
------------------------------

This is not a source for an official boost library and is
not reviewed, however meant as a prototype to be exhibit 
as a proof of concept to the community hoping to develop and submit
a final library to formal review for inclusion.

To install this library, you need to perform the following steps - 

1.  sudo apt-get install libreoffice-dev

2.  cd /usr/lib/libreoffice/sdk

3.  source setsdkenv\_unix.sh       # This sets the appropriate environment variables

4.  cd ~/libreoffice\_sdk           # The folder name may vary

5.  cppumaker -Gc -BUCR -O"$OO\_SDK\_OUT/include/" /usr/lib/ure/share/misc/types.rdb /usr/lib/libreoffice/program/types/offapi.rdb /usr/lib/libreoffice/program/types/oovbaapi.rdb         #You can also run an example in sdk directory for the same effect.

6.  cd boost\_1\_57\_0/libs/ 	# The folder name may vary, it is your boost directory which you downloaded from sourceforge.

7.  git clone https://github.com/anuragxel/boost-generic-document-library.git document

8.  cd document/build

9.  ../../../b2 cxxflags="-I$OO\_SDK\_OUT/include/"

10. cd ../test

11. chmod 000 Test3.ods #This is just to make tests run effectively

12. soffice "--accept=socket,host=localhost,port=2083;urp;StarOffice.ServiceManager" &  #Running the libreoffice server instance

13. ../../../b2 cxxflags="-I$OO\_SDK\_OUT/include/"   # This will run the test


