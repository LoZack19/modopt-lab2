#ifndef TESTBENCH_H
#define TESTBENCH_H

#include "systemc.h"

SC_MODULE(Testbench) {
    sc_in<bool> sum;
    sc_in<bool> cout;
    sc_out<bool> a;
    sc_out<bool> b;
    sc_out<bool> cin;

    sc_event wakeup_driver;
    sc_event wakeup_monitor;

    SC_CTOR(Testbench) {
        SC_THREAD(driver);
        SC_THREAD(monitor);
    }

    void driver(void);
    void monitor(void);
};

#endif // TESTBENCH_H
