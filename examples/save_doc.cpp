#ifndef _SAVE_DOC_CPP
#define _SAVE_DOC_CPP

//[save_doc_example

#include <boost/document.hpp>
#include <string>

int main(int argc, char **argv) {
    boost::document doc("../test/Test2.ods");
    doc.open_document();
    boost::sheet s = doc["Anurag"];
    s.rename_sheet("Vatika");
    s.rename_sheet("Anurag");
    doc.save_document();
    return 0;
}

//] [/save_doc_example]

#endif
