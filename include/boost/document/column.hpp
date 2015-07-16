#ifndef _COLUMN_HPP
#define _COLUMN_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <memory>

#include <boost/document/cell.hpp>

#include <boost/document/detail/sheet_interface.hpp>
#include <boost/document/detail/document_exception.hpp>

#include <boost/optional.hpp>


namespace boost {
	class column {
		protected:
		std::shared_ptr<sheet_interface> obj_;
		std::size_t row_;
		public:
		column(std::shared_ptr<sheet_interface> obj, std::size_t row) : obj_(obj), row_(row) {}

		boost::cell get_cell(std::size_t column) {
			return obj_->get_cell(row_,column);
		}

		boost::cell operator[](std::size_t column) {
			return obj_->get_cell_unchecked(row_,column);
		}

		std::size_t get_row_index() const {
			return row_;
		}

		class column_iterator: public boost::iterator_facade<
			column_iterator, 
			boost::cell, 
			boost::random_access_traversal_tag
			> {
			public:
			friend class boost::iterator_core_access;
			boost::column* r_;
			std::size_t cell_no_;
			mutable boost::optional<boost::cell> current_cell_;        
						
			typedef boost::iterator_facade<
				column_iterator, 
				boost::cell,
				boost::random_access_traversal_tag
			> base_t;

			column_iterator(boost::column* r, std::size_t num) : r_(r), cell_no_(num) 
			{}

			void increment() { ++this->cell_no_; }

			void decrement() { --this->cell_no_; }
						
			void advance(std::size_t n) { this->cell_no_ += n; }
						 
			bool equal(column_iterator const& other) const {
				return this->r_ == other.r_ and this->cell_no_ == other.cell_no_;
			}

			std::size_t distance_to(column_iterator const& other) const {
				if(this->r_ != other.r_) {
					boost::throw_exception(document_exception(
					"Error: Both the iterators are not equal"));    
				}
				int s = (int)this->cell_no_ - (int)other.cell_no_;
				return (std::size_t)(s>0?s:-s);
			}

			base_t::reference dereference() const { 
				//if (!current_cell_ || current_cell_->get_row_index() != cell_no_) {
				current_cell_ = r_->get_cell(cell_no_);
				//}
				return *current_cell_;
			}
		};  
		column_iterator begin() { return column_iterator(this, (std::size_t)0); }
		column_iterator end() { return column_iterator(this, obj_->max_column()); }
	};
} // namespace boost

#endif