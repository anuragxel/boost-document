//! \file
//! \brief Microsoft Office Internal Functions
#ifndef _MS_FUNCTIONS_CPP
#define _MS_FUNCTIONS_CPP

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

namespace boost { namespace doc { namespace ms_functions {

//! \fn Returns the corresponding enum value given the
//!     the file extension.
//!
// XlFileFormats is an enum whose value needs to be provided to SaveAs
// for selecting the correct fileformat to save to.
// Look here for the enum values
// https://msdn.microsoft.com/en-us/library/bb241279%28v=office.12%29.aspx
// http://stackoverflow.com/questions/13407744/excel-how-to-find-the-default-file-extension
int get_filetype_from_file_ext(const std::string extension) {
	if (extension == ".xlsx" ) {
		return 51;
	}
	else if (extension == ".xlsb") {
		return 50;
	}
	else if (extension == ".xlsm") {
		return 52;
	}
	else if (extension == ".xls") {
		return 56;
	}
	else if (extension == ".ods") {
		return 60;
	}
	else if (extension == ".csv") {
		return 23;
	}
	else if (extension == ".xml") {
		return 46;
	}
	else {
		return 42;
	}
}
//! \fn Returns a string of type BSTR to be used 
//!     in all the COM API calls.
//!
//! Important to remember remember to delete the  
//! BSTR later. (BSTR is a pointer to another MS String type)
//! Either do delete [] ptr or VariantClear(&variant) as 
//! appropriate.
BSTR string_to_BSTR(const std::string& str) {
	int wslen = ::MultiByteToWideChar(CP_ACP, 0 ,str.c_str(), str.length(), NULL, 0);
	BSTR wsdata = ::SysAllocStringLen(NULL, wslen);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), wsdata, wslen);
	return wsdata;
}

//! \fn Returns a string of type std::string
//!     given a BSTR used in all the COM API calls.
//!
//! Important to remember remember to delete the  
//! BSTR later. (BSTR is a pointer to another MS String type)
//! Either do delete [] ptr or VariantClear(&variant) as 
//! appropriate.
std::string BSTR_to_string(const BSTR bstr) {
	int wslen = ::SysStringLen(bstr);
	int len = ::WideCharToMultiByte(CP_ACP, 0, (wchar_t*)bstr, wslen, NULL, 0, NULL, NULL);
	std::string str(len, '\0');
	len = ::WideCharToMultiByte(CP_ACP, 0, (wchar_t*)bstr, wslen, &str[0], len, NULL, NULL);
	return str;
}

//! \fn Helper function which makes the actual COM API Call
//!
//! int cArgs provides the number of arguments to the method.
//! All arguments after that of type VARIANT are sent during the method invokation
//! in ****REVERSE ORDER**** of their specification at the function call.
//! IDispatch *pDisp is the object pointer
//! LPOLESTR ptName is the method to be performed
//! VARIANT *pvResult can be used to obtain the results.
//! int autoType can be DISPATCH_PROPERTYGET, DISPATCH_PROPERTYPUT, DISPATCH_METHOD
void auto_wrap_helper(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...) {
    va_list marker;
    va_start(marker, cArgs);
    if(!pDisp) {
		boost::throw_exception(document_exception("Error: NULL IDispatch passed to AutoWrap()"));
    }
    DISPPARAMS dp = { NULL, NULL, 0, 0 };
    DISPID dispidNamed = DISPID_PROPERTYPUT;
    DISPID dispID;
    HRESULT hr;
    char szName[200];
    WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);
    hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
    if(FAILED(hr)) {
		boost::throw_exception(document_exception(
			"Error: IDispatch::GetIDsOfNames(" + std::string(szName) + ") failed w/err " +  std::to_string((int)hr)));
    }

	std::vector<VARIANT> pArgs(cArgs + 1);
	for (int i = 0; i<cArgs; i++) {
		pArgs[i] = va_arg(marker, VARIANT);
	}
	dp.cArgs = cArgs;
	dp.rgvarg = pArgs.data();
	if (autoType & DISPATCH_PROPERTYPUT) {
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
	}
	hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
	if (FAILED(hr)) {
		boost::throw_exception(document_exception(
			"Error: IDispatch::GetIDsOfNames(" + std::string(szName) + "=" +
			std::to_string((int)dispID) + ") failed w/err " + std::to_string((int)hr)));
	}
	va_end(marker);
}

//! \fn Helper Function to get the CLSID of The Excel
//!     Application to later get a pointer to Application
//!     object.
CLSID get_clsid() {
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(L"Excel.Application", &clsid);
	if(FAILED(hr)) {
		boost::throw_exception(document_exception(
		   "Error: CLSIDFromProgID() failed."));
	}
	return clsid;
}

//! \fn Gets the application Pointer
//!     from the clsid obtained.
//!
void get_application_pointer(CLSID clsid, IDispatch*& appl_ptr) {
	HRESULT hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **)&appl_ptr);
	if (FAILED(hr)) {
		boost::throw_exception(document_exception(
			"Error: Excel is not registered properly."));
	}
}

//! \fn Sets the visibility of the 
//!     Application GUI.
//!
void set_visibility(IDispatch *appl_ptr) {
	boost::detail::com_variant prop(1);
	auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, appl_ptr, L"Visible", 1, prop.native());
}

//! \fn Unsets the visibility of the
//!     Application GUI.
//!
void unset_visibility(IDispatch *appl_ptr) {
	boost::detail::com_variant prop(0);
	auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, appl_ptr, L"Visible", 1, prop.native());
}

//! \fn Suppress Warnings that are displayed as user
//!     dialog while performing certain methods. 
//!     Takes the default action provided in the
//!     dialog box.
void supress_warnings(IDispatch *appl_ptr,bool sure) {
	VARIANT prop;
	prop.vt = VT_I4;
	if (sure) {
		prop.lVal = 1;
	}
	else {
		prop.lVal = 0;
	}
	auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, appl_ptr, L"DisplayAlerts", 1, prop);
}

//! \fn Call application to quit
//!     and release the application 
//!     pointer.
void close_app(IDispatch*& appl_ptr) {
	// Application.Quit()
	auto_wrap_helper(DISPATCH_METHOD, NULL, appl_ptr, L"Quit", 0);
	appl_ptr->Release();
}

//! \fn Opens the file in the file path
//!     and attaches the book_pointer. 
void open_ms(const boost::filesystem::path& fpath, IDispatch *appl_ptr,IDispatch*& book_ptr) {
	if (!boost::filesystem::exists(fpath)) {
		boost::throw_exception(document_exception("Error: Path is empty or does not exist."));
	}
	// Create a new Workbook. (i.e. Application.Workbooks.Add)
	// Get the Workbooks collection
	IDispatch *pXlBooks = NULL;
	{
		VARIANT result;
		VariantInit(&result);
		auto_wrap_helper(DISPATCH_PROPERTYGET, &result, appl_ptr, L"Workbooks", 0);
		pXlBooks = result.pdispVal;
	}
	// Call Workbooks.open()
	{
		VARIANT result;
		VariantInit(&result);
		boost::detail::com_variant x(fpath);
		auto_wrap_helper(DISPATCH_METHOD, &result, pXlBooks, L"Open", 1, x.native());
		book_ptr = result.pdispVal;
	}
}

//! \fn Saves the file in the given file path.
//!     If there is an existing file, it deletes 
//!     the file and then saves it.
//!     Saves in the required format depending on the
//!     extension of the given file path.
void save_ms(const boost::filesystem::path &inputPath, IDispatch* appl_ptr,
	IDispatch*& book_ptr) {
	
	boost::detail::com_variant vt_file_name(inputPath);
	
	boost::detail::com_variant vt_format(get_filetype_from_file_ext(inputPath.extension().string()));
	
	supress_warnings(appl_ptr, true);

	if (boost::filesystem::exists(inputPath)) {
		boost::filesystem::remove(inputPath);
	}

	// Reverse order of params is important.
	auto_wrap_helper(DISPATCH_METHOD, NULL, book_ptr, L"SaveAs", 2, 
		vt_format.native(),
		vt_file_name.native()
		);
	
	supress_warnings(appl_ptr, false);
	
}

//! \fn Exports the file in the filepath
//!     and file format given, replacing 
//!     the extension as appropriate.
//!
//!     Calls ExportAsFixedFormat for PDF, normal
//!     save for the CSV and XML formats.
//!     XlFixedFormatType is an enum having
//!     XPS and PDF types.
//!		Also, XPS isn't supported, however
//!     XlFixedFormatType::xlTypeXPS = 1
//!     and can be changed in VARIANT vt_format
//!     appropriately.
void export_ms(const boost::filesystem::path& fpath,
	boost::document_file_format::type format, IDispatch* appl_ptr,
	IDispatch*& book_ptr) {	
	if (!boost::filesystem::exists(fpath)) {
		boost::throw_exception(document_exception(
			"Error: Path is empty or does not exist."));
	}
	boost::filesystem::path out_path(fpath);
	if (format == boost::document_file_format::PDF) {
		out_path.replace_extension(".pdf");
		
		boost::detail::com_variant vt_file_name(out_path);
		
		boost::detail::com_variant vt_format(0);
		
		// Reverse order of params is important.
		auto_wrap_helper(DISPATCH_METHOD, NULL, book_ptr, L"ExportAsFixedFormat", 2, 
			vt_file_name.native(),
			vt_format.native());
	}
	else if (format == boost::document_file_format::CSV) {
		out_path.replace_extension(".csv");
		save_ms(out_path, appl_ptr, book_ptr);
	}
	else if (format == boost::document_file_format::XML) {
		out_path.replace_extension(".xml");
		save_ms(out_path, appl_ptr, book_ptr);
	}
}

//! \fn Closes the specific document   
//!     being accessed and releases 
//!     the book_ptr.
void close_ms(const boost::filesystem::path& inp_path, bool save, 
		IDispatch* appl_ptr, IDispatch*& book_ptr) {
	if (save) {
		save_ms(inp_path, appl_ptr, book_ptr);
	}
	auto_wrap_helper(DISPATCH_METHOD, NULL, book_ptr, L"Close", 0);
	if (book_ptr != NULL) {
		book_ptr->Release();
	}
}

//! \fn Creates a new Document at the 
//!     file path given.
void create_ms(const boost::filesystem::path& path, IDispatch *appl_ptr, 
	IDispatch*& book_ptr) {
	// Create a new Workbook. (i.e. Application.Workbooks.Add)
	// Get the Workbooks collection
	IDispatch *pXlBooks = NULL;
	{
		VARIANT result;
		VariantInit(&result);
		auto_wrap_helper(DISPATCH_PROPERTYGET, &result, appl_ptr, L"Workbooks", 0);
		pXlBooks = result.pdispVal;
	}
	// Call Workbooks.Add() to get a new workbook
	{
		VARIANT result;
		VariantInit(&result);
		auto_wrap_helper(DISPATCH_METHOD, &result, pXlBooks, L"Add", 0);
		book_ptr = result.pdispVal;
	}
	save_ms(path, appl_ptr, book_ptr);
}

}}}

#endif
