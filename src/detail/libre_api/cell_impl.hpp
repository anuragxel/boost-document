#ifndef _LIBRE_CELL_IMPL_HPP
#define _LIBRE_CELL_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/cell_interface.hpp>

#include <boost/document/detail/cell_content_type.hpp>
#include <boost/document/detail/cell_alignment_type.hpp>

#include <boost/document/detail/libre_api/libre_cell_func.hpp>

namespace boost { namespace detail {

class libre_cell : public cell_interface {

	protected:
	std::size_t row_, column_;
	::com::sun::star::uno::Reference < com::sun::star::table::XCell > xCell_;
	public:
	libre_cell(const ::com::sun::star::uno::Reference < com::sun::star::table::XCell >& xCell, std::size_t row, std::size_t column) {
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

	void reset() {
		boost::doc::libre_cell_func::reset(this->xCell_);
	}

	void set_style(const std::string& str) {
		boost::doc::libre_cell_func::set_cell_style(this->xCell_, str);
	}

	void set_foreground_color(int x) {
		boost::doc::libre_cell_func::set_cell_foreground_color(this->xCell_, x);
	}

	void set_background_color(int x) {
		boost::doc::libre_cell_func::set_cell_background_color(this->xCell_, x);
	}

	void set_font_size(double x) {
		boost::doc::libre_cell_func::set_cell_font_size(this->xCell_, x);
	}

	void set_horizontal_alignment(boost::cell_horizontal_alignment::type t) {
		boost::doc::libre_cell_func::set_cell_horizontal_alignment(this->xCell_, t);
	}

	void set_vertical_alignment(boost::cell_vertical_alignment::type t) {
		boost::doc::libre_cell_func::set_cell_vertical_alignment(this->xCell_, t);
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
		if(boost::doc::libre_cell_func::get_content_type(this->xCell_) == boost::cell_content_type::EMPTY) {
			return true;
		}
		return false;
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
