#ifndef SHARED_PTR
#define SHARED_PTR

#include <vector>

template<class T>
class SharedPtr{
public:
    SharedPtr(T *sp = nullptr);
    SharedPtr(const SharedPtr<T> &sp);
    ~SharedPtr();
    int use_count() const;
    T *get();
    void reset();
    void reset(T *sp);
    SharedPtr<T>& operator=(const SharedPtr<T> &sp);
    T &operator*();
    T *operator->();
    operator bool() const;

private:
    T *_p;
    int *usecount;
};

template <class T>
SharedPtr<T> make_shared(T t);

#include <shared_ptr.hpp>

#endif //SHARED_PTR