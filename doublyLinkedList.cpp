#include <iostream>
#include <string>
using namespace std;

struct node {
    int id;
    string name;
    string duration;
    node * next = nullptr;
    node * prev = nullptr;
};

class PlayList {
private:
    node * head;
    node * tail;
    node * currentSong; 

public:
    int id_counter = 1; 

    PlayList() {
        
        head = nullptr;
        tail = nullptr;
        currentSong = nullptr; 
    }

   
    void addSong(string name, string duration) {
        node * new_node = new node;
        new_node->name = name;
        new_node->duration = duration;
        new_node->id = id_counter++; 

        if (head == nullptr) {
            head = new_node;
            tail = new_node;
            currentSong = new_node;
        }
        else {
        
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node; 
        }
        cout << "Added: " << name << " (" << duration << ")" << endl;
    }

    string searchSong(int id) { 
        node* left = head;
        node* right = tail;

        while (left != nullptr && right != nullptr && left != right && left->prev != right) {
            if (left->id == id) {
                return "Found: " + left->name + " - " + left->duration;
            }
            if (right->id == id) {
                return "Found: " + right->name + " - " + right->duration;
            }
            left = left->next;
            right = right->prev;
        }
        
        if (left != nullptr && left->id == id) {
            return "Found: " + left->name + " - " + left->duration;
        }

        return "Song with ID " + to_string(id) + " not found."; // Fixed: Missing return path
    }

  
    void deleteSong(int id) {
        if (head == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }
        node* current = head;

        while (current != nullptr) {
            if (current->id == id) {
                
                
                if (current == currentSong) {
                    currentSong = (current->next != nullptr) ? current->next : head;
                }

                if (current == head) {
                    head = current->next;
                    if (head != nullptr) {
                        head->prev = nullptr; 
                    } else {
                        tail = nullptr;       
                    }
                }
                else if (current == tail) {
                    tail = current->prev;
                    if (tail != nullptr) {
                        tail->next = nullptr; 
                    }
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                
                delete current;
                cout << "Song (ID: " << id << ") deleted successfully." << endl;
                return; 
            }
            current = current->next;
        }
        cout << "Song with ID " << id << " not found." << endl;
    }

    
    void displayForward() {
        if (head == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }
        cout << "\n--- Playlist (Forward) ---" << endl;
        node* temp = head;
        while (temp != nullptr) {
            cout << "[" << temp->id << "] " << temp->name << " (" << temp->duration << ")";
            if (temp == currentSong) cout << " <-- NOW PLAYING";
            cout << endl;
            temp = temp->next;
        }
        cout << "--------------------------\n" << endl;
    }

    
    void displayBackward() {
        if (tail == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }
        cout << "\n--- Playlist (Backward) ---" << endl;
        node* temp = tail;
        while (temp != nullptr) {
            cout << "[" << temp->id << "] " << temp->name << " (" << temp->duration << ")" << endl;
            temp = temp->prev;
        }
        cout << "---------------------------\n" << endl;
    }

    void playNext() {
        if (currentSong != nullptr && currentSong->next != nullptr) {
            currentSong = currentSong->next;
            cout << "Skipped forward. Now playing: " << currentSong->name << endl;
        } else {
            cout << "You are at the end of the playlist." << endl;
        }
    }


    void playPrevious() {
        if (currentSong != nullptr && currentSong->prev != nullptr) {
            currentSong = currentSong->prev;
            cout << "Skipped backward. Now playing: " << currentSong->name << endl;
        } else {
            cout << "You are at the beginning of the playlist." << endl;
        }
    }

    void reversePlaylist() {
        if (head == nullptr || head->next == nullptr) {
            cout << "Not enough songs to reverse." << endl;
            return;
        }

        node* current = head;
        node* temp = nullptr;

        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            
            current = current->prev;
        }
        temp = head;
        head = tail;
        tail = temp;

        cout << "Playlist reversed!" << endl;
    }
};

int main() {
    PlayList myPlaylist;

    myPlaylist.addSong("Let it happen", "5:55");
    myPlaylist.addSong("bombastic", "6:30");
    myPlaylist.addSong("Shape of You", "3:53");
    myPlaylist.addSong("jinx", "3:20");

    myPlaylist.displayForward();

    myPlaylist.playNext();
    myPlaylist.playNext();
    myPlaylist.playPrevious();

    myPlaylist.displayForward();

    cout << "\nSearch Result: " << myPlaylist.searchSong(2) << endl;
    cout << "Search Result: " << myPlaylist.searchSong(99) << "\n" << endl;

    myPlaylist.deleteSong(3); // Deletes Shape of You
    myPlaylist.displayForward();

    myPlaylist.reversePlaylist();
    myPlaylist.displayForward();

    return 0;
}