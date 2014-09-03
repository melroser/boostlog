
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

typedef boost::logging::basic_logger<>::type logger_type;

#define L_(lvl) BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_log_level(), lvl )

BOOST_DEFINE_LOG_FILTER(g_log_level, boost::logging::level::holder ) // holds the application log level
BOOST_DEFINE_LOG(g_l, logger_type)

int main() {

    // formatting    : time [idx] message \n
    // destinations  : console, file "out.txt" and debug window
    g_l()->writer().write("%time%($hh:$mm.$ss.$mili) [%idx%] |\n", "cout file(out.txt) debug");
    g_l()->mark_as_initialized();

    int i = 1;
    L_(debug) << "this is so cool " << i++;
    L_(error) << "first error " << i++;

    std::string hello = "hello", world = "world";
    L_(debug) << hello << ", " << world;

    using namespace boost::logging;
    g_log_level()->set_enabled(level::error);
    L_(debug) << "this will not be written anywhere";
    L_(info) << "this won't be written anywhere either";
    L_(error) << "second error " << i++;

    g_log_level()->set_enabled(level::info);
    L_(info) << "good to be back ;) " << i++;
    L_(error) << "third error " << i++;
}

// End of file

