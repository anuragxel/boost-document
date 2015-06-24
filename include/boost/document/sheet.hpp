#ifndef _SHEET_HPP
#define _SHEET_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/document/detail/sheet_interface.hpp>
#include <memory>

#include <boost/document/cell.hpp>

namespace boost {
    //! \brief This is the main class interface to be 
    //!        exposed to the library user.
    //!
	class sheet {
	private:
		std::shared_ptr<sheet_interface> pimpl_;
		//boost::shared_ptr<sheet_interface> init() {
 	   	//	return boost::detail::open_sheet_instance();
		//}
	public:
		//! \brief The Constructor.
		//!        Creates a new document object.  
		explicit sheet(const std::shared_ptr<sheet_interface> impl) : pimpl_(impl) {

		}
		//! \brief Gets the sheet name
		//!        which is being accessed.
		std::string sheet_name() {
			return pimpl_->sheet_name();
		}

		//! \brief Gets the sheet index
		//!        which is being accessed.
	 	int sheet_index() {
	 		return pimpl_->sheet_index();
	 	}

		//! \brief Renames the sheet to str
		//!        which is being accessed.
	 	void rename_sheet(const std::string& str) {
	 		pimpl_->rename_sheet(str);
	 	}

	 	//! Gets the cell instance
	 	//! which can be manipulated.
	 	boost::cell get_cell(int i, int j) {
	 		return pimpl_->get_cell(i,j);
	 	}


	 	class cell_proxy {
			protected:
			sheet* obj_;
			int row_;
			public:
			cell_proxy(sheet* obj, int row) {
				obj_ = obj;
				row_ = row;
			}
			boost::cell operator[](int column) {
				return obj_->pimpl_->get_cell_unchecked(row_,column);
			}
		};

		//! Gets the cell instance
	 	//! which can be manipulated.
	 	//! No Exception Handling.
		cell_proxy operator[](int i) {
			return cell_proxy(this,i);
		}
	 	
	 	//! \brief Destructor
		//!        Closes Unsaved Documents.
		~sheet() {
		}
	};
} // namespace boost

#endif
