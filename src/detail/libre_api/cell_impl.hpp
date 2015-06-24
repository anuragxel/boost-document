#ifndef _LIBRE_SHEET_IMPL_HPP
#define _LIBRE_SHEET_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <memory>

#include <boost/filesystem.hpp>


#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/cell_interface.hpp>

#include <boost/document/detail/libre_api/libre_cell_func.hpp>

namespace boost { namespace detail { 

class libre_cell: public cell_interface {

	protected:
	int row, column;
	Reference < XCell > xCell;
	public:
	libre_cell(int row, int column, Reference < XCell > xCell) {
		this->xCell = xCell;
		this->row = row;
		this->column = column;
	}

	void set_cell_value(const std::string& str) {

	}

	void set_cell_value(int i) {

	}

 	~libre_cell() {
 		
 	}

};

}} // namespace boost::detail


#endif
