#ifndef _OO_FUNCTIONS_HPP
#define _OO_FUNCTIONS_HPP

#include <string>
#include <iostream>
#include <cstdlib>

#include <boost/filesystem.hpp>

#include <sal/main.h>
#include <cppuhelper/bootstrap.hxx>
#include <osl/file.hxx>
#include <osl/process.h>
#include <rtl/process.h>
#include <rtl/bootstrap.hxx>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/frame/XStorable.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>

namespace boost { namespace ooInternalFunctions {

	std::string convertExtensionToPdfFilterType(const std::string extension);
	::rtl::Reference<com::sun::star::lang::XMultiServiceFactory> connectWithOO();
	void initializeOffapi();
	::rtl::OUString getURLfromPath(const boost::filesystem::path& path);
	int openOO(const boost::filesystem::path& path);
	int exportOO(const boost::filesystem::path &inputPath, boost::office_file_format::type format);
}
}
#endif