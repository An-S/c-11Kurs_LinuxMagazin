#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

using std::cout;
using std::endl;

using std::string;

using std::chrono::milliseconds;

using std::atomic_int;

using std::mutex;
using std::condition_variable;
using std::thread;
using std::this_thread::sleep_for;
using std::unique_lock;

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

// Worker
// number of prepared or done workers
atomic_int preparedCount, doneCount;

mutex startWorkMutex, goHomeMutex;

// notify the boss
condition_variable worker2BossCondVariable;

// Boss
bool startWork, goHome;
mutex preparedMutex, doneMutex;

// notify the workers
condition_variable boss2WorkerCondVariable;

int getRandomTime(int start, int end){
  
  random_device seed;
  mt19937 engine(seed());
  uniform_int_distribution<int> dist(start,end);
  
  return dist(engine);
};

class Worker{
public:
  Worker(string n):name(n){};
  
    void operator() (){
      
      // prepare the work and notfiy the boss
      int prepareTime= getRandomTime(500,2000);
      sleep_for(milliseconds(prepareTime));
      preparedCount++;
      cout << name << ": " << "Work prepared after " << prepareTime << " milliseconds." << endl;
      worker2BossCondVariable.notify_one();
      
      // wait for the start notification
      unique_lock<mutex> startWorkLock( startWorkMutex );
      boss2WorkerCondVariable.wait( startWorkLock,[]{ return startWork;});
      
      // do the work and notify the boss
      int workTime= getRandomTime(200,400);
      sleep_for(milliseconds(workTime));
      doneCount++;
      cout << name << ": " << "Work done after " << workTime << " milliseconds." << endl;
      worker2BossCondVariable.notify_one();
      
      // wait for the go home notification of the boss
      unique_lock<mutex> goHomeLock( goHomeMutex );
      boss2WorkerCondVariable.wait( goHomeLock,[]{ return goHome;});
  
    }
private:
  string name;
};

int main(){
  
  cout << endl;
  
  Worker herb("  Herb");
  thread herbWork(herb);
  
  Worker scott("    Scott");
  thread scottWork(scott);
  
  Worker bjarne("      Bjarne");
  thread bjarneWork(bjarne);
  
  Worker andrei("        Andrei");
  thread andreiWork(andrei);
  
  Worker andrew("          Andrew");
  thread andrewWork(andrew);
  
  Worker david("            David");
  thread davidWork(david);
  
  cout << "BOSS: PREPARE YOUR WORK.\n " << endl;
  
  // waiting for the worker 
  preparedCount.store(0);
  unique_lock<mutex> preparedUniqueLock( preparedMutex );
  worker2BossCondVariable.wait(preparedUniqueLock,[]{ return preparedCount == 6; });
  
  // notify the worker about the begin of the work
  startWork= true;
  cout << "\nBOSS: START YOUR WORK. \n" << endl;
  boss2WorkerCondVariable.notify_all();
  
  // waiting for the worker
  doneCount.store(0);
  unique_lock<mutex> doneUniqueLock( doneMutex );
  worker2BossCondVariable.wait(doneUniqueLock,[]{ return doneCount == 6; }); 
  
  // notify the worker about the end of the work
  goHome= true;
  cout << "\nBOSS: GO HOME. \n" << endl;
  boss2WorkerCondVariable.notify_all();
  
  herbWork.join();
  scottWork.join();
  bjarneWork.join();
  andreiWork.join();
  andrewWork.join();
  davidWork.join();
   

}