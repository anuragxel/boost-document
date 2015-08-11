#ifndef _SAVE_DOC_CPP
#define _SAVE_DOC_CPP

//[save_doc_example

#include <boost/document.hpp>

int main(int argc, char **argv) {
    boost::document doc("/foo/bar/file.ods");
    doc.open_document();
    boost::sheet s = doc["Anurag"];
    s.rename_sheet("Vatika");
    doc.save_document();
    return 0;
}

//] [/save_doc_example]

#endif
