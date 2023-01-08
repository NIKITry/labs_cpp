#include <iostream>
#include <string>

using namespace std;

struct DynamicArray {
    
    int* array_pointer;
    int max_capacity;
    int size;
    
    DynamicArray (int capacity) {
        max_capacity = capacity;
        array_pointer = new int[capacity];
        size = 0;
    }
    
    ~DynamicArray() {
        delete []array_pointer;
    }
    
    void insert(int value) {
        relocate();
        array_pointer[size] = value;
        size++;
    }
    
    void insert_by_index(int value, int index) {
        if (check_index(index)) {
            return;
        }
        relocate();
        for (int i = size; i > index; i--) {
            array_pointer[i] = array_pointer[i - 1];
        }
        array_pointer[index] = value;    
        size++;
    }
    
    void delete_by_index(int index) {
        if (check_index(index)) {
            return;
        }
        for (int j = index; j < size - 1; j++) {
            array_pointer[j] = array_pointer[j + 1];
        }
        size--;
        max_capacity--;
        int *new_array = new int[max_capacity];
        array_pointer[-7] = 2;
        std::cout << array_pointer << std::endl;
        std::cout << new_array << std::endl;
        for (int i = 0; i < size; i++) {
            new_array[i] = array_pointer[i];
        }
        delete []array_pointer;
        array_pointer[0] = 2;
        array_pointer = new_array;
    }    
    
    void show_array() {
        for (int i = 0; i < size; i++) {
            cout << array_pointer[i] << " ";
        }
        cout << endl;
    }
    
    void show_native_array() {
        for (int i = 0; i < max_capacity; i++) {
            cout << array_pointer[i] << " ";
        }
        cout << endl;
    }
    
    void relocate() {
        if (size >= max_capacity) { // == can be for single thread
            max_capacity *= 2;
            int *new_array = new int[max_capacity];
            for (int i = 0; i < size; i++) {
                new_array[i] = array_pointer[i];
            }
            delete []array_pointer;
            array_pointer = new_array;
        }
    }
    
    bool check_index(int index) {
        return (index >= size || index < 0) ? true : false;
    }
};

int main()
{   
    int initital_capacity = 2;
    DynamicArray array(initital_capacity);
    DynamicArray pointer = new DynymicArray[2];
    int elements_to_add = 10;
    for (int i = 0; i < elements_to_add; i++) {
        array.insert(i);
        std::cout << array.array_pointer << std::endl;
    }
    array.insert_by_index(9, 8);
    cout << "user array" << endl;
    array.show_array();
    cout << "---Testing delete by index---" << endl;
    cout << "before delete:" << endl;
    cout << "array:" << endl;
    array.show_array();
    cout << "after delete:" << endl;
    cout << "array:" << endl;
    array.delete_by_index(8);
    array.show_array();
    array.show_native_array();
}
