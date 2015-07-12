#ifndef _ROW_ITERATOR_HPP
#define _ROW_ITERATOR_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <boost/document/cell.hpp>
#include <boost/document/detail/sheet_interface.hpp>

namespace boost {
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

                    base_t::reference dereference() const { 
                        current_cell_ = r_->obj_->get_cell(r_->row_, cell_no_);
                        return current_cell_;
                    }
                };  
} // namespace boost

#endif