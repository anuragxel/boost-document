#ifndef _DOCUMENT_CPP
#define _DICUMENT_CPP

#include "Document.hpp"


Reference< XMultiServiceFactory > ooConnect(OUString con_string){
   // create the initial component context
   Reference< XComponentContext > rComponentContext = 
				defaultBootstrap_InitialComponentContext();
 
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
      rInstance = rResolver->resolve( OUString::createFromAscii( con_string ) );
 
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

// Code Adapted from the DocumentLoader Example given
// in the LibreOffice Documentation
int open_oo(const filesystem::path& path, std::string con_string="uno:socket,host=localhost,port=2083;urp;StarOffice.ServiceManager") {

	OUString OU_con_string = OUString::createFromAscii(con_string.c_str());

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
            resolver->resolve( OU_con_string ), UNO_QUERY );
    }
    catch ( Exception& e ) {
        exit(1);
    }
    Reference< XPropertySet > xPropSet( xInterface, UNO_QUERY );
    xPropSet->getPropertyValue("DefaultContext") >>= xComponentContext;

    Reference< XMultiComponentFactory > xMultiComponentFactoryServer(
        xComponentContext->getServiceManager() );
    Reference < XDesktop2 > xComponentLoader = Desktop::create(xComponentContext);

    OUString sAbsoluteDocUrl, sWorkingDir, sDocPathUrl;
    OUString sArgDocUrl = OUString::createFromAscii(path.string().c_str());

    osl_getProcessWorkingDir(&sWorkingDir.pData);
    osl::FileBase::getFileURLFromSystemPath( sArgDocUrl, sDocPathUrl);
    osl::FileBase::getAbsoluteFileURL( sWorkingDir, sDocPathUrl, sAbsoluteDocUrl);

    Reference< XComponent > xComponent = xComponentLoader->loadComponentFromURL(
        sAbsoluteDocUrl, 
        OUString( "_blank" ), 
        0,
        Sequence < ::com::sun::star::beans::PropertyValue >() 
       	);
    Reference< XComponent >::query( xMultiComponentFactoryClient )->dispose();

    return 0;
}

void open(const boost::filesystem::path& path) {
	open_oo(path,"uno:socket,host=localhost,port=2083;urp;StarOffice.ServiceManager");	
}


void export(const filesystem::path& path,format::type format=format::PDF) {
	Reference< XMultiServiceFactory > rOfficeServiceManager;
    rOfficeServiceManager = ooConnect();
    if( rOfficeServiceManager.is() ){
        printf( "Connected sucessfully to the office\n" );
    }
 
	//get the desktop service using createInstance returns an XInterface type
    Reference< XInterface  > Desktop = rOfficeServiceManager->createInstance(
    OUString::createFromAscii( "com.sun.star.frame.Desktop" ));
 
	//query for the XComponentLoader interface
    Reference< XComponentLoader > rComponentLoader (Desktop, UNO_QUERY);
    if( rComponentLoader.is() ){
        	printf( "XComponentloader successfully instanciated\n" );
    }

	//get an instance of the spreadsheet
    Reference< XComponent > xcomponent = rComponentLoader->loadComponentFromURL(
		OUString::createFromAscii("private:factory/scalc"),
        OUString::createFromAscii("_blank"),
        0,
        Sequence < ::com::sun::star::beans::PropertyValue >()
        );
    
    // access its XTextDocument interface
    XTextDocument xTextDocument = (XTextDocument) UnoRuntime.queryInterface(
            XTextDocument.class, xComponent);
     
    // access the text body and set a string
    XText xText = xTextDocument.getText();
    xText.setString("Simple PDF export demo.");
     
    // XStorable to store the document
    XStorable xStorable = (XStorable) UnoRuntime.queryInterface(
            XStorable.class, xComponent);
     
    // XStorable.storeToURL() expects an URL telling where to store the document
    // and an array of PropertyValue indicating how to store it

    // URL
    OUString sAbsoluteDocUrl, sWorkingDir, sDocPathUrl;
    OUString sArgDocUrl = OUString::createFromAscii(path.string().c_str());

    osl_getProcessWorkingDir(&sWorkingDir.pData);
    osl::FileBase::getFileURLFromSystemPath( sArgDocUrl, sDocPathUrl);
    osl::FileBase::getAbsoluteFileURL( sWorkingDir, sDocPathUrl, sAbsoluteDocUrl);

    sAbsoluteDocUrl = sAbsoluteDocUrl + ".pdf";

    // Exporting to PDF consists of giving the proper
    // filter name in the property "FilterName"
    // With only this, the document will be exported
    // using the existing PDF export settings
    // (the one used the last time, or the default if the first time)
    PropertyValue[] aMediaDescriptor = new PropertyValue[1];
    aMediaDescriptor[0] = new PropertyValue();
    aMediaDescriptor[0].Name = "FilterName";
    aMediaDescriptor[0].Value = "writer_pdf_Export";
    xStorable.storeToURL(sAbsoluteDocUrl, aMediaDescriptor);
    return 0;
}

#endif
