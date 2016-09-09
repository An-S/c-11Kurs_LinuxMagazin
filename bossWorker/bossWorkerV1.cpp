#include <chrono>
#include <iostream>
#include <thread>

using std::cout;
using std::endl;

using std::string;

using std::chrono::milliseconds;

using std::thread;
using std::this_thread::sleep_for;

class Worker{
public:
  Worker(string n):name(n){};
  
    void operator() (){
      for (int i= 1; i <= 3; ++i){
	// begin work
	sleep_for(milliseconds(200));
	// end work
	cout << name << ": " << "Work " << i << " done !!!" << endl;
      }
      
    }
private:
  string name;
};


int main(){

  cout << endl;
  
  cout << "Boss: Let's start working.\n\n";
 
  thread herb= thread(Worker("Herb"));
  thread andrei= thread(Worker("  Andrei"));
  thread scott= thread(Worker("    Scott"));
  thread bjarne= thread(Worker("      Bjarne"));
  thread andrew= thread(Worker("        Andrew"));
  thread david= thread(Worker("          David"));
  
  herb.join();
  andrei.join();
  scott.join();
  bjarne.join();
  andrew.join();
  david.join();
  
  cout << "\n" << "Boss: Let's go home." << endl;
  
  cout << endl;

}
