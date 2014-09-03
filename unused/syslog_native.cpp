#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/syslog_backend.hpp>
#include <boost/log/formatters.hpp>

void initialize(const std::string& name) {

    using namespace boost::log;

    // Creating a syslog sink.
    boost::shared_ptr< sinks::synchronous_sink< sinks::syslog_backend > > sink;
    sink.reset(new sinks::synchronous_sink< sinks::syslog_backend >
        (keywords::use_impl = sinks::syslog::native)
    );
    sink->locked_backend()->set_formatter(formatters::format(name + ": %1%") % formatters::message());

    // Mapping our custom levels to the syslog levels.
    sinks::syslog::custom_severity_mapping< level > mapping("Severity");
    mapping[critical] = sinks::syslog::critical;
    mapping[warning] = sinks::syslog::warning;
    mapping[info] = sinks::syslog::info;
    mapping[notice] = sinks::syslog::notice;
    mapping[debug] = sinks::syslog::debug;
    sink->locked_backend()->set_severity_mapper(mapping);

    // Setting the remote address to sent syslog messages to.
    sink->locked_backend()->set_target_address("localhost");

    // Adding the sink to the core.
    core::get()->add_sink(sink);
}

int main(){

    initialize("native_syslog");

    return 0;
}
