#include "sketchify.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Too less arguments" << endl;
        return 1;
    }

    IS::Image src{argv[1]};
    IS::Image out;

    IS::sketchify(src, out,
                  std::strtod(argv[3], nullptr),
                  std::strtol(argv[4], nullptr, 10));
    cv::imwrite(argv[2], out.bgr());

    return 0;
}
