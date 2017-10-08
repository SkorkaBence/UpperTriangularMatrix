#ifndef H_SBL_VECTOR
#define H_SBL_VECTOR

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

        vector(const vector<T>& copythis) {
            arr = nullptr;
            real_size = 0;
            reserved_size = 0;

            this->resize(copythis.size());
            for (int i = 0; i < copythis.size(); i++) {
                arr[i] = copythis.arr[i];
            }
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
                return true;
            } else if (real_size > 0) {
                real_size--;
                return true;
            }
            return false;
        }

        bool resize(unsigned int ns) {
            T* newarr = new T[ns];

            if (real_size > 0) {
                int minimumsize = ns > real_size ? real_size : ns;
                for (int i = 0; i < minimumsize; i++) {
                    newarr[i] = arr[i];
                }
                deleteArray();
            }
            
            reserved_size = ns;
            real_size = ns;
            arr = newarr;

            return true;
        }

        bool reserve(unsigned int ns) {
            if (ns < reserved_size) {
                return true;
            }

            T* newarr = new T[ns];
            for (int i = 0; i < reserved_size; i++) {
                newarr[i] = arr[i];
            }
            deleteArray();
            reserved_size = ns;
            arr = newarr;

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

        friend std::ostream& operator << (std::ostream& out, vector<T> vect) {
            out << "{" << vect.size();
            for (int i = 0; i < vect.size(); i++) {
                out << ", " << (int)vect[i];
            }
            out << "}";
        }
    };

}

#endif // ! H_SBL_VECTOR
