#include <boost/program_options.hpp>
#include <i3d/diffusion_filters.h>
#include <iostream>
#include <string>
#include <thread>

using namespace std::literals;
namespace po = boost::program_options;

// program options
std::size_t po_threads = std::thread::hardware_concurrency() / 2;
std::string po_precision = "float"s;
double po_sigma = 0.1;
double po_rho = 1.0;
double po_tau = 0.25;
std::size_t po_iters = 1;
bool po_save_steps = false;

void parse_args(int argc, const char** argv) {
	po::options_description desc("Options");
	desc.add_options()("help,h", "print help message") // Help
	    ("sigma,s", po::value<double>(&po_sigma)->default_value(po_sigma),
	     "Standard deviation of the Gaussian filter that is applied before the "
	     "gradient estimation.") // Sigma
	    ("rho,r", po::value<double>(&po_rho)->default_value(po_rho),
	     "Standard deviation of the Gaussian filter that is applied in order "
	     "to smooth structure tensors.") // Rho
	    ("tau,t", po::value<double>(&po_tau)->default_value(po_tau),
	     "Time step of one iteration.") // Tau
	    ("iters,i", po::value<std::size_t>(&po_iters)->default_value(po_iters),
	     "Number of iterations") // Iters
	    ("max_threads",
	     po::value<std::size_t>(&po_threads)->default_value(po_threads),
	     "Maximum number of work threads to use ( 0 means 'all' )") // Threads
	    ("save_steps",
	     "Save intermediate steps ( e.g. name_f20.tif for frame 20 )") // Save
	    ("precision", po::value(&po_precision)->default_value(po_precision),
	     "Precision for computation {float, double}") // Precision
	    ;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.contains("help")) {
		std::cout << desc << "\n";
		exit(0);
	}

	if (std::string val = vm["precision"].as<std::string>();
	    !(val == "float"s || val == "double"s)) {
		std::cerr << "Invalid precision choice" << std::endl;
		std::terminate();
	}

	if (vm.contains("save_steps"))
		po_save_steps = true;

	if (po_threads == 0)
		po_threads = std::thread::hardware_concurrency();
}

int main(int argc, const char** argv) {
	parse_args(argc, argv);
}
