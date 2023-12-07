#include <functional>
#include <sstream>
#include <string>
#include <vector>

// FYI https://stackoverflow.com/a/17305457

static inline void split_and_loop(std::string input, char delimiter,
                                  std::function<void(std::string, int)> cb) {
  std::istringstream input_stream;
  input_stream.str(input);
  int i = 0;
  for (std::string item; std::getline(input_stream, item, delimiter);) {
    cb(item, i);
    i++;
  }
}
