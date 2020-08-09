#ifndef FILEIO_H__
#define FILEIO_H__

#include "Base.h" // Base include file
#include "displayout.h"

class FileIO
{
    private:
        

        std::vector<std::string> LinkLocations; // I dont know if i need this but i will put it in here

        displayout dis;


        // Threaded File ops
        std::thread Loading_Thread;
        void LoadingThread();
        bool ToldToQuit = false;
        std::vector<std::string> EnumPlusData; // used to pass commands to the LoadingThreadOps enum, like filename or data to add to a file

        // Loading Thread Ops -- Used to keep the file addressable from threads and other memery unsafe areas
        // Could be fixed latter
        enum LoadingThreadOps {
            __LOAD_NULL_OP = 0,

            // Read Write
            __LOAD_READ_FILE,
            __LOAD_WRITE_FILE,
            __LOAD_SAVE,

            // Basic Op
            __LOAD_APPEND_END,
            __LOAD_POP,
            __LOAD_REMOVELOC_LOC,
            __LOAD_CLEAR_FILE, // <-- This will stop all file ops and clear the file vector
        };
        std::vector<LoadingThreadOps> LoadOperation;

        // Function to start the thread
        void StartThread();

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

        // Adv Ops
        /*TODO*/        

        // Saving and reading 
        void Save();
        void SaveToLoc(std::string Name);
        void ReadFile(std::string Filename);


        ~FileIO(); // unload file and mem
};

#endif