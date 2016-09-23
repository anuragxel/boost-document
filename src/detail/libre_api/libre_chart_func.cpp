//! \file
//! \brief Libre Office Cell Related Internal Functions
#ifndef _LIBRE_CHART_FUNC_CPP
#define _LIBRE_CHART_FUNC_CPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>

#include <com/sun/star/awt/Rectangle.hpp>

#include <com/sun/star/beans/Property.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/beans/XPropertySetInfo.hpp>

#include <com/sun/star/chart/XDiagram.hpp>
#include <com/sun/star/chart/XChartDocument.hpp>

#include <com/sun/star/container/XNameAccess.hpp>

#include <com/sun/star/document/XEmbeddedObjectSupplier.hpp>

#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
#include <com/sun/star/sheet/XSpreadsheet.hpp>
#include <com/sun/star/sheet/XCellRangeAddressable.hpp>

#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/table/CellRangeAddress.hpp>
#include <com/sun/star/table/XCellRange.hpp>
#include <com/sun/star/table/XTableChart.hpp>
#include <com/sun/star/table/XTableCharts.hpp>
#include <com/sun/star/table/XTableChartsSupplier.hpp>

#include <boost/document/detail/chart_type.hpp>

#include <boost/document/detail/document_exception.hpp>

using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
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

/*template<typename U>
void __debug_find_props(Reference < U > xSomething) {
  Reference < XPropertySet > xChartProps(xSomething, UNO_QUERY);
  Reference < XPropertySetInfo > xPropInfo(xChartProps->getPropertySetInfo());
  Sequence < Property > props = xPropInfo->getProperties();
  for(int i = 0; i < props.getLength(); i++) {
    std::cout << props[i].Name << std::endl;
  }
}*/

template<typename U, typename T>
void set_chart_property(Reference < U > xSomething, const OUString& prop, const T& val) {
    try {
        Reference < XPropertySet > xChartProps(xSomething, UNO_QUERY);
        Any propVal;
        propVal <<= val;
        xChartProps->setPropertyValue(prop, propVal);
    }
    catch( Exception &e ){
        throw_document_exception(e);
    }
}

void set_title(Reference<XChartDocument> xChart, const std::string& title) {
    set_chart_property(xChart, OUString::createFromAscii("HasMainTitle"), (sal_Bool)true);
    set_chart_property(xChart->getTitle(), OUString::createFromAscii("String"), OUString::createFromAscii(title.c_str()));
}

void set_legend(Reference<XChartDocument> xChart, bool set) {
    set_chart_property(xChart, OUString::createFromAscii("HasLegend"), (sal_Bool)set);
}


Reference<XDiagram> helper_get_XDiagram(Reference<XChartDocument> xChart, std::string service_name) {
    Reference<XMultiServiceFactory> xMSF(xChart, UNO_QUERY);
    Reference<XDiagram> xDiag(xMSF->createInstance(OUString::createFromAscii(service_name.c_str())), UNO_QUERY);
    return xDiag;
}
// MS Office : https://msdn.microsoft.com/en-us/library/office/ff838409.aspx
// OpenOffice : https://www.openoffice.org/api/docs/common/ref/com/sun/star/chart/module-ix.html
void set_type(Reference<XChartDocument> xChart, boost::chart_type::type t, bool enable_3d) {
    Reference<XDiagram> xDiag = NULL;
    bool v,o;
    switch(t) {
        case boost::chart_type::AREA :
            xDiag = helper_get_XDiagram(xChart, "com.sun.star.chart.AreaDiagram");
            break;
        case boost::chart_type::BAR :
            xDiag = helper_get_XDiagram(xChart, "com.sun.star.chart.BarDiagram");
            break;
        case boost::chart_type::BUBBLE :
            xDiag = helper_get_XDiagram(xChart, "com.sun.star.chart.BubbleDiagram");
            break;
        case boost::chart_type::DONUT :
            xDiag = helper_get_XDiagram(xChart, "com.sun.star.chart.DonutDiagram");
            break;
        case boost::chart_type::LINE :
            xDiag = helper_get_XDiagram(xChart, "com.sun.star.chart.LineDiagram");
            break;
        case boost::chart_type::RADAR :
            xDiag = helper_get_XDiagram(xChart, "com.sun.star.chart.NetDiagram");
            break;
        case boost::chart_type::PIE :
            xDiag = helper_get_XDiagram(xChart, "com.sun.star.chart.PieDiagram");
            break;
        case boost::chart_type::STOCK :
        case boost::chart_type::STOCKO :
        case boost::chart_type::STOCKV :
        case boost::chart_type::STOCKVO :
            if(t == boost::chart_type::STOCK) { v = false; o = false; }
            else if(t == boost::chart_type::STOCKO) { v = false; o = true; }
            else if(t == boost::chart_type::STOCKV) { v = true; o = false;}
            else { v = true; o = true; }
            xDiag = helper_get_XDiagram(xChart, "com.sun.star.chart.StockDiagram");
            set_chart_property(xDiag, OUString::createFromAscii("Volume"), (sal_Bool)v);
            set_chart_property(xDiag, OUString::createFromAscii("UpDown"), (sal_Bool)o);
            break;
        case boost::chart_type::SCATTER :
            xDiag = helper_get_XDiagram(xChart, "com.sun.star.chart.XYDiagram");
            break;
    }
    set_chart_property(xDiag, OUString::createFromAscii("Dim3D"), (sal_Bool)enable_3d);
    xChart->setDiagram(xDiag);
}

Reference < XChartDocument >
add_chart(Reference<XSpreadsheet> xSheet, const std::string& name, const std::string& cell_range,
                          int left, int top, int width, int height, boost::chart_type::type t, bool enable_3d) {
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

      set_title(xChart, name);
      set_legend(xChart, true);
      set_type(xChart, t, enable_3d);
      /*std::cout << "Chart Props\n\n\n" << std::endl;
      __debug_find_props(xChart);
      std::cout << "Diagram Props\n\n\n" << std::endl;
      __debug_find_props(xChart->getDiagram());
      std::cout << "Legend Props\n\n\n" << std::endl;
      __debug_find_props(xChart->getLegend());*/
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
