//! \file
//! \brief Libre Office Cell Related Internal Functions
#ifndef _LIBRE_CHART_FUNC_CPP
#define _LIBRE_CHART_FUNC_CPP

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

#include <com/sun/star/awt/Rectangle.hpp>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>

#include <com/sun/star/chart/XDiagram.hpp>
#include <com/sun/star/chart/XChartDocument.hpp>

#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/container/XNamed.hpp>

#include <com/sun/star/document/XEmbeddedObjectSupplier.hpp>

#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/table/CellRangeAddress.hpp>
#include <com/sun/star/table/XCellRange.hpp>
#include <com/sun/star/table/XTableChart.hpp>
#include <com/sun/star/table/XTableCharts.hpp>
#include <com/sun/star/table/XTableChartsSupplier.hpp>

#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
#include <com/sun/star/sheet/XSpreadsheet.hpp>
#include <com/sun/star/sheet/XCellRangeAddressable.hpp>

#include <boost/document/detail/chart_type.hpp>

#include <boost/document/detail/document_exception.hpp>

using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::sheet;
using namespace com::sun::star::table;
using namespace com::sun::star::chart;
using namespace com::sun::star::awt;
using namespace com::sun::star::sheet;
using namespace com::sun::star::container;
using namespace com::sun::star::document;

using namespace rtl;
using namespace cppu;

using ::rtl::OString;
using ::rtl::OUString;
using ::rtl::OUStringToOString;

namespace boost { namespace doc { namespace libre_chart_func {

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
    try {
      Rectangle oRect(left, top, width, height);

      Reference<XCellRange> oRange(xSheet, UNO_QUERY);
      Reference<XCellRange> xRange = oRange->getCellRangeByName(OUString::createFromAscii(cell_range.c_str()));
      Reference<XCellRangeAddressable> oRangeAddr(xRange, UNO_QUERY);
      CellRangeAddress xAddr = oRangeAddr->getRangeAddress();
      Sequence < CellRangeAddress > oAddr(1);
      oAddr[0] = xAddr;

      // Adding the chart to the destination
      Reference<XTableChartsSupplier> oSupp(xSheet, UNO_QUERY);
      Reference<XTableCharts> oCharts = oSupp->getCharts();
      oCharts->addNewByName(OUString::createFromAscii(name.c_str()), oRect, oAddr, true, true);

      // Get the XChartDocument object which is the Chart interface
      Reference<XNameAccess> xNamed(oCharts, UNO_QUERY);
      Any oChart = xNamed->getByName(OUString::createFromAscii(name.c_str()));
      Reference<XEmbeddedObjectSupplier> oEOS(oChart, UNO_QUERY);
      Reference<XInterface> oInt = oEOS->getEmbeddedObject();
      Reference<XChartDocument> xChart(oInt, UNO_QUERY);
      return xChart;
    }
    catch( Exception &e ){
        throw_document_exception(e);
    }
}


void delete_chart(Reference<XSpreadsheet> xSheet, const std::string& name) {
    try {
      Reference<XTableChartsSupplier> oSupp(xSheet, UNO_QUERY);
      Reference<XTableCharts> oCharts = oSupp->getCharts();
      oCharts->removeByName(OUString::createFromAscii(name.c_str()));
    }
    catch( Exception &e ){
        throw_document_exception(e);
    }
}

}}}

#endif
