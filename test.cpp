#include <iostream>
#include "document.hpp"

void negative_try_opening_null() {
	try {
		boost::document d = boost::document();
		d.open_document();
	}
	catch(boost::document_exception& e) {	
		std::cout << "Test negative_try_opening_null Passed. Expected -- " << e.what() << std::endl;
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
		b.export_document(boost::document_file_format::PDF);
		c.export_document(boost::document_file_format::PDF);
	//	b.close_document();
	//	c.close_document();
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


int main(int argc, char **argv) {

	boost::filesystem::path path(argv[1]);

	boost::document b = boost::document(path);
	// Create a document. Change to the correct path there to run the tests.
	boost::document c = boost::document("/home/anurag/testing.ods");

	// Create a document, change the rwx permission to 000. Change to the correct path there to run the test.
	boost::document d = boost::document("/home/anurag/permission.ods");

	// Sanity Checks
	negative_try_opening_null();
	negative_try_closing_null();
	negative_closing_unopened_document(b);
	negative_absurd_path_opening();

	// Permissions related checks
	negative_opening_file_without_permission(d);
	negative_exporting_file_without_permission(d);
	
	// Positive Checks.
	working_on_multiple_documents(b,c);

	return 0;
}
