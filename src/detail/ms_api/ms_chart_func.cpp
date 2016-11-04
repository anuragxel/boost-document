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
#include <boost/document/detail/chart_axis.hpp>

#include <boost/document/detail/ms_api/com_variant.hpp>
#include <boost/document/detail/ms_api/ms_functions.hpp>

#include <boost/document/detail/document_exception.hpp>

namespace ms_func = boost::doc::ms_functions;

namespace boost { namespace doc { namespace ms_chart_func {

void set_title(IDispatch* chart_ptr, const std::string& title) {
    VARIANT result;
    VariantInit(&result);
    boost::detail::com_variant hastitle(true);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, &result, chart_ptr, L"HasTitle", 1, 
        hastitle.native()
    );
    
    IDispatch *chart_title_ptr;
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, chart_ptr, L"ChartTitle", 0);
    chart_title_ptr=result.pdispVal;
    VariantClear(&result);

    IDispatch *chars_ptr;
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_METHOD, &result, chart_title_ptr, L"Characters", 0);
    chars_ptr=result.pdispVal;
    boost::detail::com_variant vt_title(title);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, &result, chars_ptr, L"Text", 1, 
        vt_title.native()
    );
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
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, chart_ptr, L"ChartType", 1, 
        vt_cell.native()
        );
}

void set_legend(IDispatch* chart_ptr, bool set) {
    VARIANT result;
    VariantInit(&result);
    boost::detail::com_variant haslegend(set);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, &result, chart_ptr, L"HasLegend", 1, 
        haslegend.native()
    );
}

void set_axis_title(IDispatch* chart_ptr, boost::chart_axis::type t, const std::string& title) {
    // https://msdn.microsoft.com/en-us/library/office/ff198060.aspx
    boost::detail::com_variant axes_type;
    if(t == boost::chart_axis::X) {
        axes_type = 1;
    }
    else if (t == boost::chart_axis::Y) {
        axes_type = 2;
    }
    else if(t == boost::chart_axis::Z) {
        axes_type = 3;
    }
    // check if axis exists
    VARIANT result;
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, chart_ptr, L"HasAxis", 1,
        axes_type.native()
    );
    bool check = (result.boolVal==VARIANT_TRUE)?true:false;
    VariantClear(&result);

    if(!check) {
        boost::throw_exception(document_exception(
              "Error: Chart type doesn't support axis."));
    }

    // get the axis
    IDispatch *axis_ptr;
    VariantInit(&result);
    // https://msdn.microsoft.com/en-us/library/office/ff196160.aspx
    boost::detail::com_variant axes_group(1);
    // https://msdn.microsoft.com/en-us/library/office/ff821055.aspx
    // Reverse as usual
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, chart_ptr, L"Axes", 2,
        axes_group.native(),
        axes_type.native()
    );
    axis_ptr = result.pdispVal;
    VariantClear(&result);

    // Get the Axis Title Obj
    IDispatch *axis_title_ptr;
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, axis_ptr, L"AxisTitle", 0);
    axis_title_ptr=result.pdispVal;
    VariantClear(&result);

    // Set the title 
    IDispatch *chars_ptr;
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_METHOD, &result, axis_title_ptr, L"Characters", 0);
    chars_ptr = result.pdispVal;
    boost::detail::com_variant vt_title(title);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, &result, chars_ptr, L"Text", 1, 
        vt_title.native()
    );
    VariantClear(&result);


}

void set_axis_orientation(IDispatch* chart_ptr, boost::chart_axis::type t, bool set) {
    // https://msdn.microsoft.com/en-us/library/office/ff198060.aspx
    boost::detail::com_variant axes_type;
    if(t == boost::chart_axis::X) {
        axes_type = 1;
    }
    else if (t == boost::chart_axis::Y) {
        axes_type = 2;
    }
    else if(t == boost::chart_axis::Z) {
        axes_type = 3;
    }
    // check if axis exists
    VARIANT result;
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, chart_ptr, L"HasAxis", 1,
        axes_type.native()
    );
    bool check = (result.boolVal==VARIANT_TRUE)?true:false;
    VariantClear(&result);

    if(!check) {
        boost::throw_exception(document_exception(
              "Error: Chart type doesn't support axis."));
    }

    // get the axis
    IDispatch *axis_ptr;
    VariantInit(&result);
    // https://msdn.microsoft.com/en-us/library/office/ff196160.aspx
    boost::detail::com_variant axes_group(1);
    // https://msdn.microsoft.com/en-us/library/office/ff821055.aspx
    // Reverse as usual
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, chart_ptr, L"Axes", 2,
        axes_group.native(),
        axes_type.native()
    );
    axis_ptr = result.pdispVal;
    VariantClear(&result);

    // Change the axis orientation
    // Crosses property: https://msdn.microsoft.com/en-us/library/office/ff820959.aspx
    // XlAxisCrosses Enum: https://msdn.microsoft.com/en-us/library/office/ff195050.aspx
    // Maximum = 2, Minimum = 4
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, axis_ptr, L"Crosses", 0);
    int current_axis_orient = result.lVal;
    VariantClear(&result);

    // Reverse direction
    int setter = (current_axis_orient == 4)?2:4;
    boost::detail::com_variant vt_prop(setter);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, axis_ptr, L"Crosses", 1, 
        vt_prop.native()
    );
}

void set_cell_range(IDispatch* chart_ptr, IDispatch* sheet_ptr, const std::string& cell_range) {
    // Get the range pointer
    VARIANT result;
    VARIANT var_range_dispatch;
    VariantInit(&result);
    boost::detail::com_variant vt_cell(cell_range);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"Range", 1,
        vt_cell.native()
        );
    var_range_dispatch.vt = VT_DISPATCH;
    var_range_dispatch.pdispVal = result.pdispVal;
    VariantClear(&result);
 
    // Set the source data
    VariantInit(&result);
    boost::detail::com_variant plotby(1);
    ms_func::auto_wrap_helper(DISPATCH_METHOD, &result, chart_ptr, L"SetSourceData", 2, 
        plotby.native(), 
        var_range_dispatch
    );
}

void set_rectangle(std::string& chart_name, IDispatch* sheet_ptr, int top, int left, int width, int height) {
    // http://stackoverflow.com/questions/2191000/how-do-we-set-the-position-of-an-excel-chart-from-c
    VARIANT result;
    IDispatch *shapes_ptr;
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"Shapes", 0);
    shapes_ptr = result.pdispVal;
    VariantClear(&result);

    boost::detail::com_variant vt_chart(chart_name);
    IDispatch* shape_ptr;
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, shapes_ptr, L"Item", 1,
        vt_chart.native()
        );
    shape_ptr = result.pdispVal;


    boost::detail::com_variant vt_prop((double)top);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, shape_ptr, L"Top", 1, 
        vt_prop.native()
        );
    vt_prop.clear();
    vt_prop = (double)left;
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, shape_ptr, L"Left", 1, 
        vt_prop.native()
        );
    vt_prop.clear();
    vt_prop = (double)width;
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, shape_ptr, L"Width", 1, 
        vt_prop.native()
        );
    vt_prop.clear();
    vt_prop = (double)height;
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYPUT, NULL, shape_ptr, L"Height", 1, 
        vt_prop.native()
    );
    vt_prop.clear();

}

void add_chart(IDispatch* sheet_ptr, const std::string& name, const std::string& cell_range,
                int left, int top, int width, int height, IDispatch*& chart_ptr) {
    // Get the range
    VARIANT result;
    VARIANT var_range_dispatch;
    VariantInit(&result);
    boost::detail::com_variant vt_cell(cell_range);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"Range", 1,
        vt_cell.native()
        );
    var_range_dispatch.vt = VT_DISPATCH;
    var_range_dispatch.pdispVal = result.pdispVal;
    VariantClear(&result);
    
    // Get the chart objects
    IDispatch *chart_objects_ptr;
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"ChartObjects", 0);
    chart_objects_ptr = result.pdispVal;
    VariantClear(&result);
    
    // Get the chart object by adding it
    IDispatch *chart_object_ptr;
    VariantInit(&result);
    boost::detail::com_variant vt_left((double)left), vt_top((double)top), vt_width((double)width), vt_height((double)height);
    ms_func::auto_wrap_helper(DISPATCH_METHOD, &result, chart_objects_ptr, L"ADD", 4, 
        vt_height.native(),
        vt_width.native(),
        vt_top.native(),
        vt_left.native()
        );
    chart_object_ptr = result.pdispVal;
    VariantClear(&result);

    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, chart_object_ptr, L"Chart", 0);
    chart_ptr = result.pdispVal; // Now we have assigned the chart_ptr!
    VariantClear(&result);

    VariantInit(&result); 
    ms_func::auto_wrap_helper(DISPATCH_METHOD, &result, chart_ptr, L"ChartWizard", 1, 
        var_range_dispatch
    );
    VariantClear(&result);

    set_legend(chart_ptr, true);
    set_title(chart_ptr, name);
    set_type(chart_ptr, boost::chart_type::SCATTER, false);

    VariantInit(&result);
    boost::detail::com_variant plotby(1);
    ms_func::auto_wrap_helper(DISPATCH_METHOD, &result, chart_ptr, L"SetSourceData", 2, 
        plotby.native(), 
        var_range_dispatch
    );
}

void get_chart(IDispatch* sheet_ptr, const std::string& chart_name, IDispatch*& chart_ptr) {
    // Get the chart objects
    VARIANT result;
    IDispatch *chart_objects_ptr;
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"ChartObjects", 0);
    chart_objects_ptr = result.pdispVal;
    VariantClear(&result);

    // Get from the chart objects
    boost::detail::com_variant vt_sheet(chart_name);
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, chart_objects_ptr, L"Charts", 1,
        vt_sheet.native()
        );
    chart_ptr = result.pdispVal;   
}


void delete_chart(IDispatch* sheet_ptr, const std::string& name) {
    // Get the chart objects
    VARIANT result;
    IDispatch *chart_objects_ptr;
    VariantInit(&result);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, &result, sheet_ptr, L"ChartObjects", 0);
    chart_objects_ptr = result.pdispVal;
    VariantClear(&result);

    // Delete from the chart objects
    IDispatch *chart_ptr;
    get_chart(chart_objects_ptr, name, chart_ptr);
    ms_func::auto_wrap_helper(DISPATCH_PROPERTYGET, NULL, chart_ptr, L"Delete", 0);
}

}}}

#endif
