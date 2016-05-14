//! \file
//! \brief Libre Office Sheet Related Internal Functions
#ifndef _LIBRE_SHEET_FUNC_CPP
#define _LIBRE_SHEET_FUNC_CPP

#include <string>
#include <iostream>
#include <cstdlib>

#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>

#include <sal/main.h>
#include <cppuhelper/bootstrap.hxx>
#include <osl/file.hxx>
#include <osl/process.h>
#include <rtl/process.h>
#include <rtl/bootstrap.hxx>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>

#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/frame/XStorable.hpp>
#include <com/sun/star/frame/XModel.hpp>

#include <com/sun/star/util/XCloseable.hpp>
#include <com/sun/star/util/XModifiable.hpp>

#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include <com/sun/star/registry/XSimpleRegistry.hpp>

#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
#include <com/sun/star/sheet/XSpreadsheet.hpp>

#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/container/XNamed.hpp>
#include <com/sun/star/container/XIndexContainer.hpp>

#include <boost/document/detail/document_file_format.hpp>
#include <boost/document/detail/document_exception.hpp>

#include <com/sun/star/sheet/XCellRangeAddressable.hpp>


using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::frame;
using namespace com::sun::star::registry;
using namespace com::sun::star::io;
using namespace com::sun::star::util;
using namespace com::sun::star::sheet;
using namespace com::sun::star::container;

using namespace rtl;
using namespace cppu;

using ::rtl::OString;
using ::rtl::OUString;
using ::rtl::OUStringToOString;

namespace boost { namespace doc { namespace libre_sheet_func {

//! \fn Returns the XSpreadsheetDocument interface
//!     which will be later used to find the XSpreadsheets
//!     interface.
Reference< XSpreadsheetDocument > get_xSheetDoc(
        Reference<XComponent> xComponent) {
    if(xComponent == NULL) {
         boost::throw_exception(document_exception(
            "Error: The Document is not open."));
    }
    try {
        Reference< XSpreadsheetDocument > xSheetDoc (xComponent, UNO_QUERY);
        return xSheetDoc;
    }
    catch( Exception &e ){
      OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
      boost::throw_exception(document_exception(o.pData->buffer));
    }
}

//! \fn Internal Function which returns all
//!     the sheets of the spreadsheet.Uses
//!     XSpreadsheets interface to do so.
Reference< XSpreadsheets > get_sheets_of_document(
            Reference < XSpreadsheetDocument > xSheetDoc) {
    try  {
        Reference< XSpreadsheets > xSheets = xSheetDoc->getSheets();
        return xSheets;
    }
    catch( Exception &e ){
      OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
      boost::throw_exception(document_exception(o.pData->buffer));
    }
}


//! \fn Gets the sheet Reference by name of the sheet
//!     provided. Raises an exception otherwise. Uses
//!     XSpreadsheets interface to do so.
Reference < XSpreadsheet > get_sheet_by_name(
            Reference< XSpreadsheets > xSheets,
                const std::string& sheetName) {
    if(sheetName.empty() or sheetName == "") {
        boost::throw_exception(document_exception(
            "Error: Sheet Name Not Specified.."));
    }
    try {
        Any xSheetAny = xSheets->getByName(OUString::createFromAscii(sheetName.c_str()));
        Reference < XSpreadsheet > xSheet(xSheetAny, UNO_QUERY);
        return xSheet;
    }
    catch( Exception &e ){
      OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
      boost::throw_exception(document_exception(o.pData->buffer));
    }
}

//! \fn Gets the sheet Reference by name of the sheet
//!     provided, no exception handling. Uses
//!     XSpreadsheets interface to do so.
Reference < XSpreadsheet > get_sheet_by_name_unchecked(
            Reference< XSpreadsheets > xSheets,
                const std::string& sheetName) {
    Any xSheetAny = xSheets->getByName(OUString::createFromAscii(sheetName.c_str()));
    Reference < XSpreadsheet > xSheet(xSheetAny, UNO_QUERY);
    return xSheet;
}



//! \fn Gets the sheet Reference by name of the sheet
//!     provided. Raises an exception otherwise.
//!     Uses XIndexAccess Interface to do so
//!     which acts as the indexing gateway.
Reference < XSpreadsheet > get_sheet_by_index(
            Reference< XSpreadsheets > xSheets,
            int index) {
    try {
        Reference< XIndexAccess > xSheetsByIndex (xSheets, UNO_QUERY);
        Any xSheetAny = xSheetsByIndex->getByIndex( (short)index );
        Reference < XSpreadsheet > xSheet(xSheetAny, UNO_QUERY);
        return xSheet;
    }
    catch( Exception &e ){
      OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
      boost::throw_exception(document_exception(o.pData->buffer));
   }
}


//! \fn Returns the sheet Reference by providing the index
//!     of the sheet, no exception handling.
//!     Uses XIndexAccess Interface to do so
//!     which acts as the indexing gateway.
Reference < XSpreadsheet > get_sheet_by_index_unchecked(
            Reference< XSpreadsheets > xSheets,
            int index) {
    Reference< XIndexAccess > xSheetsByIndex (xSheets, UNO_QUERY);
    Any xSheetAny = xSheetsByIndex->getByIndex( (short)index );
    Reference < XSpreadsheet > xSheet(xSheetAny, UNO_QUERY);
    return xSheet;
}


//! \fn Renames the sheet instance through the sheet name
//!     Raises an exception if there is some kind of conflict.
void rename_sheet(Reference< XSpreadsheet > xSheet,const std::string& sheetName) {
    if(sheetName.empty() or sheetName == "") {
        boost::throw_exception(document_exception(
            "Error: Sheet Name Not Specified.."));
    }
    try {
        Reference< XNamed > xName(xSheet, UNO_QUERY);
        xName->setName(OUString::createFromAscii(sheetName.c_str()));
    }
    catch( Exception &e ){
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}

//! \fn Gets the sheet count of the document
//!     as an integer. Uses XIndexAccess Interface to do so
//!     which acts as the indexing gateway and
//!     hence provides the count.
int get_sheet_count(Reference< XSpreadsheets > xSheets) {
    try {
        Reference< XIndexAccess > xSheetsByIndex (xSheets, UNO_QUERY);
        return xSheetsByIndex->getCount();
    }
    catch( Exception &e ){
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}


//! \fn Returns the sheet Reference after inserting
//!     it at 1st pos with name sheetName.
//!     Uses XSpreadsheets Interface to do so.
Reference < XSpreadsheet >  insert_sheet_by_name(Reference< XSpreadsheets> xSheets,std::string sheetName) {
    if(sheetName.empty() or sheetName == "") {
        boost::throw_exception(document_exception(
            "Error: Sheet Name Not Specified.."));
    }
    try {
        xSheets->insertNewByName(OUString::createFromAscii(sheetName.c_str()), (short)0);
        return get_sheet_by_name(xSheets, sheetName);
    }
    catch( Exception &e ){
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}

//! \fn Deletes the sheet by name.
//!     Uses XSpreadsheets Interface to do so.
void delete_sheet_by_name(Reference< XSpreadsheets > xSheets,std::string str) {
    if(str.empty() or str == "") {
        boost::throw_exception(document_exception(
            "Error: Sheet Name Not Specified.."));
    }
    try {
        xSheets->removeByName(OUString::createFromAscii(str.c_str()));
    }
    catch( Exception &e ){
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}

//! \fn Deletes the sheet by index.
//!     Uses XIndexContainer Interface to do so.
void delete_sheet_by_index(Reference< XSpreadsheets > xSheets,int index) {
    try {
        Reference < XIndexContainer > xIndexContainer(xSheets, UNO_QUERY);
        xIndexContainer->removeByIndex((short)index);
    }
    catch( Exception &e ){
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}

//! \fn
//!
//!
std::string get_sheet_name(Reference< XSpreadsheet > xSheet) {
    try {
        Reference< XNamed > xName(xSheet, UNO_QUERY);
        OString o = OUStringToOString( xName->getName(), RTL_TEXTENCODING_ASCII_US );
        return std::string(o.pData->buffer);
    }
    catch( Exception &e ){
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}


//! \fn
//!
//!
int get_sheet_index(Reference< XSpreadsheet > xSheet) {
    try {
        Reference < XCellRangeAddressable > xRangeAddr(xSheet, UNO_QUERY);
        ::com::sun::star::table::CellRangeAddress r = xRangeAddr->getRangeAddress();
        return r.Sheet;
    }
    catch( Exception &e ){
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}




}}}

#endif
