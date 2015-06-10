#ifndef _LIBRE_SHEET_IMPL_HPP
#define _LIBRE_SHEET_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/filesystem.hpp>

#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/sheet_interface.hpp>

#include <boost/document/detail/libre_api/libre_sheet.hpp>

namespace boost { namespace detail { 

class libre_sheet: public sheet_interface {
	
	
	std::string get_sheet_name() {
		return "sheet";
	}

	int get_sheet_index() {
		return 1;
	}

	void remame_sheet(const std::string& str) {
	 	
	}

	void delete_sheet() {
		
	}

 	~libre_sheet() {
 		
 	}

};

sheet_interface* open_libre_sheet_instance() {
	return new libre_sheet();
}

}} // namespace boost::detail


#endif
