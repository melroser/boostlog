/**
 * @file custom_dedicated_example.cpp
 *
 *
 *
 *
 */

#include <boost/move/utility.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)

void local_logging() {

    // create logger
    src::logger lg;

    // using the macro
    BOOST_LOG(lg) << "Greetings from the local logger!";

    // manual logging
    logging::record rec = lg.open_record();
    if (rec)
    {
        logging::record_ostream strm(rec);
        strm << "Greetings from manual logging!";
        strm.flush();
        lg.push_record(boost::move(rec));
    }
}

void global_logging() {

    // use global logger
    src::logger_mt& lg = my_logger::get();

    // using the macro
    BOOST_LOG(lg) << "Greetings from the global logger!";

}

int main(int, char*[]) {

    logging::add_file_log("sample.log");
    logging::add_common_attributes();

    local_logging();
    global_logging();

    return 0;
}

