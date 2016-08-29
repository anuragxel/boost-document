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
#include <boost/lexical_cast.hpp>

#include <boost/document/detail/document_file_format.hpp>

#include <boost/document/detail/cell_content_type.hpp>
#include <boost/document/detail/cell_alignment_type.hpp>

#include <boost/document/detail/document_exception.hpp>

#include <boost/document/detail/ms_api/com_variant.hpp>
#include <boost/document/detail/ms_api/ms_functions.hpp>

namespace boost { namespace doc { namespace ms_cell_func {

//! \fn https://msdn.microsoft.com/en-us/library/bb687869(v=office.12).aspx
//!     Gets the representation of the cell row and column as string.
std::string get_cell_str(int row, int column) {
	std::string result = "";
	while(column != 0) {
		result += (char)(column%26 + 'A');
		column /= 26;
	}
	result += boost::lexical_cast<std::string>(row);
	return result;
}

void get_cell(IDispatch* sheet_ptr,int i, int j, IDispatch*& cell_ptr) {
	VARIANT result;
	VariantInit(&result);
	boost::detail::com_variant vt_cell(get_cell_str(i,j));
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"Range", 1,
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
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, cell_ptr, L"Value", 1,
		vt_cell.native()
		);
}

//! \fn Sets Cell value as string str
void set_cell_value(IDispatch* cell_ptr,double x) {
	boost::detail::com_variant vt_cell(x);
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, cell_ptr, L"Value", 1,
		vt_cell.native()
		);
}

//! \fn Sets Cell formula as string str
void set_cell_formula(IDispatch* cell_ptr, const std::string& str) {
	boost::detail::com_variant vt_cell(str);
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, cell_ptr, L"Formula", 1,
		vt_cell.native()
		);
}


//! \fn Gets the string value of the cell if
//!     it is present.
std::string get_string(IDispatch* cell_ptr) {
	VARIANT result;
	VariantInit(&result);
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, cell_ptr, L"Text", 0);
	std::string s = boost::doc::ms_functions::BSTR_to_string(result.bstrVal);
	VariantClear(&result);
	return s;
}


//! \fn Gets the formula of the cell if
//!     it is present.
std::string get_formula(IDispatch* cell_ptr) {
	VARIANT result;
	VariantInit(&result);
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, cell_ptr, L"Formula", 0);
	return boost::doc::ms_functions::BSTR_to_string(result.bstrVal);
}


//! \fn Gets the float value of the cell if
//!     it is present.
double get_value(IDispatch* cell_ptr) {
	VARIANT result;
	VariantInit(&result);
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, cell_ptr, L"Value", 0);
	return result.dblVal;
}

//! \fn Gets the content type of the cell in Excel
//! https://fastexcel.wordpress.com/2011/11/30/text-vs-value-vs-value2-slow-text-and-how-to-avoid-it/
boost::cell_content_type::type get_content_type(IDispatch* cell_ptr) {
	VARIANT result;
	VariantInit(&result);
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, cell_ptr, L"Value2", 0);
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
	return boost::cell_content_type::ERROR;
}

//! \fn
//!
void set_style(IDispatch* cell_ptr, const std::string& str) {

}

//! \fn
//!
void set_foreground_color(IDispatch* cell_ptr, int x) { 
	IDispatch *font_ptr = NULL;
	VARIANT result;
	VariantInit(&result);
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, font_ptr, L"Font",0);
	font_ptr = result.pdispVal;
	
	// x is of the form, 0x00bbggrr
	boost::detail::com_variant vt_cell( x );
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, font_ptr, L"Color", 1, 
		vt_cell.native()
	);
}

//! \fn
//!
void set_background_color(IDispatch* cell_ptr, int x) {
	IDispatch *interior_ptr = NULL;
	VARIANT result;
	VariantInit(&result);
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, cell_ptr, L"Interior",0);
	interior_ptr=result.pdispVal;
	// x is of the form, 0x00bbggrr
	boost::detail::com_variant vt_cell( x );
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, interior_ptr, L"Color", 1, 
		vt_cell.native()
	);
}

//! \fn
//!
void set_font_size(IDispatch* cell_ptr, double x) {
	IDispatch *font_ptr = NULL;
	VARIANT result;
	VariantInit(&result);
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, font_ptr, L"Font",0);
	font_ptr = result.pdispVal;
	
	// font size is integer in Excel COM API :/
	boost::detail::com_variant vt_cell( (int) x );
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, font_ptr, L"Size", 1, 
		vt_cell.native()
	);

}

//! \fn
//!
void set_horizontal_alignment(IDispatch* cell_ptr, boost::cell_horizontal_alignment::type t) {
	// Left: -4131 Center: -4108  Right: -4152 
	// https://msdn.microsoft.com/en-us/library/microsoft.office.interop.excel.constants.aspx
	int x = -4108;
	if(t == boost::cell_horizontal_alignment::RIGHT) {
		x = -4152;
	}
	else if(t == boost::cell_horizontal_alignment::LEFT) {
		x = -4131;
	}
	boost::detail::com_variant vt_cell(x);
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, cell_ptr, L"HorizontalAlignment", 1, 
		vt_cell.native()
		);
}

//! \fn
//!
void set_vertical_alignment(IDispatch* cell_ptr, boost::cell_vertical_alignment::type t) {
	// Top: -4160 Bottom: -4107 Center: -4108
	// https://msdn.microsoft.com/en-us/library/microsoft.office.interop.excel.constants.aspx
	int x = -4108;
	if(t == boost::cell_vertical_alignment::BOTTOM) {
		x = -4107;
	}
	else if(t == boost::cell_vertical_alignment::TOP) {
		x = -4160;
	}
	boost::detail::com_variant vt_cell(x);
	boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, cell_ptr, L"VerticalAlignment", 1, 
		vt_cell.native()
		);
}

}}}

#endif
