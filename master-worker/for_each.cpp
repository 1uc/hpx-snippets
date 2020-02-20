#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/parallel/algorithms/for_each.hpp>
#include <hpx/parallel/execution_policy.hpp>

#include <boost/program_options.hpp>
#include <sstream>

struct JobParams {
  double a;
  double b;

  void serialize(hpx::serialization::output_archive &ar) const { ar << a << b; }
};

void run_job(const JobParams &job_params) {
  std::stringstream ss;
  ss << "Running job { a = " << std::setw(3) << job_params.a
     << ", b = " << std::setw(3) << job_params.b << "}"
     << " on thread '" << hpx::this_thread::get_id() << "'.\n";

  hpx::cout << ss.str();
}

int hpx_main(boost::program_options::variables_map &) {
  int n_jobs = 30;

  auto jobs = std::vector<JobParams>(0);
  for (int i = 0; i < n_jobs; ++i) {
    jobs.push_back({double(i), double(i % 2)});
  }

  auto executor = hpx::parallel::execution::parallel_executor();
  auto policy = hpx::parallel::execution::par.on(executor);

  auto loop_body = [](const JobParams &job) { run_job(job); };
  hpx::parallel::v1::for_each(policy, jobs.begin(), jobs.end(), loop_body);

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
