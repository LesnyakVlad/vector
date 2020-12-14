#include "std_lib_facilities.h"
#ifndef VECTOR_18_VECTOR_18_H
#define VECTOR_18_VECTOR_18_H


using namespace std;

class vector_18
{
    int sz;
    double* elem;
public:
    explicit vector_18(int s)
            : sz {s}, elem {new double [s]}
    {
        for (int i = 0; i < s; ++i)
            elem[i] = 0;
    }

    vector_18(initializer_list<double> lst) : sz {static_cast<int>(lst.size())}, elem {new double[sz]}
    {
        copy(lst.begin(), lst.end(), elem);
    }

    vector_18(const vector_18& arg)
            : sz{arg.sz}, elem{new double[arg.sz]}
    {
        copy(arg.elem, arg.elem + arg.sz, elem);
    }

    vector_18& operator = (const vector_18& arg)
    {
        double* p = new double[arg.sz];
        copy(arg.elem, arg.elem+arg.sz, p);
        delete[] elem;
        elem = p;
        sz = arg.sz;
        return *this; //возврат ссылки на ссебя
    }

    vector_18(vector_18&& a)
            : sz{a.sz}, elem{a.elem}
    {
        a.sz = 0;
        a.elem = nullptr;
    }

    vector_18& operator=(vector_18&& a)
    {
        delete[] elem;
        elem = a.elem;
        sz = a.sz;
        a.elem = nullptr;
        a.sz = 0;
        return *this;
    }

    ~vector_18() {delete [] elem; }
    int size() const { return sz; }
    double& operator[](int n) { return elem[n]; }
    const double& operator [] (int n) const { return elem[n]; }

    double get (int n) const { return elem [n]; }
    void set (int n, double v) { elem[n] = v; }
};

#endif //VECTOR_18_VECTOR_18_H
