#ifndef _LIBRE_CELL_HPP
#define _LIBRE_CELL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>

#include <com/sun/star/sheet/XSpreadsheet.hpp>
#include <com/sun/star/table/XCell.hpp>

#include <boost/document/detail/cell_content_type.hpp>
#include <boost/document/detail/cell_alignment_type.hpp>
#include <boost/document/detail/cell_border_type.hpp>


namespace boost { namespace doc { namespace libre_cell_func {

::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > get_cell(::com::sun::star::uno::Reference < com::sun::star::sheet::XSpreadsheet > xSheet,int i, int j);
::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > get_cell_unchecked(::com::sun::star::uno::Reference < com::sun::star::sheet::XSpreadsheet > xSheet,int i, int j);

void set_cell_value(::com::sun::star::uno::Reference< ::com::sun::star::table::XCell > xCell, const std::string& str);
void set_cell_value(::com::sun::star::uno::Reference< ::com::sun::star::table::XCell > xCell, float x);

void reset(::com::sun::star::uno::Reference< ::com::sun::star::table::XCell > xCell);

std::string get_string(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell);
std::string get_formula(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell);
double get_value(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell);

boost::cell_content_type::type get_content_type(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell);

void set_cell_style(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell, const std::string& str);
void set_cell_background_color(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell, int val);
void set_cell_foreground_color(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell, int val);
void set_cell_font_size(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell, double val);
void set_cell_horizontal_alignment(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell, boost::cell_horizontal_alignment::type t);
void set_cell_vertical_alignment(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell, boost::cell_vertical_alignment::type t);
void set_cell_font_name(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell, const std::string& str);
void set_cell_border(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell, boost::cell_border_style::type t, boost::cell_border_weight::type w, int color);

}}}
#endif
