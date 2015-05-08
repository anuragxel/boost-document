#ifndef _LIBRE_DOCUMENT_IMPL_HPP
#define _LIBRE_DOCUMENT_IMPL_HPP

#include <boost/filesystem.hpp>
#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/document_file_format.hpp>
#include <boost/document/detail/libre_api/libre_functions.hpp>
#include <boost/document/detail/document_interface.hpp>

namespace boost { namespace detail { 

class libre_document: public document_interface {
	
	boost::filesystem::path doc_path_;
	bool is_file_opened;	
	::com::sun::star::uno::Reference< com::sun::star::lang::XComponent > xComponent_;

	void initialize(const boost::filesystem::path& fpath) {
		boost::doc::libre_functions::set_bootstrap_offapi();
		this->doc_path_ = fpath;
		if(!boost::filesystem::exists(this->doc_path_)) {
        		boost::throw_exception(document_exception(
            		"Error: Path is empty or does not exist."));
    		}
		this->xComponent_ = boost::doc::libre_functions::get_xComponent_from_path(fpath);
		this->is_file_opened = false;
	}

	void open() {
		if(!this->is_file_opened) {
			boost::doc::libre_functions::open_libre(this->doc_path_,this->xComponent_);
			this->is_file_opened = true;
		}
 	}

 	void close() {
 		if(this->is_file_opened) {
			boost::doc::libre_functions::close_libre(this->doc_path_, false, this->xComponent_);
			this->is_file_opened = false;
		}
		else {
			boost::throw_exception(document_exception(
            		"Error: Trying to close unopened file."));	
		}
 	}
 	
 	void save() {
 		boost::doc::libre_functions::save_libre(this->doc_path_, this->xComponent_);
 	}
 	
 	void export_as(boost::document_file_format::type format) {
 		boost::doc::libre_functions::export_libre(this->doc_path_, format, this->xComponent_);
 	}

 	~libre_document() {
 		if(this->is_file_opened) {
			boost::doc::libre_functions::close_libre(this->doc_path_, false, this->xComponent_);
			this->is_file_opened = false;
		}
 	}

};

document_interface* open_libre_instance() {
	return new libre_document();
}

}} // namespace boost::detail


#endif
