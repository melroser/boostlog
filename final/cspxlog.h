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



} // end of cspxlog namespace

#define LOG(log_, lvl_) BOOST_LOG_SEV(mylog::tag_log_location(log_, __FILE__, __LINE__, __FUNCTION__), lvl_)

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


#endif    //  _CSPXLOG_H_INCLUDED
