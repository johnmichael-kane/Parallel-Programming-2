#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
// This uses the third method on here, where all the guests are in a queue/line

class Showroom{
private:
  std::mutex mtx; 
  std::condition_variable cv;
  std::queue<int> queue; // Queue to manage guest turns
  bool showroomAvailable = true; // Initially, the showroom is available
  int totalGuests; // Example total number of guests
  std::vector<std::thread> guests;

public:
  Showroom(int totalGuests) : totalGuests(totalGuests) {}

  void visitShowroom(int guestId) {
    {
      std::unique_lock<std::mutex> lock(mtx); //locks the mutex thread
      queue.push(guestId); // Guest gets in line
    
      while (queue.front() != guestId || !showroomAvailable) { // Wait for turn and availability
        cv.wait(lock);
      }
      //once it's the guests turn they can enter the showroom
      showroomAvailable = false;
    }
    
    //problem simulation
    std::cout << "Guest " << guestId << " is viewing the vase." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Guest " << guestId << " has finished viewing the vase." << std::endl;
  
    {
      std::unique_lock<std::mutex> lock(mtx); //locks the thread until th guest is removed from queue
      showroomAvailable = true;
      queue.pop(); // Remove guest from the queue
    }

    cv.notify_one(); // Notify the next guest
  }
  
  void startParty() {
    //creates the thread for all of the guests
    std::vector<std::thread> guests;
    for (int i = 0; i < totalGuests; ++i) {
      guests.emplace_back(&Showroom::visitShowroom, this, i);
    }
  
    for (auto& guest : guests) {
      guest.join();
    }
    
    std::cout << "All guests have viewed the vase." << std::endl;
    }
};

int main() {
  int totalGuests=10;
  Showroom showroom(totalGuests);
  showroom.startParty();
  return 0;
}
