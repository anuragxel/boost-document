#ifndef _LIBRE_CELL_IMPL_HPP
#define _LIBRE_CELL_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <memory>

#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/cell_interface.hpp>
#include <boost/document/detail/cell_content_type.hpp>

#include <boost/document/detail/libre_api/libre_cell_func.hpp>

namespace boost { namespace detail {

class libre_cell : public cell_interface {

	protected:
	std::size_t row_, column_;
	::com::sun::star::uno::Reference < com::sun::star::table::XCell > xCell_;
	public:
	libre_cell(::com::sun::star::uno::Reference < com::sun::star::table::XCell >& xCell, std::size_t& row, std::size_t& column) {
		this->xCell_ = xCell;
		this->row_ = row;
		this->column_ = column;
	}

	void set_cell_formula(const std::string& str) {
 		boost::doc::libre_cell_func::set_cell_value(this->xCell_, str);
	}

	void set_cell_value(const std::string& str) {
 		boost::doc::libre_cell_func::set_cell_value(this->xCell_, str);
	}

	void set_cell_value(double x) {
		boost::doc::libre_cell_func::set_cell_value(this->xCell_, x);
	}

	boost::cell_content_type::type get_content_type() const {
		return boost::doc::libre_cell_func::get_content_type(this->xCell_);
	}

	std::string get_string() const {
		return boost::doc::libre_cell_func::get_string(this->xCell_);
	}


	std::string get_formula() const {
		return boost::doc::libre_cell_func::get_formula(this->xCell_);
	}

	double get_value() const {
		return boost::doc::libre_cell_func::get_value(this->xCell_);
	}

	bool empty() const {
		if(boost::doc::libre_cell_func::get_content_type(this->xCell_) == boost::cell_content_type::type::EMPTY) {
			return true;
		}
		return false;
	}

	void reset() {
		boost::doc::libre_cell_func::reset(this->xCell_);
	}

	std::size_t get_row_index() const {
		return row_;
	}

	std::size_t get_column_index() const {
		return column_;
	}

 	~libre_cell() {
 	}

};

}} // namespace boost::detail


#endif
