#include <iostream>
#include <iomanip>
#include <string>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sinks/debug_output_backend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/phoenix/bind/bind_function_object.hpp>
#include <boost/log/support/date_time.hpp>

using namespace std;
using namespace boost;
using namespace boost::log;

namespace {

    // log severity level
    enum log_level {
        Debug,
        Info,
        Warning,
        Error
    };

    // logger type with severity level and multithread support
    typedef sources::severity_logger_mt<log_level> logger_t;

    // windows debugger output (e.g. DbgView) sink type with synchronization support
    typedef sinks::synchronous_sink<sinks::debug_output_backend> sink_t;

    // global variables
    log_level g_log_level = Info;  // log level
    logger_t* g_logger; // logger

    // define the keywords to use in filter and formatter
    BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", log_level)
    BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", 
        attributes::local_clock::value_type)
    BOOST_LOG_ATTRIBUTE_KEYWORD(processid, "ProcessID", 
        attributes::current_process_id::value_type)
    BOOST_LOG_ATTRIBUTE_KEYWORD(threadid, "ThreadID", 
        attributes::current_thread_id::value_type)

    // the filter used to filter log records according to level
    bool log_level_filter(value_ref<log_level, tag::severity> const& level) {
        return level >= g_log_level;
    }

    // stream output support for log_level
    std::ostream& operator<<(std::ostream& stream, log_level level) {
        static const char* strings[] = { "debug", " info", " warn", "error" };
        int l = static_cast<size_t>(level);
        if (l >= 0 && l < sizeof(strings) / sizeof(strings[0]))
            stream << strings[l];
        else
            stream << l;
        return stream;
    }

    void initialize_logger() {
        // create a logger
        g_logger = new logger_t();

        boost::shared_ptr<core> core = core::get();

        // add attributes
        core->add_global_attribute("TimeStamp", attributes::local_clock());
        core->add_global_attribute("ProcessID", attributes::current_process_id());
        core->add_global_attribute("ThreadID", attributes::current_thread_id());

        // add level filter
        core->set_filter(phoenix::bind(&log_level_filter, severity.or_none()));

        // create a debug output sink
        boost::shared_ptr<sink_t> sink(new sink_t());

        // sink formatter
        sink->set_formatter(expressions::stream
            << "[" << processid << "]"
            << "[" << threadid << "]"
            << "[" << expressions::format_date_time(
                                        timestamp, "%Y-%m-%d %H:%M:%S") << "]"
            << "[" << severity << "] "
            << expressions::smessage);

        // add sink
        core->add_sink(sink);
    }

    void cleanup_logger() {
        if (g_logger) {
            delete g_logger;
            g_logger = nullptr;
        }
    }

    // macros to get log streams
    #define LOG_DEBUG()     BOOST_LOG_STREAM_SEV(*g_logger, Debug) \ 
        << __FUNCTION__ << "(): "
    #define LOG_INFO()      BOOST_LOG_STREAM_SEV(*g_logger, Info) \ 
        << __FUNCTION__ << "(): "
    #define LOG_WARNING()   BOOST_LOG_STREAM_SEV(*g_logger, Info) \ 
        << __FUNCTION__ << "(): "
    #define LOG_ERROR()     BOOST_LOG_STREAM_SEV(*g_logger, Error) \ 
        << __FUNCTION__ << "(): "
    #define LOG()           LOG_INFO()
}

void doSomething() {
    LOG() << "Log message from doSomethng()";
}

int main(int argc, char** argv) {
    initialize_logger();

    LOG() << "Application started";
    LOG_ERROR() << "An error occured";
    doSomething();

    LOG_DEBUG() << "This message won't be log if g_log_level >= Info";
    g_log_level = Debug;
    LOG_DEBUG() << "This message will be log if g_log_level >= Debug";

    cleanup_logger();
    return 0;
}
