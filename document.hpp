#ifndef _DOCUMENT_HPP
#define _DOCUMENT_HPP

#include <boost/filesystem.hpp>
#include "office_file_format.hpp"


namespace boost {

	/*
	class document_exception : public std::logic_error {
	public:
    	explicit document_exception(const std::string& msg) {
       		std::logic_error(msg)
    	}
	};
	*/
	
	class document {
	private:
		boost::filesystem::path file_path;
	public:
		document();
		document(const boost::filesystem::path path);
		~document();
		void open_document();
		void open_document(const boost::filesystem::path& path);
		void export_document(const boost::filesystem::path& path,boost::office_file_format::type format = office_file_format::PDF);
		void export_document(boost::office_file_format::type format = office_file_format::PDF);
	};
} // namespace boost

#endif