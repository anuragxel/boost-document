#ifndef _DOCUMENT_CPP
#define _DOCUMENT_CPP

#include "Document.hpp"
// #include "ooFunctions.cpp" // Hacky. TODO. Remove ASAP.

Document::Document() {

}

Document::~Document() {

}

void Document::open_document(const boost::filesystem::path& path) {
    __openOO(path); // This the open office internal function.
}


void Document::export_document(const filesystem::path& path,office_file_format::type format) {
    __exportOO(path,format); // This the open office internal function.
}

#endif
