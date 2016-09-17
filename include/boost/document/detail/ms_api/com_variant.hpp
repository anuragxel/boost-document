#ifndef _COM_VARIANT_HPP
#define _COM_VARIANT_HPP

#include <string>
#include <windows.h>
#include <ole2.h>
#include <objbase.h>

#include <boost/noncopyable.hpp>
#include <boost/filesystem.hpp>

namespace boost { namespace detail {

class com_variant : boost::noncopyable {
    VARIANT v_;

    static VARIANT make_empty() {
        VARIANT v;
        VariantInit(&v);
        return v;
    }

    VARIANT make_bstr(const std::string& str) {
        VARIANT v;
        const int wslen = ::MultiByteToWideChar(CP_ACP, 0 ,str.c_str(), str.length(), NULL, 0);
        v.vt = VT_BSTR;
        v.bstrVal = ::SysAllocStringLen(NULL, wslen);
        ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), v_.bstrVal, wslen);

        return v;
    }

    static VARIANT make_int(int i) {
        VARIANT v;
        v.vt = VT_I4;
        v.lVal = i;
        return v;
    }

    static VARIANT make_double(double i) {
        VARIANT v;
        v.vt = VT_R8;
        v.dblVal = i;
        return v;
    }

    static VARIANT make_bool(bool i) {
        VARIANT v;
        v.vt = VT_BOOL;
        v.boolVal = (i==true)?VARIANT_TRUE:VARIANT_FALSE;
        return v;
    }

public:
    com_variant()
        : v_(make_empty())
    {}

    explicit com_variant(const std::string& str)
        : v_(make_bstr(str))
    {}

    explicit com_variant(const boost::filesystem::path& path)
        : v_(make_bstr(path.string()))
    {}

    explicit com_variant(int i)
        : v_(make_int(i))
    {}


    explicit com_variant(double i)
        : v_(make_double(i))
    {}

    explicit com_variant(bool i)
        : v_(make_bool(i))
    {}


    void clear() {
        VariantClear(&v_);
    }

    ~com_variant() {
        clear();
    }

    com_variant& operator=(const std::string& str) {
        clear();
        v_ = make_bstr(str);
        return *this;
    }

    com_variant& operator=(const boost::filesystem::path& path) {
        clear();
        v_ = make_bstr(path.string());
        return *this;
    }

    com_variant& operator=(int i) {
        clear();
        v_ = make_int(i);
        return *this;
    }

    com_variant& operator=(double i) {
        clear();
        v_ = make_double(i);
        return *this;
    }

    com_variant& operator=(bool i) {
        clear();
        v_ = make_bool(i);
        return *this;
    }

    VARIANT native() {
        return v_;
    }
};

}}

#endif