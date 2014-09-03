#ifndef _CSPXLOG_H_
#define _CSPXLOG_H_

#include <string>

#include <boost/log/sources/severity_logger.hpp>


enum severity_level {
    trace,
    debug,
    info,
    warning,
    error,
    fatal
};

namespace cspxlog {
    typedef boost::log::attributes::mutable_constant<int, boost::mutex, boost::lock_guard< boost::mutex > > mutable_int_mt;
    typedef boost::log::attributes::mutable_constant<std::string, boost::mutex, boost::lock_guard< boost::mutex > > mutable_string_mt;
    typedef boost::log::sources::severity_logger<severity_level> logger;
    extern boost::shared_ptr<mutable_string_mt> file_attr;
    extern boost::shared_ptr<mutable_string_mt> function_attr;
    extern boost::shared_ptr<mutable_int_mt> line_attr;

    template<typename T>
        static inline T& tag_log_location ( T &log_,
                                            const std::string file_,
                                            int line_,
                                            const std::string function_) {
        mylog::file_attr->set_value(file_);
        mylog::function_attr->set_value(function_);
        mylog::line_attr->set_value(line_);
        return log_;
    }

    void init_logging();

}

#define LOG(log_, lvl_) BOOST_LOG_SEV(cspxlog::tag_log_location(log_, __FILE__, __LINE__, __FUNCTION__), lvl_)

#endif
