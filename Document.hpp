#ifndef _DOCUMENT_HPP
#define _DOCUMENT_HPP

#include <string>
#include <stdio.h>
#include <wchar.h>

#include <boost/filesystem.hpp>
#include <sal/main.h>
#include <cppuhelper/bootstrap.hxx>

#include <osl/file.hxx>
#include <osl/process.h>
#include <rtl/process.h>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>

using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::frame;
using namespace com::sun::star::registry;

using namespace boost;

using ::rtl::OUString;
using ::rtl::OUStringToOString;


struct format {
	enum type {
		PDF,CSV,
	};
};

void open(const boost::filesystem::path& path);
void export(const filesystem::path& path,format::type format = format::PDF);

#endif
