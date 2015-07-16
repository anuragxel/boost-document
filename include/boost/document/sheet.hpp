#ifndef _SHEET_HPP
#define _SHEET_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <memory>

#include <boost/document/cell.hpp>
#include <boost/document/column.hpp>
#include <boost/document/row.hpp>

#include <boost/document/detail/sheet_interface.hpp>

#include <boost/document/detail/document_exception.hpp>

#include <utility>
#include <cctype>

namespace boost {

	namespace detail {
		std::pair<std::size_t,std::size_t> get_indices_from_address(const std::string& str) {
		    std::size_t row = 0;
		    std::size_t column = 0;
		    for(auto &c : str) {
		        if(!isdigit(c) && isupper(c)) {
		            row = row*26 + (c - 'A' + 1);
		        }
		        else if(!isdigit(c) && islower(c)) {
		            row = row*26 + (c - 'a'+ 1);
		        }
		        else {
		                column = column*10 + (c - '0');
		        }
		    }
		    // zero-indexed
		    row -= 1;
		    column -= 1;
		    return std::make_pair(row,column);
		}
	}

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
	 	std::size_t sheet_index() {
	 		return pimpl_->sheet_index();
	 	}

		//! \brief Renames the sheet to str
		//!        which is being accessed.
	 	void rename_sheet(const std::string& str) {
	 		pimpl_->rename_sheet(str);
	 	}

		//! Returns the maximum 
		//! number of rows
	 	std::size_t max_row() {
	 		return pimpl_->max_row();
	 	}

		//! Returns the maximum 
		//! number of columns
	 	std::size_t max_column() {
	 		return pimpl_->max_column();
	 	}

	 	//! Gets the cell instance
	 	//! which can be manipulated.
	 	boost::cell get_cell(std::size_t row, std::size_t column) {
	 		return pimpl_->get_cell(row,column);
	 	}


		//! Gets a row instance
		//!	which can be iterated
		//! over
		boost::row get_row(std::size_t i) {
			return boost::row(pimpl_,i);
		}


		//! Gets a column instance
		//!	which can be iterated
		//! over
		boost::column get_column(std::size_t i) {
			return boost::column(pimpl_,i);
		}

		//! Gets the column instance
	 	//! which can be manipulated.
	 	//! No Exception Handling.
		boost::column operator[](std::size_t i) {
			return boost::column(pimpl_,i);
		}

		//! Gets the cell instance
	 	//! which can be manipulated.
	 	//! No Exception Handling.
		boost::cell operator[](const std::string& str) {
			auto p = boost::detail::get_indices_from_address(str);
			return pimpl_->get_cell_unchecked(p.first,p.second);
		}
	 	
	 	//! \brief Destructor
		//!        Closes Unsaved Documents.
		~sheet() {
		}
	};
} // namespace boost

#endif
