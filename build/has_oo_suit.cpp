// Copyright Anurag Ghosh 2015.
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <sal/main.h>
#include <cppuhelper/bootstrap.hxx>
#include <osl/file.hxx>
#include <osl/process.h>
#include <rtl/process.h>
#include <rtl/bootstrap.hxx>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>
#include <com/sun/star/frame/XDesktop.hpp>

#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/frame/XStorable.hpp>
#include <com/sun/star/frame/XModel.hpp>

#include <com/sun/star/util/XCloseable.hpp>
#include <com/sun/star/util/XModifiable.hpp>

#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>

#include <boost/document/detail/document_file_format.hpp>
#include <boost/document/detail/oo_functions.hpp>
#include <boost/document/detail/document_exception.hpp>

#ifndef BOOST_DOCUMENT_HAS_OO
#   error BOOST_DOCUMENT_HAS_OO is not defined in has_oo_suilt.cpp! Jamfile error!
#endif



using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::frame;
using namespace com::sun::star::registry;
using namespace com::sun::star::io;
using namespace com::sun::star::util;

using namespace rtl;
using namespace cppu;

using ::rtl::OString;
using ::rtl::OUString;
using ::rtl::OUStringToOString;


int main () {    
   Reference< XComponentContext > rComponentContext = 
                ::cppu::defaultBootstrap_InitialComponentContext();

   Reference< XMultiComponentFactory > rServiceManager = 
                rComponentContext->getServiceManager();

   Reference< XInterface > rInstance =  rServiceManager->createInstanceWithContext(
         OUString::createFromAscii("com.sun.star.bridge.UnoUrlResolver" ),rComponentContext );

    (void)rInstance; // suppressing warnings

    return 0;
}
