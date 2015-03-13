#ifndef _DOCUMENT_HPP
#define _DOCUMENT_HPP

#include "OfficeFileFormat.hpp"
#include "ooFunctions.hpp"

using namespace boost;

namespace boost {
	class Document {
	public:
		Document();
		~Document();
		void open_document(const boost::filesystem::path& path);
		void export_document(const boost::filesystem::path& path,office_file_format::type format = office_file_format::PDF);
	};

} // namespace boost

#endif