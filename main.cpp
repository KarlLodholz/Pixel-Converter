#include "picture.h"

int main() {    
    std::string f_name, p_name = "test";
    std::string h_s = "FF6666",l_s="66FF66",l_v="6666FF";

    std::cout<<"enter file name: ";
    std::cin>>f_name;

    std::cout<<"enter picture name: ";
    std::cin>>p_name;

    std::cout<<"enter high saturation color hex: ";
    std::cin>>h_s;

    std::cout<<"enter low saturation color hex: ";
    std::cin>>l_s;

    std::cout<<"enter low value color hex: ";
    std::cin>>l_v;

    std::system(("convert "+f_name+" -compress none temp.ppm").c_str());

    Picture p(p_name);
    p.print(l_v,l_s,h_s);

    std::system("rm temp.ppm");


    return 0;
}