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
//	: less_than_comparable<cell, std::string>
//	, equality_comparable<cell, std::string>
//	, equality_comparable<cell> {
	{
	protected:
		std::shared_ptr<cell_interface> pimpl_;
	public:

		//! The default constructor which takes in
		//! the corresponding cell_interface for operation.
		//! Follows the pimpl idiom to support MS and LibreOffice.
		explicit cell(const std::shared_ptr<cell_interface> impl)
		: pimpl_(impl)
		{}

		//! \brief The copy constructor of the cell.
		cell(const cell& c)
		: pimpl_(c.pimpl_)
		{}

		//! \brief The assignment operator of the cell class.
		//!        Makes all operations non shallow
		//!        with respect to the internal cells.
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

		//! \brief The overloaded = operator sets a string
		//!        in the cell.
		cell& operator=(const std::string& str) {
			pimpl_->set_cell_value(str);
			return *this;
		}


		//! \brief The overloaded = operator sets a double
		//!        in the cell.
		cell& operator=(double x) {
			pimpl_->set_cell_value(x);
			return *this;
		}


		//! \brief Sets a formula
		//!        in the cell.
		void set_formula(const std::string& s) {
			pimpl_->set_cell_formula(s);
		}

		//! \brief Sets a string
		//!        in the cell.
		void set_string(const std::string& str) {
			pimpl_->set_cell_value(str);
		}

		//! \brief Sets a double
		//!        in the cell.
		void set_value(double x) {
			pimpl_->set_cell_value(x);
		}

		//! \brief Resets the contents
		//!        of the cell.
		void reset() {
			pimpl_->reset();
		}

		//! \brief Gets the formula
		//!        in the cell
		std::string get_formula() const {
			return pimpl_->get_formula();
		}

		//! \brief Gets the string present
		//!        in the cell
		std::string get_string() const {
			return pimpl_->get_string();
		}


		//! \brief Gets the value present
		//!        in the cell
		double get_value() const {
			return pimpl_->get_value();
		}

		//!  \brief Gets the row index of the
		//!         cell.
		std::size_t get_row_index() const {
			return pimpl_->get_row_index();
		}

		//! \brief Gets the column index of the
		//!        cell.
		std::size_t get_column_index() const {
			return pimpl_->get_column_index();
		}

		//! \brief Returns whether the cell
		//!        is empty or not as a boolean.
		bool empty() const {
			return pimpl_->empty();
		}

		//! \brief Given the cell content, returns the type of
		//!        cell content currently present in it in the.
		//!        form of boost::cell_content_type::type enum
		//!        which can be of the following values,
		//!		   EMPTY,STRING,VALUE,FORMULA,ERROR.
		boost::cell_content_type::type get_content_type() const {
			return pimpl_->get_content_type();
		}

		//! \brief Default Destructor.
		//!        Does nothing.
		~cell() {
		}

		//! \brief Compares the cell with a string assuming
		//!        that the cell contains a string.
		inline bool operator<(const std::string& str) {
			return pimpl_->get_string() < str;
		}


		//! \brief Compares the cell with a string assuming
		//!        that the cell contains a string.
		inline bool operator>(const std::string& str) {
			return pimpl_->get_string() > str;
		}

		//! \brief Compares the cell with a string assuming
		//!        that the cell contains a string.
		inline bool operator==(const std::string& str) {
			return pimpl_->get_string() == str;
		}

		//! \brief Compares the cell with another
		//!        cell
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

	//! \brief Compares the cell with a string assuming
	//!        that the cell contains a string.
	//!        Method is outside class because it
	//!        take cell as the second operand.
	inline bool operator>(const std::string& lhs, const cell& rhs) {
		return lhs > rhs.get_string();
	}

} // namespace boost

#endif
