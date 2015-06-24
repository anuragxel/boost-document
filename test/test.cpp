#ifndef _TEST_CPP
#define _TEST_CPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/filesystem.hpp>

#include <boost/document/document.hpp>
#include <boost/document/sheet.hpp>

#include <boost/test/minimal.hpp>



// Negative Tests
int negative_try_opening_null() {
    try {
        boost::document d("");
        d.open_document();
        return 1;
    }
    catch(boost::document_exception& e) {   
        std::cout << "Test negative_try_opening_null Passed. Expected -- " << e.what() << std::endl;
        return 0;
    }
}

int negative_try_exporting_null() {
    try {
        boost::document d("");
        d.export_document();
        return 1;
    }
    catch(boost::document_exception& e) {   
        std::cout << "Test negative_try_exporting_null Passed. Expected -- " << e.what() << std::endl;
        return 0;
    }
}

int negative_try_closing_null() {
    try {
        boost::document d("");
        d.close_document();
        return 1;
    }
    catch(boost::document_exception& e) {   
        std::cout << "Test negative_try_closing_null Passed. Expected -- " << e.what() << std::endl;
        return 0;
    }
}

int negative_closing_unopened_document(boost::document& b) {
    try {
        b.close_document();
        return 1;
    }
    catch(boost::document_exception& e) {
        std::cout << "Test negative_closing_unopened_document Passed. Expected -- " << e.what() << std::endl;
        return 0;
    }
}

int negative_absurd_path_opening() {
    try {
        boost::document a("./foo/bar.xls");
        a.open_document();
        return 1;
    }
    catch(boost::document_exception& e) {
        std::cout << "Test negative_absurd_path Passed. Expected -- " << e.what() << std::endl;
        return 0;
    }
}

int negative_opening_file_without_permission(boost::document& d) {
    try {
        d.open_document();
        return 1;
    }
    catch(boost::document_exception& e) {
        std::cout << "Test negative_opening_file_without_permission Passed. Expected -- " << e.what() << std::endl;
        return 0;
    }
}

int negative_exporting_file_without_permission(boost::document& d) {
    try {
        d.export_document();
        return 1;
    }
    catch(boost::document_exception& e) {
        std::cout << "Test negative_opening_file_without_permission Passed. Expected -- " << e.what() << std::endl;
        return 0;
    }
}

int negative_closing_file_without_permission(boost::document& d) {
    try {
        d.close_document();
        return 1;
    }
    catch(boost::document_exception& e) {
        std::cout << "Test negative_closing_file_without_permission Passed. Expected -- " << e.what() << std::endl;
        return 0;
    }
}






// Sheet Related Tests.
int negative_absurd_get_sheet_string(boost::document& d) {
    try {
        boost::sheet s = d.get_sheet("AbsurdSheetName");
        return 1;
    }
    catch(boost::document_exception& e) {
    std::cout << "Test negative_get_sheet_string Passed. Expected -- " << e.what() << std::endl;
    return 0;
    }
}

int negative_absurd_get_sheet_index(boost::document& d) {
    try{
        boost::sheet s = d.get_sheet(5232);
        return 1;
    }
    catch(boost::document_exception& e) {
        std::cout << "Test negative_get_sheet_index Passed. Expected -- " << e.what() << std::endl;
        return 0;
   }
}





// Cell Related Tests
int negative_get_invalid_cell(boost::document& d) {
    try{
        boost::sheet s = d.get_sheet(0);
        boost::cell c = s.get_cell(-1,0);
        return 1;
    }
    catch(boost::document_exception& e) {
        std::cout << "Test negative_get_invalid_cell Passed. Expected -- " << e.what() << std::endl;
        return 0;
   }
}








// Postive Tests
int exporting_to_pdf(boost::document& b) {
    try {

        b.export_document(boost::document_file_format::PDF);
        std::cout << "Test exporting_to_pdf Passed." << std::endl;
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test exporting_to_pdf Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int exporting_to_csv(boost::document& b) {
    try {
        b.export_document(boost::document_file_format::CSV);        
        std::cout << "Test exporting_to_csv Passed." << std::endl;
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test exporting_to_csv Failed." << std::endl;
        std::cerr << e.what() << std::endl;
       return 1;
    }
}


int working_on_multiple_documents(boost::document& b, boost::document& c) {
    try {
        b.export_document(boost::document_file_format::CSV);
        c.export_document(boost::document_file_format::PDF);
        std::cout << "Test working_on_multiple_documents Passed." << std::endl;
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test working_on_multiple_documents Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}


int get_valid_sheets(boost::document& b, boost::document& c) {
    try {
        boost::sheet s1 = c.get_sheet("Anurag"); // 1
        boost::sheet s2 = b.get_sheet(0); // "Sheet1"
        std::cout << "Test get_valid_sheets Passed." << std::endl;
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test get_valid_sheets Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int rename_valid_sheet(boost::document& b) {
    try {
        boost::sheet s1 = b.get_sheet("Anurag"); // 1
        s1.rename_sheet("Sheet2");
        BOOST_REQUIRE(s1.sheet_name() == "Sheet2");
        s1.rename_sheet("Anurag"); // Rename Back. :P
        std::cout << "Test rename_valid_sheets Passed." << std::endl;
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test rename_valid_sheets Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int get_valid_sheet_count(boost::document& b) {
    try {
        BOOST_REQUIRE(b.sheet_count() == 2);
        std::cout << "Test get_valid_sheet_count Passed." << std::endl;
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test get_valid_sheet_count Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int insert_new_sheet(boost::document& b) {
    try {
        boost::sheet s1 = b.insert_sheet("Vatika");
        BOOST_REQUIRE(b.sheet_count() == 3); 
        std::cout << "Test insert_new_sheet Passed." << std::endl;
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test insert_new_sheet Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int delete_new_sheet(boost::document& b) {
    try {
        b.delete_sheet("Vatika");
        BOOST_REQUIRE(b.sheet_count() == 2); 
        std::cerr << "Test delete_new_sheet Passed." << std::endl;
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test delete_new_sheet Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int get_valid_cell_and_set_values(boost::document& b) {
    try {
        boost::sheet s = b.get_sheet(0);
        boost::cell c = s.get_cell(0,0);
        c = "Shell";
        boost::cell c1 = s.get_cell(0,1);
        c1 = 2.0;
        std::cout << "Test get_valid_cell_and_set_values Passed." << std::endl;
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test get_valid_cell_and_set_values Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

// No Exception Handling.
int sheet_and_cell_syntatic_sugar(boost::document& b,boost::document& c) {
    boost::sheet s1 = b[0];
    boost::sheet s2 = c["Anurag"];
    boost::cell cl = s2[0][0];
    s2[0][1] = "Vatika";
    s2[1][1] = "Anurag";
    return 0;
}

int test_main(int argc, char *argv[]) {

   
//#ifdef BOOST_DOCUMENT_HAS_MS
//    boost::document b("Excel_Test1.xlsx");  
//    boost::document d("Excel_Test2.xlsx");
//    boost::document c("Excel_Test3.xlsx");
//#elif defined(BOOST_DOCUMENT_HAS_LIBRE)   
    boost::document b("Test1.ods");
    boost::document c("Test2.ods");
    boost::document d("Test3.ods");
//#else
//#endif


    int rv = 0;
    
    // Sanity Checks
    rv += negative_try_opening_null();
    rv += negative_try_exporting_null();
    rv += negative_try_closing_null();
    rv += negative_closing_unopened_document(b);
    rv += negative_absurd_path_opening();

    // Permissions related checks
    rv += negative_opening_file_without_permission(d);
    rv += negative_exporting_file_without_permission(d);
    rv += negative_closing_file_without_permission(d);

    b.open_document();
    c.open_document();

    //rv += negative_absurd_get_sheet_string(b);
    //rv += negative_absurd_get_sheet_index(b);
    rv += negative_get_invalid_cell(b); 

    // Positive Checks
    rv += exporting_to_pdf(b);
    rv += exporting_to_csv(b);
    rv += working_on_multiple_documents(b,c);
    rv += get_valid_sheets(b,c);
    rv += rename_valid_sheet(c);
    rv += get_valid_sheet_count(c);
    rv += insert_new_sheet(c);
    rv += delete_new_sheet(c);
    rv += get_valid_cell_and_set_values(b);
    rv += sheet_and_cell_syntatic_sugar(b,c);

    if (rv > 0) {
        std::cout << rv << " Tests Failed. Look at Log for more information." << std::endl;
    } 
    return rv;
}

#endif
