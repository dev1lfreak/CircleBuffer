#ifndef OP_ONCPP_CIRCLE_BUF_H
#define OP_ONCPP_CIRCLE_BUF_H

#include <iostream>
#include <iterator>

template<typename T>
class CircleBuffer {
private:
    T *_array;
    size_t _size;
    size_t _capacity;

    void resize(){
        T* new_arr = new T[2*_capacity];
        for(int i{0}; i < _size; i++){
            new_arr[i] = _array[i];
        }
        delete _array;
        _array = new_arr;
        _capacity *= 2;
    }
public:
    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T* _pointer;
    public:
        iterator(T* obj): _pointer(obj){}

        ~iterator() = default;

        iterator(const iterator& obj){
            _pointer = obj._pointer;
        }

        T& operator*(){return *_pointer;}

        bool operator!=(const iterator &source){
            return (this->_pointer != source._pointer);
        }

        iterator& operator++(){
            _pointer++;
            return *this;
        }

        T* operator->(){
            return _pointer;
        }

        iterator& operator--(){
            _pointer--;
            return *this;
        }

        iterator operator+(int n){
            _pointer = _pointer + n;
            return *this;
        }

        iterator& operator-(int n){
            _pointer = _pointer - n;
            return *this;
        }

        iterator& operator-(const iterator &obj){
            _pointer = _pointer - obj._pointer;
            return *this;
        }

        iterator& operator+(const iterator &obj){
            _pointer = _pointer + obj._pointer;
            return *this;
        }

        iterator& operator*(int n){
            _pointer = _pointer * 2;
            return *this;
        }
    };

    explicit CircleBuffer() : _array(nullptr), _size(0), _capacity(0) {}

    explicit CircleBuffer(int x) : _array(new T[4 * x]), _size(x), _capacity(4 * x) {}  

    CircleBuffer(const CircleBuffer &obj) {
        this->_size = obj.size();
        this->_capacity = obj.capacity();
        this->_array = new T[_capacity];

        for (auto i{0}; i < this->_size; i++) {
            _array[i] = obj[i];
        }
    }

    size_t size() {
        return this->_size;
    }

    size_t capacity() {
        return this->_capacity;
    }

    iterator begin() {
        return iterator(_array);
    }

    iterator end() {
        return iterator(_array + _size);
    }

    T &operator[](const int index) {
        return _array[index % _size];
    }

    void push_back(const T& source){
        if((_size + 1) > _capacity / 2) resize();
        _array[_size] = source;
        _size++;
    }

    T& pop_back(){
        if(_size != 0) _size--;
        return _array[_size];
    }

    void push_front(const T& source){
        if((_size + 1) > _capacity / 2) this->resize();
        for(int i{_size}; i > 0; i--){
            _array[i] = _array[i - 1];
        }
        _size++;
        _array[0] = source;
    }

    T& pop_front(){
        T tmp = _array[0];
        _size--;
        for(int i{1}; i < _size; i++){
            _array[i-1] = _array[i];
        }
        return tmp;
    }

    void insert(iterator it, T source){
        if((_size + 1) > _capacity / 2) resize();
        for(iterator i{this->end()}; i != it; --i){
            *i = *(i-1);
        }
        _size++;
        *it = source;
    }

    void erase(iterator it){
        for(iterator i{it}; i != end() - 1; --i){
            *i = *(i+1);
        }
        _size--;
    }
};

#endif //OP_ONCPP_CIRCLE_BUF_H
