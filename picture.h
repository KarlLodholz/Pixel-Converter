#ifndef PICTURE_H
#define PICTURE_H

#include "pixel.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

class Picture {
public:
    //used to set a range of values determined from the file
    int h_v, l_v, h_s, l_s;
    
    //prob def gonna change
    int num_gradients = 5;
    
    std::vector<Pixel> pixel;

    std::string file_name;
    std::string picture_name;
    
    //ppm header stuff
    std::string type;
    int x_size,y_size;
    int intensity;

    Picture(const std::string& file_name, const std::string& picture_name);

    void print(const std::string& low_value_color_hex, const std::string& low_saturation_color_hex, const std::string& high_saturation_color_hex);

private:
    void update_range(Pixel &p);
};

//do not include # in hex number and use Capital letters only
int hex_to_int(const std::string& hex) {
    int num = 0;
    for(int i = 0; i < hex.size(); i++)
        num += (hex[i]-(hex[i]>57? 65:48))*std::pow(16,hex.size()-1-i);
    return num;
}

Picture::Picture(const std::string& file_name, const std::string& picture_name) {
    this -> file_name = file_name;
    this -> picture_name = picture_name;
    
    //read file and fill in pixel
    std::ifstream f;
    std::string b0,b1,b2;
    f.open(file_name);
    f.seekg(3);
    f>>x_size;
    f>>y_size;
    f>>intensity;
    for(int i=0;i<x_size*y_size;i++) {
        f>>b0;f>>b1;f>>b2;
        pixel.push_back(Pixel(std::stoi(b0),std::stoi(b1),std::stoi(b2)));
        update_range(pixel[i]);
    }
    f.close();

    //assigning textures
    for(int i = 0; i < x_size*y_size; i++)
        pixel[i].texture = pixel[i].get_s() / ((h_s-l_s) / (num_gradients-(pixel[i].get_v() / ((h_v-l_v) / num_gradients))));       
}

void Picture::print(const std::string& low_value_color_hex, const std::string& low_saturation_color_hex, const std::string& high_saturation_color_hex) {

    //color hexes broken down into rgb
    int h_sat_r, h_sat_g, h_sat_b;
    int l_sat_r, l_sat_g, l_sat_b;
    int l_val_r, l_val_g, l_val_b;

    l_val_r = hex_to_int(low_value_color_hex.substr(0,2));
    l_val_g = hex_to_int(low_value_color_hex.substr(2,2));
    l_val_b = hex_to_int(low_value_color_hex.substr(4,2));

    l_sat_r = hex_to_int(low_saturation_color_hex.substr(0,2));
    l_sat_g = hex_to_int(low_saturation_color_hex.substr(2,2));
    l_sat_b = hex_to_int(low_saturation_color_hex.substr(4,2));

    h_sat_r = hex_to_int(high_saturation_color_hex.substr(0,2));
    h_sat_g = hex_to_int(high_saturation_color_hex.substr(2,2));
    h_sat_b = hex_to_int(high_saturation_color_hex.substr(4,2));

    std::vector<int> pic;
    for(int i=0; i<pixel.size()*4; i++) {
        // pic[i*2] = get_color_temp(pixel[i].texture,0);
        // pic[i*2+1] = get_color_temp(pixel[i].texture,0);
        // pic[i*2+1]
    }

    std::ofstream p;
    p.open(picture_name+".ppm");
    //header
    p<<type<<" "<<x_size<<" "<<y_size<<" "<<intensity<<"\n";
    //body of ppm
    for(int i=0; i<pixel.size(); i++) {

        // p<<pixel[i].r<<' ';
        // p<<pixel[i].g<<' ';
        // p<<pixel[i].b<<"\t";
    }
    p.close();
}

void Picture::update_range(Pixel& p) {
    if(p.get_s() < l_s) l_s = p.get_s();
    if(p.get_s() > h_s) h_s = p.get_s();
    if(p.get_v() < l_v) l_v = p.get_v();
    if(p.get_v() > h_v) h_v = p.get_v();
}

#endif