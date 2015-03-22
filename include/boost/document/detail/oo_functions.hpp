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

	//! \brief Provides the corresponding filter with respect to
	//!        the extension given.
	std::string convert_extension_to_pdf_filter(const std::string extension);
	
	//! \brief Helper which returns the OfficeServiceManager
	//!        if connection is established.
	::com::sun::star::uno::Reference<com::sun::star::lang::XMultiServiceFactory> connect_to_oo_server();
	
	//! \brief The C++ Language Bindings need to be bootstrapped 
	//!        to the offapi.rdb file of the StarOffice backend. 
	void set_bootstrap_offapi();
	
	//! \brief Converts boost::filesystem::path to
	//!        absolute path and then to OUString.
	::rtl::OUString get_url_from_path(const boost::filesystem::path& path);
	
	void open_oo(const boost::filesystem::path& path);

	void export_oo(const boost::filesystem::path &inputPath, boost::document_file_format::type format);

	void close_oo(const boost::filesystem::path &inputPath,bool save);

	void save_oo(const boost::filesystem::path &inputPath);

	::com::sun::star::uno::Reference< com::sun::star::lang::XComponent> get_xComponent_from_path(const boost::filesystem::path& inputPath);

}}}

#endif