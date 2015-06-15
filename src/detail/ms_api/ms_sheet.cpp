//! \file
//! \brief Microsoft Office Sheet Functions
#ifndef _MS_SHEET_CPP
#define _MS_SHEET_CPP

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
#include <boost/document/detail/ms_api/ms_functions.hpp>
#include <boost/document/detail/document_exception.hpp>

namespace ms_func = boost::doc::ms_functions;

namespace boost { namespace doc { namespace ms_sheet {

//! \fn
//!
//!
void get_sheets_of_document(IDispatch*& sheets_ptr, IDispatch* book_ptr) {
	VARIANT result;
	VariantInit(&result);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, book_ptr, L"Sheets", 0);
	sheets_ptr = result.pdispVal;
}

//! \fn
//!
//!
void get_sheet_by_name(IDispatch *sheets_ptr, const std::string& sheet_name, IDispatch*& sheet_ptr) {
	VARIANT result;
	VARIANT vt_sheet;
	VariantInit(&result);
	vt_sheet.vt = VT_BSTR;
	vt_sheet.bstrVal = ms_func::string_to_BSTR(sheet_name);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheets_ptr, L"Sheets", 1,
		vt_sheet
		);
	sheet_ptr = result.pdispVal;
	VariantClear(&vt_sheet);
}

//! \fn
//!
//!
void get_sheet_by_index(IDispatch *sheets_ptr, int sheet_index, IDispatch*& sheet_ptr) {
	VARIANT result;
	VARIANT vt_sheet;
	VariantInit(&result);
	vt_sheet.vt = VT_I4;
	vt_sheet.lVal = sheet_index;
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheets_ptr, L"Sheets", 1,
		vt_sheet
		);
	sheet_ptr = result.pdispVal;
}

//! \fn
//!
//!
void get_active_sheet(IDispatch *sheets_ptr, IDispatch*& sheet_ptr) {
	VARIANT result;
	VariantInit(&result);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheets_ptr, L"ActiveSheet", 0);
	sheet_ptr = result.pdispVal;
}

//! \fn
//!
//!
void activate_sheet(IDispatch* sheet_ptr) {
	ms_func::auto_wrap_helper(DISPATCH_METHOD, NULL, sheet_ptr, L"Activate", 0);
}
	
}}}
#endif