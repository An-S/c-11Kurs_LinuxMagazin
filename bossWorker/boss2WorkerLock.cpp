#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using std::endl;

using std::mutex;
using std::lock_guard;
using std::thread;
using std::unique_lock;
using std::this_thread::sleep_for;

using std::chrono::milliseconds;

mutex notifiedMutex;
bool notified;

void worker(){
  
  cout << "Worker: Waiting for Notification." << endl;
  
  unique_lock<mutex> lck(notifiedMutex); 
  
  while(!notified){
    
    lck.unlock();
    sleep_for(milliseconds(1000));
    lck.lock();
    
  } 
  
  cout << "Worker: Get Notification." << endl;

}

void boss(){

    cout << "Boss: Notify Worker."  << endl;
    lock_guard<std::mutex> lck(notifiedMutex);
    notified=true;

}

int main(){
  
  cout << endl;

  std::thread workerThread(worker);
  std::thread bossThread(boss);

  workerThread.join();
  bossThread.join();

  cout << endl;
  
}
 