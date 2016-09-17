#ifndef _CHART_TYPE_HPP
#define _CHART_TYPE_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost {

	//! \brief Cell Content Type
	//!        Currently present in Cell.
	//!
	struct chart_type {
		enum type {
			AREA,
			BAR,
			BUBBLE,
			DONUT,
			LINE,
			RADAR,
			PIE,
			STOCK,
			STOCKO,
			STOCKV,
			STOCKVO,
			SCATTER
		};
	};
} // namespace boost

#endif
