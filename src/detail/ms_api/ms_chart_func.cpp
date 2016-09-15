#ifndef _MS_CHART_FUNC_CPP
#define _MS_CHART_FUNC_CPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ole2.h>
#include <objbase.h>

#include <boost/filesystem.hpp>

#include <boost/document/detail/chart_type.hpp>

#include <boost/document/detail/ms_api/com_variant.hpp>
#include <boost/document/detail/ms_api/ms_functions.hpp>

namespace boost { namespace doc { namespace ms_chart_func {

void add_chart(IDispatch* sheet_ptr,const std::string& name, const std::string& cell_range,
               int left, int top, int width, int height, boost::chart_type::type t, IDispatch*& chart_ptr) {}

void delete_chart(IDispatch* sheet_ptr, const std::string& name) {}

void set_title(IDispatch* chart_ptr, const std::string& title) {}

void set_legend(IDispatch* chart_ptr, bool set) {}

}}}

#endif
