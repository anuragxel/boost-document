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

#include <boost/document/detail/ms_api/com_variant.hpp>

namespace ms_func = boost::doc::ms_functions;

namespace boost { namespace doc { namespace ms_sheet {

//! \fn
//!
//!
void get_sheets_of_document(IDispatch*& sheets_ptr, IDispatch*& book_ptr) {
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
	boost::detail::com_variant vt_sheet(sheet_name);
	VariantInit(&result);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheets_ptr, L"Sheets", 1,
		vt_sheet.native()
		);
	sheet_ptr = result.pdispVal;
}

//! \fn
//!
//!
void get_sheet_by_index(IDispatch *sheets_ptr, int sheet_index, IDispatch*& sheet_ptr) {
	VARIANT result;
	boost::detail::com_variant vt_sheet(sheet_index);
	VariantInit(&result);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheets_ptr, L"Sheets", 1,
		vt_sheet.native()
		);
	sheet_ptr = result.pdispVal;
}


//! \fn
//!
//!
void delete_sheet_by_name(IDispatch *sheets_ptr, const std::string& str) {
	IDispatch *sheet_ptr;
	get_sheet_by_name(sheets_ptr, str, sheet_ptr);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, NULL, sheet_ptr, L"Delete", 0);
}

//! \fn
//!
//!
void delete_sheet_by_index(IDispatch *sheets_ptr, int index) {
	IDispatch *sheet_ptr;
	get_sheet_by_index(sheets_ptr, index, sheet_ptr);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, NULL, sheet_ptr, L"Delete", 0);
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
void activate_sheet(IDispatch *sheet_ptr) {
	ms_func::auto_wrap_helper(DISPATCH_METHOD, NULL, sheet_ptr, L"Activate", 0);
}

//! \fn
//!
//!
int get_sheet_count(IDispatch *sheets_ptr) {
	VARIANT result;
	VariantInit(&result);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheets_ptr, L"Count", 0);
	return result.lVal;
}

//! \fn
//!
//!
std::string get_sheet_name(IDispatch *sheet_ptr) {
	VARIANT result;
	VariantInit(&result);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"Name", 0);
	std::string str = boost::doc::ms_functions::BSTR_to_string(result.bstrVal);
	VariantClear(&result);
	return str;
}

//! \fn
//!
//!
int get_sheet_index(IDispatch *sheet_ptr) {
	VARIANT result;
	VariantInit(&result);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"Index", 0);
	return result.lVal;
}

//! \fn
//!
//!
void rename_sheet(IDispatch* sheet_ptr, const std::string& sheet_name) {
	boost::detail::com_variant vt_sheet_name(sheet_name);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, sheet_ptr, L"Name", 1,
		vt_sheet_name.native()
		);

}


//! \fn
//!
//!
void insert_new_sheet(IDispatch *sheets_ptr, const std::string& sheet_name, IDispatch*& sheet_ptr) {
	VARIANT result;
	VariantInit(&result);
	ms_func::auto_wrap_helper(DISPATCH_METHOD, &result, sheets_ptr, L"Add", 0);
	sheet_ptr = result.pdispVal;
	rename_sheet(sheet_ptr, sheet_name);
}


}}}

#endif