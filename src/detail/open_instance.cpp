#ifndef _OPEN_INSTANCE_CPP
#define _OPEN_INSTANCE_CPP

#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/document_interface.hpp>

namespace boost { namespace detail { 

document_interface* open_instance() {

#ifdef BOOST_DOCUMENT_HAS_LIBRE
    return open_libre_instance();
#elif defined(BOOST_DOCUMENT_HAS_MS)
    return open_ms_instance();
#else
	boost::throw_exception(document_exception(
            	"Error: No Known Office Suite Exists."));
#endif

}

}}

#endif