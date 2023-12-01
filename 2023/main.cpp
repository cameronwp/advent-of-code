#include <boost/program_options.hpp>
#include <iostream>

#include "day1.hpp"

namespace po = boost::program_options;

int main(int ac, char *av[]) {
  try {
    po::options_description desc("Allowed options");

    desc.add_options()
        ("help", "produce help message")
        ("day", po::value<int>(), "pick a day to run")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      std::cout << desc << "\n";
      return 1;
    }

    if (vm.count("day")) {
      std::cout << "day was set to "
                << vm["day"].as<int>() << ".\n";
    } else {
      std::cout << "day was not set.\n";
    }
  } catch (std::exception &e) {
    std::cerr << "error: " << e.what() << "\n";
    return 1;
  } catch (...) {
    std::cerr << "Exception of unknown type!\n";
  }

  Day1 day;
  std::string result;
  result = day.run();

  std::cout << result << std::endl;

  return 0;
}
