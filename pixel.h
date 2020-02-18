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
    int h = get_v();
    int l = r;
    if(l > g) l = g;
    if(l > b) l = b;
    return !h?h:(int)(h-(l/255.0*100)/h);
}

int Pixel::get_v() {
    int h = r;
    if(h < g) h = g;
    if(h < b) h = b;
    return h/255.0*100; //intensity
}

int Pixel::texture() {
    int temp = 0,tempf;
    for(int i=0; i<4; i++) {
        //std::cout<<"v:"<<v_num<<" s:"<<s_num<<std::endl<<temp<<'\n';
        if(i < v_num-1) temp += std::pow(10 ,(TWO_PIX_NUM % (int)(std::pow(10,4-i)) / (int)std::pow(10,4-1-i)));
        if(i < s_num-1) temp += 2*std::pow(10 ,TWO_PIX_NUM % (int)(std::pow(10,i+1) / (int)std::pow(10,i)));
    }
    //TWO_PIX_NUM.substring(v_num-5,1);
    return temp;
}

#endif