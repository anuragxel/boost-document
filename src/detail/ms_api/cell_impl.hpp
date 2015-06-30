#ifndef _MS_CELL_IMPL_HPP
#define _MS_CELL_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <memory>

#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/cell_interface.hpp>
#include <boost/document/detail/cell_content_type.hpp>

namespace boost { namespace detail { 

class ms_cell : public cell_interface {

	protected:
	int row, column;
	public:
	ms_cell() {
	}

	void set_cell_value(const std::string& str) {
	}

	void set_cell_value(double x) {
	}

	boost::cell_content_type::type get_content_type() {
		return boost::cell_content_type::EMPTY;
	}

	std::string get_string() {
		return "";
	}


	std::string get_formula() {
		return "";
	}

	double get_value() {
		return -1.0;
	}
 
	bool empty() {
		return true;
	}

 	~ms_cell() {
 	}

};

}} // namespace boost::detail


#endif
