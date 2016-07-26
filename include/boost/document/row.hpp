#ifndef _ROW_HPP
#define _ROW_HPP

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

	template<typename Value> class row_iter;

	typedef row_iter<boost::cell> row_iterator;
	typedef row_iter<boost::const_cell> const_row_iterator;

	class row {
		protected:
		boost::shared_ptr<sheet_interface> obj_;
		std::size_t row_;
		public:
		typedef row_iterator iterator;
		row(boost::shared_ptr<sheet_interface> obj, std::size_t row) : obj_(obj), row_(row) {}

		boost::cell get_cell(std::size_t column) {
			return obj_->get_cell(row_,column);
		}

		boost::cell operator[](std::size_t column) {
			return obj_->get_cell_unchecked(row_,column);
		}

		std::size_t get_row_index() const {
			return row_;
		}

		bool operator==(const row& rhs) const {
				if(obj_ == rhs.obj_ && row_ == rhs.row_)
						return true;
				return false;
		}

		inline row_iterator begin();

		inline row_iterator end();

		inline const_row_iterator cbegin();

		inline const_row_iterator cend();

	};

	template<typename Cell>
	class row_iter: public boost::iterator_facade<
		row_iter<Cell>,
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
		mutable boost::optional<Cell> current_cell_;
		std::size_t row_;
		public:
		friend class boost::iterator_core_access;

		row_iter(sheet_interface_t r, std::size_t num, std::size_t row) : r_(r), cell_no_(num), row_(row)
		{}

		void increment() { ++this->cell_no_; }

		void decrement() { --this->cell_no_; }

		void advance(std::size_t n) { this->cell_no_ += n; }

		template <class T>
		bool equal(row_iter<T> const& other) const {
		    return this->r_ == other.r_  &&
							 this->row_ == other.row_ &&
							 this->cell_no_ == other.cell_no_;
		}

		template <class T>
		std::size_t distance_to(row_iter<T> const& other) const {
			if(this->r_ == other.r_  && this->row_ != other.row_) {
				boost::throw_exception(document_exception(
				"Error: Both the iterators are not equal"));
			}
			return (std::size_t)(this->cell_no_> other.cell_no_?this->cell_no_-other.cell_no_:other.cell_no_-this->cell_no_);
		}

		Cell& dereference() const {
			if (!current_cell_ || current_cell_->get_row_index() != cell_no_) {
				current_cell_ = boost::none; // set it to none.
				current_cell_ = r_->get_cell(row_,cell_no_); // now this isn't an assignment :D
			}
			return *current_cell_;
		}
	};

	inline row_iterator row::begin() { return row_iterator(obj_, (std::size_t)0,row_); }

	inline row_iterator row::end() { return row_iterator(obj_, obj_->max_column(),row_); }

	inline const_row_iterator row::cbegin() { return const_row_iterator(obj_, (std::size_t)0,row_); }

	inline const_row_iterator row::cend() { return const_row_iterator(obj_, obj_->max_column(),row_); }

} // namespace boost

#endif
