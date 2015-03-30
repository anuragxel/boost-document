#ifndef _DOCUMENT_CPP
#define _DOCUMENT_CPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/document/document.hpp>
#include <boost/document/detail/oo_functions.hpp>

using namespace boost;

document::document() {
	boost::doc::oo_functions::set_bootstrap_offapi();
	this->is_file_opened = false;
}

document::document(const boost::filesystem::path path) {
	boost::doc::oo_functions::set_bootstrap_offapi();
	this->file_path = path;
	this->is_file_opened = false;
}

document::~document() {
	if(this->is_file_opened && boost::filesystem::exists(this->file_path)) {
		boost::doc::oo_functions::close_oo(this->file_path,false);
	}
}

void document::open_document(const boost::filesystem::path& path) {
     boost::doc::oo_functions::open_oo(path); // This the open office internal function.
}

void document::open_document() {
	this->is_file_opened = true;
	boost::doc::oo_functions::open_oo(this->file_path);
}

void document::save_document() {
	boost::doc::oo_functions::save_oo(this->file_path);
}

void document::close_document() {
	if(this->is_file_opened && boost::filesystem::exists(this->file_path)) {
		boost::doc::oo_functions::close_oo(this->file_path,true);
		this->is_file_opened = false;
	}
	else {
		boost::throw_exception(document_exception("Error: Trying to close unopened file."));
	}
}

void document::close_document(const boost::filesystem::path& path) {
	if(this->is_file_opened && boost::filesystem::exists(path)) {
		boost::doc::oo_functions::close_oo(path,true);
		this->is_file_opened = false;
	}
	else {
		boost::throw_exception(document_exception("Error: Trying to close unopened file."));
	}
}

void document::export_document(const filesystem::path& path,document_file_format::type format) {
    if(boost::filesystem::exists(path)) {
    	boost::doc::oo_functions::export_oo(path,format); // This the open office internal function.
    }
    else {
		boost::throw_exception(document_exception("Error: Trying to export nonexistant file."));
	}
}

void document::export_document(document_file_format::type format) {
    if(boost::filesystem::exists(this->file_path)) {
        boost::doc::oo_functions::export_oo(this->file_path,format); // This the open office internal function.
    }
    else {
		boost::throw_exception(document_exception("Error: Trying to export nonexistant file."));
	}
}

#endif
