/**
 * @file    cspxlog.h
 *
 * @breif   The logging library for CSP NextGen.
 *
 * This header file defines the subset of the massive
 * Boost.Log framework that will be used to log messeges to syslog
 * and the results file from CSP NextGen's C++ code.
 */

#ifndef _CSPXLOG_H_INCLUDED
#define _CSPXLOG_H_INCLUDED

#include <iostream>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

namespace cspxlog {

    namespace logging = boost::log;
    namespace sinks = boost::log::sinks;
    namespace attrs = boost::log::attributes;
    namespace src = boost::log::sources;
    namespace expr = boost::log::expressions;
    namespace keywords = boost::log::keywords;

    /**
     * @brief the severity_level enum
     *  define application severity levels.
     */
    enum severity_level {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    // The formatting logic for the severity level
    template< typename CharT, typename TraitsT >
    inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
    {
        static const char* const str[] =
        {
            "TRACE",
            "DEBUG",
            "INFO",
            "WARNING",
            "ERROR",
            "FATAL"
        };
        if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
            strm << str[lvl];
        else
            strm << static_cast< int >(lvl);
        return strm;
    }

    static inline void setLevel(cspxlog::severity_level level) {

        logging::core::get()->set_filter( expr::attr< severity_level >("severity") >= level);
    }

    static inline void init() {

        // set format for console output
        //logging::add_console_log( std::clog,
                                 //keywords::format = expr::format("time:%1%\ttrace:[%2%]\tlevel:%3%\tmessage:%4%")
                                 //% expr::format_date_time< boost::posix_time::ptime >("timestamp", "%y-%m-%d %h:%m:%s.%f")
                                 //% expr::format_named_scope("scope", keywords::format = "%n:%l")
                                 //% expr::attr< severity_level >("severity")
                                 //% expr::message
                                 //);

        // if you want to write logs to file,
        //logging::add_file_log ( "logs/sample.log",
                               //keywords::format = expr::format("%1% [%2%] [%3%] <%4%> %5%")
                               //% expr::format_date_time< boost::posix_time::ptime >("timestamp", "%y-%m-%d, %h:%m:%s.%f")
                               //% expr::format_date_time< attrs::timer::value_type >("uptime", "%o:%m:%s")
                               //% expr::format_named_scope("scope", keywords::format = "%n (%f:%l)")
                               //% expr::attr< severity_level >("severity")
                               //% expr::message
                               //);

        //logging::core::get()->add_thread_attribute("scope", attrs::named_scope());

        //setLevel(INFO);

        // log to file sample.log
        logging::add_file_log("sample.log");
        // add some commonly used attributes, like timestamp and record counter.
        logging::add_common_attributes();
        src::logger lg;
    }

} // end of cspxlog namespace

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::severity_logger_mt< severity_level> )


#define LOG(log_, lvl_) BOOST_LOG_SEV(mylog::tag_log_location(log_, __FILE__, __LINE__, __FUNCTION__), lvl_)


#endif    //  _CSPXLOG_H_INCLUDED
