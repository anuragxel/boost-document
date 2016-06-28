#ifndef _CELL_ALIGNMENT_TYPE_HPP
#define _CELL_ALIGNMENT_TYPE_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost {

	//! \brief Horizontal alignment
	//!        of the cell contents.
	//!
	struct cell_horizontal_alignment {
		enum type {
			LEFT, CENTER, RIGHT
		};
	};

  //! \brief Horizontal alignment
	//!        of the cell contents.
	//!
	struct cell_vertical_alignment {
		enum type {
			TOP, CENTER, BOTTOM
		};
	};


} // namespace boost

#endif
