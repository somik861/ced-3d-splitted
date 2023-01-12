#include <boost/program_options.hpp>
#include <iostream>
namespace po = boost::program_options;

// program options
std::size_t po_threads = 0;
bool po_save_steps = false;

void parse_args(int argc, const char** argv) {
	std::cout << "parsing " << argc << " arguments\n";
}

int main(int argc, const char** argv) { parse_args(argc, argv); }
