#ifndef _CELL_BASIC_CPP
#define _CELL_BASIC_CPP

//[cell_basic_example

#include <boost/document.hpp>

int main(int argc, char **argv) {
    boost::document doc("/foo/bar/file.ods");
    doc.open_document();
    boost::sheet s = doc.get_sheet("Anurag");

    boost::cell c = s.get_cell(4,5); // row = 4, column = 5
    c.set_string("Boost");
    if(c.get_content_type() == boost::cell_content_type::STRING) {
        std::cout << c.get_string() << std::endl;
    }

    if(s["B2"].empty()) {
        s["B2"] = 2.56;
    }

    doc["Vatika"][7][2] = "Anurag";
    boost::sheet new = doc["Vatika"];

    new["C3"] = 0.5; // row = 4, column = 2
    new["C4"] = 0.5;
    new["C5"].set_formula("=C3+C4");

    std::cout << doc["Vatika"]["C5"].get_value() << std::endl;

    new["D8"] = c; // Assignment
    if(new["D8"].get_string() == "Boost") {
        std::cout << "Yay!" << std::endl;
    }

    doc.save_document();
    return 0;
}

//] [/cell_basic_example]

#endif
