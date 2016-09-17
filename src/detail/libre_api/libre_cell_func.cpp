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

#include <com/sun/star/awt/FontSlant.hpp>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>

#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include <com/sun/star/registry/XSimpleRegistry.hpp>

#include <com/sun/star/sheet/XSpreadsheet.hpp>

#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/table/CellContentType.hpp>
#include <com/sun/star/table/CellHoriJustify.hpp>
#include <com/sun/star/table/CellVertJustify.hpp>

#include <com/sun/star/table/TableBorder.hpp>
#include <com/sun/star/table/BorderLine.hpp>

#include <com/sun/star/table/TableBorder2.hpp>
#include <com/sun/star/table/BorderLine2.hpp>
#include <com/sun/star/table/BorderLineStyle.hpp>

#include <com/sun/star/text/XText.hpp>

#include <boost/document/detail/cell_content_type.hpp>
#include <boost/document/detail/cell_alignment_type.hpp>
#include <boost/document/detail/cell_border_type.hpp>
#include <boost/document/detail/cell_format_property.hpp>

#include <boost/document/detail/document_exception.hpp>


using namespace com::sun::star;
using namespace com::sun::star::awt;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::registry;
using namespace com::sun::star::sheet;
using namespace com::sun::star::table;
using namespace com::sun::star::text;

using namespace rtl;
using namespace cppu;

using ::rtl::OString;
using ::rtl::OUString;
using ::rtl::OUStringToOString;

namespace boost { namespace doc { namespace libre_cell_func {


/*template<typename U>
void __debug_find_props(Reference < U > xSomething) {
    Reference < XPropertySet > xChartProps(xSomething, UNO_QUERY);
    Reference < XPropertySetInfo > xPropInfo(xChartProps->getPropertySetInfo());
    Sequence < Property > props = xPropInfo->getProperties();
    for(int i = 0; i < props.getLength(); i++) {
      std::cout << props[i].Name << std::endl;
    }
}*/

//! \fn Helper function to throw an unwrapped
//!     exception
//!
void throw_document_exception(Exception& e) {
    OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
    boost::throw_exception(document_exception(o.pData->buffer));
}

//! \fn Returns an XCell Reference by the position
//!     with Exception Handling.
//!
Reference < XCell > get_cell(Reference <XSpreadsheet> xSheet,int i, int j) {
    try {
        Reference< XCell > xCell = xSheet->getCellByPosition(i, j);
        return xCell;
    }
    catch( Exception &e ){
        throw_document_exception(e);
    }
}

//! \fn Sets Cell value as string str. the enum value of the cell
//!     changes to CellContentType_STRING
//!
void set_cell_value(Reference< XCell > xCell, const std::string& str) {
    try {
        xCell->setFormula(OUString::createFromAscii(str.c_str()));
    }
    catch( Exception &e ){
        throw_document_exception(e);
    }
}

//! \fn Sets Cell value as string str. the enum value of the cell
//!     changes to CellContentType_STRING
//!
void reset(Reference< XCell > xCell) {
    try {
	      Reference< XText > xText(xCell, UNO_QUERY);
	      xText->setString(OUString());
    }
    catch( Exception &e ){
        throw_document_exception(e);
    }
}

//! \fn Sets Cell value as float x. the enum value of the cell
//!     changes to CellContentType_VALUE
//!
void set_cell_value(Reference< XCell > xCell, float x) {
    try {
        xCell->setValue(x);
    }
    catch( Exception &e ){
        throw_document_exception(e);
    }
}

//! \fn Gets the cell content type of the cell. Returns the boost enum value
//!     depending upon the Internal OO enum.
//!
boost::cell_content_type::type get_content_type(Reference < XCell > xCell) {
    switch (xCell->getType()){
        case CellContentType_EMPTY : return boost::cell_content_type::EMPTY;
        case CellContentType_VALUE : return boost::cell_content_type::VALUE;
        case CellContentType_TEXT : return boost::cell_content_type::STRING;
        case CellContentType_FORMULA : return boost::cell_content_type::FORMULA;
        case CellContentType_MAKE_FIXED_SIZE: return boost::cell_content_type::ERROR;
    }
    return boost::cell_content_type::ERROR;
}

//! \fn Gets the string value of the Cell
//!     if it is present.
//!
std::string get_string(Reference < XCell > xCell) {
 try {
        OString s = OUStringToOString( xCell->getFormula(), RTL_TEXTENCODING_ASCII_US );
        return std::string(s.pData->buffer);
    }
    catch( Exception &e ){
        throw_document_exception(e);
    }
}

//! \fn Gets the formula value of the cell
//!     if it is present.
//!
std::string get_formula(Reference < XCell > xCell) {
 try {
        OString s = OUStringToOString( xCell->getFormula(), RTL_TEXTENCODING_ASCII_US );
        return std::string(s.pData->buffer);
    }
    catch( Exception &e ){
        throw_document_exception(e);
    }
}

//! \fn Gets the float value of the cell if
//!     it is present.
//!
double get_value(Reference < XCell > xCell) {
 try {
        return xCell->getValue();
    }
    catch( Exception &e ){
        throw_document_exception(e);
    }
}

template<typename T>
void set_cell_property(Reference < XCell > xCell,const OUString& prop, const T& val) {
    try {
        Reference < XPropertySet > xCellProps(xCell, UNO_QUERY);
        Any propVal;
        propVal <<= val;
        xCellProps->setPropertyValue(prop, propVal);
    }
    catch( Exception &e ){
        throw_document_exception(e);
    }
}

Any get_cell_property(Reference < XCell > xCell,const OUString& prop) {
    try {
        Reference < XPropertySet > xCellProps(xCell, UNO_QUERY);
        return xCellProps->getPropertyValue(prop);
    }
    catch( Exception &e ){
        throw_document_exception(e);
    }
}


void set_cell_style(Reference < XCell > xCell, const std::string& str) {
    set_cell_property(xCell, OUString::createFromAscii("CellStyle"), OUString::createFromAscii(str.c_str()));
}

// \fn Helper to maintain standards,
// Libreoffice and MS Office have different color standards.
int colorref_to_librecolor(int val) {
    // COLORREF -> 0x00BBGGRR
    // LIBRE -> 0x00RRGGBB
    int b = (val & 0x00FF0000) >> 16;
    int g = val & 0x0000FF00;
    int r = (val & 0x000000FF) << 16;
    return (b | g | r);
}

void set_cell_background_color(Reference < XCell > xCell, int val) {
    set_cell_property(xCell, OUString::createFromAscii("CellBackColor"), colorref_to_librecolor(val));
}

void set_cell_foreground_color(Reference < XCell > xCell, int val) {
    set_cell_property(xCell, OUString::createFromAscii("CharColor"), colorref_to_librecolor(val));
}

void set_cell_font_size(Reference < XCell > xCell, double val) {
    set_cell_property(xCell, OUString::createFromAscii("CharHeight"), (float)val);
    set_cell_property(xCell, OUString::createFromAscii("CharHeightAsian"), (float)val);
    set_cell_property(xCell, OUString::createFromAscii("CharHeightComplex"), (float)val);
}

void set_cell_font_name(Reference < XCell > xCell, const std::string& str) {
    set_cell_property(xCell, OUString::createFromAscii("CharFontName"), OUString::createFromAscii(str.c_str()));
    set_cell_property(xCell, OUString::createFromAscii("CharFontNameAsian"), OUString::createFromAscii(str.c_str()));
    set_cell_property(xCell, OUString::createFromAscii("CharFontNameComplex"), OUString::createFromAscii(str.c_str()));
}

void set_cell_horizontal_alignment(Reference < XCell > xCell, boost::cell_horizontal_alignment::type t) {
    switch(t) {
      case boost::cell_horizontal_alignment::LEFT :
          set_cell_property(xCell, OUString::createFromAscii("HoriJustify"), CellHoriJustify_LEFT);
          break;
      case boost::cell_horizontal_alignment::CENTER :
          set_cell_property(xCell, OUString::createFromAscii("HoriJustify"), CellHoriJustify_CENTER);
          break;
      case boost::cell_horizontal_alignment::RIGHT :
          set_cell_property(xCell, OUString::createFromAscii("HoriJustify"), CellHoriJustify_RIGHT);
          break;
    }
}

void set_cell_vertical_alignment(Reference < XCell > xCell, boost::cell_vertical_alignment::type t) {
    switch(t) {
      case boost::cell_vertical_alignment::TOP :
          set_cell_property(xCell, OUString::createFromAscii("VertJustify"), CellVertJustify_TOP);
          break;
      case boost::cell_vertical_alignment::CENTER :
          set_cell_property(xCell, OUString::createFromAscii("VertJustify"), CellVertJustify_CENTER);
          break;
      case boost::cell_vertical_alignment::BOTTOM :
          set_cell_property(xCell, OUString::createFromAscii("VertJustify"), CellVertJustify_BOTTOM);
          break;
    }
}

// Documentation Link: https://wiki.openoffice.org/wiki/Documentation/DevGuide/Text/Formatting
void set_cell_formatting_property(::com::sun::star::uno::Reference < ::com::sun::star::table::XCell > xCell, boost::cell_format_property::type t, bool set) {
  if(t == boost::cell_format_property::BOLD) {
      float val = (set == true)?150.0:100.0; // 150 = BOLD, NORMAL = 100, THIN = 50
      set_cell_property(xCell, OUString::createFromAscii("CharWeight"), val);
  }
  else if(t == boost::cell_format_property::ITALIC) {
      int val = (set==true)?(FontSlant_ITALIC):(FontSlant_NONE);
      set_cell_property(xCell, OUString::createFromAscii("CharPosture"), val);

  }
  else if(t == boost::cell_format_property::STRIKETHROUGH ) { // CharCrossedOut, CharStrikeout (specifies type of strikeout)
      set_cell_property(xCell, OUString::createFromAscii("CharCrossedOut"), (sal_Bool)set); // crossedout or not
  }
  else if(t == boost::cell_format_property::UNDERLINE) { // CharUnderline, CharUnderlineHasColor, CharUnderlineColor
      int val = (set == true)?1:0; // 1 = SINGLE, 0 = NONE, DASH = 5, DOTTED = 3, DASHDOT = 7
      set_cell_property(xCell, OUString::createFromAscii("CharUnderline"), val);
      if(set) {
          // Set the color of the underline same as the font color
          set_cell_property(xCell, OUString::createFromAscii("CharUnderlineHasColor"), (sal_Bool)true);
          Reference < XPropertySet > xCellProps(xCell, UNO_QUERY);
          xCellProps->setPropertyValue(OUString::createFromAscii("CharUnderlineColor"), get_cell_property(xCell,"CharColor"));
      }
  }
}


void set_cell_border(Reference < XCell > xCell, boost::cell_border_style::type t, boost::cell_border_weight::type w, int color) {
    // This code is supported by Libreoffice 5+, it seems. :(
    // Border Weight: MEDIUM, THICK, THIN
    int style_weight = 50; // MEDIUM
    if(w == boost::cell_border_weight::THICK) {
      style_weight = 100;
    }
    else if(w == boost::cell_border_weight::THIN) {
      style_weight = 20;
    }
    sal_Bool x = (sal_Bool)true;
    try {
        // NONE, CONTINUOUS, DASH, DASHDOT
        int style_type = BorderLineStyle::SOLID;
        if(t == boost::cell_border_style::DASH) {
            style_type = BorderLineStyle::DASHED;
        }
        else if(t == boost::cell_border_style::DASHDOT) {
            style_type = BorderLineStyle::DASH_DOT;
        }
        else if(t == boost::cell_border_style::NONE) {
            x = (sal_Bool)false;
            style_type = BorderLineStyle::NONE;
        }
        BorderLine2 b2(colorref_to_librecolor(color), 0, style_weight, 0, style_type, 0);
        TableBorder2 val2(
          b2, x,
          b2, x,
          b2, x,
          b2, x,
          b2, x,
          b2, x,
          0, (sal_Bool)true
        );
        set_cell_property(xCell, OUString::createFromAscii("TableBorder2"), val2);
    }
    catch( Exception &e ){
        // Open Office: API Difference with  Libreoffice
        // Open Office doesn't support the BorderLine2 interface and thus TableBorder2
        // interface. There is no support for style of the border AFAIK.
        // This code is supported by both Libreoffice 4+ and Openoffice
        if(t == boost::cell_border_style::NONE) {
            x = (sal_Bool)false;
        }
        BorderLine b(colorref_to_librecolor(color), 0, style_weight, 0);
        TableBorder val(
          b, x,
          b, x,
          b, x,
          b, x,
          b, x,
          b, x,
          0, (sal_Bool)true
        );
        set_cell_property(xCell, OUString::createFromAscii("TableBorder"), val);
    }
}

}}}

#endif
