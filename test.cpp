#include <iostream>
#include "document.hpp"

void negative_try_opening_null() {
	try {
		boost::document d = boost::document();
		d.open_document();
	}
	catch(boost::document_exception& a) {
		std::cout << "Test 1 Passed." << std::endl;
	}
}

void working_on_multiple_documents(boost::document b, boost::document c) {
	try {
		b.open_document();
		c.open_document();
		b.export_document(boost::office_file_format::PDF);
		c.export_document(boost::office_file_format::PDF);
		std::cout << "Test 2 Passed." << std::endl;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test 2 Failed." << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

int main(int argc, char **argv) {

	boost::filesystem::path path(argv[1]);

	boost::document b = boost::document(path);
	boost::document c = boost::document("/home/anurag/testing.ods");

	negative_try_opening_null();
	working_on_multiple_documents(b,c);

	return 0;
}
