#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>

class Labyrinth {
private:
  std::mutex mtx;
  std::condition_variable cv;
  bool cupcakeAvailable = true;
  int totalGuests; 
  std::atomic<int> guestsWhoHaveEatenCupcake{0}; // Count of guests who have eaten the cupcake
  std::vector<bool> hasVisited; // Track if each guest has visited
  std::atomic<bool> allGuestsHaveVisited{false}; // Flag to indicate all guests have visited

public:
  Labyrinth(int numGuests) : totalGuests(numGuests), hasVisited(numGuests, false) {}

  void enterLabyrinth(int guestId) {
    std::unique_lock<std::mutex> lock(mtx);
    // Wait until it's this guest's turn or until all guests have visited
    cv.wait(lock, [this, guestId]() { return allGuestsHaveVisited || !hasVisited[guestId]; });

    if (!cupcakeAvailable) {
      // If the cupcake is not available and this guest hasn't eaten, ask for a new one
      if (!hasVisited[guestId]) {
        cupcakeAvailable = true; // A new cupcake is placed
        std::cout << "Guest " << guestId << " asked for a new cupcake.\n";
      }
    }

    if (cupcakeAvailable && !hasVisited[guestId]) {
      // If the cupcake is available and this guest hasn't visited, eat the cupcake
      cupcakeAvailable = false; // Guest decides to eat the cupcake
      guestsWhoHaveEatenCupcake++;
      std::cout << "Guest " << guestId << " eats the cupcake.\n";
    }

    // The leader remembers this guest went in the maze
    hasVisited[guestId] = true;

    // If this is the counter guest and all guests have eaten the cupcake
    if (guestsWhoHaveEatenCupcake == totalGuests) {
      //iff all Guests
      allGuestsHaveVisited = true;
      std::cout << "All guests have visited the labyrinth and eaten the cupcake.\n";
      return;
    }

    cv.notify_all();
  }

  void startParty() {
    std::vector<std::thread> guests;
    for (int i = 0; i < totalGuests; ++i) {
      guests.emplace_back(&Labyrinth::enterLabyrinth, this, i);
    }

    for (auto& guest : guests) {
      guest.join();
    }
  }
};

int main() {
  int totalGuests;
  std::cout << "Enter the number of guests: ";
  std::cin >> totalGuests;

  Labyrinth labyrinth(totalGuests);
  labyrinth.startParty();

  return 0;
}
