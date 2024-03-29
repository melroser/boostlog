/**
 *
 *
 *
 */

#include "cspxlog.h"
#include <boost/logging/format/named_write.hpp>

BOOST_DEFINE_LOG_FILTER(g_log_filter, filter_type ) 
BOOST_DEFINE_LOG(g_l, logger_type) 


void init_logs() {
    // formatting    : time [idx] message \n
    // destinations  : console, file "out.txt" and debug window
    g_l()->writer().write("%time%($hh:$mm.$ss.$mili) [%idx%] |\n", "cout file(out.txt) debug");
    g_l()->mark_as_initialized();
}

int main() {
    int i = 1;
    LOG << "this is a simple message " << i;
    std::string hello = "hello";
    LOG << hello << " world";
}
