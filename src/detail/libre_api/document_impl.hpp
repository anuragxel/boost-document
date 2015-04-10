#ifndef _LIBRE_DOCUMENT_IMPL_HPP
#define _LIBRE_DOCUMENT_IMPL_HPP

#include <boost/filesystem.hpp>
#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/document_file_format.hpp>
#include <boost/document/detail/libre_api/libre_functions.hpp>
#include <boost/document/detail/libre_api/document_interface.hpp>

using namespace boost;

class libre_document: public document_interface {
	boost::filesystem::path doc_path_;
	bool is_file_opened;
	Reference< XComponent > xComponent_;
	void init(const boost::filesystem::path fpath) {
		boost::doc::libre_functions::set_bootstrap_offapi();
		this->doc_path_ = fpath;
		if(!boost::filesystem::exists(inputPath)) {
        	boost::throw_exception(document_exception(
            	"Error: Path is empty or does not exist."));
    	}
		this->xComponent_ = boost::doc::libre_functions::get_xComponent_from_path(fpath);
		this->is_file_opened = false;
	}
	void open() {
		if(not this->is_file_opened) {
			boost::doc::libre_functions::open_libre(this->fpath);
		}
 	}

};

document_interface* open_instance() {
	return new libre_document()
}



#endif
