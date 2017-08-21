#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "System.h"

#define BUFFER_SIZE 128
#define IS_NUM(x) ((int) (x) >= 48 && (int) (x) <= 57)

class Tokenizer
{
private:
    std::vector<std::string> tokens;
    bool status;

public:
    Tokenizer(const char* path)
    {
        FILE* file = fopen(path, "r");
        if(!file)
        {
            printf("Error: Could not find file [%s].\n", path);
            throw -1;
        }

        char c = 0;
        char buffer[BUFFER_SIZE];
        int index = 0;
        size_t line = 1;
        size_t character = 1;
        
        this->status = true;

        while((c = fgetc(file)) != EOF)
        {
            character ++;
            switch(c)
            {
                case '\n':
                    character = 1;
                    line ++;
                case ' ':
                case '\t':
                    if(index > 0) {
                        buffer[index] = '\0';
                        tokens.push_back(std::string(buffer));
                        index = 0;
                    }
                    break;
                case ',':
                    if(index > 0) {
                        buffer[index] = '\0';
                        tokens.push_back(std::string(buffer));
                        buffer[0] = c;
                        buffer[1] = '\0';
                        tokens.push_back(std::string(buffer));
                        index = 0;
                    } else {
                        printf("Error [%zu, %zu]: Invalid token '%c'\n", line, character, c);
                        this->status = false;
                    }
                    break;
                case '[':
                case ']':
                    if(index > 0) {
                        buffer[index] = '\0';
                        tokens.push_back(std::string(buffer));
                    }
                    buffer[0] = c;
                    buffer[1] = '\0';
                    tokens.push_back(std::string(buffer));
                    index = 0;
                    break;
                case '"':
                    index = 0;
                    tokens.push_back(std::string("\""));
                    while(true)
                    {
                        if((c = fgetc(file)) == EOF) {
                            printf("Error: Unterminated string\n");
                            this->status = false;
                        } else {
                            switch(c)
                            {
                                case '"':
                                    buffer[index] = '\0';
                                    tokens.push_back(std::string(buffer));
                                    index = 0;
                                    goto BREAK_STRING;
                                    break;
                                case '\n':
                                    line ++;
                                    break;
                                default:
                                    character++;
                                    buffer[index++] = c;
                                    break;
                            }
                        }
                    }
                    BREAK_STRING:
                    tokens.push_back("\"");
                    break;
                default:
                    buffer[index++] = c;
                    break;
            }
        }
    }

    inline const std::vector<std::string>& getTokens() const { return this->tokens; }
};

int main(int argc, char** argv)
{
    if(argc < 3) {
        printf("Invalid command line arguments:\n\tUsage: ./compiler [output_file] [sources files ...]\n");
        return -1;
    }

    for(int i = 2; i < argc; i++) {
        Tokenizer t = Tokenizer(argv[i]);
        for(int o = 0; o < t.getTokens().size(); o++) printf("%i:%s\n", o, t.getTokens()[o].c_str());
    }

    return 0;
}

