#include <iostream>
#include <string>

using namespace std;

struct Node {
    int bit;
    Node* next;
    Node* prev;
    
    Node(int b) {
        bit = b;
        next = nullptr;
        prev = nullptr;
    }
};

class BinaryDLL {
private:
    Node* head;
    Node* tail;

    void insertAtHead(int bit) {
        Node* newNode = new Node(bit);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertAtTail(int bit) {
        Node* newNode = new Node(bit);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    int getSize() const {
        int size = 0;
        Node* curr = head;
        while (curr) {
            size++;
            curr = curr->next;
        }
        return size;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

public:
    BinaryDLL() : head(nullptr), tail(nullptr) {}

    BinaryDLL(const BinaryDLL& other) : head(nullptr), tail(nullptr) {
        Node* curr = other.head;
        while (curr) {
            insertAtTail(curr->bit);
            curr = curr->next;
        }
    }

    // Assignment Operator
    BinaryDLL& operator=(const BinaryDLL& other) {
        if (this != &other) {
            clear();
            Node* curr = other.head;
            while (curr) {
                insertAtTail(curr->bit);
                curr = curr->next;
            }
        }
        return *this;
    }

    // Destructor
    ~BinaryDLL() {
        clear();
    }

    void store(string binaryStr) {
        clear();
        for (char c : binaryStr) {
            if (c == '0' || c == '1') {
                insertAtTail(c - '0');
            }
        }
        padTo8Bits();
    }

    void padTo8Bits() {
        int size = getSize();
        if (size == 0) insertAtHead(0); // If empty, at least one 0
        
        size = getSize();
        int remainder = size % 8;
        if (remainder != 0) {
            int needed = 8 - remainder;
            for (int i = 0; i < needed; i++) {
                insertAtHead(0);
            }
        }
    }

    // 2. 1's Complement (Flip all bits)
    void onesComplement() {
        Node* curr = head;
        while (curr) {
            curr->bit = 1 - curr->bit; 
            curr = curr->next;
        }
    }

    BinaryDLL add(const BinaryDLL& other) const {
        BinaryDLL result;
        Node* p1 = this->tail;
        Node* p2 = other.tail;
        int carry = 0;

        while (p1 != nullptr || p2 != nullptr || carry > 0) {
            int sum = carry;
            if (p1) { sum += p1->bit; p1 = p1->prev; }
            if (p2) { sum += p2->bit; p2 = p2->prev; }
            
            result.insertAtHead(sum % 2); // Current bit
            carry = sum / 2;              // Next carry
        }
        
        result.padTo8Bits();
        return result;
    }

    // 4. 2's Complement (1's complement + 1 using DLL addition)
    void twosComplement() {
        onesComplement();
        
        BinaryDLL one;
        one.store("1"); // Creates an 8-bit grouped DLL containing '1'
        
        // Add 1 to the current number
        *this = this->add(one);
    }

    // 5. Binary Multiplication (Repeated Addition + Shifting)
    BinaryDLL multiply(const BinaryDLL& other) const {
        BinaryDLL result;
        result.store("0");

        BinaryDLL tempMultiplicand = *this; // Value to shift
        Node* multiplierBit = other.tail;   // Start from LSB

        while (multiplierBit != nullptr) {
            if (multiplierBit->bit == 1) {
                result = result.add(tempMultiplicand);
            }
            // Left Shift the multiplicand by appending a '0' at the tail
            tempMultiplicand.insertAtTail(0);
            
            multiplierBit = multiplierBit->prev;
        }
        
        result.padTo8Bits();
        return result;
    }

    // 6. Conversion to Decimal
    long long toDecimal() const {
        long long decimalVal = 0;
        Node* curr = head;
        while (curr) {
            decimalVal = (decimalVal * 2) + curr->bit;
            curr = curr->next;
        }
        return decimalVal;
    }

    // Display list in 8-bit blocks
    void display() const {
        int size = getSize();
        Node* curr = head;
        int count = 0;
        
        while (curr) {
            cout << curr->bit;
            count++;
            // Print space to visually separate into 8-bit blocks
            if ((size - count) % 8 == 0 && curr->next != nullptr) {
                cout << " ";
            }
            curr = curr->next;
        }
        cout << endl;
    }
};

// Driver Code
int main() {
    BinaryDLL num1, num2;
    
    // 1. Store
    cout << "--- 1. Store Binary Numbers ---" << endl;
    num1.store("1010"); // 10
    num2.store("110");  // 6
    cout << "Num1 (10): "; num1.display();
    cout << "Num2 (6) : "; num2.display();

    // 2. 1's Complement
    cout << "\n--- 2. 1's Complement ---" << endl;
    BinaryDLL comp1 = num1; 
    comp1.onesComplement();
    cout << "1's Complement of Num1: "; comp1.display();

    // 3. 2's Complement
    cout << "\n--- 3. 2's Complement ---" << endl;
    BinaryDLL comp2 = num1;
    comp2.twosComplement();
    cout << "2's Complement of Num1: "; comp2.display();

    // 4. Addition
    cout << "\n--- 4. Binary Addition ---" << endl;
    BinaryDLL sum = num1.add(num2);
    cout << "Num1 + Num2: "; sum.display();
    cout << "Decimal check: " << sum.toDecimal() << " (Expected: 16)" << endl;

    // 5. Multiplication
    cout << "\n--- 5. Binary Multiplication ---" << endl;
    BinaryDLL product = num1.multiply(num2);
    cout << "Num1 * Num2: "; product.display();
    cout << "Decimal check: " << product.toDecimal() << " (Expected: 60)" << endl;

    // 6. Decimal Conversion
    cout << "\n--- 6. Decimal Conversions ---" << endl;
    cout << "Num1 in decimal: " << num1.toDecimal() << endl;
    cout << "Num2 in decimal: " << num2.toDecimal() << endl;

    return 0;
}