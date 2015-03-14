#ifndef _DOCUMENT_CPP
#define _DOCUMENT_CPP

#include "document.hpp"
#include "detail/oo_functions.hpp"

using namespace boost;

document::document() {
}

document::document(const boost::filesystem::path path) {
	this->file_path = path;
}

document::~document() {
}

void document::open_document(const boost::filesystem::path& path) {
     boost::doc::oo_functions::open_oo(path); // This the open office internal function.
}

void document::open_document() {
	boost::doc::oo_functions::open_oo(this->file_path);
}


void document::export_document(const filesystem::path& path,document_file_format::type format) {
    boost::doc::oo_functions::export_oo(path,format); // This the open office internal function.
}

void document::export_document(document_file_format::type format) {
    boost::doc::oo_functions::export_oo(this->file_path,format); // This the open office internal function.
}

#endif
