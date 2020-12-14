#ifndef VECTOR19_VECTOR_19_H
#define VECTOR19_VECTOR_19_H

#include <iostream>
#include "std_lib_facilities.h"
#include <iterator>


using namespace std;


template <class T, class A> class vector19_base
{
public:
    using size_type = std::size_t;
    A alloc;
    size_type sz;
    T* elem;
    size_type space;
    vector19_base(A a, size_type n) : alloc{ a }, sz{ n }, elem{ a.allocate(n) }, space{n}
    {}
    ~vector19_base() { alloc.deallocate(elem, space); }
};

template <class T, class A = std::allocator<T>>
class vector19 : private vector19_base<T, A>
{
public:

    using size_type = typename vector19_base<T, A>::size_type;
    explicit vector19 (size_type s, T def = T(), A alloc = A());
    vector19 (initializer_list <T> lst, A alc = A());
    vector19 (const A& alloc = A()): vector19_base<T, A> (alloc, 0)
    {}
    vector19 (const vector19& v); //копирующий конструктор
    vector19& operator = (const vector19& v); //копирующее присваивание
    vector19 (vector19&& v); //перемещающий конструктор
    vector19& operator = (vector19&& v); //перемещающее присваивание
    ~vector19()
    {
        for(size_type i = 0; i < this -> sz; ++i)
            this -> alloc.destroy(this -> elem + i);
    }
    T& at(size_type n);
    const T& at(size_type n) const;
    T& operator[](size_type i) { return this -> elem[i]; }
    const T& operator[](size_type i) const { return this -> elem[i]; }
    size_type size() const { return this -> sz; }
    size_type capacity() const { return this -> space; }
    auto begin() { return  this -> elem; }
    auto cbegin() const { return this -> elem; }
    auto cend() const { return this -> elem + this -> sz;}
    auto end() { return (this -> elem + this -> sz); }
    void reserve (size_type newalloc);
    void push_back(const T& val);
    void resize (size_type newsize, T val = T());
};



template<class T, class A>
vector19<T, A>::vector19 (size_type s, T def, A alc)
        : vector19_base<T, A> (alc, s)
{
    for (size_type i = 0; i < this -> size(); ++i)
        this -> alloc.construct(&this -> elem[i], def);
}

template<class T, class A>
vector19<T, A>::vector19 (std::initializer_list<T> lst, A alc)
        : vector19_base<T, A> (alc, lst.size())
{
    for (size_type i = 0; i < this->size(); ++i)
        this -> alloc.construct(&this->elem[i], *(lst.begin() + i));
}

template<class T, class A>
vector19<T, A>::vector19 (const vector19<T, A>& v) : vector19_base<T, A> (v.alloc, v.sz)
{
    for(size_type i = 0; i < this -> sz; ++i)
        this -> alloc.construct(&this -> elem[i], v[i]); //копирующий конструктор
}

template<class T, class A>
vector19<T, A>::vector19 (vector19<T, A>&& v) : vector19_base<T, A> (v.alloc, v.size())  //перемещающий конструктор
{
    this->elem = v.elem;
    v.sz = 0;
    v.elem = nullptr;
}

template<class T, class A>
T& vector19<T, A>::at(size_type n)
{ if (n < 0 or !(this -> sz > n))
        throw std::out_of_range("Range error " + std::to_string(n)); //проверка на выход за границы
    return this -> elem[n] ;
}

template<class T, class A>
vector19<T, A>& vector19<T,A>::operator = (const vector19<T, A>& v)
{
    if (this == &v)
        return *this;
    vector19_base<T, A> b{this -> alloc, v.sz};
    std::uninitialized_copy(& v[0], &v[v.size()], b.elem);
    std::swap (this -> elem, b.elem);
    std::swap (this -> sz, b.sz);
    std::swap (this -> space, b.space);
    for(size_type i = 0; i < b.sz; ++i)
        b.alloc.destroy(b.elem + i);
    return *this;
}

template<class T, class A>
vector19<T, A>& vector19<T,A>::operator = (vector19<T,A>&& v)
{
    
    std::swap (this->elem, v.elem);
    std::swap (this->sz, v.sz);
    std::swap (this->space, v.space);
    return *this;
}

template<class T, class A>
void vector19<T, A>::reserve (size_type newalloc)
{
    if (newalloc <= this -> space) return;
    vector19_base<T, A> b (this -> alloc, newalloc) ;
    uninitialized_copy(&this -> elem[0], &this -> elem[this -> sz], b.elem);

    for(size_type i = 0; i < this -> sz; ++i)
        this -> alloc.destroy( &this -> elem[i]);
        std::swap (this -> elem, b.elem);
    std::swap (this -> sz, b.sz);
    std::swap (this -> space, b.space);
}

template<class T, class A>
void vector19<T, A>::push_back(const T& val)
{
    if (this -> space == 0)
        reserve(8) ;
    else if (this -> sz == this -> space)
        reserve (2 * this -> space);
    this -> alloc.construct(this -> elem + this -> sz, val) ;
    ++ this -> sz;
}

template<class T, class A>
void vector19<T, A>::resize (size_type newsize, T val)
{
    reserve (newsize);
    for(size_type i = this -> sz; i < newsize; ++i)
        this -> alloc.construct(&this -> elem[i], val);
    for(size_type i = newsize; i < this -> sz; ++i)
        this -> alloc.destroy(&this -> elem[i]);
    this -> sz = newsize;
}



#endif //VECTOR19_VECTOR_19_H
