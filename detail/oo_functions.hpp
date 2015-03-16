#ifndef _OO_FUNCTIONS_HPP
#define _OO_FUNCTIONS_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <boost/filesystem.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

namespace boost { namespace doc { namespace oo_functions {

	std::string convert_extension_to_pdf_filter(const std::string extension);
	::com::sun::star::uno::Reference<com::sun::star::lang::XMultiServiceFactory> connect_to_oo_server();
	void set_bootstrap_offapi();
	::rtl::OUString get_url_from_path(const boost::filesystem::path& path);
	void open_oo(const boost::filesystem::path& path);
	void export_oo(const boost::filesystem::path &inputPath, boost::document_file_format::type format);
	void close_oo(const boost::filesystem::path &inputPath,bool save);
	void save_oo(const boost::filesystem::path &inputPath);
	::com::sun::star::uno::Reference< com::sun::star::lang::XComponent> get_xComponent_from_path(const boost::filesystem::path& inputPath);

}}}

#endif