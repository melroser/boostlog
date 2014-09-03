// csp_log.cpp - DEFINE your loggers & filters here
#include "csp_log.h"
#include <boost/logging/format.hpp>
#include <boost/logging/format/named_write.hpp>

BOOST_DEFINE_LOG_FILTER(g_log_filter, filter_type ) 
BOOST_DEFINE_LOG(g_l, logger_type) 


void init_logs() {
    // formatting    : time [idx] message \n
    // destinations  : console, file "out.txt" and debug window
    g_l()->writer().write("%time%($hh:$mm.$ss.$mili) [%idx%] |\n", "cout file(out.txt) debug");
    g_l()->mark_as_initialized();
}

void use_logger() {
    int i = 1;
    L_ << "this is a simple message " << i;
    std::string hello = "hello";
    L_ << hello << " world";
}

