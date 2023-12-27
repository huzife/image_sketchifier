#include "sketchify.h"

namespace IS {

void sketchify(const Image &src_img, Image &out_img) {
    out_img = src_img;

    grayscale(out_img);
    // invert(out_img);
    // Gaussian_blur(out_img);
}

void grayscale(Image &img) {
    auto yuv = img.yuv();
    for (int i = 0; i < img.height(); ++i) {
        for (int j = 0; j < img.width(); ++j) {
            yuv.at<cv::Vec3b>(i, j)[1] = 0;
            yuv.at<cv::Vec3b>(i, j)[2] = 0;
        }
    }

    img.set_yuv(yuv);
}

void invert(Image &img) {
    auto& bgr = img.bgr();
    for (int i = 0; i < img.height(); ++i) {
        for (int j = 0; j < img.width(); ++j) {
            auto& pixel = bgr.at<cv::Vec3b>(i, j);
            pixel = cv::Vec3b{255, 255, 255} - pixel;
        }
    }
}

} // namespace IS
