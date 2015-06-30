#ifndef _SHEET_HPP
#define _SHEET_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <memory>

#include <boost/document/cell.hpp>
#include <boost/document/detail/sheet_interface.hpp>

#include <boost/document/detail/document_exception.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace boost {
    
    //! \brief This is the main class interface to be 
    //!        exposed to the library user.
    //!
	class sheet {
	private:
		std::shared_ptr<sheet_interface> pimpl_;
		//boost::shared_ptr<sheet_interface> init() {
 	   	//	return boost::detail::open_sheet_instance();
		//}
	public:
		//! \brief The Constructor.
		//!        Creates a new document object.  
		explicit sheet(const std::shared_ptr<sheet_interface> impl) : pimpl_(impl) {

		}
		//! \brief Gets the sheet name
		//!        which is being accessed.
		std::string sheet_name() {
			return pimpl_->sheet_name();
		}

		//! \brief Gets the sheet index
		//!        which is being accessed.
	 	std::size_t sheet_index() {
	 		return pimpl_->sheet_index();
	 	}

		//! \brief Renames the sheet to str
		//!        which is being accessed.
	 	void rename_sheet(const std::string& str) {
	 		pimpl_->rename_sheet(str);
	 	}


	 	std::size_t max_row() {
	 		return pimpl_->max_row();
	 	}

	 	std::size_t max_column() {
	 		return pimpl_->max_column();
	 	}

	 	//! Gets the cell instance
	 	//! which can be manipulated.
	 	boost::cell get_cell(std::size_t row, std::size_t column) {
	 		return pimpl_->get_cell(row,column);
	 	}

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
			class row_iterator: public boost::iterator_facade<
				    row_iterator, 
				    boost::cell, 
				    boost::random_access_traversal_tag
				> {
				public:
				friend class boost::iterator_core_access;
				row* r_;
				std::size_t cell_no_;
				boost::cell current_cell_;

				typedef boost::iterator_facade<
				    row_iterator, 
				    cell,
				    boost::random_access_traversal_tag
				> base_t;

				row_iterator(row* r, std::size_t num) : r_(r), cell_no_(num),current_cell_(r_->obj_->get_cell_unchecked(r_->row_, cell_no_)) 
				{}

				void increment() { ++this->cell_no_; }

				void decrement() { --this->cell_no_; }
				
				void advance(std::size_t n) { this->cell_no_ += n; }
				 
				bool equal(row_iterator const& other) const {
        			return this->r_ == other.r_ and this->cell_no_ == other.cell_no_;
    			}

    			std::size_t distance_to(row_iterator const& other) const {
    				if(this->r_ != other.r_) {
    					boost::throw_exception(document_exception(
            			"Error: Both the iterators are not equal"));	
    				}
    				int s = (int)this->cell_no_ - (int)other.cell_no_;
    				return (std::size_t)(s>0?s:-s);
    			}

				base_t::reference dereference() { 
					current_cell_ = this->r_->obj_->get_cell(r_->row_, cell_no_);
					return current_cell_;
				}

			};
			row_iterator begin() { return row_iterator(this, (std::size_t)0); }
			row_iterator end() { return row_iterator(this, obj_->max_column()); }
		};


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
		};

		row get_row(std::size_t i) {
			return row(pimpl_,i);
		}

		column get_column(std::size_t i) {
			return column(pimpl_,i);
		}

		//! Gets the cell instance
	 	//! which can be manipulated.
	 	//! No Exception Handling.
		row operator[](std::size_t i) {
			return row(pimpl_,i);
		}
	 	
	 	//! \brief Destructor
		//!        Closes Unsaved Documents.
		~sheet() {
		}
	};
} // namespace boost

#endif
