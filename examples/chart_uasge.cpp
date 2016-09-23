#ifndef _CHART_USAGE_CPP
#define _CHART_USAGE_CPP

//[chart_usage_example

#include <boost/document.hpp>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    boost::document doc("../test/Test2.ods");
    doc.open_document();
    boost::sheet s = doc["Anurag"];

    s1[0][1] = "JAN";
    s1[0][2] = "FEB";
    s1[0][3] = "MAR";
    s1[0][4] = "APR";
    s1[0][5] = "MAY";

    s1[1][0] = "Smith";
    s1[1][1] = 42;
    s1[1][2] = 58.9;
    s1[1][3] = 23.5;
    s1[1][4] = 43.4;
    s1[1][5] = 44.5;

    s1[2][0] = "Jones";
    s1[2][1] = 21;
    s1[2][2] = 40.9;
    s1[2][3] = 57.5;
    s1[2][4] = 48.4;
    s1[2][5] = 34.5;

    s1[3][0] = "Brown";
    s1[3][1] = 31.45;
    s1[3][2] = 20.9;
    s1[3][3] = 32.5;
    s1[3][4] = 23.4;
    s1[3][5] = 64.5;


    boost::chart ch = s1.add_chart("QuaterlyChart", "A1:E4", 100, 3000, 20000, 8000, boost::chart_type::PIE);
    ch.set_legend(true);
    ch.set_title("Employee Quarterly Chart");
    ch.set_type(boost::chart_type::AREA, true);
    doc.save_document();

    return 0;
}

//] [/chart_usage_example]

#endif
