#ifndef _MS_CHART_IMPL_HPP
#define _MS_CHART_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>

#include <boost/document/detail/document_exception.hpp>

#include <boost/document/detail/chart_interface.hpp>
#include <boost/document/detail/chart_type.hpp>
#include <boost/document/detail/chart_axis.hpp>

#include <boost/document/detail/ms_api/ms_chart_func.hpp>


namespace boost { namespace detail {

class ms_chart : public chart_interface {

    protected:
    std::string name_, cell_range_;
    IDispatch* chart_ptr_; 
    IDispatch* sheet_ptr_;
    int left_, top_, width_, height_;
    boost::chart_type::type t_;

    public:
    ms_chart(IDispatch* chart_ptr, IDispatch* sheet_ptr, const std::string& name, const std::string& cell_range,
        int left, int top, int width, int height) {
        this->chart_ptr_ = chart_ptr;
        this->sheet_ptr_ = sheet_ptr;
        this->cell_range_ = cell_range;
        this->name_ = name;
        this->left_ = left;
        this->top_ = top;
        this->width_ = width;
        this->height_ = height;
    }

    void set_title(const std::string& title) {
        boost::doc::ms_chart_func::set_title(chart_ptr_, title);
    }

    void set_axis_title(boost::chart_axis::type t, const std::string& title) {
        boost::doc::ms_chart_func::set_axis_title(chart_ptr_, t, title);
    }

    void set_axis_orientation(boost::chart_axis::type t, bool set) {
        boost::doc::ms_chart_func::set_axis_orientation(chart_ptr_, t, set);
    }

    void set_range(const std::string& cell_range) {
        cell_range_ = cell_range;
        boost::doc::ms_chart_func::set_cell_range(chart_ptr_, sheet_ptr_, cell_range_);
    }

    void set_position(std::size_t top, std::size_t left) {
        left_ = left;
        top_ = top;
        boost::doc::ms_chart_func::set_rectangle(name_, sheet_ptr_, (int)top_, (int)left_, (int)width_, (int)height_);
    }

    void set_size(std::size_t width, std::size_t height) {
        width_ = width;
        height_ = height;
        boost::doc::ms_chart_func::set_rectangle(name_, sheet_ptr_, (int)top_, (int)left_, (int)width_, (int)height_);
    }

    void set_type(boost::chart_type::type t, bool enable_3d) {
        t_ = t;
        boost::doc::ms_chart_func::set_type(chart_ptr_, t, enable_3d);
    }

    void set_legend(bool set) {
        boost::doc::ms_chart_func::set_legend(chart_ptr_, set);
    }

    ~ms_chart() {
    }

};

}} // namespace boost::detail


#endif
