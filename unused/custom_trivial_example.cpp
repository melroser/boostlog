/**
 * @file custom_trivial_example.cpp
 *
 *
 *
 *
 */

#include <iostream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/sinks/text_file_backend.hpp>

using namespace std;

void log_to_file() { 
    boost::log::add_file_log("sample.log"); 
}

void severity_filter(int level) {
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= level
    );
}

void trivial_logging() {

    // Trivial logging macros
    BOOST_LOG_TRIVIAL(trace)   << "hello world!";
    BOOST_LOG_TRIVIAL(debug)   << "hello world!";
    BOOST_LOG_TRIVIAL(info)    << "hello world!";
    BOOST_LOG_TRIVIAL(warning) << "hello world!";
    BOOST_LOG_TRIVIAL(error)   << "hello world!";
    BOOST_LOG_TRIVIAL(fatal)   << "hello world!";

}

int main() {

    cout << "BOOST.LOG Custom Example" << endl;
    cout << endl;

    // cout
    cout << "Printing with cout:" << endl;
    cout << "hello world!" << endl;
    cout << endl;

    // trivial logging
    cout <<  "Logging to console using trivial:" << endl;
    trivial_logging();
    cout << endl;

    // severity filter info
    cout << "Severity filtering set to info " << endl;
    severity_filter(boost::log::trivial::info);
    trivial_logging();
    cout << endl;

    // severity filter error
    cout << "Severity filtering set to error" << endl;
    severity_filter(boost::log::trivial::error);
    trivial_logging();
    cout << endl;

    // turn off severity filtering
    severity_filter(boost::log::trivial::trace);

    // log to file
    cout << "Logging to the file simple.log" << endl;
    log_to_file();
    trivial_logging();
    cout << endl;

    // Exit
    cout << "Custom example complete!" << endl;
    return 0;
}
