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

//#include <boost/test/minimal.hpp>

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

int working_on_multiple_documents(boost::document& b, boost::document& c) {
    try {
        b.open_document();
        c.open_document();
        b.export_document(boost::document_file_format::CSV);
        c.export_document(boost::document_file_format::PDF);
        b.close_document();
        c.close_document();
        std::cout << "Test working_on_multiple_documents Passed." << std::endl;
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test working_on_multiple_documents Failed." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int negative_closing_unopened_document(boost::document& b) {
    try {
        b.close_document();
        std::cerr << "Test negative_closing_unopened_document Failed." << std::endl;
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

int negative_absurd_get_sheet_string(boost::document& d) {
    try {
        d.open_document();
	boost::sheet s = d.get_sheet("AbsurdSheetName");
	d.close_document();
        return 1;
    }
    catch(boost::document_exception& e) {
        std::cout << "Test negative_get_sheet_string Passed. Expected -- " << e.what() << std::endl;
        d.close_document();
	return 0;
    }
}

int negative_absurd_get_sheet_index(boost::document& d) {
    try{
	d.open_document();
	boost::sheet s = d.get_sheet(5232);
	d.close_document();
    }
    catch(boost::document_exception& e) {
   	std::cout << "Test negative_get_sheet_index Passed. Expected -- " << e.what() << std::endl;
	d.close_document();
	return 0;
   }
}

int exporting_to_pdf(boost::document& b) {
    try {
		b.open_document();
        b.export_document(boost::document_file_format::PDF);
		b.close_document();
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
		b.open_document();
        b.export_document(boost::document_file_format::CSV);        
		b.close_document();
		std::cout << "Test exporting_to_csv Passed." << std::endl;
        return 0;
    }
    catch(boost::document_exception& e) {
        std::cerr << "Test exporting_to_csv Failed." << std::endl;
        std::cerr << e.what() << std::endl;
       return 1;
    }
}


int main(int argc, char **argv) {
    
//#ifdef BOOST_DOCUMENT_HAS_MS
//	boost::document b("Excel_Test1.xlsx");	
//	boost::document d("Excel_Test2.xlsx");
//	boost::document c("Excel_Test3.xlsx");
//#elif defined(BOOST_DOCUMENT_HAS_LIBRE)	
    	boost::document b("Test1.ods");
    	boost::document c("Test2.ods");
    	boost::document d("Test3.ods");
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
    	rv += negative_absurd_get_sheet_string(b);
    	rv += negative_absurd_get_sheet_index(b);
    	// Positive Checks
	rv += exporting_to_pdf(b);
	rv += exporting_to_csv(b);
    	rv += working_on_multiple_documents(b,c);

    	if (rv > 0) {
        	std::cout << rv <<" Tests Failed. Look at Log for more information." << std::endl;
    	}
   
    return rv;
}

#endif
