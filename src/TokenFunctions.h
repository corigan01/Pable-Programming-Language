#ifndef TOKEN_FUN__H__
#define TOKEN_FUN__H__

#include "Base.h"
#include "displayout.h"
#include "tokenizer.h"
#include "FileIO.h"


displayout dis;


inline int WorkingLine = 0;

struct StringSplit
{
    std::string BeforeChar;
    std::string AfterChar;
};


void Pable_ERROR(std::string Error, int LineERR, bool breakstop = true) {
    dis.out(D_ERROR, "Line " + std::to_string(LineERR) + ": " + Error );

    if (breakstop) {
        usleep(1000000);
        exit(1);   
    }
}


StringSplit SplitString(std::string Args, std::string Char) {
    int foundLoc = Args.find_first_of(Char);

    if (foundLoc == -1) {
        Pable_ERROR("Could not find the spliter in SplitString()", WorkingLine, false);

    }


}


void RemoveWhiteSpace(std::string &Content) {
    int firstchar = Content.find_first_not_of(" ");
    for (int e = 0; e < firstchar; e++) {
        Content.erase(Content.begin());
    }
 
    //return Content;
}



bool IsfoundinVar(std::vector<Var> ScopeVar, std::string Arg) {

    int FindEnd = Arg.find_first_of(")");

    if (FindEnd == -1) {
        dis.out(D_ERROR, "You need to have end a function call with \')\'");
        usleep(1000);
        exit(1);
    }


    std::string CouldBeVar = "";

    for (int e = 0; e < FindEnd; e++) {
        CouldBeVar.push_back(Arg[e]);
    }

    dis.out(D_DEBUG, CouldBeVar);

    bool flagFound = 0;
    for (auto e : ScopeVar) {
        if (CouldBeVar == e.VarName) {
            std::cout << e.VarContent << std::endl;
            flagFound = 1;
            break;
        }
    }

    return flagFound;

}

int ExtractIntDef(std::string Args) {
    RemoveWhiteSpace(Args);

    Args.push_back('\t');

    std::string got = "[NULL]";

    int FoundNotof = Args.find_first_not_of("0123456789");

    if (Args[FoundNotof] != '\t') {
        Pable_ERROR("Could not determine prescence of int --> " + Args, WorkingLine);
    }
    
    if (FoundNotof != 0) {
        got = "";
        for (int i = 0; i < FoundNotof; i ++) {
            got += Args[i];
        }
    }

    if (got == "[NULL]") {
        Pable_ERROR("Could not find any numbers for this int defined", WorkingLine);
    }

    //Pable_ERROR(std::to_string(FoundNotof), 0);
    return std::stoi(got);
}


std::string ExtractStringDef(std::string Args) {
    std::string got = "";
    Args.erase(Args.begin());

    bool nocallflag = 0;
    for (auto r : Args) {
        if (r == '\"') {
            nocallflag = 1;
            break;
        }
        
        else {
            got += r;
        }
    }

    if (!nocallflag) {
        dis.out(D_ERROR, "You need \'\"\' to end a string def!");
        exit(1);
    }

    return got;
}


bool FoundStringDef(std::string Args) {
    RemoveWhiteSpace(Args);

    if (Args[0] == '\"'){
        return 1;
    }
    return 0;
}


#endif