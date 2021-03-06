#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>

#include <boost/program_options.hpp>
#include <sstream>

struct JobParams {
  double a;
  double b;

  friend class hpx::serialization::access;
  template <class Archive>
  void serialize(Archive &ar, const unsigned int ) {
    ar & a;
    ar & b;
  }
};

void run_job(const JobParams &job_params) {
  std::stringstream ss;
  ss << "Running job { a = " << std::setw(3) << job_params.a
     << ", b = " << std::setw(3) << job_params.b << "}.\n";

  hpx::cout << ss.str();
}

void launch_job(JobParams job_params) { return run_job(job_params); }
HPX_PLAIN_ACTION(launch_job, launch_job_action);

int hpx_main(boost::program_options::variables_map &) {
  int n_jobs = 30;

  auto jobs = std::vector<JobParams>(0);
  for (int i = 0; i < n_jobs; ++i) {
    jobs.push_back({double(i), double(i % 2)});
  }

  auto localities = hpx::find_all_localities();
  std::size_t i = 0;

  // Round-robin work distribution.
  for (auto &&job : jobs) {
    hpx::apply(launch_job_action(), localities[i], job);
    i = (i + 1) % localities.size();
  }

  hpx::finalize();
  return 0;
}

int main(int argc, char *argv[]) {
  using namespace boost::program_options;

  options_description desc_commandline;
  // This program has no own command line options.

  std::vector<std::string> const cfg;
  // We also don't need to force any special HPX config.

  return hpx::init(desc_commandline, argc, argv, cfg);
}
