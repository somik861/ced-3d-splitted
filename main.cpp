#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/program_options.hpp>
#include <chrono>
#include <filesystem>
#include <fmt/core.h>
#include <i3d/diffusion_filters.h>
#include <iostream>
#include <string>
#include <thread>

using namespace std::literals;
namespace po = boost::program_options;
namespace fs = std::filesystem;

// program options (constants after 'parse_args' is called)
std::size_t po_threads = std::thread::hardware_concurrency() / 2;
std::string po_precision = "float"s;
std::string po_image_format = "uint16"s;
double po_sigma = 0.1;
double po_rho = 1.0;
double po_tau = 0.25;
std::size_t po_iters = 1;
bool po_save_steps = false;
fs::path po_input_file;
fs::path po_output_file;

void parse_args(int argc, const char** argv) {
	po::options_description desc("Options");
	desc.add_options()("help,h", "print help message") // Help
	    ("image_format,f",
	     po::value(&po_image_format)->default_value(po_image_format),
	     "Image format type {uint8, uint16, float, double}") // image format
	    ("sigma,s", po::value(&po_sigma)->default_value(po_sigma),
	     "Standard deviation of the Gaussian filter that is applied before the "
	     "gradient estimation.") // Sigma
	    ("rho,r", po::value(&po_rho)->default_value(po_rho),
	     "Standard deviation of the Gaussian filter that is applied in order "
	     "to smooth structure tensors.") // Rho
	    ("tau,t", po::value(&po_tau)->default_value(po_tau),
	     "Time step of one iteration.") // Tau
	    ("iters,i", po::value(&po_iters)->default_value(po_iters),
	     "Number of iterations") // Iters
	    ("max_threads",
	     po::value<std::size_t>(&po_threads)->default_value(po_threads),
	     "Maximum number of work threads to use ( 0 means 'all' )") // Threads
	    ("save_steps",
	     "Save intermediate steps ( e.g. name_f20.tif for frame 20 )") // Save
	    ("precision", po::value(&po_precision)->default_value(po_precision),
	     "Precision for computation {float, double}") // Precision

	    ;
	po::options_description hidden_desc;
	hidden_desc.add_options() // Hidden
	    ("input_file", po::value(&po_input_file),
	     "Input file") // Input file
	    ("output_file", po::value(&po_output_file),
	     "Output file") // Output file
	    ;

	po::positional_options_description po_desc;

	po_desc.add("input_file", 1);
	po_desc.add("output_file", 1);

	po::options_description all_desc;
	all_desc.add(desc).add(hidden_desc);

	po::variables_map vm;
	po::store(po::command_line_parser(argc, argv)
	              .options(all_desc)
	              .positional(po_desc)
	              .run(),
	          vm);
	po::notify(vm);

	if (vm.contains("help")) {
		std::cout << "Usage: ./program [options] input_file output_file\n";
		std::cout << desc << '\n';
		exit(0);
	}

	auto require_argument = [&](std::string name) {
		if (!vm.contains(name)) {
			std::cerr << "Positional argument '" << name << "' is not set\n";
			std::terminate();
		}
	};

	require_argument("input_file");
	require_argument("output_file");

	if (std::string val = vm["precision"].as<std::string>();
	    !(val == "float"s || val == "double"s)) {
		std::cerr << "Invalid precision choice" << std::endl;
		std::terminate();
	}

	if (std::string val = vm["image_format"].as<std::string>();
	    !(val == "uint8"s || val == "uint16"s || val == "float"s ||
	      val == "double"s)) {
		std::cerr << "Invalid image format choice" << std::endl;
		std::terminate();
	}

	if (vm.contains("save_steps"))
		po_save_steps = true;

	if (po_threads == 0)
		po_threads = std::thread::hardware_concurrency();
}

template <typename img_t, typename prec_t>
void process_image() {
	fmt::print("Running algorithm, options:\n");
	fmt::print("\tThreads: {}\n\tPrecision: {}\n\tSigma: {}\n\tRho: {}\n\tTau: "
	           "{}\n\tIters: {}\n",
	           po_threads, po_precision, po_sigma, po_rho, po_tau, po_iters);
	if (po_save_steps)
		fmt::print("Saving intermediate images");

	i3d::Image3d<img_t> img(po_input_file.c_str());
}

int main(int argc, const char** argv) {
	parse_args(argc, argv);

	process_image<float, float>();

	boost::asio::thread_pool tpool(po_threads);

	tpool.join();
}
