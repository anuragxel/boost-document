#include <iostream>
#include "document.hpp"

void negative_try_opening_null() {
	try {
		boost::document d = boost::document();
		d.open_document();
	}
	catch(boost::document_exception& a) {	
		std::cout << a.what() << std::endl;
		std::cout << "Test negative_try_opening_null Passed. Expected -- " << std::endl;
	}
}

void working_on_multiple_documents(boost::document b, boost::document c) {
	try {
		b.open_document();
		c.open_document();
		b.export_document(boost::document_file_format::PDF);
		c.export_document(boost::document_file_format::PDF);
		std::cout << "Test working_on_multiple_documents Passed." << std::endl;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test working_on_multiple_documents Failed." << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

void negative_absurd_path() {
	try {
		boost::document a = boost::document();
		a.open_document("./foo/bar.xls");
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_absurd_path Passed. Expected -- " << e.what() << std::endl;
	}
}

int main(int argc, char **argv) {

	boost::filesystem::path path(argv[1]);

	boost::document b = boost::document(path);
	boost::document c = boost::document("/home/anurag/testing.ods");

	negative_try_opening_null();
	working_on_multiple_documents(b,c);
	negative_absurd_path();
	return 0;
}
