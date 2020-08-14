#include "FileIO.h"


FileIO::FileIO(std::string FileName) {
    //dis.out(D_INFO, "File IO class is loading file: " + FileName);
    
    ReadFile(FileName);
}

FileIO::FileIO() {
    // This has no input for a file to read
    //dis.out(D_INFO, "File IO class has no input!");

}

int FileIO::FileSize(std::string FileName) {
    std::streampos BeginPoint, EndPoint;

    std::ifstream File(FileName, std::ios::binary);

    BeginPoint = File.tellg();

    File.seekg(0, std::ios::end);

    EndPoint = File.tellg();

    File.close();

    return (EndPoint-BeginPoint);
}



void FileIO::ReadFile(std::string Filename) {
    std::string LineContent;
    std::ifstream File(Filename, std::ios::binary);

    if (File.is_open()) {
        //dis.out(D_INFO, "Reading file with name --> " + Filename);
        //dis.out(D_INFO, "File size: " + std::to_string(FileSize(Filename)) + " Bytes");

        while(std::getline(File, LineContent)) {
            FileContent.push_back(LineContent);
        }
        //dis.out(D_INFO, "Closing File");
    }
    else {
        //dis.out(D_ERROR, "Can't open file with name --> " + Filename);

    }

}


FileIO::~FileIO() {

}