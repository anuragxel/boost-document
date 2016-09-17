#ifndef _CELL_FORMAT_PROPERTY_HPP
#define _CELL_FORMAT_PROPERTY_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost {

	//! \brief Text Format Type
	//!        Currently present in Cell.
	//!
	struct cell_format_property {
		enum type {
			BOLD,
      ITALIC,
      STRIKETHROUGH,
      UNDERLINE
		};
	};


} // namespace boost

#endif
