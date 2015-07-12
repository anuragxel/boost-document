#ifndef _CELL_HPP
#define _CELL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <boost/document/detail/cell_interface.hpp>
#include <boost/document/detail/cell_content_type.hpp>

namespace boost {

	class cell {

	public:
	std::shared_ptr<cell_interface> pimpl_;
	explicit cell(const std::shared_ptr<cell_interface> impl) : pimpl_(impl) {
		
	}

    cell& operator=(const std::string& str) {
    	pimpl_->set_cell_value(str);
    	return *this;
    }

    cell& operator=(double x) {
    	pimpl_->set_cell_value(x);
        return *this;
    }

    cell& operator=(cell c) {
    	pimpl_ = c.pimpl_;
    	return *this;
    }

    void set_formula(const std::string& s) {
		pimpl_->set_cell_value(s);
	}


	void set_string(const std::string& str) {
		pimpl_->set_cell_value(str);
	}

	void set_value(double x) {
		pimpl_->set_cell_value(x);
	}

	std::string get_formula() const {
		return pimpl_->get_formula();
	}


	std::string get_string() const {
		return pimpl_->get_string();
	}

	double get_value() const {
		return pimpl_->get_value();
	}
    
    bool empty() const {
    	return pimpl_->empty();
    }

    boost::cell_content_type::type get_content_type() {
    	return pimpl_->get_content_type();
    }

	~cell() {
	}

	};
} // namespace boost

#endif
