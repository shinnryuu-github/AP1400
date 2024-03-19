template<class T>
SharedPtr<T>::SharedPtr(T *sp)
: _p(sp), usecount(new int(0)){
    if (_p != nullptr)
        *usecount = 1;
}

template <class T>
SharedPtr<T> make_shared(T t){
    return SharedPtr<T>(new T(t));
}

template<class T>
SharedPtr<T>::~SharedPtr(){
    if (*usecount > 1){
        *usecount -= 1;
        _p = nullptr;
    }
    else if (*usecount == 1){
        delete _p;
        _p = nullptr;
        *usecount = 0;
    }
}

template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &sp)
: _p(sp._p), usecount(sp.usecount) {
    if (_p != nullptr && &sp != this)
        *usecount += 1;
}

template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T> &sp){
    _p = sp._p;
    usecount = sp.usecount;
    if (_p != nullptr && &sp != this)
        *usecount += 1;
    return *this;
}

template<class T>
int SharedPtr<T>::use_count() const{
    return *usecount;
}

template<class T>
T* SharedPtr<T>::get(){
    return _p;
}

template<class T>
T& SharedPtr<T>::operator*(){
    return *_p;
}

template<class T>
T* SharedPtr<T>::operator->(){
    return _p;
}

template<class T>
void SharedPtr<T>::reset(){
    if (*usecount > 1){
        *usecount -= 1;
        _p = nullptr;
    }
    else if (*usecount == 1){
        delete _p;
        _p = nullptr;
        *usecount = 0;
    }
}

template<class T>
void SharedPtr<T>::reset(T *sp){
    if (*usecount > 1)
        *usecount--;
    else if (*usecount == 1)
        delete _p;
    _p = sp;
    usecount = new int(0);
    if (_p != nullptr)
        *usecount = 1;
}

template<class T>
SharedPtr<T>::operator bool() const{
    return _p != nullptr;
}