#include "Base.h"
#include "displayout.h"
#include "FileIO.h"

// Main Thread
int main() {
    displayout dis;
    dis.out(D_INFO, "Starting Main Thread");

    FileIO file;

    file.ReadFile("test.txt");
    



    usleep(10000); // holds the program for the threads to stop
}