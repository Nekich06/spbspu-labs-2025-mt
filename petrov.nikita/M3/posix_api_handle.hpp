#ifndef POSIX_API_HANDLE
#define POSIX_API_HANDLE

struct PosixApiHandle
{
  PosixApiHandle() = default;
  explicit PosixApiHandle(int & h);
  ~PosixApiHandle();
  PosixApiHandle(const PosixApiHandle &) = delete;
  PosixApiHandle(PosixApiHandle && rhs);

  PosixApiHandle & operator=(const PosixApiHandle &) = delete;
  PosixApiHandle & operator=(PosixApiHandle && rhs);
  operator int() const;

  void closeHandle();
private:
  int handle_ = -1;
};

#endif
