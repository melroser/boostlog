#include "cspxlog.h"

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/logger.hpp>

using namespace std;


namespace cspxlog {

    void init_logging() {
        namespace logging = boost::log;
        namespace sinks = boost::log::sinks;
        namespace src = boost::log::sources;
        namespace expr = boost::log::expressions;
        namespace attrs = boost::log::attributes;
        namespace keywords = boost::log::keywords;

        logging::add_common_attributes();
    }
}


int main(int argc, char** argv) {

    cspxlog::init_logging();
    cspxlog::logger lg;
    LOG(lg, info) << "Hi!";
}

