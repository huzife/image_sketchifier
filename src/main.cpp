#include "sketchify.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Too less arguments" << endl;
        return 1;
    }

    IS::Image src{argv[1]};
    IS::Image out;

    IS::sketchify(src, out);
    out.show("out");

    return 0;
}
