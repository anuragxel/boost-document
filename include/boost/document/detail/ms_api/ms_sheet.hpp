#ifndef _MS_SHEET_HPP
#define _MS_SHEET_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ole2.h>
#include <objbase.h>

#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>

#include <boost/document/detail/document_file_format.hpp>
#include <boost/document/detail/document_exception.hpp>

namespace boost { namespace doc { namespace ms_sheet {

void get_sheets_of_document(IDispatch*& sheets_ptr, IDispatch* book_ptr);
void get_sheet_by_name(IDispatch *sheets_ptr, const std::string& sheet_name, IDispatch*& sheet_ptr);
void get_sheet_by_index(IDispatch *sheets_ptr, int sheet_index, IDispatch*& sheet_ptr);
void get_active_sheet(IDispatch *sheets_ptr, IDispatch*& sheet_ptr);
void activate_sheet(IDispatch* sheet_ptr);

}}}
#endif