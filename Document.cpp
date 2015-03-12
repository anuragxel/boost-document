#ifndef _DOCUMENT_CPP
#define _DICUMENT_CPP

#include "Document.hpp"

Document::Document() {

}

Document::~Document() {

}


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
   if( ! rResolver.is() ){
      printf( "Error: Couldn't instantiate com.sun.star.bridge.UnoUrlResolver service\n" );
      return NULL;
   }
   try {
      // resolve the uno-url
      rInstance = rResolver->resolve( OUString::createFromAscii(
        "uno:socket,host=localhost,port=2083;urp;StarOffice.ServiceManager") );
 
      if( ! rInstance.is() ){
         printf( "StarOffice.ServiceManager is not exported from remote counterpart\n" );
         return NULL;
      }

      // query for the simpler XMultiServiceFactory interface, sufficient for scripting
      Reference< XMultiServiceFactory > rOfficeServiceManager (rInstance, UNO_QUERY);
 
      if( ! rOfficeServiceManager.is() ){
            printf( "XMultiServiceFactory interface is not exported for StarOffice.ServiceManager\n" );
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
            OUString("com.sun.star.bridge.UnoUrlResolver"),
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
    
    return 0;
}

void Document::open_spreadsheet(const boost::filesystem::path& path) {
    __openOO(path); // This the open office internal function.
}


void Document::export_spreadsheet(const filesystem::path& path,office_file_format::type format) {

    __initializeOffapi();

    Reference< XMultiServiceFactory > rOfficeServiceManager;
    rOfficeServiceManager = connectWithOO();
    if( rOfficeServiceManager.is() ){
        printf( "Connected sucessfully to the office\n" );
    }
 
     //get the desktop service using createInstance returns an XInterface type
    Reference< XInterface  > Desktop = rOfficeServiceManager->createInstance(
    OUString::createFromAscii( "com.sun.star.frame.Desktop" ));
 
     //query for the XComponentLoader interface
    Reference< XComponentLoader > rComponentLoader (Desktop, UNO_QUERY);
    if( rComponentLoader.is() ){
            printf( "XComponentloader successfully instantiated\n" );
    }

    //get an instance of the spreadsheet
    Reference< XComponent > xcomponent = rComponentLoader->loadComponentFromURL(
        getURLfromPath(path),
        OUString::createFromAscii("_blank"),
        0,
        Sequence < ::com::sun::star::beans::PropertyValue >()
    );

    // code here. :)
}

#endif
