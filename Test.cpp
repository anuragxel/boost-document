#include "Document.hpp"
// #include "Document.cpp" // Hacky. TODO. Remove ASAP.

int main(int argc, char **argv) {

	boost::filesystem::path path(argv[1]);

	boost::Document b = boost::Document(); 
	b.open_document(path);
	//b.export_document(path,boost::office_file_format::PDF);
	return 0;
}
