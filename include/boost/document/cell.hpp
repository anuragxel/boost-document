#ifndef _CELL_HPP
#define _CELL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/document/detail/cell_interface.hpp>
#include <boost/document/detail/cell_content_type.hpp>
#include <boost/document/detail/cell_alignment_type.hpp>
#include <boost/document/detail/cell_data.hpp>


#include <boost/operators.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/variant.hpp>

#include <iostream>
#include <typeinfo>

namespace boost {

	class cell;

	class const_cell
	{
	protected:
		boost::shared_ptr<cell_interface> pimpl_;

		// This ensures that we call const qualified method of `cell_interface`.
		// If `cell_interface` method is not const qualified, you'll get a compilation error here
		// (for example call impl().set_string() will result in an error)
		const cell_interface& impl() const {
			return *pimpl_;
		}

		friend class cell;

	public:
		//! The default constructor which takes in
		//! the corresponding cell_interface for operation.
		//! Follows the pimpl idiom to support MS and LibreOffice.
		explicit const_cell(const boost::shared_ptr<cell_interface>& impl)
		: pimpl_(impl)
		{}

		//! \brief Gets the formula
		//!        in the cell
		std::string get_formula() const {
			return impl().get_formula();
		}

		//! \brief Gets the string present
		//!        in the cell
		std::string get_string() const {
			return impl().get_string();
		}

		//! \brief Gets the value present
		//!        in the cell
		double get_value() const {
			return impl().get_value();
		}

		//!  \brief Gets the row index of the
		//!         cell.
		std::size_t get_row_index() const {
			return impl().get_row_index();
		}

		//! \brief Gets the column index of the
		//!        cell.
		std::size_t get_column_index() const {
			return impl().get_column_index();
		}

		//! \brief Returns whether the cell
		//!        is empty or not as a boolean.
		bool empty() const {
			return impl().empty();
		}

		//! \brief Given the cell content, returns the type of
		//!        cell content currently present in it in the.
		//!        form of boost::cell_content_type::type enum
		//!        which can be of the following values,
		//!		     EMPTY,STRING,VALUE,FORMULA,ERROR.
		boost::cell_content_type::type get_content_type() const {
			return impl().get_content_type();
		}

		//---------------------------------------------
		//---------------------------------------------
		// Cell Comparisons
		//---------------------------------------------
		//---------------------------------------------
				inline bool operator<(const std::string& str) const {
					if(impl().get_content_type() == boost::cell_content_type::FORMULA) {
						return impl().get_string() < str;
					}
					else if(impl().get_content_type() != boost::cell_content_type::STRING) {
							return impl().get_content_type() < boost::cell_content_type::STRING;
					}
					return impl().get_string() < str;
				}

				inline bool operator==(const std::string& str) const {
					if(impl().get_content_type() == boost::cell_content_type::FORMULA) {
						return impl().get_string() == str;
					}
					else if(impl().get_content_type() != boost::cell_content_type::STRING) {
							return false;
					}
					return impl().get_string() == str;
				}

				inline bool operator!=(const std::string& str) const {
					return !(*this==str);
				}

				inline bool operator>(const std::string& str) const {
					if(impl().get_content_type() == boost::cell_content_type::FORMULA) {
						return impl().get_string() > str;
					}
					else if(impl().get_content_type() != boost::cell_content_type::STRING) {
							return impl().get_content_type() > boost::cell_content_type::STRING;
					}
					return impl().get_string() > str;
				}

				inline bool operator<=(const std::string& str) const {
					return !(*this>str);
				}

				inline bool operator>=(const std::string& str) const {
					return !(*this<str);
				}

				inline bool operator<(double val) const {
					if(impl().get_content_type() == boost::cell_content_type::FORMULA) {
						return impl().get_value() < val;
					}
					else if(impl().get_content_type() != boost::cell_content_type::VALUE) {
							return impl().get_content_type() < boost::cell_content_type::VALUE;
					}
					return impl().get_value() < val;
				}

				inline bool operator==(double val) const {
					if(impl().get_content_type() == boost::cell_content_type::FORMULA) {
							return impl().get_value() == val;
					}
					else if(impl().get_content_type() != boost::cell_content_type::VALUE) {
							return false;
					}
					return impl().get_value() == val;
				}

				inline bool operator!=(double val) const {
					return !(*this==val);
				}

				inline bool operator>(double val) const {
					if(impl().get_content_type() == boost::cell_content_type::FORMULA) {
						return impl().get_value() > val;
					}
					else if(impl().get_content_type() != boost::cell_content_type::VALUE) {
							return impl().get_content_type() > boost::cell_content_type::VALUE;
					}
					return impl().get_value() > val;
				}

				inline bool operator<=(double val) const {
					return !(*this>val);
				}

				inline bool operator>=(double val) const {
					return !(*this<val);
				}

				//! \brief Compares the cell with another
				//!        cell
				inline bool operator==(const const_cell& c) const {
					if(impl().get_content_type() == c.get_content_type()) {
						switch(impl().get_content_type()) {
							case boost::cell_content_type::STRING:
								return impl().get_string() == c.get_string();
							case boost::cell_content_type::VALUE:
							case boost::cell_content_type::FORMULA:
							// get the value instead
							// ie. we evaluate the value derived from the formula
								return impl().get_value() == c.get_value();
							case boost::cell_content_type::ERROR:
							case boost::cell_content_type::EMPTY:
								return true;
						}
					}
					return false; // if the types are not equal
				}

				inline bool operator<(const const_cell& c) const {
					// Cells are partially ordered, however we
					// enforce the EMPTY < VALUE < TEXT constraint
					// to make all cells comparable.
					if (impl().get_content_type() != c.get_content_type()) {
        			return impl().get_content_type() < c.get_content_type();
    			}
					switch(impl().get_content_type()) {
						case boost::cell_content_type::STRING:
							return impl().get_string() < c.get_string();
						case boost::cell_content_type::VALUE:
						case boost::cell_content_type::FORMULA:
							// get the value instead
							// ie. we evaluate the value derived from the formula
							return impl().get_value() < c.get_value();
						case boost::cell_content_type::ERROR:
						case boost::cell_content_type::EMPTY:
								return false;
					}
					return false; // not reacheable
				}

				inline bool operator!=(const const_cell& c) const {
					return !(*this==c);
				}

				inline bool operator>(const const_cell& c) const {
					return (c<*this);
				}

				inline bool operator<=(const const_cell& c) const {
					return !(*this>c);
				}

				inline bool operator>=(const const_cell& c) const {
					return !(*this<c);
				}

	}; // class const_cell

	class cell
	: public const_cell
	{
	protected:
		cell_interface& impl() {
        	return *pimpl_;
    }
	public:

		//! The default constructor which takes in
		//! the corresponding cell_interface for operation.
		//! Follows the pimpl idiom to support MS and LibreOffice.
		explicit cell(boost::shared_ptr<cell_interface> pimpl)
	 	: const_cell(pimpl)
 		{}

		cell(const cell& c)
		: const_cell(c.pimpl_)
		{}

		cell(const const_cell& c)
		: const_cell(c.pimpl_)
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
				case boost::cell_content_type::EMPTY:
				case boost::cell_content_type::ERROR:
					reset(); // because the assigned cell is bad, clear the original cell
					break;
			}
			return *this;
		}

		cell& operator=(const const_cell& c) {
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
				case boost::cell_content_type::EMPTY:
				case boost::cell_content_type::ERROR:
					reset(); // because the assigned cell is bad, clear the original cell
					break;
			}
			return *this;
		}

		cell& operator=(const boost::cell_data& cdata) {
			switch(cdata.type) {
				case boost::cell_content_type::STRING:
					set_string(boost::get<std::string>(cdata.value));
					break;
				case boost::cell_content_type::VALUE:
					set_value(boost::get<double>(cdata.value));
					break;
				case boost::cell_content_type::FORMULA:
					set_formula(boost::get<std::string>(cdata.value));
					break;
				case boost::cell_content_type::EMPTY:
				case boost::cell_content_type::ERROR:
					reset(); // because the assigned cell is bad, clear the original cell
					break;
			}
			return *this;
		}

		//! \brief The overloaded = operator sets a string
		//!        in the cell.
		cell& operator=(const std::string& str) {
			impl().set_cell_value(str);
			return *this;
		}

		//! \brief The overloaded = operator sets a double
		//!        in the cell.
		cell& operator=(double x) {
			impl().set_cell_value(x);
			return *this;
		}

		//! \brief Sets a formula
		//!        in the cell.
		void set_formula(const std::string& s) {
			impl().set_cell_formula(s);
		}

		//! \brief Sets a string
		//!        in the cell.
		void set_string(const std::string& str) {
			impl().set_cell_value(str);
		}

		//! \brief Sets a double
		//!        in the cell.
		void set_value(double x) {
			impl().set_cell_value(x);
		}

		//! \brief Resets the contents
		//!        of the cell.
		void reset() {
			impl().reset();
		}

		void set_style(const std::string& str) {
			impl().set_style(str);
		}

		void set_foreground_color(int color) {
			impl().set_foreground_color(color);
		}

		void set_background_color(int color) {
			impl().set_background_color(color);
		}

		void set_font_size(double val) {
			impl().set_font_size(val);
		}

		void set_horizontal_alignment(boost::cell_horizontal_alignment::type t) {
			impl().set_horizontal_alignment(t);
		}

		void set_vertical_alignment(boost::cell_vertical_alignment::type t) {
			impl().set_vertical_alignment(t);
		}

		//! \brief Default Destructor.
		//!        Does nothing.
		~cell() {
		}

	}; // class cell

	//! \brief Compares the cell with a string assuming
	//!        that the cell contains a string.
	//!        Method is outside class because it
	//!        take cell as the second operand.
	inline bool operator<(const std::string& lhs, const cell& rhs) {
		if(rhs.get_content_type() == boost::cell_content_type::FORMULA) {
			return lhs < rhs.get_string();
		}
		else if (rhs.get_content_type() != boost::cell_content_type::STRING) {
				return boost::cell_content_type::STRING < rhs.get_content_type();
		}
		return lhs < rhs.get_string();
	}

	inline bool operator==(const std::string& lhs, const cell& rhs) {
		if(rhs.get_content_type() == boost::cell_content_type::FORMULA) {
			return lhs == rhs.get_string();
		}
		else if (rhs.get_content_type() != boost::cell_content_type::STRING) {
				return false;
		}
		return lhs == rhs.get_string();
	}

	inline bool operator!=(const std::string& lhs, const cell& rhs) {
		return !(lhs==rhs);
	}

	inline bool operator>(const std::string& lhs, const cell& rhs) {
		return rhs<lhs;
	}

	inline bool operator>=(const std::string& lhs, const cell& rhs) {
		return !(lhs<rhs);
	}


	inline bool operator<=(const std::string& lhs, const cell& rhs) {
		return !(lhs>rhs);
	}

	inline bool operator<(double lhs, const cell& rhs) {
		if(rhs.get_content_type() == boost::cell_content_type::FORMULA) {
			return lhs < rhs.get_value();
		}
		else if(rhs.get_content_type() != boost::cell_content_type::VALUE) {
				return boost::cell_content_type::VALUE < rhs.get_content_type();
		}
		return lhs < rhs.get_value();
	}

	inline bool operator==(double lhs, const cell& rhs) {
		if(rhs.get_content_type() == boost::cell_content_type::FORMULA) {
			return lhs == rhs.get_value();
		}
		else if (rhs.get_content_type() != boost::cell_content_type::VALUE) {
				return false;
		}
		return lhs == rhs.get_value();
	}

	inline bool operator!=(double lhs, const cell& rhs) {
		return !(lhs==rhs);
	}

	inline bool operator>(double lhs, const cell& rhs) {
		return rhs<lhs;
	}

	inline bool operator>=(double lhs, const cell& rhs) {
		return !(lhs<rhs);
	}

	inline bool operator<=(double lhs, const cell& rhs) {
		return !(lhs>rhs);
	}

	inline boost::variant<double, std::string> cell_to_variant(const boost::cell& a) {
		boost::variant<double, std::string> temp;
		switch(a.get_content_type()) {
			case boost::cell_content_type::STRING:
				temp = a.get_string();
				break;
			case boost::cell_content_type::VALUE:
				temp = a.get_value();
				break;
			case boost::cell_content_type::FORMULA:
				temp = a.get_formula();
				break;
			case boost::cell_content_type::EMPTY:
			case boost::cell_content_type::ERROR:
				break;
		}
		return temp;
	}

	inline void variant_to_cell(boost::cell& a,
											 const boost::variant<double, std::string>& var,
											 const boost::cell_content_type::type& t) {
			switch(t) {
				case boost::cell_content_type::STRING:
					a = boost::get<std::string>(var);
					break;
				case boost::cell_content_type::VALUE:
					a = boost::get<double>(var);
					break;
				case boost::cell_content_type::FORMULA:
					a = boost::get<std::string>(var);
					break;
				case boost::cell_content_type::EMPTY:
				case boost::cell_content_type::ERROR:
					a.reset();
					break;
			}
	}

	inline void swap(cell lhs, cell rhs) {
			boost::cell_content_type::type ltype = lhs.get_content_type();
			boost::cell_content_type::type rtype = rhs.get_content_type();
			boost::variant<double, std::string> lvalue = cell_to_variant(lhs);
			boost::variant<double, std::string> rvalue = cell_to_variant(rhs);
			variant_to_cell(rhs, lvalue, ltype);
			variant_to_cell(lhs, rvalue, rtype);
	}

	cell_data::cell_data(const cell& c) {
			type = c.get_content_type();
			switch(type) {
				case boost::cell_content_type::STRING:
					value = c.get_string();
					break;
				case boost::cell_content_type::VALUE:
					value = c.get_value();
					break;
				case boost::cell_content_type::FORMULA:
					value = c.get_formula();
					formula_val = c.get_value();
					break;
				case boost::cell_content_type::EMPTY:
				case boost::cell_content_type::ERROR:
					break;
			}
	}

	bool operator<(const cell_data& lhs, const cell& rhs) {
		if (lhs.type != rhs.get_content_type()) {
				return lhs.type < rhs.get_content_type();
		}
		switch(lhs.type) {
			case boost::cell_content_type::STRING:
				return boost::get<std::string>(lhs.value) < rhs.get_string();
			case boost::cell_content_type::VALUE:
				return boost::get<double>(lhs.value) < rhs.get_value();
			case boost::cell_content_type::FORMULA:
				return lhs.formula_val < rhs.get_value();
			case boost::cell_content_type::ERROR:
			case boost::cell_content_type::EMPTY:
					return false;
		}
		return false; // not reacheable
	}

	bool operator<(const cell& lhs, const cell_data& rhs) {
		if (lhs.get_content_type() != rhs.type) {
				return lhs.get_content_type() < rhs.type;
		}
		switch(lhs.get_content_type()) {
			case boost::cell_content_type::STRING:
				return lhs.get_string() < boost::get<std::string>(rhs.value);
			case boost::cell_content_type::VALUE:
				return lhs.get_value() < boost::get<double>(rhs.value);
			case boost::cell_content_type::FORMULA:
				return lhs.get_value() < rhs.formula_val;
			case boost::cell_content_type::ERROR:
			case boost::cell_content_type::EMPTY:
					return false;
		}
		return false; // not reacheable
	}

	bool operator==(const cell_data& lhs, const cell& rhs) {
		if (lhs.type == rhs.get_content_type()) {
			switch(lhs.type) {
				case boost::cell_content_type::STRING:
					return boost::get<std::string>(lhs.value) == rhs.get_string();
				case boost::cell_content_type::VALUE:
					return boost::get<double>(lhs.value) == rhs.get_value();
				case boost::cell_content_type::FORMULA:
					return lhs.formula_val == rhs.get_value();
				case boost::cell_content_type::ERROR:
				case boost::cell_content_type::EMPTY:
					return true;
			}
		}
		return false;
	}

	bool operator==(const cell& lhs, const cell_data& rhs) {
			return rhs==lhs;
	}

	inline bool operator!=(const cell& lhs, const cell_data& rhs) {
		return !(lhs==rhs);
	}

	inline bool operator>(const cell& lhs, const cell_data& rhs) {
		return rhs<lhs;
	}

	inline bool operator>=(const cell& lhs, const cell_data& rhs) {
		return !(lhs<rhs);
	}

	inline bool operator<=(const cell& lhs, const cell_data& rhs) {
		return !(lhs>rhs);
	}

	inline bool operator!=(const cell_data& lhs, const cell& rhs) {
		return !(lhs==rhs);
	}

	inline bool operator>(const cell_data& lhs, const cell& rhs) {
		return rhs<lhs;
	}

	inline bool operator>=(const cell_data& lhs, const cell& rhs) {
		return !(lhs<rhs);
	}

	inline bool operator<=(const cell_data& lhs, const cell& rhs) {
		return !(lhs>rhs);
	}

} // namespace boost

#endif
