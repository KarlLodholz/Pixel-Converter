#ifndef PICTURE_H
#define PICTURE_H

#include "pixel.h"
#include <iostream>
#include <vector>
#include <fstream>

class Picture {
public:
    //used to set a range of values determined from the file
    int h_v, l_v, h_s, l_s;

    //color hexes broken down into rgb
    int h_sat_r, h_sat_g, h_sat_b;
    int l_sat_r, l_sat_g, l_sat_b;
    int l_val_r, l_val_g, l_val_b;
    
    //prob def gonna change
    int num_gradients = 5;
    
    std::vector<std::vector<Pixel> > pixel;

    std::string file_name;
    std::string picture_name;

    Picture(const std::string& file_name, const std::string& picture_name, const std::string& low_value_color_hex, const std::string& low_saturation_color_hex, const std::string& high_saturation_color_hex);

    void print();
};

Picture::Picture(const std::string& file_name, const std::string& picture_name, const std::string& low_value_color_hex, const std::string& low_saturation_color_hex, const std::string& high_saturation_color_hex) {
    this -> file_name = file_name;
    this -> picture_name = picture_name;

    //convert hexes to rgb integers and store


    //read file and fill in pixel


    //assigning textures
    for(int i = 0; i < pixel.size(); i++) {
        for(int j = 0; j < pixel[i].size(); j++) {
            pixel[i][j].texture = pixel[i][j].get_s() / ((h_s-l_s) / (num_gradients-(pixel[i][j].get_v() / ((h_v-l_v) / num_gradients))));       
        }
    }
}

void Picture::print() {
    //print stuff
}

#endif