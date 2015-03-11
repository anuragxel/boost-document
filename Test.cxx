#include "Document.hpp"
#include "Document.cxx"

int main(int argc, char **argv) {
	boost::filesystem::path pth(argv[1]);
	open_spreadsheet(pth);
	//export_spreadsheet(pth,format::PDF);
	return 0;
}