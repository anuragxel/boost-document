#ifndef _CELL_DATA_HPP
#define _CELL_DATA_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/document/detail/cell_content_type.hpp>
#include <boost/variant.hpp>


namespace boost {

  class cell;

  struct cell_data {
    cell_data() {}
    cell_data(const cell_data& c) : type(c.type), value(c.value), formula_val(c.formula_val) {}
    cell_data(const cell& c);
    boost::cell_content_type::type type;
    boost::variant<double, std::string> value;
    double formula_val; // How else to handle ?
	};

} // namespace boost

#endif
