#ifndef FILEIO_H__
#define FILEIO_H__

#include "Base.h" // Base include file

class FileIO
{
    private:
        std::vector<std::string> FileContent;
        std::string FileLoc;
        std::string FileName;
        int LineLen;

        std::vector<std::string> LinkLocations; // I dont know if i need this but i will put it in here
    public:
        // Constructing
        FileIO(std::string FileName); // for loading a file right away
        FileIO(); // for waiting to load a file later for global construction

        // Basic Ops
        void ReadFile(std::string Filename);
        void Append(std::string Content);
        void PopBack();
        void RemoveLoc(int index);
        void Clear();

        // Adv Ops
        /*TODO*/        

        // Saving
        void Save();
        void SaveToLoc(std::string Name);

        ~FileIO();
};

#endif