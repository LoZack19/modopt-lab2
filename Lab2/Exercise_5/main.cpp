#include "Adder.h"
#include "Testbench.h"
#include "systemc.h"

int sc_main(int argc, char *argv[]) {
    // ---------------------------------------------------------
    // 0. CONFIGURATION: Prevent Hard Crashes
    // ---------------------------------------------------------
    // By default, SystemC might stop on the first error. We change this
    // to just DISPLAY the error and continue, so we can count them all.
    sc_report_handler::set_actions(SC_ERROR, SC_DISPLAY);

    // ---------------------------------------------------------
    // 1. INSTANTIATION
    // ---------------------------------------------------------
    Adder adder("adder");
    Testbench testbench("testbench");

    // Signals
    sc_signal<bool> a_sig, b_sig, cin_sig, cout_sig, sum_sig;

    // ---------------------------------------------------------
    // 2. CONNECT SIGNALS (Idiomatic "Functor" Style)
    // ---------------------------------------------------------
    // SystemC allows you to treat ports like functions to bind signals.
    // This is cleaner and more readable than using .bind() repeatedly.

    // Connect Adder
    adder.a(a_sig);
    adder.b(b_sig);
    adder.cin(cin_sig);
    adder.sum(sum_sig);
    adder.cout(cout_sig);

    // Connect Testbench (mirrors the adder)
    testbench.a(a_sig);
    testbench.b(b_sig);
    testbench.cin(cin_sig);
    testbench.sum(sum_sig);
    testbench.cout(cout_sig);

    // ---------------------------------------------------------
    // 3. RUN SIMULATION
    // ---------------------------------------------------------
    sc_start(); // Runs until no more events or sc_stop() is called

    // ---------------------------------------------------------
    // 4. ERROR SUMMARY REPORT
    // ---------------------------------------------------------
    int error_count = sc_report_handler::get_count(SC_ERROR);
    int fatal_count = sc_report_handler::get_count(SC_FATAL);

    std::cout << "\n------------------------------------------------\n";
    std::cout << " SIMULATION SUMMARY\n";
    std::cout << "------------------------------------------------\n";

    if (error_count == 0 && fatal_count == 0) {
        std::cout << " STATUS: PASSED \n";
        return 0; // Return 0 to OS (Success)
    } else {
        std::cout << " STATUS: FAILED \n";
        std::cout << " ERRORS: " << error_count << "\n";
        std::cout << " FATALS: " << fatal_count << "\n";
        return 1; // Return non-zero to OS (Failure)
    }

    return 0;
}
