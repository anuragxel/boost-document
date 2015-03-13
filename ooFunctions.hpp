#ifndef _OO_FUNCTIONS_HPP
#define _OO_FUNCTIONS_HPP

#ifdef _WIN32
#define OFFAPI "C:\\Program Files\\OpenOffice.org 3\\basis\\program\\offapi.rdb"	
#elif _WIN64
#define OFFAPI "C:\\Program Files (x86)\\OpenOffice.org 3\\basis\\program\\offapi.rdb"
#elif __linux
#define OFFAPI "/usr/lib/libreoffice/program/types/offapi.rdb"
#endif

#include <string>
#include <iostream>

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

#include "OfficeFileFormat.hpp"

using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::frame;
using namespace com::sun::star::registry;
using namespace com::sun::star::io;
//using namespace com::sun::star::text;

using namespace rtl;
using namespace cppu;

using ::rtl::OString;
using ::rtl::OUString;
using ::rtl::OUStringToOString;

using namespace boost;

std::string __convertExtensionToPdfFilterType(std::string extension);
Reference< XMultiServiceFactory > __connectWithOO();
void __initializeOffapi();
OUString __getURLfromPath(const boost::filesystem::path& path);
int __openOO(const boost::filesystem::path& path);
//int __exportOO(const filesystem::path &inputPath, office_file_format::type format);

#endif