#include <boost/program_options.hpp>
#include <iostream>
#include <string>
namespace po = boost::program_options;

// program options
std::size_t po_threads = 0;
bool po_save_steps = false;
std::string po_precision = "float";

void parse_args(int argc, const char** argv) {
	po::options_description desc("Options");
	desc.add_options()("help,h", "print help message") // Help
	    ("max_threads,t",
	     po::value<std::size_t>(&po_threads)->default_value(po_threads),
	     "Maximum number of work threads to use ( 0 means 'all' )") // Threads
	    ("save_steps,s",
	     "Save intermediate steps ( e.g. name_f20.tif for frame 20 )") // Save
	    ("precision,p", po::value(&po_precision)->default_value(po_precision),
	     "Precision for computation {float, double}") // Prec
	    ;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.contains("help")) {
		std::cout << desc << "\n";
		exit(0);
	}
}

int main(int argc, const char** argv) { parse_args(argc, argv); }
