#ifndef _LIBRE_FUNCTIONS_HPP
#define _LIBRE_FUNCTIONS_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <boost/filesystem.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

namespace boost { namespace doc { namespace libre_functions {

	std::string convert_extension_to_pdf_filter(const std::string extension);
	//::com::sun::star::uno::Reference<com::sun::star::lang::XMultiServiceFactory> connect_to_libre_server();
	::com::sun::star::uno::Reference<com::sun::star::frame::XComponentLoader> connect_to_libre_server();
	void set_bootstrap_offapi();
	::rtl::OUString get_url_from_path(const boost::filesystem::path& path);
	::com::sun::star::uno::Reference< com::sun::star::lang::XComponent> create_libre(const boost::filesystem::path& path);
	void export_libre(const boost::filesystem::path &inputPath, boost::document_file_format::type format,::com::sun::star::uno::Reference< com::sun::star::lang::XComponent > xComponent, const boost::filesystem::path &outPath);
	void close_libre(const boost::filesystem::path &inputPath,bool save,::com::sun::star::uno::Reference< com::sun::star::lang::XComponent > xComponent);
	void save_libre(const boost::filesystem::path &inputPath,::com::sun::star::uno::Reference< com::sun::star::lang::XComponent > xComponent);
	::com::sun::star::uno::Reference< com::sun::star::lang::XComponent> get_xComponent_from_path(const boost::filesystem::path& inputPath);

}}}

#endif
