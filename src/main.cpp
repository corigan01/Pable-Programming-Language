#include "displayout.h"
#include "Base.h"
#include "FileIO.h"
#include "tokenizer.h"

void RemoveWhiteSpace(std::string &Content) {
    int firstchar = Content.find_first_not_of(" ");
    for (int e = 0; e < firstchar; e++) {
        Content.erase(Content.begin());
    }

    //return Content;
}



int main() {
    displayout dis;

    //dis.out(D_INFO, "Starting Main");

    FileIO file;
    file.ReadFile("../Pable Source/Program.pable");
    
    FileIO Token_file;
    Token_file.ReadFile("Pable Tokens/Tokens.txt");

    std::vector<std::string> VarTypesInToken = {"string", "int"};
    std::vector<Token> Tokens;

    std::vector<Var> Pable_vars;


    for (auto i : Token_file.FileContent) {
        auto output = split(i, " ");

        if (output.size() > 1) {
            Token token;
            token.token = output[0];
            output.erase(output.begin());
            token.TokenContent = output;
            token.NumArg = output.size();
            
            for (auto i : output) {
                if (i == "$VAR_STRING") {
                    token.VartypeInArg.push_back(VAR_STRING);
                }
                else if (i == "$VAR_INT") {
                    token.VartypeInArg.push_back(VAR_INT);
                }
                else {
                    dis.out(D_ERROR, "Arg type with name --> " + i + " can not be found in the list of args!");
                    usleep(1000);
                    exit(1);
                }
            }


            Tokens.push_back(token);
        }
        else if (output.size() == 1) {
            Token token;
            token.token = output[0];
            token.NumArg = 0;

            Tokens.push_back(token);
        }
        else {
            continue;
        }


    }



   

    auto f = file.FileContent;

    for (auto i : f) {
       
        //std::cout << __LINE__ << std::endl;
        
        //i = RemoveWhiteSpace(i);

        
        
        dis.out(D_INFO, i);

        int commentfound = i.find("#");
        int eb = i.size();
        if (commentfound != -1) {
            for (int e = 0; e < (eb - commentfound); e++ ) {
                i.erase(i.begin() + commentfound);
            }
        }

       // i = RemoveWhiteSpace(i);

        RemoveWhiteSpace(i);


        dis.out(D_DEBUG, i);

        if (i.size() > 0) {
            size_t found = i.find_first_of(" (=");
            if (found != std::string::npos) {
                dis.out(D_FILE, "Found out command at a pos : " + std::to_string(found));

                std::string FoundToken = i;
                std::string args = "";
                for (int e = found; e < i.size(); e++) {
                    args.push_back(FoundToken[found]);
                    FoundToken.erase(FoundToken.begin() + found);
                }

                RemoveWhiteSpace(args);

                dis.out(D_FILE, "Found token --> \'" + FoundToken + "\' with args --> \'" + args + "\'");

                bool FoundInArray = 0;
                bool FoundComment = 0;
                for (auto e : Tokens) {
                    if (FoundToken == e.token) {
                        FoundInArray = 1;
                    }
                }

                if (!FoundInArray) {
                    dis.out(D_ERROR, "Token with name --> \'" + FoundToken + "\' was not found in the list of tokens!\n\tOf command --> " + i); // token not found ERROR
                    break;
                }

                // This needs to be fixed
                if (FoundToken == "out") {
                    if (args.size() > 0) {
                        if (args[0] == '(') {
                            args.erase(args.begin());

                            RemoveWhiteSpace(args);


                            if (args[0] == '\"') {
                                std::string got = "";
                                args.erase(args.begin());

                                bool nocallflag = 0;
                                for (auto r : args) {
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
                                    break;
                                }

                                std::cout << got << std::endl;

                            }
                            else {
                                 int FindEnd = args.find_first_of(")");

                                if (FindEnd == -1) {
                                    dis.out(D_ERROR, "You need to have end a function call with \')\'");
                                    usleep(1000);
                                    exit(1);
                                }

                                std::string CouldBeVar = "";

                                for (int e = 0; e < FindEnd; e++) {
                                    CouldBeVar.push_back(args[e]);
                                }

                                dis.out(D_DEBUG, CouldBeVar);

                                bool flagFound = 0;
                                for (auto e : Pable_vars) {
                                    if (CouldBeVar == e.VarName) {
                                        std::cout << e.VarContent << std::endl;
                                        flagFound = 1;
                                        break;
                                    }
                                }

                                if (!flagFound) {
                                    dis.out(D_ERROR, "Need '\"' to begin a string def because var with name \'" + CouldBeVar + "\' could not be found in the list of defined vars!");
                                    break;
                                }
                            }
                        }
                        else {
                            dis.out(D_ERROR, "Need '(' to begin a function call!");
                            break;
                        }
                    }
                }
                else if (FoundToken == "string") {
                    int clipoff = args.find_first_of(" =");

                    std::string VarName = "";
                    std::string LatArg = args;
                    for (int e = 0; e < clipoff; e++) {
                        VarName.push_back(args[e]);
                        LatArg.erase(LatArg.begin());
                    }

                    RemoveWhiteSpace(LatArg);

                    if (LatArg[0] == '=') {
                        LatArg.erase(LatArg.begin());
                    }

                    RemoveWhiteSpace(LatArg);

                    dis.out(D_INFO, LatArg);
                    dis.out(D_INFO, VarName);

                    Var TempVar;

                    if (VAR_STRING != TempVar.DetectVarType(LatArg)) {
                        dis.out(D_ERROR, "A string def needs to have a string as a definer!");
                        usleep(1000);
                        exit(1);
                    }


                    if (LatArg[0] == '\"') {
                        LatArg.erase(LatArg.begin());
                        int LatArgPosName = LatArg.find_first_of("\"");

                        if (LatArgPosName == -1) {
                            dis.out(D_ERROR, "Cant find end of string def!");
                            usleep(1000);
                            exit(1);
                        }


                        std::string VarContent = "";

                        for (int e = 0; e < LatArgPosName; e++) {
                            VarContent.push_back(LatArg[e]);
                        }

                        dis.out(D_INFO, "Found Var with name of \'" + VarName + "\' and content of --> \'" + VarContent + "\'");

                        TempVar.StoreVar(VAR_STRING, VarContent, VarName);

                        Pable_vars.push_back(TempVar);
                    }
                    else {
                        dis.out(D_ERROR, "Unknown char --> " + LatArg[0]);
                        usleep(1000);
                        exit(1);
                    }

                    
                }
            
                


            }            
            else {
                dis.out(D_ERROR, "Token with name --> \'" + i + "\' was not found in the list of tokens!\n\tof command --> \'" + i + "\'"); // token not found ERROR
                break;
            }
        }
        else {
            dis.out(D_WARNING, "Null line");
        }

        //std::cout << __LINE__ << std::endl;


    }
 
	usleep(1000);

    return 0;
}

