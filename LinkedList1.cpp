#include <iostream>
using namespace std;

class Node {
public:
    int info;
    Node* next;
    int ctr;

    Node(int i, Node* n = 0) {
        info = i;
        next = n;
        ctr = 1;
    }
};

class Linkedlist {
private:
    Node* head;
public:
    Linkedlist() { head = nullptr; }

    void addInOrder(int value) {
        Node* newNode = new Node(value);

        if (!head || value < head->info) {
           newNode->next = head;
           head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && current->next->info < value)
            current = current->next;

        if (current->info == value) {
            current->ctr++;
        } else if (current->next && current->next->info == value) {
            current->next->ctr++;
        } else {
            current->next = new Node(value, current->next);
        }
    }

    void display() {
        Node* temp = head;
        while (temp) {
            for (int i = 0; i < temp->ctr; i++)
                cout << temp->info << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void deleteValue(int value) {
        if (!head) return;
        if (head->info == value) {
            if (head->ctr > 1) head->ctr--;
            else {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            return;
        }

        Node* current = head;
        while (current->next && current->next->info != value)
            current = current->next;

        if (!current->next) return;
        if (current->next->ctr > 1) {
            current->next->ctr--;
        } else {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    void displayDescending() {
        settingNode(head);
        cout << endl;
    }

    void settingNode(Node* node) {
        if (!node) return;
        settingNode(node->next);
        for (int i = 0; i < node->ctr; i++)
            cout << node->info << " ";
    }

    void removeMax() {
        if (!head) return;
        Node* current = head, *prev = nullptr;
        Node* maxNode = head, *maxPrev = nullptr;

        while (current) {
            if (current->info > maxNode->info) {
                maxNode = current;
                maxPrev = prev;
            }
            prev = current;
            current = current->next;
        }

        if (maxPrev) maxPrev->next = maxNode->next;
        else head = maxNode->next;
        delete maxNode;
    }

    void generateFromArray(int arr[], int size) {
        for (int i = 0; i < size; i++)
            addInOrder(arr[i]);
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    ~Linkedlist() { clear(); }
};

int main() {
    Linkedlist list;
    int arr[] = {10, 5, 8, 10, 5, 10};
    list.generateFromArray(arr, 6);
    list.display();

    list.addInOrder(7);
    list.display();

    list.deleteValue(10);
    list.display();

    list.displayDescending();

    list.removeMax();
    list.display();

    list.clear();
    return 0;
}
