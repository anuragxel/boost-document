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
#include <boost/document/detail/chart_axis.hpp>

namespace boost { namespace doc { namespace ms_chart_func {

void add_chart(IDispatch* sheet_ptr,const std::string& name, const std::string& cell_range,
               int left, int top, int width, int height, IDispatch*& chart_ptr);
void get_chart(IDispatch* sheet_ptr,const std::string& name, IDispatch*& chart_ptr);
void delete_chart(IDispatch* sheet_ptr, const std::string& name);

void set_title(IDispatch* chart_ptr, const std::string& title);
void set_legend(IDispatch* chart_ptr, bool set);
void set_type(IDispatch* chart_ptr, boost::chart_type::type t, bool enable_3d);
void set_legend(IDispatch* chart_ptr, bool set);
void set_axis_title(IDispatch* chart_ptr, boost::chart_axis::type t, const std::string& title);
void set_axis_orientation(IDispatch* chart_ptr, boost::chart_axis::type t, bool set);
void set_cell_range(IDispatch* chart_ptr, IDispatch* sheet_ptr, const std::string& cell_range);
void set_rectangle(std::string& chart_name, IDispatch* sheet_ptr, int top, int left, int width, int height);

}}}
#endif