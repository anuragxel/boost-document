#ifndef _LIBRE_SHEET_HPP
#define _LIBRE_SHEET_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

#include <boost/filesystem.hpp>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>

#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>

#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
#include <com/sun/star/sheet/XSpreadsheet.hpp>

namespace boost { namespace doc { namespace libre_sheet_func {

::com::sun::star::uno::Reference < com::sun::star::sheet::XSpreadsheets > get_sheets_of_document(::com::sun::star::uno::Reference < com::sun::star::sheet::XSpreadsheetDocument > xSheetDoc);
::com::sun::star::uno::Reference < com::sun::star::sheet::XSpreadsheet > get_sheet_by_name(com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheets > xSheets,const std::string& sheetName);
::com::sun::star::uno::Reference < com::sun::star::sheet::XSpreadsheet > insert_sheet_by_name(com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheets > xSheets,std::string sheetName);
::com::sun::star::uno::Reference < com::sun::star::sheet::XSpreadsheet > get_sheet_by_index(com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheets > xSheets, int index);
::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheetDocument > get_xSheetDoc(::com::sun::star::uno::Reference<com::sun::star::lang::XComponent> xComponent);
void rename_sheet(::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet > xSheet,const std::string& sheetName);
void delete_sheet_by_name(::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheets > xSheets, std::string str);
std::string get_sheet_name(::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet > xSheet);
int get_sheet_count(::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheets > xSheets);
int get_sheet_index(::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet > xSheet);

}}}
#endif