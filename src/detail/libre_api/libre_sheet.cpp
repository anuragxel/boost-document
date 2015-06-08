//! \file
//! \brief Libre Office Sheet Related Internal Functions
#ifndef _LIBRE_SHEET_CPP
#define _LIBRE_SHEET_CPP

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

#include <boost/document/detail/document_file_format.hpp>
#include <boost/document/detail/document_exception.hpp>

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

namespace boost { namespace doc { namespace libre_sheet {


//! \fn Internal Function which returns all the sheets 
//!     of the spreadsheet.
//!
Reference< XSpreadsheets > get_sheets_of_document(
            Reference < XComponent > xComponent) {

    if(xComponent == NULL) {
         boost::throw_exception(document_exception(
            "Error: The Document is not open."));
    }
    Reference< XSpreadsheetDocument > xSheetDoc (xComponent, UNO_QUERY);
    try  {
        Reference< XSpreadsheets > xSheets = xSheetDoc->getSheets();
        return xSheets;
    }
    catch( Exception &e ){
      OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
      boost::throw_exception(document_exception(o.pData->buffer));
    }
}


//! \fn
//!
//!
Reference < XSpreadsheet > get_sheet_by_name(
            Reference< XSpreadsheets > xSheets,
                std::string sheetName) {
    try { 
        Any xSheetAny = xSheets->getByName(OUString::createFromAscii(sheetName.c_str())); 
        Reference < XSpreadsheet > xSheet (xSheetAny, UNO_QUERY);
        return xSheet;
    }
    catch( Exception &e ){
      OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
      boost::throw_exception(document_exception(o.pData->buffer));
    }
}


//! \fn
//!
//!
Reference < XSpreadsheet > get_sheet_by_index(
            Reference< XSpreadsheets > xSheets,
            int index) {
    try {
        Reference< XIndexAccess > xSheetsByIndex (xSheets, UNO_QUERY);  
        Any xSheetAny = xSheetsByIndex->getByIndex( (short)index ); 
        Reference < XSpreadsheet > xSheet (xSheetAny, UNO_QUERY);
        return xSheet;
    }
    catch( Exception &e ){
      OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
      boost::throw_exception(document_exception(o.pData->buffer));
   }
}


}}}

#endif