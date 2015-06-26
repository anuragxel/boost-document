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
	 	boost::cell get_cell(int row, int column) {
	 		return pimpl_->get_cell(row,column);
	 	}


	 	class column {
			protected:
			sheet* obj_;
			int row_;
			public:
			column(sheet* obj, int row) {
				obj_ = obj;
				row_ = row;
			}
			boost::cell get_cell(int column) {
				return obj_->pimpl_->get_cell(row_,column);
			}
			boost::cell operator[](int column) {
				return obj_->pimpl_->get_cell_unchecked(row_,column);
			}
		};


	 	class row {
			protected:
			sheet* obj_;
			int column_;
			public:
			row(sheet* obj, int column) {
				obj_ = obj;
				column_ = column;
			}
			boost::cell get_cell(int row) {
				return obj_->pimpl_->get_cell(row,column_);
			}
			boost::cell operator[](int row) {
				return obj_->pimpl_->get_cell_unchecked(row,column_);
			}
		};

		row get_row(int i) {
			return row(this,i);
		}

		column get_column(int i) {
			return column(this,i);
		}

		//! Gets the cell instance
	 	//! which can be manipulated.
	 	//! No Exception Handling.
		row operator[](int i) {
			return row(this,i);
		}
	 	
	 	std::size_t max_row() {
	 		return pimpl_->max_row();
	 	}

	 	std::size_t max_column() {
	 		return pimpl_->max_column();
	 	}

	 	//! \brief Destructor
		//!        Closes Unsaved Documents.
		~sheet() {
		}
	};
} // namespace boost

#endif
