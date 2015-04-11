#ifndef _DOCUMENT_HPP
#define _DOCUMENT_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/filesystem.hpp>
#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/document_file_format.hpp>
#include <boost/document/detail/document_interface.hpp>


namespace boost {

	namespace detail {
		document_interface* boost::document::detail::open_instance();
	}

    //! \brief This is the main class interface to be 
    //!        exposed to the library user.
    //!
	class document {
	private:
		boost::filesystem::path file_path;
		document_interface* pimpl_;
		
		dicument_interface* init() {
 	   		return boost::document::detail::open_instance();
		}

	public:
		
		//! \brief The Constructor.
		//!        Creates a new document object.  
		document(const boost::filesystem::path path) : pimpl_(init()) {
			this->file_path = path;
			pimpl_->initialize(this->file_path);
		}
		
		//! \brief Destructor
		//!        Closes Unsaved Documents.
		~document() {
			delete pimpl_;
		}
		
		//! \brief Opens document using Calc/Excel given in
		//!        the file path.
		void open_document() {
			pimpl_->open();
		}

		
		//! \brief Closes document using Calc/Excel given in
		//!        the file path.
		void close_document() {
			pimpl_->close();
		}
		
		//! \brief saves document using Calc/Excel given in
		//!        the file path.
		void save_document() {
			pimpl_->save();
		}

		//! \brief Exports document using Calc/Excel given in
		//!        the file path and the file format. Default
		//!        format is PDF.
		void export_document(boost::document_file_format::type format = document_file_format::PDF) {
			pimpl_->export(format);
		}
	};

} // namespace boost

#endif
