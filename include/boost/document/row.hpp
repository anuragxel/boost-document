#ifndef _ROW_HPP
#define _ROW_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <boost/document/cell.hpp>
#include <boost/document/detail/sheet_interface.hpp>

//#include <boost/document/row_iterator.hpp>

namespace boost {
	class row {
		protected:
		std::shared_ptr<sheet_interface> obj_;
		std::size_t row_;
		public:
		row(std::shared_ptr<sheet_interface> obj, std::size_t row) {
			obj_ = obj;
			row_ = row;
		}
		boost::cell get_cell(std::size_t column) {
			return obj_->get_cell(row_,column);
		}
		boost::cell operator[](std::size_t column) {
			return obj_->get_cell_unchecked(row_,column);
		}
		/*
		boost::row_iterator begin() { return boost::row_iterator(this, (std::size_t)0); }
		boost::row_iterator end() { return boost::row_iterator(this, obj_->max_column()); }
		*/
	};
} // namespace boost

#endif