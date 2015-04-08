#ifndef _LIBRE_DOCUMENT_IMPL_H
#define _LIBRE_DOCUMENT_IMPL_H

#include <boost/document/detail/libre_api/libre_functions.hpp>

using namespace boost;

class libre_document: public document_interface {
	boost::filesystem::path doc_path_;
	Reference< XComponent > xComponent_;
};

document_interface* open_instance() {
	boost::doc::libre_functions::open_libre()
	return new libre_document()
}

#endif