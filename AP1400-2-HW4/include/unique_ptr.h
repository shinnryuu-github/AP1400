#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template<class T>
class UniquePtr{
public:
    UniquePtr(T* ptr = nullptr);
    UniquePtr(const UniquePtr<T> &up);
    ~UniquePtr();
    T* get();
    void operator=(const UniquePtr<T> &up);
    T& operator*();
    T* operator->();
    operator bool() const;
    void reset();
    void reset(T* ptr);
    T* release();
private:
    T *_p;
};

template <class T>
UniquePtr<T> make_unique(T t);

#include "unique_ptr.hpp"

#endif //UNIQUE_PTR