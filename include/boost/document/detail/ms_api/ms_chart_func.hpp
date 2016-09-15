#ifndef _MS_CHART_FUNC_HPP
#define _MS_CHART_FUNC_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <windows.h>
#include <ole2.h>
#include <objbase.h>

#include <boost/document/detail/chart_type.hpp>

namespace boost { namespace doc { namespace ms_chart_func {

void add_chart(IDispatch* sheet_ptr,const std::string& name, const std::string& cell_range,
               int left, int top, int width, int height, boost::chart_type::type t, IDispatch*& chart_ptr);

void delete_chart(IDispatch* sheet_ptr, const std::string& name);

void set_title(IDispatch* chart_ptr, const std::string& title);
void set_legend(IDispatch* chart_ptr, bool set);


}}}
#endif