#ifndef _LOG_H_INCLUDED
#define _LOG_H_INCLUDED

#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/thread/mutex.hpp>

enum severity_level {
    debug = -1,
    info = 0,
    warning,
    error,
    fatal
};

namespace mylog {
    typedef boost::log::attributes::mutable_constant<int, boost::mutex, boost::lock_guard< boost::mutex > > mutable_int_mt;
    typedef boost::log::attributes::mutable_constant<std::string, boost::mutex, boost::lock_guard< boost::mutex > > mutable_string_mt;
    typedef boost::log::sources::severity_logger<severity_level> logger;
    extern boost::shared_ptr<mutable_string_mt> file_attr;
    extern boost::shared_ptr<mutable_string_mt> function_attr;
    extern boost::shared_ptr<mutable_int_mt> line_attr;

    template<typename T> static inline T& tag_log_location
        (T &log_, const std::string file_, int line_, const std::string function_) {
        mylog::file_attr->set_value(file_);
        mylog::function_attr->set_value(function_);
        mylog::line_attr->set_value(line_);
        return log_;
    }

    void init_logging();
}

#define LOG(log_, lvl_) BOOST_LOG_SEV(mylog::tag_log_location(log_, __FILE__, __LINE__, __FUNCTION__), lvl_)

template< typename CharT, typename TraitsT >
    inline std::basic_ostream< CharT, TraitsT >& operator<<
    (std::basic_ostream< CharT, TraitsT >& strm, severity_level level) {
    static const char* const str[] = {
        "debug",
        "info",
        "warning",
        "error",
        "fatal"
    };
    if(level >= debug && level <= fatal) {
        strm << str[level - debug];
    } else {
        strm << static_cast<int>(level);
    }
    return strm;
}

#endif
