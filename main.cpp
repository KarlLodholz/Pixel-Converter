#include "picture.h"

int main() {    
    std::string f_name, p_name;
    std::string h_s,l_s,l_v;

    std::cout<<"enter file name: ";
    std::cin>>f_name;

    std::cout<<"enter high saturation color hex: "<<std::endl;
    std::cin>>h_s;

    std::cout<<"enter low saturation color hex: "<<std::endl;
    std::cin>>l_s;

    std::cout<<"enter low value color hex: "<<std::endl;
    std::cin>>l_v;

    Picture p(f_name,p_name,l_v,l_s,h_s);
    p.print();

    return 0;
}