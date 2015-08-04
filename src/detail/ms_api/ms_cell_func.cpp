#ifndef _MS_CELL_FUNC_CPP
#define _MS_CELL_FUNC_CPP

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

#include <boost/document/detail/ms_api/com_variant.hpp>
#include <boost/document/detail/ms_api/ms_functions.hpp>

namespace ms_func = boost::doc::ms_functions;

namespace boost { namespace doc { namespace ms_cell_func {

//! \fn https://msdn.microsoft.com/en-us/library/bb687869(v=office.12).aspx
//!     Gets the representation of the cell row and column as string.
std::string get_cell_str(int row, int column) {
	std::string result = "";
	while(column != 0) {
		result += (char)(column%26 + 'A');
		column /= 26;
	}
	result += std::to_string(row);
	return result;
}

void get_cell(IDispatch* sheet_ptr,int i, int j, IDispatch*& cell_ptr) {
	VARIANT result;
	VariantInit(&result);
	boost::detail::com_variant vt_cell(get_cell_str(i,j));
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"Range", 1, 
		vt_cell.native()
		);
	cell_ptr = result.pdispVal;
}

void get_cell_unchecked(IDispatch* sheet_ptr,int i, int j, IDispatch*& cell_ptr) {
	get_cell(sheet_ptr,i,j,cell_ptr);
}

//! \fn Sets Cell value as float str
void set_cell_value(IDispatch* cell_ptr,const std::string& str) {
	boost::detail::com_variant vt_cell(str);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, cell_ptr, L"Value", 1, 
		vt_cell.native()
		);
}

//! \fn Sets Cell value as string str
void set_cell_value(IDispatch* cell_ptr,double x) {
	boost::detail::com_variant vt_cell(x);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, cell_ptr, L"Value", 1, 
		vt_cell.native()
		);
}

//! \fn Sets Cell formula as string str
void set_cell_formula(IDispatch* cell_ptr, const std::string& str) {
	boost::detail::com_variant vt_cell(str);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, cell_ptr, L"Formula", 1, 
		vt_cell.native()
		);
}


//! \fn Gets the string value of the cell if 
//!     it is present.
std::string get_string(IDispatch* cell_ptr) {
	VARIANT result;
	VariantInit(&result);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, cell_ptr, L"Text", 0);
	std::string s = ms_func::BSTR_to_string(result.bstrVal);
	VariantClear(&result);
	return s;
}


//! \fn Gets the formula of the cell if 
//!     it is present.
std::string get_formula(IDispatch* cell_ptr) {
	VARIANT result;
	VariantInit(&result);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, cell_ptr, L"Formula", 0);
	return ms_func::BSTR_to_string(result.bstrVal);
}


//! \fn Gets the float value of the cell if 
//!     it is present.
double get_value(IDispatch* cell_ptr) {
	VARIANT result;
	VariantInit(&result);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, cell_ptr, L"Value", 0);
	return result.dblVal;
}

//! \fn Gets the content type of the cell in Excel
//! https://fastexcel.wordpress.com/2011/11/30/text-vs-value-vs-value2-slow-text-and-how-to-avoid-it/
boost::cell_content_type::type get_content_type(IDispatch* cell_ptr) {
	VARIANT result;
	VariantInit(&result);
	ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, cell_ptr, L"Value2", 0);
	int vt = result.vt;
	VariantClear(&result);
	switch(vt) {
		case VT_I4:
		case VT_R8:
			return boost::cell_content_type::VALUE;
		case VT_BSTR:
			return boost::cell_content_type::STRING;
		case VT_ERROR:
			return boost::cell_content_type::ERROR;
		case VT_EMPTY:
		case VT_NULL:
		case VT_VOID:
			return boost::cell_content_type::EMPTY;
	} //EMPTY,STRING,VALUE,FORMULA,ERROR
}

}}}

#endif