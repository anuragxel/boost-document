#ifndef _LIBRE_CHART_IMPL_HPP
#define _LIBRE_CHART_IMPL_HPP

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

#include <boost/document/detail/libre_api/libre_chart_func.hpp>


namespace boost { namespace detail {


class libre_chart: public chart_interface {

protected:
    std::string name_, cell_range_;
    ::com::sun::star::uno::Reference < com::sun::star::chart::XChartDocument > xChart_;
    ::com::sun::star::uno::Reference < com::sun::star::sheet::XSpreadsheet > xSheet_;
    std::size_t left_, top_, width_, height_;
    boost::chart_type::type t_;
    bool enable_3d_, legend_;

public:
    libre_chart(::com::sun::star::uno::Reference < com::sun::star::chart::XChartDocument > xChart,
        ::com::sun::star::uno::Reference < com::sun::star::sheet::XSpreadsheet > xSheet,
        const std::string& name, const std::string& cell_range,
        std::size_t left, std::size_t top, std::size_t width, std::size_t height) {
        this->xChart_ = xChart;
        this->xSheet_ = xSheet;
        this->cell_range_ = cell_range;
        this->name_ = name;
        this->left_ = left;
        this->top_ = top;
        this->width_ = width;
        this->height_ = height;
        this->legend_ = true;
        //this->enable_3d_ = false;
    }

    void set_title(const std::string& title) {
            boost::doc::libre_chart_func::set_title(xChart_, title);
    }

    void set_axis_title(boost::chart_axis::type t, const std::string& title) {
            boost::doc::libre_chart_func::set_axis_title(xChart_, t, title);
    }

    void set_type(boost::chart_type::type t, bool enable_3d) {
            boost::doc::libre_chart_func::set_type(xChart_, t, enable_3d);
            t_ = t;
            enable_3d_ = enable_3d;
    }

    void set_legend(bool set) {
            boost::doc::libre_chart_func::set_legend(xChart_, set);
            legend_ = set;
    }

    void set_axis_orientation(boost::chart_axis::type t, bool set) {
            boost::doc::libre_chart_func::set_axis_orientation(xChart_, t, set);
    }

    void set_range(const std::string& cell_range) {
            cell_range_ = cell_range;
            boost::doc::libre_chart_func::set_cell_range(xChart_, xSheet_, name_, cell_range_);
    }

    void set_position(std::size_t top, std::size_t left) {
            left_ = left;
            top_ = top;
            boost::doc::libre_chart_func::set_rectangle(xChart_, xSheet_, (int)top_, (int)left_, (int)width_, (int)height_);
    }

    void set_size(std::size_t width, std::size_t height) {
            width_ = width;
            height_ = height;
            boost::doc::libre_chart_func::set_rectangle(xChart_, xSheet_, (int)top_, (int)left_, (int)width_, (int)height_);
    }


    ~libre_chart() {
    }

};

}} // namespace boost::detail


#endif
