#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> queue; // Queue to manage guest turns
bool showroomAvailable = true; // Initially, the showroom is available
int totalGuests = 10; // Example total number of guests

void visitShowroom(int guestId) {
    std::unique_lock<std::mutex> lock(mtx);
    queue.push(guestId); // Guest gets in line

    while (queue.front() != guestId || !showroomAvailable) { // Wait for turn and availability
        cv.wait(lock);
    }

    // It's this guest's turn and the showroom is available
    showroomAvailable = false;
    std::cout << "Guest " << guestId << " is viewing the vase." << std::endl;

    // Simulate the time taken to view the vase
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Guest is done viewing the vase
    showroomAvailable = true;
    queue.pop(); // Remove guest from the queue
    std::cout << "Guest " << guestId << " has finished viewing the vase." << std::endl;

    cv.notify_all(); // Notify others waiting
}

void startParty() {
    std::vector<std::thread> guests;
    for (int i = 0; i < totalGuests; ++i) {
        guests.push_back(std::thread(visitShowroom, i));
    }

    for (auto& guest : guests) {
        guest.join();
    }
}

int main() {
    startParty();
    return 0;
}
