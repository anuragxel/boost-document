#ifndef _BASIC_CPP
#define _BASIC_CPP

//[basic_example

#include <boost/document.hpp>

int main(int argc, char **argv) {
  boost::document doc("../test/Test1.ods");
  doc.open_document();
  doc.export_document(boost::document_file_format::CSV);
  return 0;
}

//] [/basic_example]

#endif
