#include "Document.hpp"
#include "Document.cpp"

int main(int argc, char **argv) {
	boost::filesystem::path path(argv[1]);
		
	boost::Document b = boost::Document(); 
	b.open_spreadsheet(path);
	//b.export_spreadsheet(path,boost::office_file_format::PDF);
	return 0;
}
