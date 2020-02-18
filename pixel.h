#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>
#include <math.h>

class Pixel {
public:
    const static int TWO_PIX_NUM = 3012;
    int r,g,b;
    int v_num,s_num;
    
    Pixel(const int& r, const int& g, const int& b);
    
    int get_s();
    int get_v();
    int texture(); 
};

Pixel::Pixel(const int& r, const int& g, const int& b) {
    this -> r = r;
    this -> g = g;
    this -> b = b;
};

int Pixel::get_s() {
    int l = r;
    int h = get_v();
    if(l > g) l = g;
    if(l > b) l = b;
    return (h-l)/(h?h:1); // dont wanna / by 0
}

int Pixel::get_v() {
    int h = r;
    if(h < g) h = g;
    if(h < b) h = b;
    return h;
}

int Pixel::texture() {
    int temp = 0;
    for(int i=0; i<4; i++) {
        if(i < v_num) temp += std::pow(10 ,TWO_PIX_NUM % (int)(std::pow(10,4-i)) / std::pow(10,4-1-i));
        if(i < s_num) temp += 2*std::pow(10 ,TWO_PIX_NUM % (int)(std::pow(10,i+1) / std::pow(10,i)));
    }
    //TWO_PIX_NUM.substring(v_num-5,1);
    return temp;
}

#endif