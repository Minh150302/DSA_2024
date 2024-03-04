#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "kNN.hpp"

// Assuming the List and DoublyLinkedList classes are defined in "List.hpp" header file

/***************** CLASS DATASET **********************/

class Dataset {
private:
    List<List<int>*>* data;

public:
    // Constructor
    Dataset() : data(new DoublyLinkedList<DoublyLinkedList<int>*>()) {}

    // Destructor
    ~Dataset() {
        clear();
        delete data;
    }

    // Copy constructor
    Dataset(const Dataset& other) : data(new DoublyLinkedList<DoublyLinkedList<int>*>()) {
        for (int i = 0; i < other.data->length(); ++i) {
            DoublyLinkedList<int>* row = new DoublyLinkedList<int>();
            for (int j = 0; j < other.data->get(i)->length(); ++j) {
                row->push_back(other.data->get(i)->get(j));
            }
            data->push_back(row);
        }
    }

    // Assignment operator
    Dataset& operator=(const Dataset& other) {
        if (this != &other) {
            clear();
            for (int i = 0; i < other.data->length(); ++i) {
                DoublyLinkedList<int>* row = new DoublyLinkedList<int>();
                for (int j = 0; j < other.data->get(i)->length(); ++j) {
                    row->push_back(other.data->get(i)->get(j));
                }
                data->push_back(row);
            }
        }
        return *this;
    }

    // Method to load data from a CSV file
    bool loadFromCSV(const char* fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            return false;
        }

        clear();

        std::string line;
        while (std::getline(file, line)) {
            DoublyLinkedList<int>* row = new DoublyLinkedList<int>();
            std::istringstream iss(line);
            std::string token;
            while (std::getline(iss, token, ',')) {
                row->push_back(std::stoi(token));
            }
            data->push_back(row);
        }

        file.close();
        return true;
    }

    // Method to print the first nRows rows and nCols columns of the dataset
    void printHead(int nRows = 5, int nCols = 5) const {
        int numRows = std::min(nRows, data->length());
        int numCols = 0;
        if (data->length() > 0) {
            numCols = std::min(nCols, data->get(0)->length());
        }

        for (int i = 0; i < numCols; ++i) {
            std::cout << "col" << i << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                std::cout << data->get(i)->get(j) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Method to print the last nRows rows and nCols columns of the dataset
    void printTail(int nRows = 5, int nCols = 5) const {
        int numRows = std::min(nRows, data->length());
        int numCols = 0;
        if (data->length() > 0) {
            numCols = std::min(nCols, data->get(0)->length());
        }

        for (int i = data->length() - numRows; i < data->length(); ++i) {
            for (int j = data->get(i)->length() - numCols; j < data->get(i)->length(); ++j) {
                std::cout << data->get(i)->get(j) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Method to get the shape of the dataset
    void getShape(int& nRows, int& nCols) const {
        nRows = data->length();
        nCols = (data->length() > 0) ? data->get(0)->length() : 0;
    }

    // Method to print the names of all columns of the dataset
    void columns() const {
        int numCols = (data->length() > 0) ? data->get(0)->length() : 0;
        for (int i = 0; i < numCols; ++i) {
            std::cout << "col" << i << " ";
        }
        std::cout << std::endl;
    }

    // Method to drop a row or column of the dataset
    bool drop(int axis = 0, int index = 0, std::string columnName = "") {
        if (axis != 0 && axis != 1) {
            return false;
        }

        if (axis == 0) {
            if (index < 0 || index >= data->length()) {
                return false;
            }
            delete data->get(index);
            data->remove(index);
        } else {
            int columnIndex = -1;
            int numCols = (data->length() > 0) ? data->get(0)->length() : 0;
            for (int i = 0; i < numCols; ++i) {
                if ("col" + std::to_string(i) == columnName) {
                    columnIndex = i;
                    break;
                }
            }
            if (columnIndex == -1) {
                return false;
            }
            for (int i = 0; i < data->length(); ++i) {
                data->get(i)->remove(columnIndex);
            }
        }
        return true;
    }

    // Method to extract a part of the dataset
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const {
        Dataset extractedData;
        int numRows = data->length();
        int numCols = (numRows > 0) ? data->get(0)->length() : 0;

        if (endRow == -1) {
            endRow = numRows;
        }
        if (endCol == -1) {
            endCol = numCols;
        }

        endRow = std::min(endRow, numRows);
        endCol = std::min(endCol, numCols);
        startRow = std::min(startRow, endRow);
        startCol = std::min(startCol, endCol);

        for (int i = startRow; i < endRow; ++i) {
            DoublyLinkedList<int>* row = new DoublyLinkedList<int>();
            for (int j = startCol; j < endCol; ++j) {
                row->push_back(data->get(i)->get(j));
            }
            extractedData.data->push_back(row);
        }

        return extractedData;
    }

private:
    // Method to clear the dataset
    void clear() {
        for (int i = 0; i < data->length(); ++i) {
            delete data->get(i);
        }
        data->clear();
    }
};