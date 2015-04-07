#ifndef _DOCUMENT_EXCEPTION_HPP
#define _DOCUMENT_EXCEPTION_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost {
    
        //! \brief The generic exception
        //!        thrown by Boost Document
        //!       library.
        //!
	class document_exception : public std::logic_error {
	public:
    	explicit document_exception(const std::string& msg) : std::logic_error(msg) {
    	}
	};

} // namespace boost

#endif
