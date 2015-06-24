#ifndef _CELL_INTERFACE_HPP
#define _CELL_INTERFACE_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

namespace boost {

	class cell_interface {
	 public:
	 	virtual void set_cell_value(const std::string& str) = 0;
    	virtual void set_cell_value(float i) = 0;
   		virtual ~cell_interface() {}
	};	
} // namespace boost

#endif
