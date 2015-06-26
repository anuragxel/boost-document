//! \file
//! \brief Libre Office Cell Related Internal Functions
#ifndef _LIBRE_CELL_FUNC_CPP
#define _LIBRE_CELL_FUNC_CPP

#include <string>
#include <iostream>
#include <cstdlib>

#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>

#include <sal/main.h>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>

#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include <com/sun/star/registry/XSimpleRegistry.hpp>

#include <com/sun/star/sheet/XSpreadsheet.hpp>

#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/table/CellContentType.hpp>

#include <boost/document/detail/cell_content_type.hpp>
#include <boost/document/detail/document_exception.hpp>


using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::registry;
using namespace com::sun::star::sheet;
using namespace com::sun::star::table;

using namespace rtl;
using namespace cppu;

using ::rtl::OString;
using ::rtl::OUString;
using ::rtl::OUStringToOString;

namespace boost { namespace doc { namespace libre_cell_func {

//! \fn
//!
//!
Reference < XCell > get_cell(Reference <XSpreadsheet> xSheet,int i, int j) {
    try {
        Reference< XCell > xCell = xSheet->getCellByPosition(i, j);
        return xCell;
    }
    catch(Exception& e) {
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}

//! \fn
//!
//!
void set_cell_value(Reference< XCell > xCell, const std::string& str) {
    try {
        xCell->setFormula(OUString::createFromAscii(str.c_str()));
    }
    catch(Exception& e) {
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}

//! \fn
//!
//!
void set_cell_value(Reference< XCell > xCell, float x) {
    try {
        xCell->setValue(x);
    }
    catch(Exception& e) {
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}

//! \fn
//!
//!
boost::cell_content_type::type get_content_type(Reference < XCell > xCell) {
    switch (xCell->getType()){
        case CellContentType_EMPTY : return boost::cell_content_type::EMPTY;
        case CellContentType_VALUE : return boost::cell_content_type::VALUE;
        case CellContentType_TEXT : return boost::cell_content_type::STRING;
        case CellContentType_FORMULA : return boost::cell_content_type::FORMULA;
    }
}

//! \fn
//!
//!
std::string get_string(Reference < XCell > xCell) {
 try {
        OString s = OUStringToOString( xCell->getFormula(), RTL_TEXTENCODING_ASCII_US );
        return std::string(s.pData->buffer); 
    }
    catch(Exception& e) {
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}

//! \fn
//!
//!
std::string get_formula(Reference < XCell > xCell) {
 try {
        OString s = OUStringToOString( xCell->getFormula(), RTL_TEXTENCODING_ASCII_US );
        return std::string(s.pData->buffer); 
    }
    catch(Exception& e) {
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}


//! \fn
//!
//!
double get_value(Reference < XCell > xCell) {
 try {
        return xCell->getValue();
    }
    catch(Exception& e) {
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        boost::throw_exception(document_exception(o.pData->buffer));
    }
}

}}}

#endif
