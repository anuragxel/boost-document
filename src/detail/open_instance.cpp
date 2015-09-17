#ifndef _OPEN_INSTANCE_CPP
#define _OPEN_INSTANCE_CPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <boost/document/detail/document_interface.hpp>

#ifdef BOOST_DOCUMENT_HAS_LIBRE
#include "libre_api/document_impl.hpp"
#elif defined(BOOST_DOCUMENT_HAS_MS)
#include "ms_api/document_impl.hpp"
#endif

namespace boost { namespace detail {

boost::shared_ptr<document_interface> open_instance() {

#ifdef BOOST_DOCUMENT_HAS_LIBRE
    return open_libre_instance();
#elif defined(BOOST_DOCUMENT_HAS_MS)
    return open_ms_instance();
#else
//	boost::throw_exception(document_exception("Error: No Known Office Suite Exists."));
#endif

}

}}

#endif
