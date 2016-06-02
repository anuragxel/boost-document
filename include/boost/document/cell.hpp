#ifndef _CELL_HPP
#define _CELL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/document/detail/cell_interface.hpp>
#include <boost/document/detail/cell_content_type.hpp>

#include <boost/operators.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/variant.hpp>

namespace boost {

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
					return !(*this<str);
				}

				inline bool operator<=(const std::string& str) const {
					return (*this<str) || (*this==str);
				}

				inline bool operator>=(const std::string& str) const {
					return (*this>str) || (*this==str);
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
					return !(*this<val);
				}

				inline bool operator<=(double val) const {
					return (*this<val) || (*this==val);
				}

				inline bool operator>=(double val) const {
					return (*this>val) || (*this==val);
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
					return !(*this<c);
				}

				inline bool operator<=(const const_cell& c) const {
					return (*this<c) || (*this==c);
				}

				inline bool operator>=(const const_cell& c) const {
					return (*this>c) || (*this==c);
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

/*
		// To complete implementation deep-copy of cells
		// we implement a simple swap function,
		// swap(a,b) {
		//    tmp = a;
		//    a = b;
		//    b = a;
		// }
		void swap(cell& b) {
				// Essentially
				// temp = *this
				boost::variant<double, std::string> temp;
				boost::cell_content_type::type type = impl().get_content_type();
				switch(type) {
					case boost::cell_content_type::STRING:
						temp = impl().get_string();
						break;
					case boost::cell_content_type::VALUE:
						temp = impl().get_value();
						break;
					case boost::cell_content_type::FORMULA:
						temp = impl().get_formula();
						break;
					case boost::cell_content_type::EMPTY:
					case boost::cell_content_type::ERROR:
						break;
				}
				*this = b;
				// Essentially
				// b = temp
				switch(type) {
					case boost::cell_content_type::STRING:
						b = boost::get<std::string>(temp);
						break;
					case boost::cell_content_type::VALUE:
						b = boost::get<double>(temp);
						break;
					case boost::cell_content_type::FORMULA:
						b = boost::get<std::string>(temp);
						break;
					case boost::cell_content_type::EMPTY:
					case boost::cell_content_type::ERROR:
						b.reset();
						break;
				}
		}
*/

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
		return !(lhs<rhs);
	}

	inline bool operator>=(const std::string& lhs, const cell& rhs) {
		return (lhs>rhs) || (lhs==rhs);
	}


	inline bool operator<=(const std::string& lhs, const cell& rhs) {
		return (lhs<rhs) || (lhs==rhs);
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
		return !(lhs<rhs);
	}

	inline bool operator>=(double lhs, const cell& rhs) {
		return (lhs>rhs) || (lhs==rhs);
	}

	inline bool operator<=(double lhs, const cell& rhs) {
		return (lhs<rhs) || (lhs==rhs);
	}

	/*inline void swap(cell& lhs, cell& rhs) {
			std::cout << "outside swap" << std::endl;
			lhs.swap(rhs);
	}*/

} // namespace boost

/*
namespace std {
		template<>
		inline void swap<boost::cell>(boost::cell& lhs, boost::cell& rhs) {
				cout << "special swap" << endl;
				lhs.swap(rhs);
		}
} // namespace std
*/
#endif
