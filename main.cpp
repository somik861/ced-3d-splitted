#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/program_options.hpp>
#include <chrono>
#include <fmt/core.h>
#include <i3d/diffusion_filters.h>
#include <iostream>
#include <string>
#include <thread>

using namespace std::literals;
namespace po = boost::program_options;

// program options (constants after 'parse_args' is called)
std::size_t po_threads = std::thread::hardware_concurrency() / 2;
std::string po_precision = "float"s;
std::string po_image_format = "uint16"s;
double po_sigma = 0.1;
double po_rho = 1.0;
double po_tau = 0.05;
std::size_t po_iters = 1;
std::size_t po_save_every = 0;
bool po_quiet = false;
std::string po_input_file;
std::string po_output_file;

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
	    ("max_threads", po::value(&po_threads)->default_value(po_threads),
	     "Maximum number of work threads to use ( 0 means 'all' )") // Threads
	    ("save_every", po::value(&po_save_every)->default_value(po_save_every),
	     "Save every xth iteration ( e.g. name_f20.tif for frame 20 ), 0 means "
	     "do not save anything") // Save
	    ("quiet",
	     "Disable standard output") // Quiet
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

	if (vm.count("help")) {
		std::cout << "Usage: ./program [options] input_file output_file\n";
		std::cout << desc << '\n';
		exit(0);
	}

	auto require_argument = [&](std::string name) {
		if (!vm.count(name)) {
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

	if (vm.count("quiet"))
		po_quiet = true;

	if (po_threads == 0)
		po_threads = std::thread::hardware_concurrency();
}

void print(const std::string& s) {
	if (!po_quiet)
		std::cout << s << '\n';
}

template <typename img_t>
i3d::Image3d<img_t>
get_slice(const i3d::Image3d<img_t>& img, std::size_t idx, std::size_t axis) {
	i3d::Image3d<img_t> out;

	switch (axis) {
	case 0:
		img.GetSliceX(out, idx);
		break;
	case 1:
		img.GetSliceY(out, idx);
		break;
	case 2:
		img.GetSliceZ(out, idx);
		break;
	default:
		throw std::out_of_range("Axis out of range");
	}

	return out;
}

template <typename img_t>
void set_slice(i3d::Image3d<img_t>& dest,
               const i3d::Image3d<img_t>& slice,
               std::size_t idx,
               std::size_t axis) {
	switch (axis) {
	case 0:
		dest.SetSliceX(slice, idx);
		break;
	case 1:
		dest.SetSliceY(slice, idx);
		break;
	case 2:
		dest.SetSliceZ(slice, idx);
		break;
	default:
		throw std::out_of_range("Axis out of range");
	}
}

template <typename prec_t>
void process_slice(i3d::Image3d<prec_t>& img,
                   std::size_t idx,
                   std::size_t axis) {
	auto slice = get_slice(img, idx, axis);
	i3d::CED_AOS(slice, prec_t(po_sigma), prec_t(po_rho), prec_t(po_tau), 1ul);
	set_slice(img, slice, idx, axis);
}

template <typename img_t, typename prec_t>
void process_image() {
	// Print argument info
	print("Running algorithm, options:");
	print(fmt::format(
	    "\tThreads: {}\n\tPrecision: {}\n\tSigma: {}\n\tRho: {}\n\tTau: "
	    "{}\n\tIters: {}",
	    po_threads, po_precision, po_sigma, po_rho, po_tau, po_iters));

	// Run algorithm
	i3d::Image3d<img_t> img(po_input_file.c_str());
	i3d::Image3d<prec_t> work;
	work.template ConvertFrom<prec_t, img_t>(img);

	for (std::size_t it = 1; it <= po_iters; ++it) {
		print(fmt::format("Starting iteration {}", it));

		for (std::size_t axis = 0; axis < 3; ++axis) {
			boost::asio::thread_pool tpool(po_threads);

			print(fmt::format("\tProcessing axis {}", axis));

			for (std::size_t i = 0; i < img.GetSize()[axis]; ++i)
				boost::asio::post(tpool, [&work, i, axis]() {
					process_slice(work, i, axis);
				});

			tpool.join();
		}
		if (po_save_every != 0 && it % po_save_every == 0 && it != po_iters) {
			std::string new_path = po_output_file;
			std::string extension = new_path.substr(new_path.rfind('.'));
			
			// Remove extension
			for (std::size_t n = 0; n < extension.size(); ++n)
				new_path.pop_back();

			
			new_path += fmt::format("_f{:0>5}", it);
			new_path += extension;

			print(fmt::format("Saving iteration: {}", new_path.c_str()));
			img.template ConvertFrom<img_t, prec_t>(work);
			img.SaveImage(new_path.c_str());
		}
	}

	print(fmt::format("Saving result: {}", po_output_file.c_str()));
	img.template ConvertFrom<img_t, prec_t>(work);
	img.SaveImage(po_output_file.c_str());
}

int main(int argc, const char** argv) {
	parse_args(argc, argv);

	if (po_precision == "float") {
		if (po_image_format == "uint8")
			process_image<i3d::GRAY8, float>();
		else if (po_image_format == "uint16")
			process_image<i3d::GRAY16, float>();
		else if (po_image_format == "float")
			process_image<float, float>();
		else if (po_image_format == "double")
			process_image<double, float>();
	} else if (po_precision == "double") {
		if (po_image_format == "uint8")
			process_image<i3d::GRAY8, double>();
		else if (po_image_format == "uint16")
			process_image<i3d::GRAY16, double>();
		else if (po_image_format == "float")
			process_image<float, double>();
		else if (po_image_format == "double")
			process_image<double, double>();
	}
}
