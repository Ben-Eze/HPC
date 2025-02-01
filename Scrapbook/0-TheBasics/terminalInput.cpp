#include <iostream>
#include <boost/program_options.hpp>
using namespace std;
namespace po = boost::program_options;

int main(int argc, char** argv) {
    po::options_description desc("Available options");

    desc.add_options()
        ("start", po::value<int>()->default_value(0), "The start value")
        ("end", po::value<int>()->default_value(10), "The end value")
        ("help", "Print help message");
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 1;
    }

    const int start = vm["start"].as<int>();
    const int end = vm["end"].as<int>();

    for (int i = start; i < end; ++i) {
        cout << i << endl;
    }

    return 0;
}
