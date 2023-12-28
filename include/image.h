#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <cstdint>
#include <string>

namespace IS {

class Image {
public:
    Image();
    Image(std::size_t width, std::size_t height);
    explicit Image(std::string file);

    Image(const Image& rhs);
    Image& operator=(const Image& rhs);
    Image(Image&& rhs);
    Image& operator=(Image&& rhs);

    // member functions
    std::size_t width() const;
    std::size_t height() const;

    cv::Mat& bgr();
    const cv::Mat& bgr() const;
    void set_bgr(const cv::Mat& bgr);

    cv::Mat yuv();
    void set_yuv(const cv::Mat& yuv);

    void show(const std::string& name, uint32_t time = 0) const;

private:
    cv::Mat bgr_;
    std::size_t width_;
    std::size_t height_;
};

} // namespace IS

#endif // IMAGE_H
