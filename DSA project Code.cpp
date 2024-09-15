#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Node {
    string song;
    Node* next;
    Node* prev;
};

class Playlist {
private:
    Node* head;
    Node* tail;
    Node* top;

public:
    Playlist() : head(nullptr), tail(nullptr), top(nullptr) {}

    void tofile(const string& song) {
        ofstream file("playlist.txt", ios::app);
        file << song << endl;
    }

    void addSong() {
        string song;
        cout << "Enter Song name: ";
        cin.ignore(); // to ignore the newline character left in the buffer
        getline(cin, song);

        Node* newNode = new Node();
        newNode->song = song;
        newNode->next = nullptr;
        newNode->prev = tail;

        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;

        tofile(song);
    }

    void deleteSong() {
        string song;
        cout << "Enter Song name to delete: ";
        cin.ignore();
        getline(cin, song);

        Node* current = head;
        while (current) {
            if (current->song == song) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                delete current;
                cout << "Song deleted." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Song not found." << endl;
    }

    void display() {
        Node* current = head;
        cout << "Playlist:" << endl;
        while (current) {
            cout << current->song << endl;
            current = current->next;
        }
    }

    void countSongs() {
        int count = 0;
        Node* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        cout << "Total songs: " << count << endl;
    }

    void searchSong() {
        string song;
        cout << "Enter song to search: ";
        cin.ignore();
        getline(cin, song);

        Node* current = head;
        while (current) {
            if (current->song == song) {
                cout << "Song found." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Song not found." << endl;
    }

    void playSong() {
        string song;
        cout << "Enter song to play: ";
        cin.ignore();
        getline(cin, song);

        Node* current = head;
        while (current) {
            if (current->song == song) {
                cout << "Now playing: " << song << endl;

                Node* newTop = new Node();
                newTop->song = song;
                newTop->next = top;
                top = newTop;

                return;
            }
            current = current->next;
        }
        cout << "Song not found." << endl;
    }

    void displayRecent() {
        Node* current = top;
        cout << "Recently played songs:" << endl;
        while (current) {
            cout << current->song << endl;
            current = current->next;
        }
    }

    void lastPlayed() {
        if (top) {
            cout << "Last played song: " << top->song << endl;
        } else {
            cout << "No last played songs." << endl;
        }
    }
};

int main() {
    Playlist playlist;
    int choice;

    do {
        cout << "\nMenu:\n1. Add Song\n2. Delete Song\n3. Display Playlist\n4. Count Songs\n5. Search Song\n6. Play Song\n7. Recently Played Songs\n8. Last Played Song\n9. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                playlist.addSong();
                break;
            case 2:
                playlist.deleteSong();
                break;
            case 3:
                playlist.display();
                break;
            case 4:
                playlist.countSongs();
                break;
            case 5:
                playlist.searchSong();
                break;
            case 6:
                playlist.playSong();
                break;
            case 7:
                playlist.displayRecent();
                break;
            case 8:
                playlist.lastPlayed();
                break;
            case 9:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
