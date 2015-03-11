#ifndef _DOCUMENT_HPP
#define _DOCUMENT_HPP

#include <boost/filesystem.hpp>

struct format {
	enum type {
		PDF,CSV,
	};
};

class Document {
	private:
		filesystem::path file_path;
	public:
		Document();
		~Document();
		void open(const filesystem::path& path);
		void export(const filesystem::path& filenane,format::type format = format::PDF);
};

#endif
