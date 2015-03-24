#ifndef _TEST_CPP
#define _TEST_CPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/document/document.hpp>

void negative_try_opening_null() {
	try {
		boost::document d = boost::document();
		d.open_document();
	}
	catch(boost::document_exception& e) {	
		std::cout << "Test negative_try_opening_null Passed. Expected -- " << e.what() << std::endl;
	}
}

void negative_try_exporting_null() {
	try {
		boost::document d = boost::document();
		d.export_document();
	}
	catch(boost::document_exception& e) {	
		std::cout << "Test negative_try_exporting_null Passed. Expected -- " << e.what() << std::endl;
	}
}

void negative_try_closing_null() {
	try {
		boost::document d = boost::document();
		d.close_document();
	}
	catch(boost::document_exception& e) {	
		std::cout << "Test negative_try_closing_null Passed. Expected -- " << e.what() << std::endl;
	}
}

void working_on_multiple_documents(boost::document b, boost::document c) {
	try {
		b.open_document();
		c.open_document();
		b.export_document(boost::document_file_format::CSV);
		c.export_document(boost::document_file_format::PDF);
		b.close_document();
		c.close_document();
		std::cout << "Test working_on_multiple_documents Passed." << std::endl;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test working_on_multiple_documents Failed." << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

void negative_closing_unopened_document(boost::document b) {
	try {
		b.close_document();
		std::cerr << "Test negative_closing_unopened_document Failed." << std::endl;
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_closing_unopened_document Passed. Expected -- " << e.what() << std::endl;
	}
}

void negative_absurd_path_opening() {
	try {
		boost::document a = boost::document();
		a.open_document("./foo/bar.xls");
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_absurd_path Passed. Expected -- " << e.what() << std::endl;
	}
}

void negative_opening_file_without_permission(boost::document d) {
	try {
		d.open_document();
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_opening_file_without_permission Passed. Expected -- " << e.what() << std::endl;
	}
}

void negative_exporting_file_without_permission(boost::document d) {
	try {
		d.export_document();
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_opening_file_without_permission Passed. Expected -- " << e.what() << std::endl;
	}
}

void negative_closing_file_without_permission(boost::document d) {
	try {
		d.close_document();
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_closing_file_without_permission Passed. Expected -- " << e.what() << std::endl;
	}
}

void exporting_to_pdf(boost::document b) {
	try {
		b.export_document(boost::document_file_format::PDF);
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test exporting_to_pdf Failed." << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

void exporting_to_csv(boost::document b) {
	try {
		b.export_document(boost::document_file_format::CSV);
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test exporting_to_csv Failed." << std::endl;
		std::cerr << e.what() << std::endl;
	}
}
int main(int argc, char **argv) {
	
	boost::document b = boost::document("./Test1.ods");
	//Create a document. Change to the correct path there to run the tests.
	boost::document c = boost::document("./Test2.ods");
	// Create a document, change the rwx permission to 000. Change to the correct path there to run the test.
	boost::document d = boost::document("./Test3.ods");

	// Sanity Checks
	negative_try_opening_null();
	negative_try_exporting_null();
	negative_try_closing_null();
	negative_closing_unopened_document(b);
	negative_absurd_path_opening();

	// Permissions related checks
	negative_opening_file_without_permission(d);
	negative_exporting_file_without_permission(d);
	negative_closing_file_without_permission(d);
	
	// Positive Checks.
	exporting_to_pdf(b);
	exporting_to_csv(c);
	working_on_multiple_documents(b,c);

	return 0;
}

#endif
