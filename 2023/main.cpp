#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"
#include "day5.hpp"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int ac, char *av[]) {
  std::cout << std::boolalpha;

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
      if (part != 1 && part != 2) {
        std::cout << "--part must be 1 or 2" << std::endl;
        return 1;
      }
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
  } else if (day == 2) {
    Day2 day;
  } else if (day == 3) {
    Day3 day;
  } else if (day == 4) {
    Day4 day;
  } else if (day == 5) {
    Day5 day;
    day.run(part);
  } else {
    std::cout << "day was not set.\n";
  }

  return 0;
}
