
#pragma once

#include <nstd/Base.h>

class Thread
{
public:
  Thread();
  ~Thread();

  bool_t start(uint_t (*proc)(void_t*), void_t* param);

  uint_t join();

  static void_t yield();
  static void_t sleep(int64_t milliseconds);

  /**
  * Get the id of the calling thread.
  *
  * @return The thread id.
  */
  static uint32_t getCurrentThreadId();

private:
  void_t* thread;
  //uint_t threadId;

  Thread(const Thread&);
  Thread& operator=(const Thread&);
};
