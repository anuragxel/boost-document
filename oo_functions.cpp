#ifndef _OO_FUNCTIONS_CPP
#define _OO_FUNCTIONS_CPP

#ifdef _WIN32
#define OFFAPI "C:\\Program Files\\OpenOffice.org 3\\basis\\program\\offapi.rdb"    
#elif _WIN64
#define OFFAPI "C:\\Program Files (x86)\\OpenOffice.org 3\\basis\\program\\offapi.rdb"
#elif __linux
#define OFFAPI "/usr/lib/libreoffice/program/types/offapi.rdb"
#endif

#include "office_file_format.hpp"

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
#include <boost/throw_exception.hpp>

#include "oo_functions.hpp"
#include "document_exception.hpp"


using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::frame;
using namespace com::sun::star::registry;
using namespace com::sun::star::io;

using namespace rtl;
using namespace cppu;

using ::rtl::OString;
using ::rtl::OUString;
using ::rtl::OUStringToOString;

using namespace boost;

std::string boost::oo_functions::convert_extension_to_pdf_filter(const std::string extension) {
    if( extension == ".doc"  ||
        extension == ".docx" ||
        extension == ".txt"  ||
        extension == ".rtf"  ||
        extension == ".html" ||
        extension == ".htm"  ||
        extension == ".xml"  ||
        extension == ".odt"  ||
        extension == ".wps"  ||
        extension == ".wpd" ) {
            return "writer_pdf_Export";
    }
    else if( extension == ".xls"  || extension == ".xlsb" || extension == ".ods" ) {
            return "calc_pdf_Export";
    }
    else if (extension == ".ppt"  || extension == ".pptx" || extension == ".odp" ) {
            return "impress_pdf_Export";
    }
    else {
        return "";
    }
}

// Helper which returns the OfficeServiceManager
// if connection is established.
::com::sun::star::uno::Reference<com::sun::star::lang::XMultiServiceFactory> boost::oo_functions::connect_to_oo_server() {
   // create the initial component context
   Reference< XComponentContext > rComponentContext = 
                ::cppu::defaultBootstrap_InitialComponentContext();

   // retrieve the servicemanager from the context
   Reference< XMultiComponentFactory > rServiceManager = 
                rComponentContext->getServiceManager();

   // instantiate a sample service with the servicemanager.
   Reference< XInterface > rInstance =  rServiceManager->createInstanceWithContext(
         OUString::createFromAscii("com.sun.star.bridge.UnoUrlResolver" ),rComponentContext );

   // Query for the XUnoUrlResolver interface
   Reference< XUnoUrlResolver > rResolver( rInstance, UNO_QUERY );
   if( !rResolver.is() ) {
      boost::throw_exception(document_exception(
        "Error: Couldn't instantiate com.sun.star.bridge.UnoUrlResolver service."));
      
   }
   try {
      // resolve the uno-url
      rInstance = rResolver->resolve( OUString::createFromAscii("uno:socket,host=localhost,port=2083;urp;StarOffice.ServiceManager") );

      if( ! rInstance.is() ) {
         boost::throw_exception(document_exception(
          "StarOffice.ServiceManager is not exported from remote counterpart\n"));
         return NULL;
      }

      // query for the simpler XMultiServiceFactory interface, sufficient for scripting
      Reference< XMultiServiceFactory > rOfficeServiceManager (rInstance, UNO_QUERY);

      if( ! rOfficeServiceManager.is() ) {
            boost::throw_exception(document_exception(
              "Error :XMultiServiceFactory interface is not exported for StarOffice.ServiceManager\n"));
        }       
        return rOfficeServiceManager;
   }
   catch( Exception &e ) {
      return NULL;
   }
   return NULL;
}

// Setting up the bootstrapping and the params. :')
// Important for Open Office server communication
void boost::oo_functions::set_bootstrap_offapi() {
    OUString sAbsoluteDocUrl, sWorkingDir, sDocPathUrl;
    osl_getProcessWorkingDir(&sWorkingDir.pData);
    osl::FileBase::getFileURLFromSystemPath(
        OUString::createFromAscii(OFFAPI), 
        sDocPathUrl);
    osl::FileBase::getAbsoluteFileURL(sWorkingDir, sDocPathUrl, sAbsoluteDocUrl);
    rtl::Bootstrap::set(
        OUString::createFromAscii("URE_MORE_TYPES"),
        rtl::Bootstrap::encode(sAbsoluteDocUrl)
    );
}

::rtl::OUString  boost::oo_functions::get_url_from_path(const boost::filesystem::path& path) {
    OUString sAbsoluteDocUrl, sWorkingDir, sDocPathUrl;
    OUString sArgDocUrl = OUString::createFromAscii(path.string().c_str());
    osl_getProcessWorkingDir(&sWorkingDir.pData);
    osl::FileBase::getFileURLFromSystemPath( sArgDocUrl, sDocPathUrl);
    osl::FileBase::getAbsoluteFileURL( sWorkingDir, sDocPathUrl, sAbsoluteDocUrl);
    return sAbsoluteDocUrl;
}

// Code Adapted from the DocumentLoader Example given
// in the LibreOffice/OpenOffice Documentation
void boost::oo_functions::open_oo(const boost::filesystem::path& path) {
    if(!boost::filesystem::exists(path)) {
        boost::throw_exception(document_exception("Error: Path is Empty"));
    }

    boost::oo_functions::set_bootstrap_offapi();
    
    OUString conString = OUString("uno:socket,host=localhost,port=2083;urp;StarOffice.ServiceManager");

    Reference< XComponentContext > xComponentContext(::cppu::defaultBootstrap_InitialComponentContext());
    
    Reference< XMultiComponentFactory > xMultiComponentFactoryClient(
        xComponentContext->getServiceManager() );
    Reference< XInterface > xInterface =
        xMultiComponentFactoryClient->createInstanceWithContext(
            OUString::createFromAscii("com.sun.star.bridge.UnoUrlResolver"),
            xComponentContext );
    
    Reference< XUnoUrlResolver > resolver( xInterface, UNO_QUERY );
    try {
        xInterface = Reference< XInterface >(
            resolver->resolve( conString ), UNO_QUERY );
    }
    catch ( Exception& e ) {
        //std::cerr <<  "StarOffice.ServiceManager is not exported from remote counterpart" << std::endl;
        // I can add one execute `soffice "--accept=socket,host=localhost,port=2083;urp;StarOffice.ServiceManager"`
        // to start the server here and then try again, but i don't think that's a good way to go about this.
        // Will find the correct way ASAP, after export is done.
        //boost::oo_functions::start_oo_server();
        //xInterface = Reference< XInterface >(
        //    resolver->resolve( conString ), UNO_QUERY );    
        boost::throw_exception(document_exception("Error: Open Office server is not running."));
    }

    Reference< XPropertySet > xPropSet( xInterface, UNO_QUERY );
    xPropSet->getPropertyValue("DefaultContext") >>= xComponentContext;
    Reference< XMultiComponentFactory > xMultiComponentFactoryServer(
        xComponentContext->getServiceManager() );
    
    Reference < XDesktop2 > xComponentLoader = Desktop::create(xComponentContext);
    
    Reference< XComponent > xComponent = xComponentLoader->loadComponentFromURL(
        boost::oo_functions::get_url_from_path(path), 
        OUString::createFromAscii( "_default" ), 
        0,
        Sequence < ::com::sun::star::beans::PropertyValue >() 
    );
    Reference< XComponent >::query( xMultiComponentFactoryClient )->dispose();    
    if( !xComponentLoader.is() ){
            boost::throw_exception(document_exception("XComponentloader not successfully instantiated"));
    }
}


void boost::oo_functions::export_oo(const boost::filesystem::path &inputPath, boost::office_file_format::type format) {
    if(!boost::filesystem::exists(inputPath)) {
        boost::throw_exception(document_exception("Error: Path is Empty"));
    }
    
    boost::oo_functions::set_bootstrap_offapi();
    
    Reference< XMultiServiceFactory > rOfficeServiceManager;
    rOfficeServiceManager = boost::oo_functions::connect_to_oo_server();
    if( !rOfficeServiceManager.is() ){
        boost::throw_exception(document_exception("Error: Not Connected sucessfully to the office"));
    }
     //get the desktop service using createInstance returns an XInterface type
    Reference< XInterface  > Desktop = rOfficeServiceManager->createInstance(
    OUString::createFromAscii( "com.sun.star.frame.Desktop" ));
    
    //query for the XComponentLoader interface
    Reference< XComponentLoader > rComponentLoader (Desktop, UNO_QUERY);
    Reference< XComponent > xComponent;
    //get an instance of the spreadsheet
    try {
        Sequence < ::com::sun::star::beans::PropertyValue > frameProperties(1);
        frameProperties[0].Name = OUString::createFromAscii("Hidden");
        frameProperties[0].Value <<= (sal_Bool)true;
        xComponent = rComponentLoader->loadComponentFromURL(
            boost::oo_functions::get_url_from_path(inputPath),
            OUString::createFromAscii("_default"),
            0,
            frameProperties
        );
        if( !rComponentLoader.is() ){
            boost::throw_exception(document_exception("Error: XComponentloader not successfully instantiated"));
        }
    }
    catch( Exception &e ){
        boost::throw_exception(document_exception("Error: Unable to Load File."));
    }
    // Creating the output path in the 
    // same location as the input file path
    // And the filter. Right now works with docs
    // and calc. 
    boost::filesystem::path outputPath(inputPath);
    std::string filter;
    if(format == boost::office_file_format::PDF) {
        outputPath.replace_extension(".pdf");
        filter = boost::oo_functions::convert_extension_to_pdf_filter( inputPath.extension().string() );
    }
    // Other Options can be added later
    // to improve the API
    Sequence < ::com::sun::star::beans::PropertyValue > pdfProperties(2);
    pdfProperties[0].Name = OUString::createFromAscii("FilterName");
    pdfProperties[0].Value <<= OUString::createFromAscii(filter.c_str()); 
    pdfProperties[1].Name = OUString::createFromAscii("Overwrite");
    pdfProperties[1].Value <<= (sal_Bool)true;
    Reference < XStorable > xStorable(xComponent,UNO_QUERY);
    xStorable->storeToURL(boost::oo_functions::get_url_from_path(outputPath), pdfProperties);  
}

#endif