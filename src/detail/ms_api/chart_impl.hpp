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

#include <boost/document/detail/ms_api/ms_chart_func.hpp>


namespace boost { namespace detail {

class ms_chart : public chart_interface {

    protected:
    std::string name_, cell_range_;
    IDispatch* chart_ptr_;
    int left_, top_, width_, height_;
    boost::chart_type::type t_;

    public:
    ms_chart(IDispatch* chart_ptr,const std::string& name, const std::string& cell_range,
        int left, int top, int width, int height,
        boost::chart_type::type t) {
        this->chart_ptr_ = chart_ptr;
        this->cell_range_ = cell_range;
        this->name_ = name;
        this->left_ = left;
        this->top_ = top;
        this->width_ = width;
        this->height_ = height;
        this->t_ = t;
    }

    void set_title(const std::string& title) {
            boost::doc::ms_chart_func::set_title(chart_ptr_, title);
    }

    void set_legend(bool set) {
            boost::doc::ms_chart_func::set_legend(chart_ptr_, set);
    }

    ~ms_chart() {

    }

};

}} // namespace boost::detail


#endif
