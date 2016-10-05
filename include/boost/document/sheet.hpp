#ifndef _SHEET_HPP
#define _SHEET_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/document/cell.hpp>
#include <boost/document/column.hpp>
#include <boost/document/row.hpp>


#include <boost/document/detail/sheet_interface.hpp>
#include <boost/document/detail/chart_interface.hpp>
#include <boost/document/detail/chart_type.hpp>

#include <boost/document/detail/document_exception.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <utility>
#include <cctype>

namespace boost {

	//! \brief This is the main class interface to be
	//!        exposed to the library user.
	//!
	class sheet {
	private:
		boost::shared_ptr<sheet_interface> pimpl_;

		//! \brief The function takes the string representation
		//!        of the index which is of the form [a-Z]+[0-9]+
		//!        and parses it to obtain the row and the
		//!        column values and with it, the cell instance
		//!        corresponding to the index.
		boost::cell cell_idx_from_string(const char* str, std::size_t length) {
			std::size_t row = 0;
			std::size_t column = 0;
			bool numbers = false; // initially no numbers
			bool alph = false;

			for (std::size_t i = 0; i < length; ++i) {
				const char c = str[i];
				if(!isdigit(c)) {
					alph = true;
					if(numbers || !isalpha(c)) {
						boost::throw_exception(document_exception(
							"Invalid index error: index must start with letters, followed by numbers"));
					}
					column = column*26 + (c + 1);
					if(isupper(c)) {
						column -= 'A';
					}
					else {
						column -= 'a';
					}
				}
				else {
					if(!alph) { // doesn't start with alphabet
						boost::throw_exception(document_exception(
							"Invalid index error: index must start with letters, followed by numbers"));
					}
					numbers = true; // as soon as first number comes
					row = row*10 + (c - '0');
				}
			}

			if (row == 0) {
			    boost::throw_exception(document_exception(
			        "Invalid index error: row number must be greater than 0"
			    ));
			}

			// zero-indexed
			column -= 1;
			row -= 1;
			return pimpl_->get_cell_unchecked(row,column);
		}
	public:
		//! \brief The Constructor.
		//!        Creates a new document object.
		explicit sheet(const boost::shared_ptr<sheet_interface> impl) : pimpl_(impl) {

		}
		//! \brief Gets the sheet name
		//!        which is being accessed.
		std::string sheet_name() const {
			return pimpl_->sheet_name();
		}

		//! \brief Gets the sheet index
		//!        which is being accessed.
		std::size_t sheet_index() const {
			return pimpl_->sheet_index();
		}

		//! \brief Renames the sheet to str
		//!        which is being accessed.
		void rename_sheet(const std::string& str) {
			pimpl_->rename_sheet(str);
		}

		//! \brief Returns the maximum
		//!        number of rows
		std::size_t max_row() const {
			return pimpl_->max_row();
		}

		//! \brief Returns the maximum
		//!        number of columns
		std::size_t max_column() const {
			return pimpl_->max_column();
		}

		//! \brief Gets the cell instance
		//!        corresponding to the row and column
		//!        which can be manipulated.
		boost::cell get_cell(std::size_t row, std::size_t column) {
			return pimpl_->get_cell(row,column);
		}


		//! \brief Gets a row instance
		//!	       which can be iterated
		//!        over
		boost::row get_row(std::size_t i) {
			return boost::row(pimpl_,i);
		}


		//! \brief Gets a column instance
		//!	       which can be iterated
		//!        over
		boost::column get_column(std::size_t i) {
			return boost::column(pimpl_,i);
		}

		//! \brief Gets the column instance
		//!        which can be manipulated.
		//!        No Exception Handling.
		boost::column operator[](std::size_t i) {
			return boost::column(pimpl_,i);
		}


		//! \brief Gets the column instance
		//!        which can be manipulated.
		//!        No Exception Handling.
		boost::column operator[](int i) {
			return boost::column(pimpl_,(std::size_t)i);
		}

		//! \brief Gets the cell instance
		//!        which can be manipulated.
		//!        No Exception Handling.
		boost::cell operator[](const std::string& str) {
			return cell_idx_from_string(str.data(),str.length());
		}

		//! \brief Gets the cell instance
		//!        which can be manipulated.
		//!        No Exception Handling.
		boost::cell operator[](const char* str) {
		    return cell_idx_from_string(str, std::strlen(str));
		}

		//! \brief Adds a chart to the sheet over cell_range,
		//!        at position (left, top) with size (width, height)
		//!        and of type boost::chart_type::type
		//!        A cell range corresponds to a string of the form
		//!        cell:cell where cell is [A-Z]+[0-9]+. The contiguous
		//!        range is taken as the input data.
		boost::chart add_chart(const std::string& name, const std::string& cell_range,
				std::size_t left, std::size_t top, std::size_t width,
				std::size_t height, boost::chart_type::type t, bool enable_3d) {
				return pimpl_->add_chart(name, cell_range, left, top, width, height, t, enable_3d);
		}

		//! \brief Deletes a chart of the
		//! 			 name 'name'
		void delete_chart(const std::string& name) {
				return pimpl_->delete_chart(name);
		}

		//! \brief Destructor
		//!        Sheet instance is destroyed.
		~sheet() {
		}
	};
} // namespace boost

#endif
