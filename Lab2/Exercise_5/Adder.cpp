#include "Adder.h"

void Adder::add(void) {
    sum = a ^ b ^ cin;
    cout = (a & b) ^ (cin & (a ^ b));
}
