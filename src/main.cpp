#include "displayout.h"
#include "Base.h"
#include "FileIO.h"


int main() {
    displayout dis;

    dis.out(D_INFO, "Does this work");
	dis.out(D_ERROR, "Stinky poo");

    for (int i = 0; i < 10; i++) {
        static int d = 0;
        d++;

        std::cout << d << std::endl;
        


    }
    
    
 


	usleep(1000);
	return 0; // closing the program
}

