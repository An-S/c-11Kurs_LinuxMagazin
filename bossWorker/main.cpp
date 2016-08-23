#include <string>
#include <iostream>
#include <thread>
#include <utility>
#include <future>
#include <string>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;
using namespace this_thread;

/*using std::cout;
using std::endl;

using std::string;
using std::move;

using std::promise;
using std::future;

using std::thread;
*/

int getRandomTime(int start, int end){

  random_device seed;
  mt19937 engine(seed());
  uniform_int_distribution<int> dist(start,end);

  return dist(engine);
};

class Worker{
public:
    using promise_data_t = string;
    using promise_t = promise<promise_data_t>;
    using future_t = future<promise_data_t>;
    using shrfuture_t = shared_future<promise_data_t>;

    Worker(const string n);

    void operator() (void){

        // still waiting for the permission to start working
        shrfuture_t ftr(startWork_promise.get_future());
        string message= ftr.get();
        cout << "Worker " << name << " received the message \"" << message << "\" from the boss." << endl;

        // prepare the work and notfiy the boss
        int prepareTime = getRandomTime(500,2000);
        sleep_for(milliseconds(prepareTime));
        sendReadySignal();

        // do the work and notify the boss
        int workTime= getRandomTime(200,400);
        sleep_for(milliseconds(workTime));
        sendDoneSignal();
        cout << name << ": " << "Work done after " << workTime << " milliseconds." << endl;

        // still waiting for the permission to go home
        waitUntilGoHome();
    }

    void sendStartSignal(void){
        startWork_promise.set_value("START YOUR WORK!");
    }

    void sendGoHomeSignal(void){
        goHome_promise.set_value("GO HOME!");
    }

    void startThread(void){
        thr = thread(operator(), this);
        //return thr;
    }

    void join(void){
        thr.join();
    }

    void sendReadySignal(void){
        ready_promise.set_value("ready.");
    }

    void sendDoneSignal(void){
        done_promise.set_value("done.");
    }

    void waitUntilReady(void){
        promise_data_t msg = ready_promise.get_future().get();
        cout << "Worker " << name << ": \"" << msg << "\"" << endl;
    }

    void waitUntilDone(void){
        promise_data_t msg = done_promise.get_future().get();
        cout << "Worker " << name << ": \"" << msg << "\"" << endl;
    }

    void waitUntilGoHome(void){
        shrfuture_t ftr(goHome_promise.get_future());
        cout << "Worker " << name << " received the message \"" << ftr.get() << "\" from the boss." << endl;
    }

    future_t getReadyFuture(void){
        return ready_promise.get_future();
    }

private:
    string name;
    thread thr;
    promise_t ready_promise, done_promise;
    static promise_t startWork_promise; //use static as this promise is used to send start signal to all workers
    static promise_t goHome_promise; //use static as this promise is used to send start signal to all workers
};

Worker::promise_t Worker::startWork_promise;
Worker::promise_t Worker::goHome_promise;

Worker::Worker(const string name){
    this->name = name;
}

int main(){

    cout << endl;

    // define the promise => Instruction from the boss
    //promise<string> startWorkPromise;

    // get the futures from the promise
    //future<string> startWorkFuture= startWorkPromise.get_future();

    Worker bjarne("Bjarne");
    bjarne.startThread();

    cout << "Boss: Notifying the worker. \n" << endl;

    bjarne.sendStartSignal();
    bjarne.waitUntilReady();

    // notify the worker about the begin of the work
    //startWorkPromise.set_value("START YOUR WORK!");


    bjarne.sendGoHomeSignal();
    bjarne.join();
    cout << endl;

}
