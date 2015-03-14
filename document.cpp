#ifndef _DOCUMENT_CPP
#define _DOCUMENT_CPP

#include "document.hpp"
#include "document_exception.hpp"
#include "oo_functions.hpp"

using namespace boost;

document::document() {
}

document::document(const boost::filesystem::path path) {
	this->file_path = path;
}

document::~document() {

}

void document::open_document(const boost::filesystem::path& path) {
     boost::oo_functions::open_oo(path); // This the open office internal function.
}

void document::open_document() {
	boost::oo_functions::open_oo(this->file_path);
}


void document::export_document(const filesystem::path& path,office_file_format::type format) {
    boost::oo_functions::export_oo(path,format); // This the open office internal function.
}

void document::export_document(office_file_format::type format) {
    boost::oo_functions::export_oo(this->file_path,format); // This the open office internal function.
}

#endif
