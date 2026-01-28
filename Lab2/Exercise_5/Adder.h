#ifndef ADDER_H
#define ADDER_H

#include "systemc.h"

SC_MODULE(Adder) {
    sc_in<bool> a;
    sc_in<bool> b;
    sc_in<bool> cin;
    sc_out<bool> sum;
    sc_out<bool> cout;

    SC_CTOR(Adder) {
        SC_METHOD(add);
        sensitive << a << b << cin;
    }

    void add(void);
};

#endif // ADDER_H
