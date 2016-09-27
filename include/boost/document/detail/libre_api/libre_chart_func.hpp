#ifndef _LIBRE_CHART_FUNC_HPP
#define _LIBRE_CHART_FUNC_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

#include <com/sun/star/beans/XPropertySet.hpp>

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
#include <boost/document/detail/chart_axis.hpp>


namespace boost { namespace doc { namespace libre_chart_func {

::com::sun::star::uno::Reference < ::com::sun::star::chart::XChartDocument > add_chart(::com::sun::star::uno::Reference < com::sun::star::sheet::XSpreadsheet > xSheet,
                                                                                      const std::string& name, const std::string& cell_range,
                                                                                      int left, int top, int width, int height, boost::chart_type::type t, bool enable_3d);
void delete_chart(::com::sun::star::uno::Reference < com::sun::star::sheet::XSpreadsheet > xSheet, const std::string& name);
void set_title(::com::sun::star::uno::Reference < ::com::sun::star::chart::XChartDocument > xChart, const std::string& title);
void set_legend(::com::sun::star::uno::Reference < ::com::sun::star::chart::XChartDocument > xChart, bool set);
void set_type(::com::sun::star::uno::Reference < ::com::sun::star::chart::XChartDocument > xChart, boost::chart_type::type t, bool enable_3d);
void set_axis_title(::com::sun::star::uno::Reference < ::com::sun::star::chart::XChartDocument > xChart, boost::chart_axis::type t, const std::string& title);
void toggle_axis_location(::com::sun::star::uno::Reference < ::com::sun::star::chart::XChartDocument > xChart, boost::chart_axis::type t, bool alt);

}}}
#endif
