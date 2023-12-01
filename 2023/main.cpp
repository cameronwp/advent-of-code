#include "day1.hpp"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int ac, char *av[]) {
  int day, part;

  try {
    po::options_description desc("Allowed options");

    auto options = desc.add_options();
    options("help", "produce help message");
    options("day", po::value<int>(), "pick a day to run");
    options("part", po::value<int>(), "pick a part of the day to run");

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      std::cout << desc << "\n";
      return 1;
    }

    if (vm.count("day")) {
      day = vm["day"].as<int>();
    }
    if (vm.count("part")) {
      part = vm["part"].as<int>();
    }
  } catch (std::exception &e) {
    std::cerr << "error: " << e.what() << "\n";
    return 1;
  } catch (...) {
    std::cerr << "Exception of unknown type!\n";
  }

  if (day == 1) {
    Day1 day;
    day.run(part);
  } else {
    std::cout << "day was not set.\n";
  }

  return 0;
}
