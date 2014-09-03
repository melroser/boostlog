/**
 *
 *
 *
 */

#ifndef my_app_LOG_H_header
#define my_app_LOG_H_header

#include <boost/logging/writer/named_write_fwd.hpp>
// #include <boost/logging/writer/on_dedicated_thread.hpp> // uncomment if you want to do logging on a dedicated thread

namespace bl = boost::logging;


typedef bl::named_logger<>::type logger_type;
typedef bl::filter::no_ts filter_type;

BOOST_DECLARE_LOG_FILTER(g_l_filter, filter_type)
BOOST_DECLARE_LOG(g_l, logger_type)

#define LOG BOOST_LOG_USE_LOG_IF_FILTER( g_l(), g_log_filter()->is_enabled() ) 

// initialize thy logs..
void init_logs();

#endif


