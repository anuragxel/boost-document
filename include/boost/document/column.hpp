#ifndef _COLUMN_HPP
#define _COLUMN_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <boost/document/cell.hpp>
#include <boost/document/detail/sheet_interface.hpp>

namespace boost {
	class column {
		protected:
		std::shared_ptr<sheet_interface> obj_;
		std::size_t column_;
		public:
		column(std::shared_ptr<sheet_interface> obj, std::size_t column) {
			obj_ = obj;
			column_ = column;
		}
		boost::cell get_cell(std::size_t row) {
			return obj_->get_cell(row,column_);
		}
		boost::cell operator[](std::size_t row) {
			return obj_->get_cell_unchecked(row,column_);
		}
		/*
		column_iterator begin() { return column_iterator(this, (std::size_t)0); }
		column_iterator end() { return column_iterator(this, obj_->max_column()); }
		*/
	};
} // namespace boost

#endif