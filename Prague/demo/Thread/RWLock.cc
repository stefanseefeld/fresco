#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/Tracer.hh>
#include <unistd.h>

using namespace Prague;

RWLock::Attribute attr;
RWLock lock(attr);

void *reader1(void *)
{
   while (true)
   {
      {
         Guard<RWLock, RLockTrait> guard(lock);
         Trace trace("reader 1 reading");
         usleep(500000);
      }
//       usleep(500000);
   }
}

void *reader2(void *)
{
   while (true)
   {
      {
         Guard<RWLock, RLockTrait> guard(lock);
         Trace trace("reader 2 reading");
         usleep(500000);
      }
//       usleep(500000);
   }
}

void *writer(void *)
{
   while (true)
   {
      {
         Guard<RWLock, WLockTrait> guard(lock);
         Trace trace("writer writing");
         usleep(500000);
      }
//       usleep(500000);
   }
}

int main(int, char **)
{
   Tracer::logging(true);
   Thread thread1(reader1, 0);
   Thread thread2(reader2, 0);
   Thread thread3(writer, 0);
   thread1.start();
   thread2.start();
   thread3.start();
   sleep(10);
}
