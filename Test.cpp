#include "Document.hpp"
#include "Document.cpp"

int main(int argc, char **argv) {
	boost::filesystem::path path(argv[1]);
	open_spreadsheet(path);
	export_spreadsheet(path,format::PDF);
	return 0;
}
