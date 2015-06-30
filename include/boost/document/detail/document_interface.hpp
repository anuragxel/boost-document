#ifndef _DOCUMENT_INTERFACE_HPP
#define _DOCUMENT_INTERFACE_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <memory>

#include <boost/filesystem.hpp>
#include <boost/document/detail/document_file_format.hpp>

#include <boost/document/sheet.hpp>

namespace boost {

	class document_interface {
	 public:
		virtual void initialize(const boost::filesystem::path& path) = 0;
		virtual void open() = 0;
		virtual void create() = 0;
		virtual void close() = 0;
		virtual void save() = 0;
		virtual void save_as(const boost::filesystem::path& path) = 0;
		virtual void export_as(boost::document_file_format::type format) = 0;
		virtual boost::sheet get_sheet(const std::string& sheet_name) = 0;
		virtual boost::sheet get_sheet_unchecked(const std::string& sheet_name) = 0;
		virtual boost::sheet get_sheet(std::size_t index) = 0;
		virtual boost::sheet get_sheet_unchecked(std::size_t index) = 0;
		virtual boost::sheet insert_sheet(const std::string& sheet_name) = 0;
		virtual void delete_sheet(const std::string& sheet_name) = 0;
		virtual void delete_sheet(std::size_t index) = 0;
		virtual std::size_t sheet_count() = 0;
		virtual ~document_interface() {}
	};	
} // namespace boost

#endif
