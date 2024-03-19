#include <exception>

template<class T>
UniquePtr<T>::UniquePtr(T* ptr)
: _p(ptr) {}

template <class T>
UniquePtr<T> make_unique(T t){
    return UniquePtr<T>(new T(t));
}

template <class T>
UniquePtr<T>::UniquePtr(const UniquePtr<T> &up){
    throw std::logic_error("unique_ptr cannot be copied!");
}

template <class T>
UniquePtr<T>::~UniquePtr(){
    delete _p;
    _p = nullptr;
}

template <class T>
void UniquePtr<T>::operator=(const UniquePtr<T> &up){
    throw std::logic_error("unique_ptr cannot be copied!");
}

template <class T>
T* UniquePtr<T>::get(){
    return _p;
}

template <class T>
T& UniquePtr<T>::operator*(){
    return *_p;
}

template <class T>
T* UniquePtr<T>::operator->(){
    return _p;
}

template <class T>
UniquePtr<T>::operator bool() const{
    return _p!= nullptr;
}

template <class T>
void UniquePtr<T>::reset(){
    delete _p;
    _p = nullptr;
}

template <class T>
void UniquePtr<T>::reset(T* ptr){
    delete _p;
    _p = ptr;
}

template <class T>
T* UniquePtr<T>::release(){
    T* tmp = _p;
    _p = nullptr;
    return tmp;
}