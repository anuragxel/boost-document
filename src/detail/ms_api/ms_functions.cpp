//! \file
//! \brief Microsoft Office Internal Functions
#ifndef _MS_FUNCTIONS_CPP
#define _MS_FUNCTIONS_CPP

// Copyright Anurag Ghosh 2015.
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ole2.h>

#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>

#include <boost/document/detail/document_file_format.hpp>
#include <boost/document/detail/libre_api/libre_functions.hpp>
#include <boost/document/detail/document_exception.hpp>

namespace boost { namespace doc { namespace ms_functions { 

HRESULT auto_wrap_helper(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...) {
    va_list marker;
    va_start(marker, cArgs);
    if(!pDisp) {
		boost::throw_exception(document_exception("Error: NULL IDispatch passed to AutoWrap()");
    }
    DISPPARAMS dp = { NULL, NULL, 0, 0 };
    DISPID dispidNamed = DISPID_PROPERTYPUT;
    DISPID dispID;
    HRESULT hr;
    char buf[200];
    char szName[200];
    WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);
    hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
    if(FAILED(hr)) {
		boost::throw_exception(document_exception(
			"Error: IDispatch::GetIDsOfNames(" + std::string(szName) + ") failed w/err " +  std::to_string((int)hr));
    }
    VARIANT *pArgs = new VARIANT[cArgs+1];
    for(int i=0; i<cArgs; i++) {
        pArgs[i] = va_arg(marker, VARIANT);
    }
    dp.cArgs = cArgs;
    dp.rgvarg = pArgs;
    if(autoType & DISPATCH_PROPERTYPUT) {
        dp.cNamedArgs = 1;
        dp.rgdispidNamedArgs = &dispidNamed;
    }
    hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
    if(FAILED(hr)) {
		boost::throw_exception(document_exception(
			"Error: IDispatch::GetIDsOfNames(" + std::string(szName) + "=" + 
					std::to_string((int)dispID) + ") failed w/err " + std::to_string((int)hr));
    }
    va_end(marker);
    delete [] pArgs;   
    return hr;
}

CLSID get_clsid() {
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(L"Excel.Application", &clsid);
	if(FAILED(hr)) {
		boost::throw_exception(document_exception(
		   "Error: CLSIDFromProgID() failed\n"));
	}
	return clsid;
}

void get_application_pointer(CLSID clsid, IDispatch *appl_ptr) {
	HRESULT hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **)&appl_ptr);
	if (FAILED(hr)) {
		boost::throw_exception(document_exception(
			"Error: Excel not registered properly\n"));
	}
}

void set_visibility(IDispatch *appl_ptr) {
	VARIANT prop;
	prop.vt = VT_I4;
	prop.lVal = 1;
	auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, appl_ptr, L"Visible", 1, prop);
}

void unset_visibility(IDispatch *appl_ptr) {
	VARIANT prop;
	prop.vt = VT_I4;
	prop.lVal = 0;
	auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, appl_ptr, L"Visible", 1, prop);
}

void create_ms(const boost::filesystem::path& path, IDispatch *appl_ptr, IDispatch **book_ptr) {
	// Create a new Workbook. (i.e. Application.Workbooks.Add)
	// Get the Workbooks collection
	IDispatch *pXlBooks = NULL;
	{
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, appl_ptr, L"Workbooks", 0);
		pXlBooks = result.pdispVal;
	}

	// Call Workbooks.Add() to get a new workbook
	{
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_METHOD, &result, pXlBooks, L"Add", 0);
		*book_ptr = result.pdispVal;
	}
}
void open_ms(const boost::filesystem::path& path, IDispatch *appl_ptr,IDispatch **book_ptr) {
	// Create a new Workbook. (i.e. Application.Workbooks.Add)
	// Get the Workbooks collection
	IDispatch *pXlBooks = NULL;
	{
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, appl_ptr, L"Workbooks", 0);
		pXlBooks = result.pdispVal;
	}

	// Call Workbooks.open()
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT x;
		x.vt = VT_BSTR;
		x.bstrVal = ::SysAllocString(path.string().c_str());
		AutoWrap(DISPATCH_METHOD, &result, pXlBooks, L"Open", 1, x);
		*book_ptr = result.pdispVal;
	}
}

void export_ms(const boost::filesystem::path& inputPath,
	boost::document_file_format::type format,
	IDispatch *appl_ptr, IDispatch *book_ptr) {
	
}

void close_ms(const boost::filesystem::path &inputPath, bool save, 
			IDispatch *appl_ptr, IDispatch *book_ptr) {

}

void save_ms(const boost::filesystem::path &inputPath, 
			IDispatch *appl_ptr, IDispatch *book_ptr) {

}

}}}

#endif
