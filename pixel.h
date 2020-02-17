#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
public:
    int r,g,b;
    int v_num,s_num;
    
    Pixel(const int& r, const int& g, const int& b);
    
    int get_s();
    int get_v();
    std::string texture();    
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

std::string Pixel::texture() {
    std::string temp = "0000";
    for(int i=0; i<4; i++) {
        temp[0] = v_num;
    }
    return temp;
}

#endif