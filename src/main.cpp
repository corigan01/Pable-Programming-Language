#include "displayout.h"
#include "Base.h"
#include "FileIO.h"

std::string RemoveWhiteSpace(std::string Content) {
    int i_size = Content.size();
    for (int e = 0; e < i_size; e++) {
        static int index = 0;
        if (Content[index] == ' ')
        {
            Content.erase(Content.begin() + index);
        }
        else if (Content[index] == '\"') {
            do {
                index++;
            } while (Content[index] == '\"');
        }
        else {
            index++;
        }
    }
    return Content;
}



int main() {
    displayout dis;

    dis.out(D_INFO, "Starting Main");

    FileIO file;
    file.ReadFile("../Pable Source/Program.pable");
    
    FileIO Token_file;
    Token_file.ReadFile("Pable Tokens/Tokens.txt");

    std::vector<std::string> VarTypesInToken = {"string", "int"};
    
    


    std::vector<std::string> Tokens = Token_file.FileContent;




    for (auto i : file.FileContent) {
        dis.out(D_FILE, i);

        
        i = RemoveWhiteSpace(i);

        


        size_t found = i.find("(");
        if (found != std::string::npos) {
            dis.out(D_FILE, "Found out command at a pos : " + std::to_string(found));

            std::string FoundToken = i;

            for (int e = found; e < i.size(); e++) {
                FoundToken.erase(FoundToken.begin() + found);
            }

            dis.out(D_FILE, FoundToken);

            bool FoundInArray = 0;
            for (auto e : Tokens) {
                if (FoundToken == e) {
                    FoundInArray = 1;
                }
            }

            if (!FoundInArray) {
                dis.out(D_ERROR, "Token with name --> " + FoundToken + " was not found in the list of tokens!"); // token not found ERROR
                break;
            }
           


            dis.out(D_FILE, i);


        }


    }
 


	usleep(1000);

    return 0;
}

