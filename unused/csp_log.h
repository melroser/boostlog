// csp_log.h - DECLARE your loggers & filters here
#ifndef CSP_LOG_H
#define CSP_LOG_H

#include <boost/logging/format.hpp>
#include <boost/logging/format/named_write_fwd.hpp>
// #include <boost/logging/writer/on_dedicated_thread.hpp> // uncomment if you want to do logging on a dedicated thread

namespace bl = boost::logging;
typedef bl::named_logger<>::type logger_type;
typedef bl::filter::no_ts filter_type;

BOOST_DECLARE_LOG_FILTER(g_l_filter, filter_type)
BOOST_DECLARE_LOG(g_l, logger_type)

#define L_ BOOST_LOG_USE_LOG_IF_FILTER( g_l(), g_log_filter()->is_enabled() ) 

// initialize thy logs..
void init_logs();

#endif
