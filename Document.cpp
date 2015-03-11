#ifndef _DOCUMENT_CPP
#define _DICUMENT_CPP

#include "Document.hpp"

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

    printf("DBG %s\n", OUStringToOString(sArgDocUrl, RTL_TEXTENCODING_ASCII_US).pData->buffer );
    
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

void open(boost::filesystem::path& path) {
	open_oo(path,"uno:socket,host=localhost,port=2083;urp;StarOffice.ServiceManager");	
}

//void export(const filesystem::path& filenane,format::type format=format::PDF) {	
//}

#endif
