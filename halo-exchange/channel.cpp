#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>

#include <sstream>
#include <boost/program_options.hpp>

int hpx_main(boost::program_options::variables_map&) {
  return 0;
}

int main(int argc, char* argv[]) {
  using namespace boost::program_options;

  options_description desc_commandline;
  // This program has no own command line options.

  std::vector<std::string> const cfg;
  // We want hpx_main to be called on both localities.

  return hpx::init(desc_commandline, argc, argv, cfg);
}
