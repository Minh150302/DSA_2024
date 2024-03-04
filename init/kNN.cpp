#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
 
 /************** List Structure *****************/
 
template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

template<typename T>
class DoublyLinkedList : public List<T> {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() override {
        clear();
    }

    void push_back(T value) override {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
        }
        tail = newNode;
        ++size;
    }

    void push_front(T value) override {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
        }
        head = newNode;
        ++size;
    }

    void insert(int index, T value) override {
        if (index < 0 || index > size) {
            return;
        }
        if (index == 0) {
            push_front(value);
        } else if (index == size) {
            push_back(value);
        } else {
            Node<T>* newNode = new Node<T>(value);
            Node<T>* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
            ++size;
        }
    }

    void remove(int index) override {
        if (index < 0 || index >= size) {
            return;
        }
        if (index == 0) {
            Node<T>* temp = head;
            head = head->next;
            if (!head) {
                tail = nullptr;
            } else {
                head->prev = nullptr;
            }
            delete temp;
        } else if (index == size - 1) {
            Node<T>* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        } else {
            Node<T>* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        --size;
    }

    T& get(int index) const override {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Out of range");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    int length() const override {
        return size;
    }

    void clear() override {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void print() const override {
        Node<T>* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void reverse() override {
        Node<T>* current = head;
        Node<T>* temp = nullptr;
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp) {
            head = temp->prev;
        }
    }
};


/***************** CLASS DATASET **********************/

class Dataset {
private:
    List<List<int>*>* data;
    //You may need to define more
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
	//endRow: 0:(28x28), endCol: nums of data_train
};













