//! \file
//! \brief Libre Office Cell Related Internal Functions
#ifndef _LIBRE_CELL_FUNC_CPP
#define _LIBRE_CELL_FUNC_CPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <iostream>
#include <cstdlib>

#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>

#include <sal/main.h>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>

#include <com/sun/star/chart/XDiagram.hpp>
#include <com/sun/star/chart/XChartDocument.hpp>

#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/container/XNameAccess.hpp>

#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/table/CellRangeAddress.hpp>
#include <com/sun/star/table/XCellRange.hpp>
#include <com/sun/star/table/XTableChart.hpp>
#include <com/sun/star/table/XTableCharts.hpp>
#include <com/sun/star/table/XTableChartsSupplier.hpp>

#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
#include <com/sun/star/sheet/XSpreadsheet.hpp>

#include <boost/document/detail/chart_type.hpp>

#include <boost/document/detail/document_exception.hpp>

using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::registry;
using namespace com::sun::star::sheet;
using namespace com::sun::star::table;
using namespace com::sun::star::chart;
using namespace com::sun::star::text;

using namespace rtl;
using namespace cppu;

using ::rtl::OString;
using ::rtl::OUString;
using ::rtl::OUStringToOString;

namespace boost { namespace doc { namespace libre_cell_func {

//! \fn Helper function to throw an unwrapped
//!     exception
//!
void throw_document_exception(Exception& e) {
    OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
    boost::throw_exception(document_exception(o.pData->buffer));
}

Reference < XChartDocument >
add_chart(Reference<XSpreadsheet> xSheet, const std::string& name, const std::string& cell_range,
                          int left, int top, int width, int height, boost::chart_type::type t) {
    return NULL;
}

void delete_chart(Reference<XSpreadsheet> xSheet, const std::string& name) {

}



}}}

#endif
