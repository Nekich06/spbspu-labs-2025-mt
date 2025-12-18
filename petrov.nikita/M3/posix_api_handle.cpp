#include "posix_api_handle.hpp"
#include <unistd.h>
#include <memory>

PosixApiHandle::PosixApiHandle(int & h):
  handle_(h)
{
  h = -1;
}


PosixApiHandle::~PosixApiHandle()
{
  close(handle_);
}

PosixApiHandle::PosixApiHandle(PosixApiHandle && rhs):
  handle_{std::exchange(rhs.handle_, -1)}
{}

PosixApiHandle & PosixApiHandle::operator=(PosixApiHandle && rhs)
{
  if (this != std::addressof(rhs))
  {
    closeHandle();
    handle_ = std::exchange(rhs.handle_, -1);
  }

  return *this;
}

PosixApiHandle::operator int() const
{
  return handle_;
}

void PosixApiHandle::closeHandle()
{
  if (handle_ != -1)
  {
    close(handle_);
    handle_ = -1;
  }
}
