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


void Pable_ERROR(std::string Error, bool breakstop = true) {
    dis.out(D_ERROR, "Line " + std::to_string(WorkingLine + 1) + ": " + Error );

    if (breakstop) {
        //usleep(1000000);
        exit(1);   
    }
}


StringSplit SplitString(std::string Args, std::string Char) {
    int foundLoc = Args.find_first_of(Char);

    if (foundLoc == -1) {
        Pable_ERROR("Could not find the spliter in SplitString()", false);
        return {"", ""};
    }

    StringSplit splitedstring;

    splitedstring.AfterChar = Args;
    for (int e = 0; e < foundLoc; e++) {
        splitedstring.BeforeChar.push_back(Args[e]);
        splitedstring.AfterChar.erase(splitedstring.AfterChar.begin());
    }


    return splitedstring;
}


bool CheckIfEqual(std::string Args) {
   
    return Args[0] == '=';

}


void RemoveWhiteSpace(std::string &Content) {
    int firstchar = Content.find_first_not_of(" ");
    for (int e = 0; e < firstchar; e++) {
        Content.erase(Content.begin());
    }
 
    //return Content;
}

void RemoveWhiteSpaceBack(std::string &Content) {
    int firstchar = Content.find_last_not_of(" ");
    for (int e = Content.size(); e > firstchar + 1; e--) {
        Content.erase(Content.end() -1);
    }
}


bool CheckIfVar(std::vector<Var> ScopeVar, std::string Arg) {
    for (auto i : ScopeVar) {
        if (i.VarName == Arg)
            return true;
        else 
            return false;
    }

    return false;
}

std::string FoundVarContent(std::vector<Var> ScopeVar, std::string Arg) {
     int FindEnd = Arg.find_first_of(")");

    if (FindEnd == -1) {
        Pable_ERROR("You need to have end a function call with \')\'");
    }


    std::string CouldBeVar = "";

    for (int e = 0; e < FindEnd; e++) {
        CouldBeVar.push_back(Arg[e]);
    }

    dis.out(D_DEBUG, CouldBeVar);

    bool flagFound = 0;
    for (auto e : ScopeVar) {
        if (CouldBeVar == e.VarName) {
            
            return e.VarContent;
            
            flagFound = 1;
            break;
        }
    }

    return "";

}


bool IsfoundinVar(std::vector<Var> ScopeVar, std::string Arg) {

    int FindEnd = Arg.find_first_of(")");

    if (FindEnd == -1) {
        Pable_ERROR("You need to have end a function call with \')\'");
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

    int FoundNotof = Args.find_first_not_of("-0123456789");

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
        Pable_ERROR("You need \'\"\' to end a string def!");
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


/*StringSplit FindNumBeforeOperator(std::string Args, std::string Op) {
    int found_input = i.find("+");
    int eb = i.size();
    if (found_input != -1) {
        StringSplit splite = SplitString(i, "+");

        RemoveWhiteSpaceBack(splite.BeforeChar);

        int found_splice1 = splite.BeforeChar.find_last_not_of("0987654321");
        std::string FoundSegment1 = "";
        std::string FoundSegment2 = "";

        if (found_splice1 != std::string::npos) {
            for (int e = splite.BeforeChar.size(); e > found_splice1 + 1; e--) {
                FoundSegment1.insert(FoundSegment1.begin(), splite.BeforeChar[e-1]);
            }
        }
        else {
            FoundSegment1 = splite.BeforeChar;
        }

        RemoveWhiteSpace(splite.AfterChar);
        
        int found_splice2 = splite.AfterChar.size();

        if (splite.AfterChar[0] == '+') {
            splite.AfterChar.erase(splite.AfterChar.begin());

            RemoveWhiteSpace(splite.AfterChar);

            found_splice2 = splite.AfterChar.find_first_not_of("0987654321");
            if (found_splice2 != std::string::npos) {
                for (int e = 0; e < found_splice2; e++) {
                    FoundSegment2 += splite.AfterChar[e];
                }
            }
            else {
                found_splice2 = splite.AfterChar.size();

                FoundSegment2 = splite.AfterChar;
            }
        }
        else {
            Pable_ERROR("Could not find the arithmetic operator during deconstruction part two!");
    }

    Pable_ERROR("Poorly Handled Compiler Code for Arithmetic operator " + Op);

    return {"", ""};

}*/

                                                                                                 \




#endif