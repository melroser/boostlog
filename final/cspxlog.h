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



namespace cspxlog {
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

} // end of cspxlog namespace

#define LOG(log_, lvl_) BOOST_LOG_SEV(mylog::tag_log_location(log_, __FILE__, __LINE__, __FUNCTION__), lvl_)


#endif    //  _CSPXLOG_H_INCLUDED
