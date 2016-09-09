#include <thread>
#include <future>
#include <iostream>
#include <utility>

using std::cout;
using std::endl;

using std::string;
using std::move;

using std::promise;
using std::future;

using std::thread;

class Worker{
public:
  Worker(string n):name(n){};

    void operator() (future<string>&& boss2Worker){

      // still waiting for the permission to start working
      string message= boss2Worker.get();
      cout << "Worker from Boss: "  << message << endl;
    }
private:
  string name;
};

int main(){

  cout << endl;

  // define the promise => Instruction from the boss
  promise<string> startWorkPromise;

  // get the futures from the promise
  future<string> startWorkFuture= startWorkPromise.get_future();

  Worker bjarne("Bjarne");
  thread bjarneWork(bjarne,move(startWorkFuture));

  // notify the worker about the begin of the work
  cout << "Boss: Notifying the worker. \n" << endl;
  startWorkPromise.set_value("START YOUR WORK!");

  bjarneWork.join();

  cout << endl;

}
