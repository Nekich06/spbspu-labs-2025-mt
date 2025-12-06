#include "calculate_interface.hpp"
#include <cstring>
#include "sets_parser.hpp"

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

    execl("M0", name.c_str(), seed, 0);
  }
  else
  {
    close(to_pipe_fds[0]);
    to_pipe_fds[0] = -1;
    close(from_pipe_fds[1]);
    from_pipe_fds[1] = -1;
    processes.insert({ name, Process{ child_pid, to_pipe_fds, from_pipe_fds } });
  }
}

void petrov::calcAreaOn(std::istream & in, const processes_map & processes, const sets_map & sets)
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

  int threads_num, tries;
  in >> threads_num >> tries;

  std::string message;
  serializeToMsg(message, set_it->second, threads_num, tries);

  int * to_pipe_fds = process_it->second.to_pipe_fds;

  size_t bytes = 0;
  while (bytes < message.size())
  {
    int ret = write(to_pipe_fds[1], message.c_str() + bytes, message.size() - bytes);
    if (ret < 0)
    {
      close(to_pipe_fds[1]);
      throw std::runtime_error("Write failed: ");
    }
    else
    {
      bytes += ret;
    }
  }
}
