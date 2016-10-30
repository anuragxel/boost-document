#ifndef _MS_SHEET_IMPL_HPP
#define _MS_SHEET_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>


#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>


#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/sheet_interface.hpp>
#include <boost/document/detail/cell_interface.hpp>
#include <boost/document/detail/chart_interface.hpp>

#include <boost/document/detail/ms_api/ms_sheet.hpp>
#include <boost/document/detail/ms_api/ms_cell_func.hpp>
#include <boost/document/detail/ms_api/ms_chart_func.hpp>

#include <boost/document/detail/chart_type.hpp>

#include "chart_impl.hpp"
#include "cell_impl.hpp"

namespace boost {
	namespace detail {

		class ms_sheet : public sheet_interface {

		protected:
			IDispatch* sheet_ptr_;
			std::size_t index;
			std::string name;

		public:
			ms_sheet(IDispatch*& sheet_ptr, std::size_t& index) {
				this->sheet_ptr_ = sheet_ptr;
				this->index = index + 1; // we store index as per implementation needs
				this->name = boost::doc::ms_sheet::get_sheet_name(this->sheet_ptr_);
				boost::doc::ms_sheet::activate_sheet(this->sheet_ptr_);
			}

			ms_sheet(IDispatch*& sheet_ptr, std::string& str) {
				this->sheet_ptr_ = sheet_ptr;
				this->name = str;
				this->index = (std::size_t)boost::doc::ms_sheet::get_sheet_index(this->sheet_ptr_);
				boost::doc::ms_sheet::activate_sheet(this->sheet_ptr_);
			}

			std::string sheet_name() {
				return this->name;
			}

			std::size_t sheet_index() {
				return (std::size_t)this->index - 1; // we return index as we represent it as.
			}

			void rename_sheet(const std::string& str) {
				if (str.empty() || str == "") {
					boost::throw_exception(document_exception("Error: String Passed is Empty."));
				}
				boost::doc::ms_sheet::rename_sheet(this->sheet_ptr_, str);
				this->name = str;
			}

			boost::cell get_cell(std::size_t row, std::size_t column) {
				if( row > max_row() || column > max_column() ) {
					boost::throw_exception(document_exception("Error: Invalid Indices Provided."));
				}
				IDispatch* cell_ptr;
				boost::doc::ms_cell_func::get_cell(this->sheet_ptr_,row + 1,column + 1,cell_ptr);
				return boost::cell(boost::dynamic_pointer_cast<cell_interface>(boost::make_shared<boost::detail::ms_cell>(cell_ptr,row,column)));
			}

			boost::cell get_cell_unchecked(std::size_t row,std::size_t column) {
				IDispatch* cell_ptr;
				boost::doc::ms_cell_func::get_cell_unchecked(this->sheet_ptr_,row + 1,column + 1,cell_ptr);
				return boost::cell(boost::dynamic_pointer_cast<cell_interface>(boost::make_shared<boost::detail::ms_cell>(cell_ptr,row,column)));
			}

			std::size_t max_row() {
				return 1024;
			}

			std::size_t max_column() {
				return 1024;
			}

			boost::chart add_chart(const std::string& name, const std::string& cell_range, std::size_t left, std::size_t top, std::size_t width, std::size_t height) {
				IDispatch* chart_ptr;
				boost::doc::ms_chart_func::add_chart(this->sheet_ptr_, name, cell_range, left, top, width, height, chart_ptr);
				return boost::chart(boost::dynamic_pointer_cast<chart_interface>(boost::make_shared<boost::detail::ms_chart>(chart_ptr, this->sheet_ptr_, name, cell_range, (int)left, (int)top, (int)width, (int)height)));
			}

			boost::chart get_chart(const std::string& name) {
				IDispatch* chart_ptr;				
				boost::doc::ms_chart_func::get_chart(this->sheet_ptr_, name, chart_ptr);
				return boost::chart(boost::dynamic_pointer_cast<chart_interface>(boost::make_shared<boost::detail::ms_chart>(chart_ptr, this->sheet_ptr_, name, "", 0, 0, 0, 0)));
			}

			void delete_chart(const std::string& name) {
				boost::doc::ms_chart_func::delete_chart(this->sheet_ptr_, name);
			}
			
			~ms_sheet() {
				sheet_ptr_->Release();
			}

		};

	}
} // namespace boost::detail


#endif
