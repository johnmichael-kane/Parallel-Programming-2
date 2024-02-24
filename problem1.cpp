#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <algorithm>

class Labrynth {
private:
  std::mutex mtx;
  std::condition_variable cv;
  int guestsEntered = 0;
  bool cupcakeAvailable = true;
  int totalGuests; // Set based on user input or a predefined value
  std::vector<bool> hasVisited; // Track if each guest has visited

public:
  Labrynth(int numGuests) : totalGuests(numGuests) {
    hasVisited.resize(totalGuests, false);
  }

  void enterLabyrinth(int guestId) {
    std::unique_lock<std::mutex> lock(mtx);
    // Wait for the Minotaur's invitation
    cv.wait(lock, [this, guestId]() { return guestsEntered == guestId; });

    if (!cupcakeAvailable) {
        // If the cupcake is not available, simulate asking for a new one
        cupcakeAvailable = true; // A new cupcake is placed
        std::cout << "Guest " << guestId << " asked for a new cupcake.\n";
    }

    // Simulate decision to eat the cupcake or not
    if (cupcakeAvailable) {
        cupcakeAvailable = false; // Guest decides to eat the cupcake
        std::cout << "Guest " << guestId << " eats the cupcake.\n";
    }

    // Mark this guest as having visited
    hasVisited[guestId] = true;
    guestsEntered++; // Prepare for the next guest
    cv.notify_all(); // Invite the next guest

    // Check if all guests have visited
    bool allHaveVisited = std::all_of(hasVisited.begin(), hasVisited.end(), [](bool visited) { return visited; });
    if (allHaveVisited) {
      std::cout << "All guests have visited the labyrinth.\n";
    }
  }

  void startParty() {
    std::vector<std::thread> guests;

    for (int i = 0; i < totalGuests; ++i) {
      guests.emplace_back(&Labrynth::enterLabyrinth, this, i);
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

  Labrynth lab(totalGuests);
  lab.startParty();

  return 0;
}
