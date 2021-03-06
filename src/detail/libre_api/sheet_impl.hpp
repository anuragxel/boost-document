#ifndef _LIBRE_SHEET_IMPL_HPP
#define _LIBRE_SHEET_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>


#include <boost/document/detail/document_exception.hpp>

#include <boost/document/detail/sheet_interface.hpp>
#include <boost/document/detail/cell_interface.hpp>
#include <boost/document/detail/chart_interface.hpp>

#include <boost/document/detail/libre_api/libre_sheet_func.hpp>
#include <boost/document/detail/libre_api/libre_cell_func.hpp>

#include <boost/document/detail/libre_api/libre_chart_func.hpp>

#include "cell_impl.hpp"
#include "chart_impl.hpp"

namespace boost { namespace detail {


class libre_sheet: public sheet_interface {

protected:
	::com::sun::star::uno::Reference < com::sun::star::lang::XComponent > xComponent_;
	::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet > xSheet_;
	std::size_t index;
	std::string name;

public:
	libre_sheet(const ::com::sun::star::uno::Reference < com::sun::star::lang::XComponent >& xComponent,
		const ::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet >& xSheet, std::size_t index) {
		this->xComponent_ = xComponent;
		this->xSheet_ = xSheet;
		this->index = index;
		this->name = boost::doc::libre_sheet_func::get_sheet_name(this->xSheet_);
	}

	libre_sheet(const ::com::sun::star::uno::Reference < com::sun::star::lang::XComponent >& xComponent,
		const ::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet >& xSheet,const std::string& str) {
		this->xComponent_ = xComponent;
		this->xSheet_ = xSheet;
		this->index = (std::size_t)boost::doc::libre_sheet_func::get_sheet_index(this->xSheet_);
		this->name = str;
	}

	std::string sheet_name() {
		return this->name;
	}

	std::size_t sheet_index() {
		return this->index;
	}

	void rename_sheet(const std::string& str) {
		if(str.empty()) {
			boost::throw_exception(document_exception("Error: String Passed is Empty."));
   		}
	 	boost::doc::libre_sheet_func::rename_sheet(this->xSheet_,str);
		this->name = str;
	}

	//Refer to https://simple.wikipedia.org/wiki/OpenOffice_Calc
	std::size_t max_row() {
		return 1048576;
	}

	std::size_t max_column() {
		return 1024;
	}

	boost::cell get_cell(std::size_t row, std::size_t column) {
		if( row > max_row() || column > max_column() ) {
			boost::throw_exception(document_exception("Error: Invalid Indices Provided."));
		}
		::com::sun::star::uno::Reference< com::sun::star::table::XCell > xCell = boost::doc::libre_cell_func::get_cell(this->xSheet_,(int)row,(int)column);
		return boost::cell(boost::dynamic_pointer_cast<cell_interface>(boost::make_shared<boost::detail::libre_cell>(xCell,row,column)));
	}

	boost::cell get_cell_unchecked(std::size_t row, std::size_t column) {
		::com::sun::star::uno::Reference< com::sun::star::table::XCell > xCell = this->xSheet_->getCellByPosition((int)row, (int)column);
		return boost::cell(boost::dynamic_pointer_cast<cell_interface>(boost::make_shared<boost::detail::libre_cell>(xCell,row,column)));
	}

	boost::chart add_chart(const std::string& name, const std::string& cell_range, std::size_t left, std::size_t top, std::size_t width, std::size_t height) {
		::com::sun::star::uno::Reference < com::sun::star::chart::XChartDocument > xChart = boost::doc::libre_chart_func::add_chart(this->xSheet_, name, cell_range, (int)left, (int)top, (int)width, (int)height);
		return boost::chart(boost::dynamic_pointer_cast<chart_interface>(boost::make_shared<boost::detail::libre_chart>(xChart, this->xSheet_, name, cell_range, left, top, width, height)));
	}

	boost::chart get_chart(const std::string& name) {
		::com::sun::star::uno::Reference < com::sun::star::chart::XChartDocument > xChart = boost::doc::libre_chart_func::get_chart(this->xSheet_, name);
		return boost::chart(boost::dynamic_pointer_cast<chart_interface>(boost::make_shared<boost::detail::libre_chart>(xChart, this->xSheet_, name, "", 0, 0, 0, 0)));
	}

	void delete_chart(const std::string& name) {
		boost::doc::libre_chart_func::delete_chart(this->xSheet_, name);
	}

 	~libre_sheet() {
 	}

};

}} // namespace boost::detail


#endif
