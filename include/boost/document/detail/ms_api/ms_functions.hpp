#ifndef _MS_FUNCTIONS_HPP
#define _MS_FUNCTIONS_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <cstdlib>
#include <windows.h>
#include <ole2.h>

#include <boost/filesystem.hpp>
#include <boost/document/detail/document_file_format.hpp>

namespace boost { namespace doc { namespace ms_functions {

HRESULT auto_wrap_helper(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...);
CLSID get_clsid();
void get_application_pointer(CLSID clsid, IDispatch *appl_ptr);
void set_visibility(IDispatch *appl_ptr);
void unset_visibility(IDispatch *appl_ptr);


IDispatch *open_ms(const boost::filesystem::path& path, IDispatch *appl_ptr, IDispatch **book_ptr);
IDispatch *create_ms(const boost::filesystem::path& path, IDispatch *appl_ptr, IDispatch **book_ptr);
void export_ms(const boost::filesystem::path& inputPath, boost::document_file_format::type format, IDispatch *book_ptr);
void close_ms(const boost::filesystem::path &inputPath, bool save, IDispatch *appl_ptr, IDispatch *book_ptr);
void save_ms(const boost::filesystem::path &inputPath, IDispatch *book_ptr);

}}}
#endif