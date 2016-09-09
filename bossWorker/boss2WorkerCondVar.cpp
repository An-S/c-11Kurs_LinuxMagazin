#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using std::endl;

using std::mutex;
using std::condition_variable;
using std::lock_guard;
using std::thread;
using std::unique_lock;

mutex notifiedMutex;
condition_variable condVar;
bool notified;

void worker(){
  
  cout << "Worker: Waiting for Notification." << endl;
  unique_lock<mutex> lck(notifiedMutex);
  condVar.wait(lck,[]{return notified;});
  cout << "Worker: Get Notification." << endl;

}

void boss(){
  
  cout << "Boss: Notify Worker."  << endl;
  lock_guard<std::mutex> lck(notifiedMutex);
  notified=true;
  condVar.notify_one();

}

int main(){

  cout << endl;

  std::thread workerThread(worker);
  std::thread bossThread(boss);

  workerThread.join();
  bossThread.join();

  cout << endl;
  
}
 