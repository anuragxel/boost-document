#include "document.hpp"

int main(int argc, char **argv) {

	boost::filesystem::path path(argv[1]);

	boost::document b = boost::document(path);
	boost::document c = boost::document("/home/anurag/testing.ods"); 
	//boost::document d = boost::document();
	b.open_document();
	c.open_document();
	b.export_document(boost::office_file_format::PDF);
	c.export_document(boost::office_file_format::PDF);
	//d.export_document(boost::office_file_format::PDF);
	return 0;
}
