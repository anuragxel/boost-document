#ifndef _CELL_DATA_HPP
#define _CELL_DATA_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/document/detail/cell_content_type.hpp>
#include <boost/variant.hpp>

namespace boost {

  class cell;

  struct cell_data {
    cell_data() {}
    cell_data(const cell_data& c) : type(c.type), value(c.value), formula_val(c.formula_val) {}
    explicit cell_data(const cell& c);
    boost::cell_content_type::type type;
    boost::variant<double, std::string> value;
    // Should be both EqualityComparable and LessThanComparable,
    // but apparently it's not LessThanComparable
    boost::variant<double, std::string> formula_val; // How else to handle ?

  };

  inline bool operator<(const boost::variant<double, std::string>& lhs, const std::string& rhs) {
    return boost::get<std::string>(lhs) < rhs;
  }

  inline bool operator<(const boost::variant<double, std::string>& lhs, double rhs) {
    return boost::get<double>(lhs) < rhs;
  }

  inline bool operator<(const std::string& lhs, const boost::variant<double, std::string>& rhs) {
    return lhs < boost::get<std::string>(rhs);
  }

  inline bool operator<(double lhs, const boost::variant<double, std::string>& rhs) {
    return lhs < boost::get<double>(rhs);
  }

  /*inline bool operator<(const boost::variant<double, std::string>& lhs, const boost::variant<double, std::string>& rhs) {
      if(lhs.type() != rhs.type()) {
          return lhs.type() < rhs.type();
      }
      if(lhs.which() == typeid(std::string)) {
          return boost::get<std::string>(lhs) < boost::get<std::string>(rhs);
      }
      else if(lhs.which() == typeid(double)) {
          return boost::get<double>(lhs) < boost::get<double>(rhs);
      }
  }*/

  inline bool operator==(const boost::variant<double, std::string>& lhs, const std::string& rhs) {
    return boost::get<std::string>(lhs) == rhs;
  }

  inline bool operator==(const boost::variant<double, std::string>& lhs, double rhs) {
    return boost::get<double>(lhs) == rhs;
  }

  inline bool operator==(const std::string& lhs, const boost::variant<double, std::string>& rhs) {
    return lhs == boost::get<std::string>(rhs);
  }

  inline bool operator==(double lhs, const boost::variant<double, std::string>& rhs) {
    return lhs == boost::get<double>(rhs);
  }

  /*inline bool operator==(const boost::variant<double, std::string>& lhs, const boost::variant<double, std::string>& rhs) {
      if(lhs.type() == rhs.type()) {
          if(lhs.which() == typeid(std::string)) {
              return boost::get<std::string>(lhs) < boost::get<std::string>(rhs);
          }
          else if(lhs.which() == typeid(double)) {
              return boost::get<double>(lhs) < boost::get<double>(rhs);
          }
      }
      return false;
  }*/

} // namespace boost

#endif
