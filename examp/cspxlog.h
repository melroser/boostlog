/**
 *
 *
 *
 *
 */


#ifndef _CSPXLOG_H_
#define _CSPXLOG_H_

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
    inline std::basic_ostream< CharT, TraitsT >& operator<< (
        std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
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

    static inline void setLoggingLevel(cspxlog::severity_level level) {

        logging::core::get()->set_filter( expr::attr< severity_level >("severity") >= level);
    }


    static inline void initLogging() {

        // set format for console output

        logging::add_console_log( std::clog,
                                  keywords::format = expr::format("time:%1%\ttrace:[%2%]\tlevel:%3%\tmessage:%4%")
                                  % expr::format_date_time< boost::posix_time::ptime >("timestamp", "%y-%m-%d %h:%m:%s.%f")
                                  % expr::format_named_scope("scope", keywords::format = "%n:%l")
                                  % expr::attr< severity_level >("severity")
                                  % expr::message
        );

        // if you want to write logs to file,
        logging::add_file_log ( "logs/sample.log",
                                keywords::format = expr::format("%1% [%2%] [%3%] <%4%> %5%")
                                % expr::format_date_time< boost::posix_time::ptime >("timestamp", "%y-%m-%d, %h:%m:%s.%f")
                                % expr::format_date_time< attrs::timer::value_type >("uptime", "%o:%m:%s")
                                % expr::format_named_scope("scope", keywords::format = "%n (%f:%l)")
                                % expr::attr< severity_level >("severity")
                                % expr::message
        );

        // add some commonly used attributes, like timestamp and record counter.
        logging::add_common_attributes();
        logging::core::get()->add_thread_attribute("scope", attrs::named_scope());

        #ifdef debug
        setlogginglevel(trace);
        #endif
    }

} // end of namespace


BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(app_logger, boost::log::sources::severity_logger<cspxlog::severity_level>)

#endif // LOGGER_HPP