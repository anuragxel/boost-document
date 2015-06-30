#ifndef _MS_SHEET_IMPL_HPP
#define _MS_SHEET_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <memory>

#include <boost/filesystem.hpp>


#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/sheet_interface.hpp>
#include <boost/document/detail/cell_interface.hpp>

#include <boost/document/detail/ms_api/ms_sheet.hpp>


#include "cell_impl.hpp"

namespace boost {
	namespace detail {

		class ms_sheet : public sheet_interface {

		protected:
			IDispatch* sheet_ptr_;
			int index;
			std::string name;

		public:
			ms_sheet(IDispatch* sheet_ptr, int index) {
				this->sheet_ptr_ = sheet_ptr;
				this->index = index + 1; // we store index as per implementation needs
				this->name = boost::doc::ms_sheet::get_sheet_name(this->sheet_ptr_);
				boost::doc::ms_sheet::activate_sheet(this->sheet_ptr_);
			}

			ms_sheet(IDispatch* sheet_ptr, std::string& str) {
				this->sheet_ptr_ = sheet_ptr;
				this->name = str;
				this->index = boost::doc::ms_sheet::get_sheet_index(this->sheet_ptr_);
				boost::doc::ms_sheet::activate_sheet(this->sheet_ptr_); 
			}

			std::string sheet_name() {
				return this->name;
			}

			int sheet_index() {
				return this->index - 1; // we return index as we represent it as.
			}

			void rename_sheet(const std::string& str) {
				if (str.empty() || str == "") {
					boost::throw_exception(document_exception("Error: String Passed is Empty."));
				}
				boost::doc::ms_sheet::rename_sheet(this->sheet_ptr_, str);
				this->name = str;
			}

			boost::cell get_cell(int row, int column) {
				if( column < 0 || row < 0 || (std::size_t)row > max_row() || (std::size_t)column > max_column() ) {
					boost::throw_exception(document_exception("Error: Invalid Indices Provided."));
				}
				return boost::cell(std::dynamic_pointer_cast<cell_interface>(std::make_shared<boost::detail::ms_cell>()));
			}

			boost::cell get_cell_unchecked(int row, int column) {
				return boost::cell(std::dynamic_pointer_cast<cell_interface>(std::make_shared<boost::detail::ms_cell>()));
			}

			std::size_t max_row() {
				return 1024;
			}
			
			std::size_t max_column() {
				return 1024;
			}

			~ms_sheet() {

			}

		};

	}
} // namespace boost::detail


#endif