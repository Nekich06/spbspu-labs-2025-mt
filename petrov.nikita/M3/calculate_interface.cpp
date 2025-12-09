#include "calculate_interface.hpp"
#include <iomanip>
#include <cstring>
#include <memory>
#include "sets_parser.hpp"

namespace
{
  class StreamGuard
  {
  public:
    StreamGuard(std::basic_ios< char > & s):
      s_(s),
      precision_(s.precision()),
      flags_(s.flags())
    {}
    ~StreamGuard()
    {
      s_.precision(precision_);
      s_.flags(flags_);
    }
  private:
    std::basic_ios< char > & s_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}

void petrov::spawnProcess(std::istream & in, processes_map & processes)
{
  std::string name;
  in >> name;
  if (processes.find(name) != processes.end())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  long int seed = 0;
  in >> seed;
  if (seed < 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  int to_pipe_fds[2];
  if (pipe(to_pipe_fds) < 0)
  {
    std::cerr << "To-child pipe creation failed: " << strerror(errno) << std::endl;
    return;
  }
  int from_pipe_fds[2];
  if (pipe(from_pipe_fds) < 0)
  {
    std::cerr << "From-child pipe creation failed: " << strerror(errno) << std::endl;
    close(to_pipe_fds[0]);
    close(to_pipe_fds[1]);
    return;
  }

  pid_t child_pid = fork();

  if (child_pid < 0)
  {
    std::cerr << "Process start failed: " << strerror(errno) << std::endl;
    close(to_pipe_fds[0]);
    close(to_pipe_fds[1]);
    close(from_pipe_fds[0]);
    close(from_pipe_fds[1]);
    return;
  }

  if (child_pid == 0)
  {
    close(to_pipe_fds[1]);
    to_pipe_fds[1] = -1;
    if (dup2(to_pipe_fds[0], STDIN_FILENO) < 0)
    {
      close(to_pipe_fds[0]);
      close(from_pipe_fds[0]);
      close(from_pipe_fds[1]);
      throw std::runtime_error("Process start failed: ");
    }
    close(to_pipe_fds[0]);

    close(from_pipe_fds[0]);
    if (dup2(from_pipe_fds[1], STDOUT_FILENO) < 0)
    {
      close(from_pipe_fds[1]);
      throw std::runtime_error("Process start failed: ");
    }
    close(from_pipe_fds[1]);

    std::string seed_str = std::to_string(seed);
    if (execl("/home/nekich06/spbspu-labs-2025-mt/out/petrov.nikita/M0/lab", name.c_str(), seed_str.c_str(), NULL) == -1)
    {
      throw std::runtime_error("Process start failed: ");
    }
  }
  else
  {
    close(to_pipe_fds[0]);
    to_pipe_fds[0] = -1;
    close(from_pipe_fds[1]);
    from_pipe_fds[1] = -1;
    processes.insert({ name, Process{ child_pid, to_pipe_fds, from_pipe_fds } });
    std::cout << "CHILD PROCESS STARTED\n";
  }
}

void petrov::calcAreaOn(std::istream & in, const processes_map & processes, calcs_map & calcs, const sets_map & sets)
{
  std::string process_name;
  in >> process_name;
  auto process_it = processes.find(process_name);
  if (process_it == processes.end())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  std::string calc_name;
  in >> calc_name;

  std::string set_name;
  in >> set_name;
  auto set_it = sets.find(set_name);
  if (set_it == sets.end())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  calcs.insert({ calc_name, Calculation{ Status::IN_PROGRESS, process_name, 0.0, 0.0 }});

  int threads_num, tries;
  in >> threads_num >> tries;

  std::string message;
  serializeToMsg(message, set_it->second, threads_num, tries);
  std::cout << "MESSAGE IS: " << message << '\n';
  std::cout << "MESSAGE SIZE IS: " << message.size() << '\n';
  int * to_pipe_fds = process_it->second.to_pipe_fds;

  size_t bytes = 0;
  int ret = 0;
  while (bytes < message.size())
  {
    ret = write(to_pipe_fds[1], message.c_str() + bytes, message.size() - bytes);
    if (ret < 0)
    {
      close(to_pipe_fds[1]);
      throw std::runtime_error("Write failed: ");
    }
    else
    {
      bytes += ret;
      std::cout << "Writing data to process...\n";
      std::cout << "Bytes written: " << bytes << '\n';
    }
  }
}

std::ostream & petrov::waitResultAndPrint(std::ostream & out, std::istream & in, const processes_map & processes, calcs_map & calcs)
{
  std::string calc_name;
  in >> calc_name;

  Calculation calculation = calcs.find(calc_name)->second;
  std::string process_name = calculation.process_name;
  auto process_it = processes.find(process_name);

  int * from_pipe_fds = process_it->second.from_pipe_fds;

  int ret = 1;
  double cvrg_area = 0.0;
  double * ptr_cvrg_area = std::addressof(cvrg_area);
  while (ret != 0)
  {
    std::cout << "Reading results from process...\n";
    ret = read(from_pipe_fds[0], ptr_cvrg_area, sizeof(cvrg_area));
    if (ret < 0)
    {
      close(from_pipe_fds[0]);
      throw std::runtime_error("Read failed: ");
    }
  }
  double calc_time = 0.0;
  double * ptr_calc_time = std::addressof(calc_time);
  ret = 1;
  while (ret != 0)
  {
    std::cout << "Reading results from process...\n";
    ret = read(from_pipe_fds[0], ptr_calc_time, sizeof(calc_time));
    if (ret < 0)
    {
      close(from_pipe_fds[0]);
      throw std::runtime_error("Read failed: ");
    }
  }
  calculation.status = FINISHED;
  StreamGuard out_guard(out);
  out << "RESULTS\n";
  out << std::fixed << std::setprecision(3);
  out << cvrg_area << " " << calc_time;
  return out;
}
