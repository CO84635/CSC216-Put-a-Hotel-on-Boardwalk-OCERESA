#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

template <typename T>
class CLL {
public:
    struct Node {
        T data;
        Node* next;
    };

    Node* append(struct Node* last, T data) {
        if (last == nullptr) {
            Node* new_node = new Node();
            new_node->data = data;
            new_node->next = new_node;

            return new_node;
        }

        Node* new_node = new Node();
        new_node->data = data;
        new_node->next = last->next;
        last->next = new_node;

        last = new_node;

        return last;
    }

    void step_forward(Node*& current) {
        if (current == nullptr) {
            cout << "The list is empty" << endl;
            return;
        }

        current = current->next;
    }

    T retrieve_data(Node*& current) {
        return current->data;
    }

    void roll_dice(Node* list, Node*& current){
        int die_1 = rand() % 6 + 1;
        int die_2 = rand() % 6 + 1;
        int dice_roll = die_1 + die_2;
        cout << "Rolled a " << dice_roll << endl;

        for (int i = 0; i < dice_roll; i++) {
            step_forward(current);
        }

        cout << "Landed on " << retrieve_data(current) << endl;
    }
};

int main(){
    CLL<string> list;
    CLL<string>::Node* last = nullptr;
    
    ifstream file("monopoly_spaces.txt");
    string line;

    CLL<string>::Node* current = nullptr;

    while(getline(file, line)) {
        last = list.append(last, line);
        if (current == nullptr) {
            current = last->next;
        }
    }

    cout << "Traversing the list, this will be quick unlike Monopoly: " << endl;
    do {
        cout << list.retrieve_data(current) << endl;
        list.step_forward(current);
    } while (current != last->next);

    cout << "Traversing the list a second time" << endl;
    do {
        cout << list.retrieve_data(current) << endl;
        list.step_forward(current);
    } while (current != last->next);

    srand(time(0));

    list.roll_dice(last, current);
    list.roll_dice(last, current);
    list.roll_dice(last, current);

    return 0;
}