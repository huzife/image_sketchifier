#include "utils.h"

namespace IS {

double constrain(double num, double lower, double upper) {
    if (lower > upper) {
        return num;
    }

    if (num < lower) {
        return lower;
    } else if (num > upper) {
        return upper;
    }

    return num;
}

} // namespace IS
