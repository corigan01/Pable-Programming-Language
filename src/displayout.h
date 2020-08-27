#pragma once

#ifndef DISPLAYOUT
#define DISPLAYOUT
// ---------------- CODE ---------------- \\

#include "Base.h"

// To Disable COLOR, INFO, WARNING, ERROR, DEBUG, and or LOG use 1 to enable use 0
#define D_DISABLE_COLOR       0
#define D_DISABLE_INFO        0
#define D_DISABLE_WARNING     0
#define D_DISABLE_ERROR       0
#define D_DISABLE_DEBUG       0
#define D_DISABLE_LOG         0

// define this if you want to backup control
#define BACKUP_CON

// defines colors if they are not defined.
#ifdef BACKUP_CON   
#ifndef D_DISABLE_COLOR
#define D_DISABLE_COLOR 0 
#endif 
#ifndef D_DISABLE_INFO
#define D_DISABLE_INFO 0
#endif 
#ifndef D_DISABLE_WARNING
#define D_DISABLE_WARNING 0
#endif 
#ifndef D_DISABLE_ERROR
#define D_DISABLE_ERROR 0
#endif 
#ifndef D_DISABLE_DEBUG
#define D_DISABLE_DEBUG 0
#endif 
#ifndef D_DISABLE_LOG
#define D_DISABLE_LOG
#endif
#endif

inline bool __IsDisplaying = false;
inline std::vector<std::string> AllLog;

enum Debug_D
{
    D_DEF = 0,
    D_LOG,
    D_FILE,
    D_DEBUG,
    D_ERROR,
    D_INFO,
    D_WARNING,
};

namespace D_COLOR {
    // Defines the color output for the console
    namespace ColorM {
        enum Code {
            FG_RED = 31,
            FG_GREEN = 32,
            FG_BLUE = 34,
            FG_YELLOW = 33,
            FG_DEFAULT = 39,
            FG_MAGENTA = 35,
            BG_RED = 41,
            BG_GREEN = 42,
            BG_BLUE = 44,
            BG_DEFAULT = 49

        };
        class Modifier {
            Code code;
        public:
            Modifier(Code pCode) : code(pCode) {}
            friend std::ostream&
                operator<<(std::ostream& os, const Modifier& mod) {
                return os << "\033[" << mod.code << "m";
            }
        };
    }
    inline ColorM::Modifier redM(ColorM::FG_RED);
    inline ColorM::Modifier greenM(ColorM::FG_GREEN);
    inline ColorM::Modifier blueM(ColorM::FG_BLUE);
    inline ColorM::Modifier magentaM(ColorM::FG_MAGENTA);
    inline ColorM::Modifier yellowM(ColorM::FG_YELLOW);
    inline ColorM::Modifier defM(ColorM::FG_DEFAULT);

    inline std::string debugstring[] = { "NULL", "LOG", "FILE", "DEBUG", "ERROR", "INFO", "WARNING" };     // Convert the Color to a readable displayname

    typedef struct __ObjectDisplayColorString {
        std::string Message;
        std::string Prompt;

        ColorM::Modifier DebugType;

    } __OBJSTRING;
}

class displayout
{
public:

    displayout();
    ~displayout();

    bool __DEBUG_ON = false;


    // Check if we have color enabled
#if D_DISABLE_COLOR == 0
    void out(int enumTypeColor, std::string ToDisplay);
#else
    void out(std::string ToDisplay);
#endif
    
protected:
   
private:
    std::vector<D_COLOR::__OBJSTRING> PreDisplayControl;
    std::thread ThreadDisplay;

    bool SetToQuit = false;

    

    void Threaded_Display();
};

#endif