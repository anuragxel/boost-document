boost-generic-document-library
------------------------------

This is not a source for an official boost library and is
not reviewed, however meant as a prototype to be exhibit 
as a proof of concept to the community hoping to submit the
final library to formal review for inclusion.

To install this library, you need to perform the following steps - 

1.  sudo apt-get install libreoffice-dev

2.  cd /usr/lib/libreoffice/sdk

3.  source setsdkenv\_unix.sh

4.  cd ~/libreoffice\_sdk           (The folder name may vary)

5.  cppumaker -Gc -BUCR -O"$OO\_SDK\_OUT/include/" /usr/lib/ure/share/misc/types.rdb /usr/lib/libreoffice/program/types/offapi.rdb /usr/lib/libreoffice/program/types/oovbaapi.rdb

6.  cd boost\_1\_57\_0/libs/document/build

7.  ../../../b2 cxxflags= "-I$OO\_SDK\_OUT/include/"


