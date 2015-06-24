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

#include <boost/document/detail/libre_api/libre_cell_func.hpp>

namespace boost { namespace detail { 

class libre_cell: public cell_interface {

	protected:
	int row, column;
	::com::sun::star::uno::Reference < com::sun::star::table::XCell > xCell_;
	public:
	libre_cell(::com::sun::star::uno::Reference < com::sun::star::table::XCell >& xCell, int& row, int& column) {
		this->xCell_ = xCell;
		this->row = row;
		this->column = column;
	}

	void set_cell_value(const std::string& str) {
 		boost::doc::libre_cell_func::set_cell_value(this->xCell_, str);
	}

	void set_cell_value(float x) {
		boost::doc::libre_cell_func::set_cell_value(this->xCell_, x);
	}

 	~libre_cell() {
 	}

};

}} // namespace boost::detail


#endif
