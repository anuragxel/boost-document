#ifndef _DOCUMENT_EXCEPTION_HPP
#define _DOCUMENT_EXCEPTION_HPP

namespace boost {

	class document_exception : public std::logic_error {
	public:
    	explicit document_exception(const std::string& msg) : std::logic_error(msg) {
    	}
	};

} // namespace boost

#endif