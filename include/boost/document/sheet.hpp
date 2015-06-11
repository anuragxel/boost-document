#ifndef _SHEET_HPP
#define _SHEET_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/document/detail/sheet_interface.hpp>


namespace boost {

	 namespace detail {
		sheet_interface* open_sheet_instance();
	}
    //! \brief This is the main class interface to be 
    //!        exposed to the library user.
    //!
	class sheet {
	private:
		sheet_interface* pimpl_;
		sheet_interface* init() {
 	   		return boost::detail::open_sheet_instance();
		}
	public:
		//! \brief The Constructor.
		//!        Creates a new document object.  
		sheet() : pimpl_(init()) {
		}
		//! \brief Gets the sheet name
		//!        which is being accessed.
		std::string get_sheet_name() {
			return pimpl_->get_sheet_name();
		}

		//! \brief Gets the sheet index
		//!        which is being accessed.
	 	int get_sheet_index() {
	 		return pimpl_->get_sheet_index();
	 	}

		//! \brief Renames the sheet to str
		//!        which is being accessed.
	 	void remame_sheet(const std::string& str) {
	 		pimpl_->remame_sheet(str);
	 	}
	 	//! \brief Destructor
		//!        Closes Unsaved Documents.
		~sheet() {
			delete pimpl_;
		}
	};
} // namespace boost

#endif
