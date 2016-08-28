#ifndef _CELL_CONTENT_TYPE_HPP
#define _CELL_CONTENT_TYPE_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost {

	#undef ERROR
	//! \brief Cell Content Type
	//!        Currently present in Cell.
	//!
	struct cell_content_type {
		enum type {
			EMPTY,VALUE,STRING,FORMULA,ERROR
		};
	};
} // namespace boost

#endif
