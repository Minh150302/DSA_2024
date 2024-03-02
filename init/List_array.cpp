#include <iostream>
#include <stdexcept>

template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
};

template<typename T>
class ArrayList : public List<T> {
private:
    T* arr;
    int capacity;
    int current_size;

    void resize() {
        capacity *= 2;
        T* new_arr = new T[capacity];
        for (int i = 0; i < current_size; ++i) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
    }

public:
    ArrayList() : capacity(10), current_size(0) {
        arr = new T[capacity];
    }

    ~ArrayList() override {
        delete[] arr;
    }

    void push_back(T value) override {
        if (current_size == capacity) {
            resize();
        }
        arr[current_size++] = value;
    }

    void push_front(T value) override {
        insert(0, value);
    }

    void insert(int index, T value) override {
        if (index < 0 || index > current_size) {
            return;
        }
        if (current_size == capacity) {
            resize();
        }
        for (int i = current_size; i > index; --i) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        ++current_size;
    }

    void remove(int index) override {
        if (index < 0 || index >= current_size) {
            return;
        }
        for (int i = index; i < current_size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --current_size;
    }

    T& get(int index) const override {
        if (index < 0 || index >= current_size) {
            throw std::out_of_range("Out of range");
        }
        return arr[index];
    }

    int length() const override {
        return current_size;
    }

    void clear() override {
        current_size = 0;
    }

    void print() const override {
        for (int i = 0; i < current_size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    void reverse() override {
        for (int i = 0; i < current_size / 2; ++i) {
            T temp = arr[i];
            arr[i] = arr[current_size - i - 1];
            arr[current_size - i - 1] = temp;
        }
    }
};

int main() {
    ArrayList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    list.insert(2, 5);
    list.print(); // Output: 0 1 5 2 3
    list.reverse();
    list.print(); // Output: 3 2 5 1 0
    return 0;
}
