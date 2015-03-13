#ifndef _DOCUMENT_CPP
#define _DOCUMENT_CPP

#include "Document.hpp"

Document::Document() {

}

Document::~Document() {

}

std::string __convertExtensionToPdfFilterType(std::string extension)
{
    if(	extension == ".doc"  ||
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
Reference< XMultiServiceFactory > connectWithOO(){
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
   if( !rResolver.is() ){
      std::cerr << "Error: Couldn't instantiate com.sun.star.bridge.UnoUrlResolver service." << std::endl;
      return NULL;
   }
   try {
      // resolve the uno-url
      rInstance = rResolver->resolve( OUString::createFromAscii(
        "uno:socket,host=localhost,port=2083;urp;StarOffice.ServiceManager") );
 
      if( ! rInstance.is() ){
         std::cerr << "StarOffice.ServiceManager is not exported from remote counterpart\n" << std::endl;
         return NULL;
      }

      // query for the simpler XMultiServiceFactory interface, sufficient for scripting
      Reference< XMultiServiceFactory > rOfficeServiceManager (rInstance, UNO_QUERY);
 
      if( ! rOfficeServiceManager.is() ){
            std::cerr << "XMultiServiceFactory interface is not exported for StarOffice.ServiceManager\n" << std::endl;
            return NULL;
        }       
        return rOfficeServiceManager;
   }
   catch( Exception &e ){
      OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
      printf( "Error: %s\n", o.pData->buffer );
      return NULL;
   }
   return NULL;
}

// Setting up the bootstrapping and the params. :')
// Inportant for Open Office server communication
void __initializeOffapi() {
    OUString sAbsoluteDocUrl, sWorkingDir, sDocPathUrl;
    osl_getProcessWorkingDir(&sWorkingDir.pData);
    osl::FileBase::getFileURLFromSystemPath(
        OUString::createFromAscii("/usr/lib/libreoffice/program/types/offapi.rdb"), // This makes it non portable. Think workaround. :(
        sDocPathUrl);
    osl::FileBase::getAbsoluteFileURL(sWorkingDir, sDocPathUrl, sAbsoluteDocUrl);
    rtl::Bootstrap::set(
        OUString::createFromAscii("URE_MORE_TYPES"),
        rtl::Bootstrap::encode(sAbsoluteDocUrl)
    );
}

OUString getURLfromPath(const boost::filesystem::path& path) {
    OUString sAbsoluteDocUrl, sWorkingDir, sDocPathUrl;
    OUString sArgDocUrl = OUString::createFromAscii(path.string().c_str());
    osl_getProcessWorkingDir(&sWorkingDir.pData);
    osl::FileBase::getFileURLFromSystemPath( sArgDocUrl, sDocPathUrl);
    osl::FileBase::getAbsoluteFileURL( sWorkingDir, sDocPathUrl, sAbsoluteDocUrl);
    return sAbsoluteDocUrl;
}


// Code Adapted from the DocumentLoader Example given
// in the LibreOffice/OpenOffice Documentation
int __openOO(const boost::filesystem::path& path) {

    __initializeOffapi();
    
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
        std::cerr <<  "StarOffice.ServiceManager is not exported from remote counterpart" << std::endl;

        // I can add one execute `soffice "--accept=socket,host=localhost,port=2083;urp;StarOffice.ServiceManager"`
        // to start the server here and then try again, but i don't think that's a good way to go about this.
        // Will find the correct way ASAP, after export is done.

        exit(1);
    }

    Reference< XPropertySet > xPropSet( xInterface, UNO_QUERY );
    xPropSet->getPropertyValue("DefaultContext") >>= xComponentContext;
    Reference< XMultiComponentFactory > xMultiComponentFactoryServer(
        xComponentContext->getServiceManager() );
    
    Reference < XDesktop2 > xComponentLoader = Desktop::create(xComponentContext);
    
    Reference< XComponent > xComponent = xComponentLoader->loadComponentFromURL(
        getURLfromPath(path), 
        OUString::createFromAscii( "_blank" ), 
        0,
        Sequence < ::com::sun::star::beans::PropertyValue >() 
    );
    Reference< XComponent >::query( xMultiComponentFactoryClient )->dispose();    
    if( !xComponentLoader.is() ){
            std::cerr << "XComponentloader not successfully instantiated" << std::endl;
            return -1;
    }
    return 0;
}


int __exportOO(const filesystem::path &inputPath, office_file_format::type format) {

    __initializeOffapi();

    Reference< XMultiServiceFactory > rOfficeServiceManager;
    rOfficeServiceManager = connectWithOO();
    if( !rOfficeServiceManager.is() ){
        std::cerr << "Not Connected sucessfully to the office" << std::endl;
        return -1;
    }
     //get the desktop service using createInstance returns an XInterface type
    Reference< XInterface  > Desktop = rOfficeServiceManager->createInstance(
    OUString::createFromAscii( "com.sun.star.frame.Desktop" ));
    
     //query for the XComponentLoader interface
    Reference< XComponentLoader > rComponentLoader (Desktop, UNO_QUERY);
    Reference< XComponent > xComponent;
    //get an instance of the spreadsheet
    try {
		xComponent = rComponentLoader->loadComponentFromURL(
        	getURLfromPath(inputPath),
        	OUString::createFromAscii("_blank"),
        	0,
        	Sequence < ::com::sun::star::beans::PropertyValue >()
    	);
    	if( !rComponentLoader.is() ){
            std::cerr << "XComponentloader not successfully instantiated" << std::endl;
            return -1;
    	}
    }
    catch( Exception &e ){
    	std::cerr << "Error While Loading File." << std::endl;
    	return -1;
    }
    
    boost::filesystem::path outputPath(inputPath);
    std::string filter;
    if(format == boost::office_file_format::PDF) {
    	outputPath.replace_extension(".pdf");
    	filter = __convertExtensionToPdfFilterType( inputPath.extension().string() );
  	}
   	
   	Sequence < ::com::sun::star::beans::PropertyValue > pdfProperties(2);
    pdfProperties[0].Name = OUString::createFromAscii("FilterName");
    pdfProperties[0].Value <<= OUString::createFromAscii(filter.c_str()); 
    pdfProperties[1].Name = OUString::createFromAscii("Overwrite");
    pdfProperties[1].Value <<= (sal_Bool)true;

    Reference < XStorable > xStorable(xComponent,UNO_QUERY);
    xStorable->storeToURL(getURLfromPath(outputPath), pdfProperties); 
}

void Document::open_document(const boost::filesystem::path& path) {
    __openOO(path); // This the open office internal function.
}


void Document::export_document(const filesystem::path& path,office_file_format::type format) {
    __exportOO(path,format); // This the open office internal function.
}

#endif
