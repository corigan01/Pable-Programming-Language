#ifndef FILEIO_H__
#define FILEIO_H__

#include "Base.h" // Base include file
#include "displayout.h"

class FileIO
{
    private:
        

        std::vector<std::string> LinkLocations; // I dont know if i need this but i will put it in here

        displayout dis;


    public:
        // Files
        std::vector<std::string> FileContent;
        std::string FileLoc;
        std::string FileName;
        int LineLen;

        // Constructing
        FileIO(std::string FileName); // for loading a file right away
        FileIO(); // for waiting to load a file later for global construction

        // Basic Ops
        void Append(std::string Content);
        void PopBack();
        void RemoveLoc(int index);
        void Clear();

        // Adv Op's
        int FileSize(std::string FileName);

        // Saving and reading 
        void Save();
        void SaveToLoc(std::string Name);
        void ReadFile(std::string Filename);


        ~FileIO(); // unload file and mem
};

#endif