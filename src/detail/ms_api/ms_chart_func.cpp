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

void set_title(IDispatch* chart_ptr, const std::string& title) {
    VARIANT result;
    VariantInit(&result);
    boost::detail::com_variant hastitle(true);
    boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYPUT, &result, chart_ptr, L"HasTitle", 1, hastitle.native());
    
    IDispatch *chart_title_ptr;
    VariantInit(&result);
    boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, chart_ptr, L"ChartTitle", 0);
    chart_title_ptr=result.pdispVal;
    VariantClear(&result);

    IDispatch *chars_ptr;
    VariantInit(&result);
    boost::doc::ms_functions::auto_wrap_helper(DISPATCH_METHOD, &result, chart_title_ptr, L"Characters", 0);
    chars_ptr=result.pdispVal;
    boost::detail::com_variant vt_title(title);
    boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYPUT, &result, chars_ptr, L"Text", 1, vt_title.native());
    VariantClear(&result);

}

void set_type(IDispatch* chart_ptr, boost::chart_type::type t, bool enable_3d) {
    int chart_id = 1;
    // https://msdn.microsoft.com/en-us/library/office/ff838409.aspx
    switch(t) {
        case boost::chart_type::AREA : if(enable_3d) { chart_id = -4098; } else { chart_id = 1; } break;
        case boost::chart_type::BAR : if(enable_3d) { chart_id = 60; } else { chart_id = 57; } break;
        case boost::chart_type::BUBBLE : if(enable_3d) { chart_id = 87; } else { chart_id = 15; } break;
        case boost::chart_type::LINE : if(enable_3d) { chart_id = -4101; } else { chart_id =    65; } break;
        case boost::chart_type::PIE : if(enable_3d) { chart_id = -4102; } else { chart_id = 5; } break;
        case boost::chart_type::DONUT : chart_id = -4120; break; // no 3D
        case boost::chart_type::RADAR : chart_id = -4151; break; // no 3D
        case boost::chart_type::STOCK :  chart_id = 88; break; // no 3D
        case boost::chart_type::STOCKO :  chart_id = 89; break; // no 3D
        case boost::chart_type::STOCKV :  chart_id = 90; break; // no 3D
        case boost::chart_type::STOCKVO :  chart_id = 91; break; // no 3D
        case boost::chart_type::SCATTER : chart_id = -4169; break; // no 3D
    }
    boost::detail::com_variant vt_cell(chart_id);
    boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, chart_ptr, L"ChartType", 1, 
        vt_cell.native()
        );
}

void set_legend(IDispatch* chart_ptr, bool set) {

}

void add_chart(IDispatch* sheet_ptr, const std::string& name, const std::string& cell_range,
                int left, int top, int width, int height, boost::chart_type::type t, IDispatch*& chart_ptr) {
    // Get the range
    IDispatch* range_ptr;
    VARIANT result;
    VARIANT var_range_dispatch;
    VariantInit(&result);
    boost::detail::com_variant vt_cell(cell_range);
    boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"Range", 1,
        vt_cell.native()
        );
    range_ptr = result.pdispVal;
    var_range_dispatch.vt = VT_DISPATCH;
    var_range_dispatch.pdispVal = result.pdispVal;
    VariantClear(&result);
    
    // Get the chart objects
    IDispatch *chart_objects_ptr;
    VariantInit(&result);
    boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"ChartObjects", 0);
    chart_objects_ptr = result.pdispVal;
    VariantClear(&result);
    
    // Get the chart object by adding it
    IDispatch *chart_object_ptr;
    VariantInit(&result);
    boost::detail::com_variant vt_left((double)left), vt_top((double)top), vt_width((double)width), vt_height((double)height);
    boost::doc::ms_functions::auto_wrap_helper(DISPATCH_METHOD, &result, chart_objects_ptr, L"ADD", 4, 
        vt_height.native(),
        vt_width.native(),
        vt_top.native(),
        vt_left.native()
        );
    chart_object_ptr = result.pdispVal;
    VariantClear(&result);

    VariantInit(&result);
    boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, chart_object_ptr, L"Chart", 0);
    chart_ptr = result.pdispVal; // Now we have assigned the chart_ptr!
    VariantClear(&result);

    VariantInit(&result); 
    boost::doc::ms_functions::auto_wrap_helper(DISPATCH_METHOD, &result, chart_ptr, L"ChartWizard", 1, 
        var_range_dispatch
    );
    VariantClear(&result);

    set_legend(chart_ptr, true);
    set_title(chart_ptr, name);
    set_type(chart_ptr, t, false);

    VariantInit(&result);
    boost::detail::com_variant plotby(1);
    boost::doc::ms_functions::auto_wrap_helper(DISPATCH_METHOD, &result, chart_ptr, L"SetSourceData", 2, 
        plotby.native(), 
        var_range_dispatch
    );
}   

void delete_chart(IDispatch* sheet_ptr, const std::string& name) {
    // Get the chart objects
    VARIANT result;
    IDispatch *chart_objects_ptr;
    VariantInit(&result);
    boost::doc::ms_functions::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"ChartObjects", 0);
    chart_objects_ptr = result.pdispVal;
    VariantClear(&result);
}


}}}

#endif
