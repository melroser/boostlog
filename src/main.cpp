#include <boost/move/utility.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(global_logger, src::logger_mt)

void init() {

    logging::add_file_log("sample.log");
    logging::add_common_attributes();

}

int main(int argc, char* argv[]) {

    src::logger_mt& lg = global_logger::get();
    init();

    BOOST_LOG(lg) << "Hello World!";
}
