#ifndef _CELL_BORDER_TYPE_HPP
#define _CELL_BORDER_TYPE_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost {

	//! \brief Support is provided only for
  //!       three kinds of borders
	//!
	struct cell_border_style {
		enum type {
      NONE, CONTINUOUS, DASH, DASHDOT
		};
	};

  //! \brief Support is provided only for
  //!       three border weights
	//!
  struct cell_border_weight {
    enum type {
        THIN, MEDIUM, THICK
		};
  };

} // namespace boost

#endif
