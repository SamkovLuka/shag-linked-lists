


#include <iostream>
#include <stdexcept>
using namespace std;





struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int value, Node* next = nullptr, Node* prev = nullptr)
        : data(value), next(next), prev(prev) {}
};

class DoubleLinkedList {
    Node* head;
    Node* tail;
    int size;
    int growFactor;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0), growFactor(1) {}

    ~DoubleLinkedList() { Clear(); }




    void AddToHead(int value) {
        Node* newNode = new Node(value, head, nullptr);
        if (IsEmpty()) {
            head = tail = newNode;
        }
        else {
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }




    void AddToTail(int value) {
        Node* newNode = new Node(value, nullptr, tail);
        if (IsEmpty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }




    void DeleteFromTail() {
        if (IsEmpty()) return;
        if (head->next == nullptr) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* beforeLast = tail->prev;
            beforeLast->next = nullptr;
            delete tail;
            tail = beforeLast;
        }
        size--;
    }




    int GetSize() const { return size; }




    void SetSize(int newSize, int grow = 1) {
        growFactor = grow;
        if (newSize < size) {
            for (int i = size; i > newSize; --i) {
                DeleteFromTail();
            }
        }
        else if (newSize > size) {
            for (int i = size; i < newSize; ++i) {
                AddToTail(0);
            }
        }
    }




    int GetUpperBound() const {
        return size - 1;
    }



    bool IsEmpty() const {
        return head == nullptr;
    }





    void FreeExtra() {
        if (size == 0) Clear();
    }




    void Clear() {
        while (!IsEmpty()) {
            DeleteFromTail();
        }
    }




    int GetAt(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }




    void SetAt(int index, int value) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->data = value;
    }



    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }




    void Add(int value) {
        if (size % growFactor == 0) {
            SetSize(size + growFactor);
        }
        AddToTail(value);
    }



    void Append(const DoubleLinkedList& other) {
        Node* current = other.head;
        while (current != nullptr) {
            AddToTail(current->data);
            current = current->next;
        }
    }


    DoubleLinkedList& operator=(const DoubleLinkedList& other) {
        if (this == &other) return *this;
        Clear();
        Node* current = other.head;
        while (current != nullptr) {
            AddToTail(current->data);
            current = current->next;
        }
        return *this;
    }



    Node* GetData() const { return head; }




    void InsertAt(int index, int value) {
        if (index < 0 || index > size) {
            throw out_of_range("Index out of range");
        }
        if (index == 0) {
            AddToHead(value);
        }
        else if (index == size) {
            AddToTail(value);
        }
        else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            Node* newNode = new Node(value, current->next, current);
            current->next->prev = newNode;
            current->next = newNode;
            size++;
        }
    }




    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            if (head) head->prev = nullptr;
            delete temp;
        }
        else if (index == size - 1) {
            DeleteFromTail();
        }
        else {
            Node* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        size--;
    }



    void Show() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    DoubleLinkedList list;
    list.AddToHead(10);
    list.AddToTail(20);
    list.AddToTail(30);
    list.InsertAt(1, 15);
    list.Show();

    list.RemoveAt(2);
    list.Show();

    cout << "Size: " << list.GetSize() << endl;
    cout << "Element at 1: " << list.GetAt(1) << endl;

    list.SetSize(5, 2);
    list.Show();

    list.FreeExtra();
    list.Show();
}
