#include "Base.h"
#include "displayout.h"


int main() {

    displayout dis;

    dis.out(D_DEBUG, "out message");
    dis.out(D_ERROR, "WOW THAT IS AN ERROR");
    
    for (int i = 0; i < 150; i++)
    {
            dis.out(D_INFO, std::to_string(i));
            dis.out(D_INFO, std::to_string(i));
            dis.out(D_INFO, std::to_string(i));
            dis.out(D_INFO, std::to_string(i));
    }
    
    

    
    



    usleep(1000); // holds the program for the threads to stop
}