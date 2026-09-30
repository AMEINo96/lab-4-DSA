#include <iostream>
using namespace std;

struct Node {
    int id;
    Node* next;
};

class JosephusSimulation {
private:
    Node* head;

public:
    JosephusSimulation() {
        head = nullptr;
    }

    void createCircle(int N) {
        if (N <= 0) {
            cout << "Number of people must be greater than 0." << endl;
            return;
        }

        Node* prev = nullptr;

        for (int i = 1; i <= N; i++) {
            Node* newNode = new Node;
            newNode->id = i;
            newNode->next = nullptr;

            if (head == nullptr) {
                head = newNode;
            } else {
                prev->next = newNode;
            }
            prev = newNode;
        }

        
        if (prev != nullptr) {
            prev->next = head;
        }
        
        cout << "Circle of " << N << " people created successfully." << endl;
    }

    void simulate(int k) {
        if (head == nullptr) {
            cout << "Circle is empty." << endl;
            return;
        }
        if (k <= 0) {
            cout << "Step count (k) must be at least 1." << endl;
            return;
        }

        Node* current = head;
        Node* prev = head;

        while (prev->next != head) {
            prev = prev->next;
        }

        cout << "Elimination Order: ";

        while (current->next != current) {

            for (int i = 1; i < k; i++) {
                prev = current;
                current = current->next;
            }

            cout << current->id << " ";

            prev->next = current->next;

            Node* temp = current;
            current = current->next; 
            delete temp;             
        }

        cout << "\n\nSurvivor: " << current->id << " is the last person remaining!" << endl;

        
        delete current;
        head = nullptr; 
    }
};

int main() {
    JosephusSimulation game;
    int N, k;

    cout << "--- Josephus Problem Simulator ---" << endl;
    cout << "Enter the number of people (N): ";
    cin >> N;
    cout << "Enter the step count (k): ";
    cin >> k;
    cout << "----------------------------------" << endl;

    game.createCircle(N);
    game.simulate(k);

    return 0;
}