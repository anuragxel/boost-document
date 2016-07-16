#ifndef _COLUMN_HPP
#define _COLUMN_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/document/cell.hpp>

#include <boost/document/detail/sheet_interface.hpp>
#include <boost/document/detail/document_exception.hpp>

#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/conditional.hpp>



namespace boost {

	template<typename Value> class column_iter;

	typedef column_iter<boost::cell> column_iterator;

	typedef column_iter<boost::const_cell> const_column_iterator;

	//! \brief This is the class which
	//! exposes a column of cells to work with.
	//! column_iterator is the standard iterator
	//! with this class.
	class column {
		protected:
		boost::shared_ptr<sheet_interface> obj_;
		std::size_t column_;
		public:
		typedef column_iterator iterator;
		column(boost::shared_ptr<sheet_interface> obj, std::size_t column) : obj_(obj), column_(column) {}

		boost::cell get_cell(std::size_t row) {
			return obj_->get_cell(row,column_);
		}

		boost::cell operator[](std::size_t row) {
			return obj_->get_cell_unchecked(row,column_);
		}

		std::size_t get_column_index() const {
			return column_;
		}

		inline column_iterator begin();

		inline column_iterator end();

		inline const_column_iterator cbegin();

		inline const_column_iterator cend();

	};

	template<typename Cell>
	class column_iter: public boost::iterator_facade<
		column_iter<Cell>,
		boost::cell_data,
		boost::random_access_traversal_tag,
		Cell
		> {
		protected:

		typedef typename boost::conditional<
        	boost::is_same<Cell, boost::const_cell>::value,
        	boost::shared_ptr<const sheet_interface>,
        	boost::shared_ptr<sheet_interface>
    	>::type sheet_interface_t;

		sheet_interface_t r_;

		std::size_t cell_no_;
		mutable boost::optional<boost::cell> current_cell_;
		std::size_t column_;

		public:

		friend class boost::iterator_core_access;

		column_iter(sheet_interface_t r, std::size_t num, std::size_t column) : r_(r), cell_no_(num), column_(column)
		{}

		void increment() { ++this->cell_no_; }

		void decrement() { --this->cell_no_; }

		void advance(std::size_t n) { this->cell_no_ += n; }

		template <class T>
		bool equal(column_iter<T> const& other) const {
		    return this->r_ == other.r_ && this->cell_no_ == other.cell_no_;
		}

		template <class T>
		std::size_t distance_to(column_iter<T> const& other) const {
			if(this->r_ != other.r_) {
				boost::throw_exception(document_exception(
				"Error: Both the iterators are not equal"));
			}
			return (std::size_t)(this->cell_no_> other.cell_no_?this->cell_no_-other.cell_no_:other.cell_no_-this->cell_no_);
		}

		Cell& dereference() const {
			if (!current_cell_ || current_cell_->get_row_index() != cell_no_) {
				current_cell_ = boost::none; // set it to none.
				current_cell_ = r_->get_cell(cell_no_,column_); // now this isn't an assignment :D
			}
			return *current_cell_;
		}
	};

	inline column_iterator column::begin() { return column_iterator(obj_, (std::size_t)0, column_); }

	inline column_iterator column::end() { return column_iterator(obj_, obj_->max_row(), column_); }

	inline const_column_iterator column::cbegin() { return const_column_iterator(obj_, (std::size_t)0, column_); }

	inline const_column_iterator column::cend() { return const_column_iterator(obj_, obj_->max_row(), column_); }
} // namespace boost

#endif
