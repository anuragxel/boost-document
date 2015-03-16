#ifndef _DOCUMENT_HPP
#define _DOCUMENT_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/filesystem.hpp>
#include "detail/document_exception.hpp"
#include "detail/document_file_format.hpp"

namespace boost {

	class document {
	private:
		boost::filesystem::path file_path;
		bool is_file_opened;
	public:
		document();
		document(const boost::filesystem::path path);
		~document();
		void open_document();
		void open_document(const boost::filesystem::path& path);
		void close_document();
		void close_document(const boost::filesystem::path& path);
		void save_document();
		void export_document(const boost::filesystem::path& path,boost::document_file_format::type format = document_file_format::PDF);
		void export_document(boost::document_file_format::type format = document_file_format::PDF);
	};

} // namespace boost

#endif