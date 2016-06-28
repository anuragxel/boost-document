//! \file
//! \brief Libre Office Internal Functions
#ifndef _LIBRE_FUNCTIONS_CPP
#define _LIBRE_FUNCTIONS_CPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifdef _WIN32
#define OFFAPI "C:\\Program Files\\LibreOffice 4\\program\\types\\offapi.rdb"
#elif _WIN64
#define OFFAPI "C:\\Program Files (x86)\\LibreOffice 4\\program\\types\\offapi.rdb"
#elif __linux__
#define OFFAPI "/usr/lib/libreoffice/program/types/offapi.rdb"
#endif

#include <string>
#include <iostream>
#include <cstdlib>

#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>

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
#include <boost/document/detail/libre_api/libre_functions.hpp>
#include <boost/document/detail/document_exception.hpp>

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



namespace boost { namespace doc { namespace libre_functions {

//! \fn Provides the corresponding filter with respect to
//!        the extension given.
//!
//! The Star Office Backend provides filters to convert data
//! from one format to another, they have a specific name
//! for every filter which needs to be specified before calling
//! storeToURL()
std::string convert_extension_to_pdf_filter(const std::string extension) {
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

OUString get_new_doc_url_from_ext(const std::string extension) {
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
            return OUString::createFromAscii("private:factory/swriter");
    }
    else if( extension == ".xls"  || extension == ".xlsb" || extension == ".ods" ) {
            return OUString::createFromAscii("private:factory/scalc");
    }
    else if (extension == ".ppt"  || extension == ".pptx" || extension == ".odp" ) {
            return OUString::createFromAscii("private:factory/simpress");
    }
    else {
        return OUString::createFromAscii("");
    }
}

//! \fn Helper which returns the XComponentLoader
//!        if connection is established.
//!
//! The StartOffice Backend uses a client server model in which document
//! component ojects act as the client and request the server to perform
//! actions for them.
Reference < XComponentLoader > connect_to_libre_server() {
    // create the initial component context
    Reference< XComponentContext > rComponentContext( ::cppu::bootstrap() );
    // retrieve the servicemanager from the context
    Reference< XMultiComponentFactory > rServiceManager (
                 rComponentContext->getServiceManager() );
    // instantiate a sample service with the servicemanager.
    Reference< XInterface > rInstance =  rServiceManager->createInstanceWithContext(
          OUString::createFromAscii("com.sun.star.frame.Desktop"), rComponentContext );
    // Query for the XUnoUrlResolver interface
    try {
        Reference < XComponentLoader > xComponentLoader(
            rInstance, UNO_QUERY );
        return xComponentLoader;
    }
    catch(Exception &e) {
        boost::throw_exception(document_exception(
        "Error: Can't Connect to LibreOffice Server.\n"));
    }
    return NULL;
}

//! \fn The C++ Language Bindings need to be bootstrapped
//!        to the offapi.rdb file of the StarOffice backend.
//!
//! Setting up the bootstrapping and the parameters.
//! Important for Open Office server communication.
//! UNO & cppuhelper needs this to be run at least once.
void set_bootstrap_offapi() {
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


//! \fn Converts boost::filesystem::path to
//!        absolute path and then to OUString.
::rtl::OUString  get_url_from_path(const boost::filesystem::path& path) {
    OUString sAbsoluteDocUrl, sWorkingDir, sDocPathUrl;
    OUString sArgDocUrl = OUString::createFromAscii(path.string().c_str());
    osl_getProcessWorkingDir(&sWorkingDir.pData);
    osl::FileBase::getFileURLFromSystemPath( sArgDocUrl, sDocPathUrl);
    osl::FileBase::getAbsoluteFileURL( sWorkingDir, sDocPathUrl, sAbsoluteDocUrl);
    return sAbsoluteDocUrl;
}


//! \fn Gets the xComponent from the path of the office file
//!        given. Assumes file path is a valid one.
Reference< XComponent > get_xComponent_from_path(
            const boost::filesystem::path& inputPath) {

    //query for the XComponentLoader interface
    Reference< XComponentLoader > rComponentLoader = connect_to_libre_server();
    if(rComponentLoader == NULL) {
        boost::throw_exception(document_exception(
            "Error: XComponentloader not successfully instantiated"));
    }
    Reference< XComponent > xComponent;

    //get an instance of the spreadsheet
    try {
        Sequence < ::com::sun::star::beans::PropertyValue > frameProperties(1);
        frameProperties[0].Name = OUString::createFromAscii("Hidden");
        frameProperties[0].Value <<= (sal_Bool)true;
        xComponent = rComponentLoader->loadComponentFromURL(
            get_url_from_path(inputPath),
            OUString::createFromAscii("_default"),
            0,
            frameProperties
        );
        if( !rComponentLoader.is() ){
            boost::throw_exception(document_exception(
                "Error: XComponentloader not successfully instantiated"));
        }
    }
    catch( Exception &e ){
        //boost::throw_exception(document_exception(
        //    "Error: Unable to Load File. Check Permissions."));
    }
    return xComponent;
}


//! \fn Exports document using Calc/Excel given in
//!        the file path and the file format. Default
//!        format is PDF.
void export_libre(const boost::filesystem::path& inputPath,
                                        boost::document_file_format::type format,
                                        Reference < XComponent > xComponent,
                                      const boost::filesystem::path& outPath) {
    if( !xComponent.is() ) {
        boost::throw_exception(document_exception(
            "Error: Unable to load Document for exporting. Check Permissions."));
    }
    // Creating the output path in the
    // same location as the input file path
    // And the filter. Right now works with docs
    // and calc.
    boost::filesystem::path outputPath(outPath);
    std::string filter;
    if(format == boost::document_file_format::PDF) {
        outputPath.replace_extension(".pdf");
        filter = convert_extension_to_pdf_filter( inputPath.extension().string() );

        // Other Options can be added later
        // to improve the API
        Sequence < ::com::sun::star::beans::PropertyValue > pdfProperties(2);
        pdfProperties[0].Name = OUString::createFromAscii("FilterName");
        pdfProperties[0].Value <<= OUString::createFromAscii(filter.c_str());
        pdfProperties[1].Name = OUString::createFromAscii("Overwrite");
        pdfProperties[1].Value <<= (sal_Bool)true;

        try {
            Reference < XStorable > xStorable(xComponent,UNO_QUERY);
            xStorable->storeToURL(boost::doc::libre_functions::get_url_from_path(outputPath), pdfProperties);
        }
        catch(Exception& e) {
            boost::throw_exception(document_exception(
                "Error: Unable to export Document. Check Permissions."));
        }

    }

    else if(format == boost::document_file_format::CSV) {
        outputPath.replace_extension(".csv");
        filter = "Text - txt - csv (StarCalc)";
        Sequence < ::com::sun::star::beans::PropertyValue > properties(3);
        properties[0].Name = OUString::createFromAscii("FilterName");
        properties[0].Value <<= OUString::createFromAscii(filter.c_str());
        properties[1].Name = OUString::createFromAscii("FilterOptions");
        properties[1].Value <<= OUString::createFromAscii("44,34,0,1,1"); // 44 for comma separation, 34 for text quotation mark
        properties[2].Name = OUString::createFromAscii("Overwrite");
        properties[2].Value <<= (sal_Bool)true;
        try {
            Reference < XStorable > xStorable(xComponent,UNO_QUERY);
            xStorable->storeToURL(get_url_from_path(outputPath), properties);
        }
        catch(Exception& e) {
            boost::throw_exception(document_exception(
                "Error: Unable to export Document. Check Permissions."));
        }
    }
}


//! \fn Closes document using Calc/Excel given in
//!        the file path.
void close_libre(
        const boost::filesystem::path &inputPath,
        bool save,
        Reference < XComponent > xComponent) {

    if(!boost::filesystem::exists(inputPath)) {
        boost::throw_exception(document_exception(
            "Error: Path is empty or does not exist."));
    }

    Reference < XModel > xModel(xComponent, UNO_QUERY);
    if(xModel != NULL) {
        Reference < XModifiable > xModifiable(xComponent, UNO_QUERY);
        Reference < XStorable > xStorable(xComponent,UNO_QUERY);
        if(xStorable != NULL && xModifiable != NULL && save == true) {
            xStorable->storeToURL(get_url_from_path(inputPath),
                Sequence < ::com::sun::star::beans::PropertyValue >());
        }
        Reference < XCloseable > xCloseable(xComponent,UNO_QUERY);
        if(xCloseable != NULL) {
            try {
                xCloseable->close((sal_Bool)true);
            }
            catch (Exception &e) {
                //boost::throw_exception(document_exception("Error: Close XCloseable object failed."));
            }
        }
        else { // No xClosable. Use dispose to handle this.
                // Unreachable Condition. Hopefully. :)
        //Reference < XComponent > xDisposeable(xModel, UNO_QUERY);
            xComponent->dispose();
        }
    }
}


//! \fn saves document using Calc/Excel given in
//!        the file path.
void save_libre(const boost::filesystem::path& inputPath,
                                            Reference < XComponent > xComponent) {
    Reference < XModel > xModel(xComponent, UNO_QUERY);
    if(xModel != NULL) {
        Reference < XModifiable > xModifiable(xComponent, UNO_QUERY);
        Reference < XStorable > xStorable(xComponent,UNO_QUERY);
        try {
            if(xStorable != NULL && xModifiable != NULL) {
                xStorable->storeToURL(get_url_from_path(inputPath),
                    Sequence < ::com::sun::star::beans::PropertyValue >());
            }
        }
        catch(Exception& e) {
            boost::throw_exception(document_exception(
                "Error: File Can't be saved. Check Permissions."));
        }
    }
}

//! \fn Creates document given in
//!        the file path.
Reference< XComponent > create_libre(
        const boost::filesystem::path& inputPath) {

    //query for the XComponentLoader interface
    Reference< XComponentLoader > rComponentLoader = connect_to_libre_server();
    Reference< XComponent > xComponent;
    if(rComponentLoader == NULL) {
        boost::throw_exception(document_exception(
            "Error: XComponentloader not successfully instantiated"));
    }

    //get an instance of the spreadsheet
    try {
        Sequence < ::com::sun::star::beans::PropertyValue > frameProperties(1);
        frameProperties[0].Name = OUString::createFromAscii("Hidden");
        frameProperties[0].Value <<= (sal_Bool)true;
        xComponent = rComponentLoader->loadComponentFromURL(
            get_new_doc_url_from_ext(inputPath.extension().string()),
            OUString::createFromAscii("_default"),
            0,
            frameProperties
        );
        if( !rComponentLoader.is() ){
            boost::throw_exception(document_exception(
                "Error: XComponentloader not successfully instantiated"));
        }
    }
    catch( Exception &e ){
        //boost::throw_exception(document_exception(
        //    "Error: Unable to Load File. Check Permissions."));
    }
    return xComponent;
}


}}} // namespace boost::doc::libre_functions

#endif
