#include <iostream>
#include <vector>

class BinaryCounter {
private:
    std::vector<bool> counter;
    int totalCost;  // Total number of bit flips (cost) performed.

public:
    BinaryCounter(int bits) {
        counter.resize(bits, false);
        totalCost = 0;  // Initialize the total cost to 0.
    }

    void increment() {
        int cost = 0;
        int i = 0;
        while (i < counter.size() && counter[i]) {
            counter[i] = false;
            cost++;
            i++;
        }
        if (i < counter.size()) {
            counter[i] = true;
            cost++;
        }
        totalCost += cost;
    }

    void display() {
        for (int i = counter.size() - 1; i >= 0; --i) {
            std::cout << counter[i];
        }
        std::cout << std::endl;
    }

    void displayTotalCost() {
        std::cout << "Total cost (bit flips): " << totalCost << std::endl;
    }
};

int main() {
    BinaryCounter counter(5);

    for (int i = 0; i < 32; ++i) {
        counter.increment();
        counter.display();
    }

    counter.displayTotalCost();
    return 0;
}
