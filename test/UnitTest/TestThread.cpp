
#include <nstd/Debug.h>
#include <nstd/Thread.h>
#include <nstd/Atomic.h>

void_t testThread()
{
  Thread thread;
  Thread thread2;
  Thread thread3;
  struct ThreadData
  {
    static uint_t proc(void_t* args)
    {
      ThreadData& threadData = *(ThreadData*)args;

      ASSERT(threadData.intParam == 123);
      for (int i = 0; i < 10000; ++i)
      {
        Atomic::increment(threadData.counter);
        Thread::yield();
      }
      return 42;
    }
    uint_t intParam;
    volatile uint_t counter;
  } threadData;
  threadData.intParam = 123;
  threadData.counter = 0;
  ASSERT(thread.start(ThreadData::proc, &threadData));
  ASSERT(thread2.start(ThreadData::proc, &threadData));
  ASSERT(thread3.start(ThreadData::proc, &threadData));
  ASSERT(thread.join() == 42);
  ASSERT(thread.start(ThreadData::proc, &threadData));
  ASSERT(thread.join() == 42);
  ASSERT(thread2.join() == 42);
  ASSERT(thread3.join() == 42);
  ASSERT(threadData.counter == 4 * 10000);
}
