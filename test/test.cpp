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
#include <boost/document/column.hpp>

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
    BOOST_REQUIRE(s2["A2"].get_string() == "Vatika");
    return 0;
}


int negative_cell_index_check(boost::document& c) {
    boost::sheet s1 = c["Anurag"];    
    try {
        s1["0A2"] = "Anurag";
        return 1;
    }
    catch(boost::document_exception& e) {
    }
    try {
        s1["A22B"] = "Anurag";
        return 1;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test negative_cell_index_check Passed." << std::endl;
        return 0;
    }
}

int cell_type_check(boost::document& c) {
    try {
        boost::sheet s1 = c["Anurag"];
        s1[1][1] = "Vatika";
        BOOST_REQUIRE(s1[1][1].get_content_type() == boost::cell_content_type::STRING);
        s1[1][2] = 3.14;
        BOOST_REQUIRE(s1[1][2].get_content_type() == boost::cell_content_type::VALUE);
        BOOST_REQUIRE(s1[3][4].empty() == true);
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test cell_type_check Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int cell_getters_check(boost::document& c) {
    try {
        boost::sheet s1 = c["Anurag"];
        s1[1][1] = "Vatika";
        BOOST_REQUIRE(s1[1][1].get_string() == "Vatika");
        s1[1][2] = 3.14;
        BOOST_REQUIRE(s1[1][2].get_value() < 3.15 and s1[1][2].get_value() > 3.13);
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test cell_getters_check Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }   
}


int cell_formula_check(boost::document& c) {
    try {
        boost::sheet s1 = c["Anurag"];
        s1[2][2] = 14.6;
        s1[2][3] = 3.14;
        s1[2][4] = "=C3+C4";
        BOOST_REQUIRE(s1[2][4].get_content_type() == boost::cell_content_type::FORMULA);
        BOOST_REQUIRE(s1[2][4].get_value() < 17.75 && s1[2][4].get_value() > 17.73);
        BOOST_REQUIRE(s1[2][4].get_content_type() == boost::cell_content_type::FORMULA);
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test cell_formula_check Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}


// TODO: Fix in a day. Not able to find the fix. :/ 
int cell_reset_check(boost::document& c) {
    try {
        boost::sheet s1 = c["Anurag"];
        s1[2][2] = 14.6;
        s1[2][2].reset();
        BOOST_REQUIRE(s1[2][4].get_content_type() == boost::cell_content_type::EMPTY);
        s1[2][4] = "=C3+C4";
        s1[2][3].reset();
        BOOST_REQUIRE(s1[2][4].get_content_type() == boost::cell_content_type::EMPTY);
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test cell_formula_check Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int check_row_and_column_class(boost::document& c) {
    try {

        boost::sheet s1 = c["Anurag"];
        
        boost::row r = s1.get_row(3);
        r[4] = "Anurag";
        BOOST_REQUIRE(s1[4][3].get_string() == "Anurag");

        boost::column l = s1.get_column(9);
        l[2] = "Vatika";
        BOOST_REQUIRE(s1[9][2].get_string() == "Vatika");

        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test check_row_and_column_class Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int check_for_sheet_and_row_scope(boost::document& c) {
    try {
        boost::sheet s = c["Anurag"];
        boost::row r = s.get_row(10);
        r[20] = "Hello world";
        boost::column k = s.get_column(20);
        
        s = c[0]; // ... new sheet is used instead of the old one
        // s is now out of scope.
        // if r and c had raw pointers of s,
        // then seg fault can occur.
        BOOST_REQUIRE(r[20].get_string() == k[10].get_string());
        BOOST_REQUIRE(k[10].get_string() == "Hello world");

        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test check_for_sheet_and_row_scope Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }   
}


int use_row_iterator(boost::document& c) {
    try {
        boost::sheet s1 = c["Anurag"];     
        boost::row r = s1.get_row(3);   
        for(auto k = r.begin(); k != r.begin() + 20; k++) {
          *k = 1;
        }
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test use_row_iterator Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int row_stl_functionality(boost::document& c) {
    try {
        boost::sheet s1 = c["Anurag"];
        boost::row r = s1.get_row(3);
        std::fill(r.begin(), r.begin() + 50, 1);
        double sum = 0;
        const boost::row_iterator end(r.begin() + 50);
        for (auto it = r.begin(); it != end; ++it) {
            sum += (*it).get_value();
        }
        BOOST_REQUIRE(sum < 50.1 && sum > 49.9);
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test use_row_iterator Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int row_iterator_caching(boost::document& c) {
    try {
        boost::sheet s1 = c["Anurag"];
        boost::cell c1 = s1[0][0];
        c1 = "Anurag";
        boost::column_iterator it = s1[0].begin();
        assert((*it).get_string() == c1.get_string());
        c1 = "Vatika"; // changed the cell value!
        assert((*it).get_string() == c1.get_string()); // Iterator should reflect the same. :)
        // It does reflect because the operations are write through.
        // there are no operations which are locally performed in the instance
        // and delegated for later. All operations are final in nature.
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test row_iterator_caching Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
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

    rv += negative_absurd_get_sheet_string(b);
    rv += negative_absurd_get_sheet_index(b);
    
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

    // Cell related checks
    rv += get_valid_cell_and_set_values(b);
    rv += sheet_and_cell_syntatic_sugar(b,c);
    rv += cell_type_check(c);
    rv += cell_getters_check(c);
    rv += cell_formula_check(c);
    //rv += cell_reset_check(c);
    rv += negative_cell_index_check(c);

    //  iterator checks
    rv += check_row_and_column_class(c);
    rv += check_for_sheet_and_row_scope(c);
    rv += use_row_iterator(c);
    rv += row_stl_functionality(c);
    rv += row_iterator_caching(c);

    if (rv > 0) {
        std::cout << rv << " Tests Failed. Look at Log for more information." << std::endl;
    } 
    return rv;
}

#endif
