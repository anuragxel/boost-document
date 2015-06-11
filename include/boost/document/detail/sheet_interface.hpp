#ifndef _SHEET_INTERFACE_HPP
#define _SHEET_INTERFACE_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

namespace boost {

	class sheet_interface {
	 public:
	 	virtual std::string get_sheet_name() = 0;
	 	virtual int get_sheet_index() = 0;
	 	virtual void remame_sheet(const std::string& str) = 0;
		virtual ~sheet_interface() {}
	};	
} // namespace boost

#endif
