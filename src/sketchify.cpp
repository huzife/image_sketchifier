#include "sketchify.h"
#include "utils.h"

namespace IS {

void sketchify(const Image& src_img, Image& out_img, double sigma, int r) {
    out_img = src_img;

    // get gray image
    grayscale(out_img);
    auto gray = out_img;

    // invert image
    invert(out_img);

    // gaussian blur
    Gaussian_blur(out_img, sigma, r);

    auto gaussian_yuv = out_img.yuv();
    auto out_yuv = gray.yuv();
    for (int i = 0; i < out_img.height(); ++i) {
        for (int j = 0; j < out_img.width(); ++j) {
            auto& g_pixel = gaussian_yuv.at<cv::Vec3b>(i, j);
            auto& o_pixel = out_yuv.at<cv::Vec3b>(i, j);
            double val = (o_pixel[0] +
                             (double)(o_pixel[0] * g_pixel[0]) /
                             (255 - g_pixel[0])) * 0.97;
            o_pixel[0] = std::min(val, 255.0);
        }
    }

    out_img.set_yuv(out_yuv);
}

void grayscale(Image& img) {
    auto yuv = img.yuv();
    for (int i = 0; i < img.height(); ++i) {
        for (int j = 0; j < img.width(); ++j) {
            yuv.at<cv::Vec3b>(i, j)[1] = 0;
            yuv.at<cv::Vec3b>(i, j)[2] = 0;
        }
    }

    img.set_yuv(yuv);
}

void invert(Image& img) {
    auto& bgr = img.bgr();
    for (int i = 0; i < img.height(); ++i) {
        for (int j = 0; j < img.width(); ++j) {
            auto& pixel = bgr.at<cv::Vec3b>(i, j);
            pixel = cv::Vec3b{255, 255, 255} - pixel;
        }
    }
}

// Gaussian Blur
int edge(int x, int offset, int bound) {
    int ret = x + offset;
    return (ret < 0 || ret >= bound) ? x - offset : ret;
}

double gaussian_1d(int x, double sigma) {
    return (1 / sigma * std::sqrt(2 * 2*3.1415926535)) *
               std::exp(-1.0 * (x * x) / (2 * sigma * sigma));
}

std::vector<double> get_weight(int r, double sigma) {
    std::vector<double> weight(2 * r + 1);
    double sum = 0;

    for (int i = 0; i < 2 * r + 1; ++i) {
        weight[i] = gaussian_1d(i - r, sigma);
        sum += weight[i];
    }

    for (auto& i : weight) {
        i /= sum;
    }

    return weight;
}

void Gaussian_blur(Image& img, double sigma, int r) {
    cv::Mat out = img.bgr();
    auto orig = out.clone();
    auto weight = get_weight(r, sigma);

    for (int y = 0; y < img.height(); ++y) {
        for (int x = 0; x < img.width(); ++x) {
            double red = 0;
            double green = 0;
            double blue = 0;
            for (int i = -r; i <= r; ++i) {
                auto index = edge(x, i, img.width());
                auto& pixel = orig.at<cv::Vec3b>(y, index);
                red += pixel[2] * weight[i + r];
                green += pixel[1] * weight[i + r];
                blue += pixel[0] * weight[i + r];
            }

            out.at<cv::Vec3b>(y, x)[0] = constrain(red, 0, 255);
            out.at<cv::Vec3b>(y, x)[1] = constrain(green, 0, 255);
            out.at<cv::Vec3b>(y, x)[2] = constrain(blue, 0, 255);
        }
    }

    orig = out.clone();
    for (int y = 0; y < img.height(); ++y) {
        for (int x = 0; x < img.width(); ++x) {
            double red = 0;
            double green = 0;
            double blue = 0;
            for (int i = -r; i <= r; ++i) {
                auto index = edge(y, i, img.width());
                auto& pixel = orig.at<cv::Vec3b>(index, x);
                red += pixel[2] * weight[i + r];
                green += pixel[1] * weight[i + r];
                blue += pixel[0] * weight[i + r];
            }

            out.at<cv::Vec3b>(y, x)[0] = constrain(red, 0, 255);
            out.at<cv::Vec3b>(y, x)[1] = constrain(green, 0, 255);
            out.at<cv::Vec3b>(y, x)[2] = constrain(blue, 0, 255);
        }
    }

    img.set_bgr(out);
}

} // namespace IS
