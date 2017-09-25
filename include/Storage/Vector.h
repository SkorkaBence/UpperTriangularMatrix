#ifndef H_VECTOR
#define H_VECTOR

#include <iostream>
#include "Storage/VectorException.h"

namespace sbl {

    template<typename T>
    class vector {
    private:
        T* arr;
        unsigned int real_size;
        unsigned int reserved_size;

        void deleteArray() {
            if (arr != nullptr) {
                /*for (int i = 0; i < reserved_size; i++) {
                    delete arr + i;
                }*/
                delete [] arr;
                arr = nullptr;
            }
        }
    public:
        vector() {
            arr = nullptr;
            real_size = 0;
            reserved_size = 0;
        }

        bool clear() {
            deleteArray();

            real_size = 0;
            reserved_size = 0;
            return true;
        }

        bool push_back(T val) {
            if (real_size >= reserved_size) {
                reserved_size = reserved_size * 2 + 1;
                T* newarr = new T[reserved_size];
                for (unsigned int i = 0; i < real_size; i++) {
                    newarr[i] = arr[i];
                }
                deleteArray();
                arr = newarr;
            }
            arr[real_size] = val;
            real_size++;
            return true;
        }

        bool pop_back() {
            if (real_size == 1) {
                clear();
            } else if (real_size > 0) {
                real_size--;
                return true;
            }
            return false;
        }

        bool resize(unsigned int ns) {
            if (ns <= reserved_size) {
                return true;
            } else {
                reserved_size = ns;
                real_size = ns;
                deleteArray();
                arr = new T[reserved_size];
            }
            return true;
        }

        T& operator [] (unsigned int index) {
            if (index >= real_size) {
                throw VectorException("Invalid index");
            }
            return arr[index];
        }

        const T& operator [] (unsigned int index) const {
            if (index >= real_size) {
                throw VectorException("Invalid index");
            }
            return arr[index];
        }

        unsigned int size() const {
            return real_size;
        }
    };

}

#endif // ! H_VECTOR
