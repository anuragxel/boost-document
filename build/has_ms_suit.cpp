// Copyright Anurag Ghosh 2015.
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>
#include <windows.h>
#include <ole2.h>

//#ifndef BOOST_DOCUMENT_HAS_MS
//#   error BOOST_DOCUMENT_HAS_MS is not defined in has_ms_suilt.cpp! Jamfile error!
//#endif

HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...) {
    va_list marker;
    va_start(marker, cArgs);
    if(!pDisp) {
		return -1;
    }
    DISPPARAMS dp = { NULL, NULL, 0, 0 };
    DISPID dispidNamed = DISPID_PROPERTYPUT;
    DISPID dispID;
    HRESULT hr;
    char buf[200];
    char szName[200];
    WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);
    hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
    if(FAILED(hr)) {
    	return hr;
    }
    VARIANT *pArgs = new VARIANT[cArgs+1];
    for(int i=0; i<cArgs; i++) {
        pArgs[i] = va_arg(marker, VARIANT);
    }
    dp.cArgs = cArgs;
    dp.rgvarg = pArgs;
    if(autoType & DISPATCH_PROPERTYPUT) {
        dp.cNamedArgs = 1;
        dp.rgdispidNamedArgs = &dispidNamed;
    }
    hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
    if(FAILED(hr)) {
    	return hr;
    }
    va_end(marker);
    delete [] pArgs;   
    return hr;
}

int main() {

	CoInitialize(NULL);
	
	CLSID clsid;
    HRESULT hr;

    // Option 1. Get CLSID from ProgID using CLSIDFromProgID.
    LPCOLESTR progID = L"Excel.Application";
    hr = CLSIDFromProgID(progID, &clsid);
    if (FAILED(hr))
    {
        return 1;
    }
    IDispatch *pXlApp = NULL;
    hr = CoCreateInstance(      
        clsid,                  
        NULL,
        CLSCTX_LOCAL_SERVER,    
        IID_PPV_ARGS(&pXlApp));
    if (FAILED(hr))
    {
        return 1;
    }

    {
        VARIANT x;
        x.vt = VT_I4;
        x.lVal = 0;
        hr = AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlApp, L"Visible", 1, x);
    }

    IDispatch *pXlBooks = NULL;
    {
        VARIANT result;
        VariantInit(&result);
        AutoWrap(DISPATCH_PROPERTYGET, &result, pXlApp, L"Workbooks", 0);
        pXlBooks = result.pdispVal;
    }
    IDispatch *pXlBook = NULL;
    {
        VARIANT result;
        VariantInit(&result);
        AutoWrap(DISPATCH_METHOD, &result, pXlBooks, L"Add", 0);
        pXlBook = result.pdispVal;
    }
    if (pXlBook != NULL)
    {
        pXlBook->Release();
    }
    if (pXlBooks != NULL)
    {
        pXlBooks->Release();
    }
    if (pXlApp != NULL)
    {
        pXlApp->Release();
    }
    return 0;
}
