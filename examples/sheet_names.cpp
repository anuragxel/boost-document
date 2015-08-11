#ifndef _SHEET_NAMES_EXAMPLE_CPP
#define _SHEET_NAMES_EXAMPLE_CPP

//[sheet_names_example

#include <boost/document.hpp>

int main(int argc, char **argv) {
    boost::document doc("/foo/bar/file.ods");
    doc.open_document();
    std::size_t count = doc.sheet_count();
    for(int i = 0 ; i < count; i++) {
        boost::sheet s = doc.get_sheet(i);
        std::cout << "#" << i << "\t" << s.sheet_name() << std::endl;
    }
    return 0;
}

//] [/sheet_names_example]

#endif
