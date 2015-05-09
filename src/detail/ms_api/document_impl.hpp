#ifndef _MS_DOCUMENT_IMPL_HPP
#define _MS_DOCUMENT_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/filesystem.hpp>
#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/document_file_format.hpp>
#include <boost/document/detail/document_interface.hpp>

namespace boost { namespace detail { 

class ms_document: public document_interface {
	
	boost::filesystem::path doc_path_;
	bool is_file_opened;	

	void initialize(const boost::filesystem::path& fpath) {
		this->doc_path_ = fpath;
		if(!boost::filesystem::exists(this->doc_path_)) {
        		boost::throw_exception(document_exception(
            		"Error: Path is empty or does not exist."));
    		}
		this->is_file_opened = false;
	}

	void open() {
		if(not this->is_file_opened) {
			//boost::doc::libre_functions::open_libre(this->doc_path_,this->xComponent_);
			this->is_file_opened = true;
		}
 	}

 	void close() {
 		if(this->is_file_opened) {
			//boost::doc::libre_functions::close_libre(this->doc_path_, false, this->xComponent_);
			this->is_file_opened = false;
		}
		else {
			boost::throw_exception(document_exception(
            		"Error: Trying to close unopened file."));	
		}
 	}
 	
 	void save() {
 		if(! this->is_file_opened) {
			boost::throw_exception(document_exception(
            		"Error: Trying to save unopened file."));
		}
 		//boost::doc::libre_functions::save_libre(this->doc_path_, this->xComponent_);
 	}
 	
 	void save_as(const boost::filesystem::path& fpath) {
 		if(! this->is_file_opened) {
			boost::throw_exception(document_exception(
            		"Error: Trying to save unopened file."));
		}
 		//boost::doc::libre_functions::save_libre(fpath, this->xComponent_);
 	}
 	
 	void export_as(boost::document_file_format::type format) {
 		if(! this->is_file_opened) {
 			boost::throw_exception(document_exception(
            		"Error: Trying to export unopened file."));
 		}
 		//boost::doc::libre_functions::export_libre(this->doc_path_, format, this->xComponent_);
 	}

 	~libre_document() {
 		if(this->is_file_opened) {
			//boost::doc::libre_functions::close_libre(this->doc_path_, false, this->xComponent_);
			this->is_file_opened = false;
		}
 	}

};

document_interface* open_ms_instance() {
	return new ms_document();
}

}} // namespace boost::detail


#endif
