#ifndef _CHART_INTERFACE_HPP
#define _CHART_INTERFACE_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/document/detail/chart_type.hpp>

namespace boost {

	class chart_interface {
	 public:
    virtual void set_title(const std::string& title) = 0;
    virtual void set_legend(bool set) = 0;
		virtual void set_type(boost::chart_type::type t, bool enable_3d) = 0;
		virtual ~chart_interface() {}
	};
} // namespace boost

#endif
