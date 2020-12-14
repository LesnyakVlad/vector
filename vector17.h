#ifndef VECTOR_VECTOR17_H
#define VECTOR_VECTOR17_H


class vector_17
{
    int sz;
    double* elem;
public:
    vector_17(int s) : sz {s}, elem {new double [s]}
    {
        for (int i = 0; i < s; ++i)
            elem[i] = 0;
    }

    ~vector_17() {delete [] elem; }
    int size() const { return sz; }

    double get (int n) const { return elem [n]; }
    void set (int n, double v) { elem[n] = v; }
};



#endif //VECTOR_VECTOR17_H
