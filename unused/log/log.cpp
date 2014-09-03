#include "log.h"
#include <fstream>
//#include <boost/log/formatters.hpp>
#include <boost/log/formatters/attr.hpp>
#include <boost/log/formatters/message.hpp>
#include <boost/log/formatters/date_time.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/utility/empty_deleter.hpp>
#include <boost/log/attributes/current_thread_id.hpp>
//#include <boost/log/utility/init/common_attributes.hpp>


using namespace std;


namespace mylog {
    boost::shared_ptr<mylog::mutable_string_mt> file_attr(new mylog::mutable_string_mt(""));
    boost::shared_ptr<mylog::mutable_string_mt> function_attr(new mylog::mutable_string_mt(""));
    boost::shared_ptr<mylog::mutable_int_mt> line_attr(new mylog::mutable_int_mt(-1));

    void init_logging() {
        namespace logging = boost::log;
        namespace attrs = boost::log::attributes;
        namespace src = boost::log::sources;
        namespace sinks = boost::log::sinks;
        namespace fmt = boost::log::formatters;
        namespace keywords = boost::log::keywords;

        boost::shared_ptr< logging::core > core = logging::core::get();

        // Create a backend and attach a couple of streams to it
        boost::shared_ptr< sinks::text_ostream_backend > backend =
            boost::make_shared< sinks::text_ostream_backend >();
        backend->add_stream(boost::shared_ptr< std::ostream >(&std::clog, logging::empty_deleter()));
        backend->add_stream(boost::shared_ptr< std::ostream >(new std::ofstream("testapp.log")));

        boost::function< void (std::ostream&, logging::record const&) > formatter =
            fmt::stream
            << "["
            << fmt::date_time< boost::posix_time::ptime >("TimeStamp")
            << " "
            << fmt::attr<attrs::current_process_id::held_type>("ProcessID")
            << "."
            << fmt::attr<attrs::current_thread_id::held_type>("ThreadID")
            << " "
            << fmt::attr< string >("Function")
            << ":"
            << fmt::attr< string >("File")
            << ":"
            << fmt::attr< int >("Line")
            << " "
            << fmt::attr<severity_level>("Severity")
            << "] " << fmt::message();
        backend->set_formatter(formatter);

        // Enable auto-flushing after each log record written
        backend->auto_flush(true);

        // Wrap it into the frontend and register in the core.
        // The backend requires synchronization in the frontend.
        typedef sinks::synchronous_sink< sinks::text_ostream_backend > sink_t;
        boost::shared_ptr< sink_t > sink(new sink_t(backend));
        core->add_sink(sink);

        core->add_global_attribute("File", mylog::file_attr);
        core->add_global_attribute("Function", mylog::function_attr);
        core->add_global_attribute("Line", mylog::line_attr);
        logging::add_common_attributes();
    }
}


int main(int argc, char** argv) {
    mylog::init_logging();
    mylog::logger lg;
    LOG(lg, warning) << "Hello, world!";
}
