#include <Prague/Sys/ThreadPool.hh>
#include <iostream>
#include <unistd.h>

using namespace Prague;

class Handler
{
public:
  Handler(int s) : msg(s) {}
  virtual void process() { cout << "Handler::process : " << msg << endl; sleep(1);}
private:
  int msg;
};

class Acceptor
{
public:
  Handler *consume(int msg) { return new Handler(msg);}
};

int main(int, char **)
{
  /*
   * create a queue able to hold 10 strings
   */
  Thread::Queue<int> queue(10);
  Acceptor acceptor;
  /*
   * create a pool of 10 threads waiting for strings on the queue
   */
  ThreadPool<int, Acceptor, Handler> pool(queue, acceptor, 10);
  pool.start();
  for (unsigned int i = 0; i != 100; i++) queue.push(i);
}
