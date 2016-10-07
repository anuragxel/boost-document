#ifndef _SHEET_INTERFACE_HPP
#define _SHEET_INTERFACE_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <boost/document/cell.hpp>
#include <boost/document/chart.hpp>

#include <boost/document/detail/chart_type.hpp>


namespace boost {

	class sheet_interface {
	 public:
	 	virtual std::string sheet_name() = 0;
	 	virtual std::size_t sheet_index() = 0;
	 	virtual void rename_sheet(const std::string& str) = 0;
	 	virtual boost::cell get_cell(std::size_t i, std::size_t j) = 0;
		virtual boost::cell get_cell_unchecked(std::size_t i, std::size_t j) = 0;
		virtual std::size_t max_row() = 0;
		virtual std::size_t max_column() = 0;

		virtual boost::chart add_chart(const std::string& name, const std::string& cell_range, std::size_t left, std::size_t top, std::size_t width, std::size_t height) = 0;
		virtual boost::chart get_chart(const std::string& name) = 0;
		virtual void delete_chart(const std::string& name) = 0;

		virtual ~sheet_interface() {}
	};
} // namespace boost

#endif
