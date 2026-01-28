#include "Testbench.h"
#include "sysc/kernel/sc_time.h"
#include <iostream>

void Testbench::driver(void) {
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                a = i ? true : false;
                b = j ? true : false;
                cin = k ? true : false;
                std::cout << "a: " << a << ", "
                          << "b: " << b << ", "
                          << "cin: " << cin << " @ " << sc_time_stamp() << ";"
                          << std::endl;

                wait(1, SC_NS);
                wakeup_monitor.notify(SC_ZERO_TIME);
                wait(wakeup_driver);
            }
        }
    }

    sc_stop();
}

void Testbench::monitor(void) {
    for (;;) {
        wait(wakeup_monitor);

        std::cout << "sum: " << sum << ", "
                  << "cout: " << cout << " @ " << sc_time_stamp() << ";"
                  << std::endl;

        int expected = a + b + cin;

        bool expected_sum = expected & 0x01;
        bool expected_cout = (expected >> 1) & 0x01;

        if (sum != expected_sum) {
            SC_REPORT_ERROR("ADDER_FAIL", "Sum mismatch detected.");
        }

        if (cout != expected_cout) {
            SC_REPORT_ERROR("ADDER_FAIL", "Cout mismatch detected.");
        }

        wait(1, SC_NS);
        wakeup_driver.notify(SC_ZERO_TIME);
    }
}
