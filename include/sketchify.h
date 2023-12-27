#ifndef SKETCHIFY_H
#define SKETCHIFY_H

#include "image.h"

namespace IS {

void sketchify(const Image& src_img, Image& out_img);

// basic process functions
void grayscale(Image& img);

void invert(Image& img);

void Gaussian_blur(Image& img);

} // namespace IS

#endif // SKETCHIFY_H
