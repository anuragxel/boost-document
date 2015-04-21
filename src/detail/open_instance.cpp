#ifndef _OPEN_INSTANCE_CPP
#define _OPEN_INSTANCE_CPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "libre_api/document_impl.hpp"

namespace boost { namespace doc { namespace detail { 

document_interface* open_instance() {

#ifdef BOOST_DOCUMENT_HAS_LIBRE
    return open_libre_instance();
#elif defined(BOOST_DOCUMENT_HAS_MS)
    return open_ms_instance();
#else
//	boost::throw_exception(document_exception("Error: No Known Office Suite Exists."));
#endif

}

}}}

#endif
