#include "cspxlog.h"
#include <iostream>

int main(int argc, char *argv[]) {

    std::cout << "---- start ----" << std::endl;

    cspxlog::init();

    boost::log::sources::severity_logger< cspxlog::severity_level > slg;

    BOOST_LOG_FUNCTION();
    BOOST_LOG_SEV(slg, cspxlog::ERROR) << "test";

    boost::log::sources::severity_logger< cspxlog::severity_level > slg;
    BOOST_LOG_SEV(slg, cspxlog::ERROR) << "test2";

      BOOST_LOG_FUNCTION();
    std::cout << "---- start test_setLoggingLevel ----" << std::endl;
    BOOST_LOG_SEV(app_logger::get(), cspxlog::DEBUG) << "first debug";
    BOOST_LOG_SEV(app_logger::get(), cspxlog::TRACE) << "first trace";

    std::cout << "set filter level \"DEBUG\"" << std::endl;
    logger::setLoggingLevel(cspxlog::DEBUG);

    BOOST_LOG_SEV(app_logger::get(), cspxlog::DEBUG) << "second debug"; // printed
    BOOST_LOG_SEV(app_logger::get(), cspxlog::TRACE) << "second trace"; // filtered


    std::cout << "---- end ----" << std::endl;
    return 0;
}
