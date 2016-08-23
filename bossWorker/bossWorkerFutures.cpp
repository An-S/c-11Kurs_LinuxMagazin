#include <future>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <utility>

using std::cout;
using std::endl;

using std::move;

using std::string;

using std::chrono::milliseconds;

using std::promise;
using std::future;
using std::shared_future;

using std::thread;
using std::this_thread::sleep_for;

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

int getRandomTime(int start, int end){

  random_device seed;
  mt19937 engine(seed());
  uniform_int_distribution<int> dist(start,end);

  return dist(engine);
};

class Worker{
public:
  Worker(string n):name(n){};

    void operator() (promise<void>&& preparedWork, shared_future<void> boss2WorkerStartWork,
                     promise<void>&& doneWork, shared_future<void>boss2WorkerGoHome ){

      // prepare the work and notfiy the boss
      int prepareTime= getRandomTime(500,2000);
      sleep_for(milliseconds(prepareTime));
      preparedWork.set_value();
      cout << name << ": " << "Work prepared after " << prepareTime << " milliseconds." << endl;

      // still waiting for the permission to start working
      boss2WorkerStartWork.wait();

      // do the work and notify the boss
      int workTime= getRandomTime(200,400);
      sleep_for(milliseconds(workTime));
      doneWork.set_value();
      cout << name << ": " << "Work done after " << workTime << " milliseconds." << endl;

      // still waiting for the permission to go home
      boss2WorkerGoHome.wait();

    }
private:
  string name;
};

int main(){

  cout << endl;

  // define the promise => Instruction from the boss
  promise<void> startWorkPromise;
  promise<void> goHomePromise;

  // get the shared futures from the promise
  shared_future<void> startWorkFuture= startWorkPromise.get_future();
  shared_future<void> goHomeFuture= goHomePromise.get_future();

  promise<void> herbPrepared;
  future<void> waitForHerbPrepared= herbPrepared.get_future();
  promise<void> herbDone;
  future<void> waitForHerbDone= herbDone.get_future();
  Worker herb("  Herb");
  thread herbWork(herb,move(herbPrepared),startWorkFuture,move(herbDone),goHomeFuture);

  promise<void> scottPrepared;
  future<void> waitForScottPrepared= scottPrepared.get_future();
  promise<void> scottDone;
  future<void> waitForScottDone= scottDone.get_future();
  Worker scott("    Scott");
  thread scottWork(scott,move(scottPrepared),startWorkFuture,move(scottDone),goHomeFuture);

  promise<void> bjarnePrepared;
  future<void> waitForBjarnePrepared= bjarnePrepared.get_future();
  promise<void> bjarneDone;
  future<void> waitForBjarneDone= bjarneDone.get_future();
  Worker bjarne("      Bjarne");
  thread bjarneWork(bjarne,move(bjarnePrepared),startWorkFuture,move(bjarneDone),goHomeFuture);

  promise<void> andreiPrepared;
  future<void> waitForAndreiPrepared= andreiPrepared.get_future();
  promise<void> andreiDone;
  future<void> waitForAndreiDone= andreiDone.get_future();
  Worker andrei("        Andrei");
  thread andreiWork(andrei,move(andreiPrepared),startWorkFuture,move(andreiDone),goHomeFuture);

  promise<void> andrewPrepared;
  future<void> waitForAndrewPrepared= andrewPrepared.get_future();
  promise<void> andrewDone;
  future<void> waitForAndrewDone= andrewDone.get_future();
  Worker andrew("          Andrew");
  thread andrewWork(andrew,move(andrewPrepared),startWorkFuture,move(andrewDone),goHomeFuture);

  promise<void> davidPrepared;
  future<void> waitForDavidPrepared= davidPrepared.get_future();
  promise<void> davidDone;
  future<void> waitForDavidDone= davidDone.get_future();
  Worker david("            David");
  thread davidWork(david,move(davidPrepared),startWorkFuture,move(davidDone),goHomeFuture);

  cout << "BOSS: PREPARE YOUR WORK.\n " << endl;

  // waiting for the worker
  waitForHerbPrepared.wait(), waitForScottPrepared.wait(), waitForBjarnePrepared.wait(), waitForAndreiPrepared.wait(), waitForAndrewPrepared.wait(), waitForDavidPrepared.wait();

  // notify the worker about the begin of the work
  cout << "\nBOSS: START YOUR WORK. \n" << endl;
  startWorkPromise.set_value();

  // waiting for the worker
  waitForHerbDone.wait(), waitForScottDone.wait(), waitForBjarneDone.wait(), waitForAndreiDone.wait(), waitForAndrewDone.wait(), waitForDavidDone.wait();

  // notify the worker about the end of the work
  cout << "\nBOSS: GO HOME. \n" << endl;
  goHomePromise.set_value();

  herbWork.join();
  scottWork.join();
  bjarneWork.join();
  andreiWork.join();
  andrewWork.join();
  davidWork.join();

}
