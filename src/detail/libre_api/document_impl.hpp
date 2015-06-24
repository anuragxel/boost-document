#ifndef _LIBRE_DOCUMENT_IMPL_HPP
#define _LIBRE_DOCUMENT_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <memory>

#include <boost/filesystem.hpp>

#include <boost/document/sheet.hpp>

#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/document_file_format.hpp>

#include <boost/document/detail/document_interface.hpp>
#include <boost/document/detail/sheet_interface.hpp>

#include <boost/document/detail/libre_api/libre_functions.hpp>
#include <boost/document/detail/libre_api/libre_sheet_func.hpp>

#include "sheet_impl.hpp"

namespace boost { namespace detail { 

class libre_document: public document_interface {
	protected:	
	boost::filesystem::path doc_path_;
	bool is_file_opened;
	
	::com::sun::star::uno::Reference< com::sun::star::lang::XComponent > xComponent_;
	
	::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheets > xSheets_;
	::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheetDocument > xSheetDoc_;
	public:
	void initialize(const boost::filesystem::path& fpath) {
		boost::doc::libre_functions::set_bootstrap_offapi();
		if(fpath.empty() or fpath == "") {
			boost::throw_exception(document_exception(
            		"Error: No path given."));	
		}
		this->doc_path_ = boost::filesystem::system_complete(fpath);
		this->xComponent_ = NULL;
		this->xSheets_ = NULL;
		this->xSheetDoc_ = NULL;
		this->is_file_opened = false;
	}

	void create() {
		if(! this->is_file_opened) {
			this->xComponent_ =  boost::doc::libre_functions::create_libre(this->doc_path_);	
			this->is_file_opened = true;
			this->save();
		}
	}

	void open() {
		if(! this->is_file_opened) {
			this->xComponent_ = boost::doc::libre_functions::get_xComponent_from_path(this->doc_path_);
			boost::doc::libre_functions::open_libre(this->doc_path_,this->xComponent_);
			this->is_file_opened = true;
		}
 	}

 	void close() {
 		if(this->is_file_opened) {
			boost::doc::libre_functions::close_libre(this->doc_path_, false, this->xComponent_);
			this->xComponent_ = NULL;
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
 		boost::doc::libre_functions::save_libre(this->doc_path_, this->xComponent_);
 	}

 	 void save_as(const boost::filesystem::path& fpath) {
 		if(! this->is_file_opened) {
			boost::throw_exception(document_exception(
            		"Error: Trying to save unopened file."));
		}
		boost::doc::libre_functions::save_libre(boost::filesystem::system_complete(fpath), this->xComponent_);
 	}
 	
 	void export_as(boost::document_file_format::type format) {
 		boost::doc::libre_functions::export_libre(this->doc_path_, format, this->xComponent_);
 	}

 	boost::sheet insert_sheet(const std::string& str) {
		if(this->xSheets_ == NULL) {
 			if(this->xSheetDoc_ == NULL) {
				this->xSheetDoc_ = boost::doc::libre_sheet_func::get_xSheetDoc(this->xComponent_);
			}
			this->xSheets_ = boost::doc::libre_sheet_func::get_sheets_of_document(this->xSheetDoc_);
		}
		std::string new_str(str);
		com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet > new_sheet = boost::doc::libre_sheet_func::insert_sheet_by_name(this->xSheets_,new_str);
		return boost::sheet(std::dynamic_pointer_cast<sheet_interface>(std::make_shared<boost::detail::libre_sheet>(this->xComponent_,new_sheet,new_str)));
 	}

 	boost::sheet get_sheet(const std::string& str) {
		if(this->xSheets_ == NULL) {
 			if(this->xSheetDoc_ == NULL) {
				this->xSheetDoc_ = boost::doc::libre_sheet_func::get_xSheetDoc(this->xComponent_);
			}
			this->xSheets_ = boost::doc::libre_sheet_func::get_sheets_of_document(this->xSheetDoc_);
		}
		com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet > new_sheet = boost::doc::libre_sheet_func::get_sheet_by_name(this->xSheets_,str);
		std::string new_str(str);
		return boost::sheet(std::dynamic_pointer_cast<sheet_interface>(std::make_shared<boost::detail::libre_sheet>(this->xComponent_,new_sheet,new_str)));
 	}

 	boost::sheet get_sheet(int index) {
 		if(this->xSheets_ == NULL) {
 			if(this->xSheetDoc_ == NULL) {
				this->xSheetDoc_ = boost::doc::libre_sheet_func::get_xSheetDoc(this->xComponent_);
			}
			this->xSheets_ = boost::doc::libre_sheet_func::get_sheets_of_document(this->xSheetDoc_);
		}
		com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet > new_sheet = boost::doc::libre_sheet_func::get_sheet_by_index(this->xSheets_,index);
		return boost::sheet(std::dynamic_pointer_cast<sheet_interface>(std::make_shared<boost::detail::libre_sheet>(this->xComponent_,new_sheet,index)));
 	}

 	boost::sheet get_sheet_unchecked(const std::string& str) {
		if(this->xSheets_ == NULL) {
 			if(this->xSheetDoc_ == NULL) {
				this->xSheetDoc_ = boost::doc::libre_sheet_func::get_xSheetDoc(this->xComponent_);
			}
			this->xSheets_ = boost::doc::libre_sheet_func::get_sheets_of_document(this->xSheetDoc_);
		}
		com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet > new_sheet = boost::doc::libre_sheet_func::get_sheet_by_name_unchecked(this->xSheets_,str);
		std::string new_str(str);
		return boost::sheet(std::dynamic_pointer_cast<sheet_interface>(std::make_shared<boost::detail::libre_sheet>(this->xComponent_,new_sheet,new_str)));
 	}

 	boost::sheet get_sheet_unchecked(int index) {
 		if(this->xSheets_ == NULL) {
 			if(this->xSheetDoc_ == NULL) {
				this->xSheetDoc_ = boost::doc::libre_sheet_func::get_xSheetDoc(this->xComponent_);
			}
			this->xSheets_ = boost::doc::libre_sheet_func::get_sheets_of_document(this->xSheetDoc_);
		}
		com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet > new_sheet = boost::doc::libre_sheet_func::get_sheet_by_index_unchecked(this->xSheets_,index);
		return boost::sheet(std::dynamic_pointer_cast<sheet_interface>(std::make_shared<boost::detail::libre_sheet>(this->xComponent_,new_sheet,index)));
 	}

 	int sheet_count() {
 		if(this->xSheets_ == NULL) {
 			if(this->xSheetDoc_ == NULL) {
				this->xSheetDoc_ = boost::doc::libre_sheet_func::get_xSheetDoc(this->xComponent_);
			}
			this->xSheets_ = boost::doc::libre_sheet_func::get_sheets_of_document(this->xSheetDoc_);
		}
		return boost::doc::libre_sheet_func::get_sheet_count(this->xSheets_);
 	}

 	void delete_sheet(const std::string& str) {
 		if(this->xSheets_ == NULL) {
 			if(this->xSheetDoc_ == NULL) {
				this->xSheetDoc_ = boost::doc::libre_sheet_func::get_xSheetDoc(this->xComponent_);
			}
			this->xSheets_ = boost::doc::libre_sheet_func::get_sheets_of_document(this->xSheetDoc_);
		}
		boost::doc::libre_sheet_func::delete_sheet_by_name(this->xSheets_,str);
 	}

 	void delete_sheet(int index) {
 		boost::throw_exception(document_exception(
            		"Function Un-implemented. :("));
 	}

 	~libre_document() {
 		if(this->is_file_opened) {
			boost::doc::libre_functions::close_libre(this->doc_path_, false, this->xComponent_);
			this->is_file_opened = false;
		}
 	}

};

std::shared_ptr<document_interface> open_libre_instance() {
	return std::dynamic_pointer_cast<document_interface>(std::make_shared<boost::detail::libre_document>());
}

}} // namespace boost::detail


#endif
