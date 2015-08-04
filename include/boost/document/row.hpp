#ifndef _ROW_HPP
#define _ROW_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <memory>

#include <boost/document/cell.hpp>

#include <boost/document/detail/sheet_interface.hpp>
#include <boost/document/detail/document_exception.hpp>

#include <boost/optional.hpp>

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/conditional.hpp>


namespace boost {

	template<typename Value> class row_iter;

	typedef row_iter<boost::cell> row_iterator;
	typedef row_iter<const boost::cell> const_row_iterator;
	
	class row {
		protected:
		std::shared_ptr<sheet_interface> obj_;
		std::size_t row_;
		public:
		typedef row_iterator iterator;
		row(std::shared_ptr<sheet_interface> obj, std::size_t row) : obj_(obj), row_(row) {}

		boost::cell get_cell(std::size_t column) {
			return obj_->get_cell(row_,column);
		}

		boost::cell operator[](std::size_t column) {
			return obj_->get_cell_unchecked(row_,column);
		}

		std::size_t get_row_index() const {
			return row_;
		}

		inline row_iterator begin();
		
		inline row_iterator end();
		
		inline const_row_iterator cbegin();
		
		inline const_row_iterator cend();
		
	};

	template<typename Cell> class row_iter: public boost::iterator_facade<
		row_iter<Cell>, 
		Cell, 
		boost::random_access_traversal_tag
		> {
		protected:
		typename boost::conditional<
        	boost::is_const<Cell>::value,
        	std::shared_ptr<const sheet_interface>,
        	std::shared_ptr<sheet_interface>
    	>::type r_;
		std::size_t cell_no_;
		mutable boost::optional<boost::cell> current_cell_;
		std::size_t row_;
		public:
		friend class boost::iterator_core_access;

		row_iter(std::shared_ptr<sheet_interface> r, std::size_t num, std::size_t row) : r_(r), cell_no_(num), row_(row) 
		{}

		void increment() { ++this->cell_no_; }

		void decrement() { --this->cell_no_; }
					
		void advance(std::size_t n) { this->cell_no_ += n; }
		
		template <class T>
		bool equal(row_iter<T> const& other) const {
		    return this->r_ == other.r_ && this->cell_no_ == other.cell_no_;
		}

		template <class T>
		std::size_t distance_to(row_iter<T> const& other) const {
			if(this->r_ != other.r_) {
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