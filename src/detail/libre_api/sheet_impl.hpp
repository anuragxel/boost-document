#ifndef _LIBRE_SHEET_IMPL_HPP
#define _LIBRE_SHEET_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <memory>

#include <boost/filesystem.hpp>


#include <boost/document/detail/document_exception.hpp>

#include <boost/document/detail/sheet_interface.hpp>
#include <boost/document/detail/cell_interface.hpp>


#include <boost/document/detail/libre_api/libre_sheet_func.hpp>
#include <boost/document/detail/libre_api/libre_cell_func.hpp>

#include "cell_impl.hpp"

namespace boost { namespace detail { 

class libre_sheet: public sheet_interface {

	protected:
	::com::sun::star::uno::Reference < com::sun::star::lang::XComponent > xComponent_;
	::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet > xSheet_;	
	int index;
	std::string name;

	public:
	libre_sheet(::com::sun::star::uno::Reference < com::sun::star::lang::XComponent >& xComponent,
		::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet >& xSheet, int& index) {
		this->xComponent_ = xComponent;
		this->xSheet_ = xSheet;
		this->index = index;
		this->name = boost::doc::libre_sheet_func::get_sheet_name(this->xSheet_);
	}

	libre_sheet(::com::sun::star::uno::Reference < com::sun::star::lang::XComponent >& xComponent,
		::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet >& xSheet, std::string& str) {
		this->xComponent_ = xComponent;
		this->xSheet_ = xSheet;
		this->index = boost::doc::libre_sheet_func::get_sheet_index(this->xSheet_);
		this->name = str;
	}

	std::string sheet_name() {
		return this->name;
	}

	int sheet_index() {
		return this->index;
	}

	void rename_sheet(const std::string& str) {
		if(str.empty()) {
			boost::throw_exception(document_exception("Error: String Passed is Empty."));
   		}
	 	boost::doc::libre_sheet_func::rename_sheet(this->xSheet_,str);
		this->name = str;
	}

	boost::cell get_cell(int i, int j) {
		if( i < 0 || j < 0) {
			boost::throw_exception(document_exception("Error: Invalid Indices Provided."));
		}
		::com::sun::star::uno::Reference< com::sun::star::table::XCell > xCell = boost::doc::libre_cell_func::get_cell(this->xSheet_,i,j);
		return boost::cell(std::dynamic_pointer_cast<cell_interface>(std::make_shared<boost::detail::libre_cell>(xCell,i,j)));
	}
	
 	~libre_sheet() {
 		
 	}

};

}} // namespace boost::detail


#endif
