#include "FileIO.h"


FileIO::FileIO(std::string FileName) {
    dis.out(D_INFO, "File IO class is loading file: " + FileName);
    
    ReadFile(FileName);

    dis.out(D_INFO, "Starting the loading Thread");

    this->StartThread();
}

FileIO::FileIO() {
    // This has no input for a file to read
    dis.out(D_INFO, "File IO class has no input!");

    this->StartThread();
}

void FileIO::StartThread() {
    Loading_Thread = std::thread(&FileIO::LoadingThread, this); // starts the thread

    
}


void FileIO::ReadFile(std::string Filename) {
    LoadOperation.push_back(__LOAD_READ_FILE);
    EnumPlusData.push_back(Filename);



}


// Handles the main ops like reading and writing to files, this will also handle the vectors for smooth memery 
void FileIO::LoadingThread() {

    dis.out(D_INFO, "File Thread Has Started");


    while(!ToldToQuit) { 

        for(auto i : LoadOperation) { // to step throgh all of the buffer

            if (i == __LOAD_READ_FILE) {

                if (EnumPlusData.size() < 1) { // this is to find if the vector has anything in it
                    dis.out(D_ERROR, "\'EnumPlusData\' does not have any members to access!");
                    break;
                }

                std::string Line;
                std::ifstream File (EnumPlusData[0]);

                if (File.is_open())
                {
                    while ( std::getline (File, Line) )
                    {

                    FileContent.push_back(Line);
                    
                    }
                    File.close(); // ends the data stream

                    dis.out(D_INFO, "Read File with name --> \"" + EnumPlusData[0] + "\"");

                    // DEBUG ONLY ============================
                    std::string AllFileContent = "";
                    for (auto i : FileContent) {
                        AllFileContent += i + "\n";
                    }
                    dis.out(D_FILE, "FILE: " + EnumPlusData[0] + "  ==============\n" + AllFileContent);
                    //========================================
                }
 
                else dis.out(D_ERROR, "No File to Read with name --> \"" + EnumPlusData[0] + "\""); 

                EnumPlusData.erase(EnumPlusData.begin()); // takes out the pos that we just read
            }
            
        }

        LoadOperation.clear();

        usleep(99); // to keep this thread from using all CPU by just running

    }

    dis.out(D_WARNING, "File Thread was told to quit");
}



FileIO::~FileIO() {
    dis.out(D_INFO, "Quitting File Threads");

    ToldToQuit = true;

    while(!Loading_Thread.joinable()); // This could cause a hold if the thread is stuck

    Loading_Thread.join();

    dis.out(D_INFO, "File Thread joined!");
}