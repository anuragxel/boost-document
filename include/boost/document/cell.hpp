#ifndef _CELL_HPP
#define _CELL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <boost/document/detail/cell_interface.hpp>
#include <boost/document/detail/cell_content_type.hpp>

#include <boost/operators.hpp>

namespace boost {

	class cell
//	less_than_comparable<cell, std::string>
//	, equality_comparable<cell, std::string>
//	, equality_comparable<cell> {
	{
	protected:
		std::shared_ptr<cell_interface> pimpl_;
	public:

		explicit cell(const std::shared_ptr<cell_interface> impl) 
		: pimpl_(impl) 
		{}

		cell(const cell& c)
		: pimpl_(c.pimpl_)
		{}

		/*
		cell& operator=(const cell& c) {
			switch(c.get_content_type()) {
				case boost::cell_content_type::STRING:
					set_string(c.get_string());
					break;
				case boost::cell_content_type::VALUE:
					set_value(c.get_value());
					break;
				case boost::cell_content_type::FORMULA:
					set_formula(c.get_formula());
					break;
				case boost::cell_content_type::ERROR:
				case boost::cell_content_type::EMPTY:
					break;
			}
			return *this;
		}
		*/

		cell& operator=(const std::string& str) {
			pimpl_->set_cell_value(str);
			return *this;
		}

		cell& operator=(double x) {
			pimpl_->set_cell_value(x);
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

		void reset() {
			pimpl_->reset();
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

		std::size_t get_row_index() const {
			return pimpl_->get_row_index();
		}

		std::size_t get_column_index() const {
			return pimpl_->get_column_index();
		}
	
		bool empty() const {
			return pimpl_->empty();
		}

		boost::cell_content_type::type get_content_type() const {
			return pimpl_->get_content_type();
		}

		~cell() {
		}

		inline bool operator<(const std::string& str) {
			return pimpl_->get_string() < str;
		}

		inline bool operator>(const std::string& str) {
			return pimpl_->get_string() > str;
		}
		
		inline bool operator==(const std::string& str) {
			return pimpl_->get_string() == str;
		}

		inline bool operator==(const cell& c) {
			if(pimpl_->get_content_type() == c.get_content_type()) {
				switch(pimpl_->get_content_type()) {
					case boost::cell_content_type::STRING:
						return pimpl_->get_string() == c.get_string();
					case boost::cell_content_type::VALUE:
						return pimpl_->get_value() == c.get_value();
					case boost::cell_content_type::FORMULA:
						return pimpl_->get_formula() == c.get_formula();
					case boost::cell_content_type::ERROR:
					case boost::cell_content_type::EMPTY:
						return true;
				}
			}
			return false;
		}
	}; // class cell

	inline bool operator>(const std::string& lhs, const cell& rhs) {
		return lhs > rhs.get_string();
	}

} // namespace boost

#endif
