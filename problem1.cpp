#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <algorithm>

td::mutex mtx;
std::condition_variable cv;

int guestsEntered = 0; 
bool cupcakeAvailable = true;
int totalGuests; // Set this based on user input or a predefined value
std::vector<bool> hasVisited; // Track if each guest has visited

void enterLabyrinth(int guestId) {
    std::unique_lock<std::mutex> lock(mtx);
    // Wait for the Minotaur's invitation
    cv.wait(lock, [guestId]() { return guestsEntered == guestId; });

    if (!cupcakeAvailable) {
        // If the cupcake is not available, ask for a new one (simulate this action)
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

void BirthdayParty() {
    std::vector<std::thread> guests;
    totalGuests = 10; // Or ask the user
    hasVisited.resize(totalGuests, false);

    for (int i = 0; i < totalGuests; ++i) {
          guests.emplace_back(enterLabyrinth, i);
    }

    for (auto& t : guests) {
        t.join();
    }
}

int main(){
  BirthdayParty();

  return 0;
}
