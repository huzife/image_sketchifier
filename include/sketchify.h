#ifndef SKETCHIFY_H
#define SKETCHIFY_H

#include "image.h"

namespace IS {

void sketchify(const Image& src_img, Image& out_img, double sigma, int r);

// basic process functions
void grayscale(Image& img);

void invert(Image& img);

void Gaussian_blur(Image& img, double sigma, int r);

} // namespace IS

#endif // SKETCHIFY_H
