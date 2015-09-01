#ifndef _ROW_ITER_USAGE_CPP
#define _ROW_ITER_USAGE_CPP

//[row_iter_usage_example

#include <boost/document.hpp>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    boost::document doc("../test/Test2.ods");
    doc.open_document();

    boost::sheet s1 = doc["Anurag"];
    boost::row r = s1.get_row(3);

    std::fill(r.begin(), r.begin() + 50, 1);

    double sum = 0;
    const boost::row_iterator end(r.begin() + 50);
    for (auto it = r.begin(); it != end; ++it) {
        sum += (*it).get_value();
    }

    std::cout << "#sum " << sum << std::endl;

    return 0;
}

//] [/row_iter_usage_example]

#endif
