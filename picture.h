#ifndef PICTURE_H
#define PICTURE_H

#include "pixel.h"

#include <vector>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    l_s = l_v = intensity; 
    h_s = h_v = 0;

    for(int i=0;i<x_size*y_size;i++) {
        f>>b0;f>>b1;f>>b2;
        pixel.push_back(Pixel(std::stoi(b0),std::stoi(b1),std::stoi(b2)));
        //std::cout<<pixel[i].get_v()<<" "<<pixel[i].get_s()<<std::endl;
        update_range(pixel[i]);
    }
    f.close();

    //assigning textures
    for(int i = 0; i < x_size*y_size; i++) {
        pixel[i].v_num = num_gradients - pixel[i].get_v() / (((h_v-l_v)/num_gradients)?((h_v-l_v)/num_gradients):1);
        pixel[i].s_num = pixel[i].get_s() / ((h_s-l_s) / (pixel[i].v_num+1));    
    }   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Picture::print(const std::string& low_value_color_hex, const std::string& low_saturation_color_hex, const std::string& high_saturation_color_hex) {

    //color hexes broken down into rgb
    int h_sat_r, h_sat_g, h_sat_b;
    int l_sat_r, l_sat_g, l_sat_b;
    int l_val_r, l_val_g, l_val_b;

    l_val_r = std::stoi(low_value_color_hex.substr(0,2),0,16);
    l_val_g = std::stoi(low_value_color_hex.substr(2,2),0,16);
    l_val_b = std::stoi(low_value_color_hex.substr(4,2),0,16);

    l_sat_r = std::stoi(low_saturation_color_hex.substr(0,2),0,16);
    l_sat_g = std::stoi(low_saturation_color_hex.substr(2,2),0,16);
    l_sat_b = std::stoi(low_saturation_color_hex.substr(4,2),0,16);

    h_sat_r = std::stoi(high_saturation_color_hex.substr(0,2),0,16);
    h_sat_g = std::stoi(high_saturation_color_hex.substr(2,2),0,16);
    h_sat_b = std::stoi(high_saturation_color_hex.substr(4,2),0,16);

    std::vector<int> pic(pixel.size()*4, 0);
    int temp;
    for(int y=0; y<y_size; y++) {
        for(int x=0; x<x_size; x++) {
            temp = pixel[y*x_size+x].texture();
            pic[(y*x_size+x+y*x_size)*2] = temp%10;
            pic[(y*x_size+x+y*x_size)*2+1] = temp%100/10;
            pic[(y*x_size+x+y*x_size)*2+x_size*2] = temp%1000/100;
            pic[(y*x_size+x+y*x_size)*2+x_size*2+1] = temp%10000/1000;
        }
    }
    std::ofstream p;
    p.open(picture_name+".ppm");
    //header
    p<<"P3"<<" "<<x_size*2<<" "<<y_size*2<<" "<<intensity<<"\n";
    //body of ppm
    for(int i=0; i<pic.size(); i++) {
       //std::cout<<pic[i]<<std::endl;
        if(pic[i] == 0) {
            p<<l_sat_r<<' '<<l_sat_g<<' '<<l_sat_b<<"\t";
        }
        else if (pic[i] == 1) {
            p<<l_val_r<<' '<<l_val_g<<' '<<l_val_b<<"\t";
        }
        else{
            p<<h_sat_r<<' '<<h_sat_g<<' '<<h_sat_b<<"\t";
        }
        
        if(i && !x_size%i)p<<'\n';
    }
    p.close();

    // testing purposes 
    // p.open("sample.ppm");
    // p<<"P3"<<" "<<x_size<<" "<<y_size<<" "<<intensity<<"\n";
    // for(int i=0; i<pixel.size(); i++) {
    //     p<<pixel[i].r<<" "<<pixel[i].g<<" "<<pixel[i].b<<"\t";
    // }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Picture::update_range(Pixel& p) {
    if(p.get_s() < l_s) l_s = p.get_s();
    if(p.get_s() > h_s) h_s = p.get_s();
    if(p.get_v() < l_v) l_v = p.get_v();
    if(p.get_v() > h_v) h_v = p.get_v();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif