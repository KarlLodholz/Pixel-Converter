#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
public:
    int r,g,b;
    int texture;
    
    Pixel(const int& r, const int& g, const int& b);
    
    int get_s();
    int get_v();
};

Pixel::Pixel(const int& r, const int& g, const int& b) {
    this -> r = r;
    this -> g = g;
    this -> b = b;
};

int Pixel::get_s() {
    return 0;
}

int Pixel::get_v() {
    return 0;
}

#endif