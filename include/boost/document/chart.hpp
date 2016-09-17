#ifndef _CHART_HPP
#define _CHART_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)




#include <boost/document/detail/chart_interface.hpp>
#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/chart_type.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <utility>
#include <cctype>

namespace boost {

	//! \brief This is the main class interface to be
	//!        exposed to the library user.
	//!
	class chart {
	private:
		boost::shared_ptr<chart_interface> pimpl_;

	public:
		//! \brief The Constructor.
		//!        Creates a new document object.
		explicit chart(const boost::shared_ptr<chart_interface> impl)
    : pimpl_(impl) {}

    void set_title(const std::string& title) {
        pimpl_->set_title(title);
    }

		void set_type(boost::chart_type::type t, bool enable_3d) {
				pimpl_->set_type(t, enable_3d);
		}

    void set_legend(bool set) {
        pimpl_->set_legend(set);
    }

		//! \brief Destructor
		//!        Chart instance is destroyed.
		~chart() {
		}
	};
} // namespace boost

#endif
