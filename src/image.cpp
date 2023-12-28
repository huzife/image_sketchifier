#include "image.h"
#include "utils.h"

namespace IS {

Image::Image(): width_(0), height_(0) {}

Image::Image(size_t width, size_t height)
    : bgr_(height, width, CV_8UC3),
      width_(width),
      height_(height) {}

Image::Image(std::string file)
    : bgr_(cv::imread(file, cv::IMREAD_COLOR)),
      width_(bgr_.cols),
      height_(bgr_.rows) {}

Image::Image(const Image& rhs)
    : bgr_(rhs.bgr_.clone()),
      width_(rhs.width_),
      height_(rhs.height_) {}

Image& Image::operator=(const Image& rhs) {
    bgr_ = rhs.bgr_.clone();
    width_ = rhs.width_;
    height_ = rhs.height_;

    return *this;
}

Image::Image(Image&& rhs)
    : bgr_(std::move(rhs.bgr_)),
      width_(rhs.width_),
      height_(rhs.height_) {}

Image& Image::operator=(Image&& rhs) {
    bgr_ = std::move(rhs.bgr_);
    width_ = rhs.width_;
    height_ = rhs.height_;

    return *this;
}

size_t Image::width() const {
    return width_;
}

size_t Image::height() const {
    return height_;
}

cv::Mat& Image::bgr() {
    return bgr_;
}

const cv::Mat& Image::bgr() const {
    return bgr_;
}

void Image::set_bgr(const cv::Mat& bgr) {
    bgr_ = bgr.clone();
    width_ = bgr_.cols;
    height_ = bgr_.rows;
}

cv::Mat Image::yuv() {
    cv::Mat ret(height_, width_, CV_8UC3);
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            const auto& pixel = bgr_.at<cv::Vec3b>(i, j);
            auto y = 0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0];
            auto u = 0.564 * (pixel[0] - y);
            auto v = 0.713 * (pixel[2] - y);
            ret.at<cv::Vec3b>(i, j)[0] = constrain(y, 0, 255);
            ret.at<cv::Vec3b>(i, j)[1] = constrain(u, 0, 255);
            ret.at<cv::Vec3b>(i, j)[2] = constrain(v, 0, 255);
        }
    }

    return ret;
}

void Image::set_yuv(const cv::Mat& yuv) {
    width_ = yuv.cols;
    height_ = yuv.rows;
    bgr_ = cv::Mat(height_, width_, CV_8UC3);
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            const auto& pixel = yuv.at<cv::Vec3b>(i, j);
            auto r = pixel[0] + 1.402 * pixel[2];
            auto g = pixel[0] - 0.344 * pixel[1] - 0.714 * pixel[2];
            auto b = pixel[0] + 1.772 * pixel[1];
            bgr_.at<cv::Vec3b>(i, j)[0] = constrain(b, 0, 255);
            bgr_.at<cv::Vec3b>(i, j)[1] = constrain(g, 0, 255);
            bgr_.at<cv::Vec3b>(i, j)[2] = constrain(r, 0, 255);
        }
    }
}

void Image::show(const std::string& name, uint32_t time) const {
    cv::namedWindow(name, cv::WINDOW_NORMAL);
    cv::imshow(name, bgr_);
    cv::waitKey(time);
}

} // namespace IS
