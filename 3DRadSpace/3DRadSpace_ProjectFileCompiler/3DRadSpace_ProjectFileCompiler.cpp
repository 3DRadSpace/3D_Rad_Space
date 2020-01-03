///Personal note: Since this is a console application, it's not worth using C# here.
/// Plus, I didn't use C++ for a while :D

#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>

int main(int argc, char* argv[])
{
    bool help = false, open = false, integrity = false;
    char path[255];
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "/?") == 0)
        {
            help = true;
            break;
        }
        if (strcmp(argv[i], "/c") == 0)
        {
            open = true;
            memcpy_s(path, sizeof(char)*255, argv[i + 1], strlen(argv[i + 1]) * sizeof(char));
            if (path == nullptr)
            {
                std::cout << "ERROR: Path was not specified. \n";
                break;
            }
        }
    }
    if (help == true)
    {
        std::cout << "3DRadSpace Project File Compiler\n";
        std::cout << "Arguments:\n";
        std::cout << "/? - Shows documentation.\n";
        std::cout << "/c - Compiles a project to bytecode.\n";
        std::cout << "Compiling algoritm complexity is O(n*2)\n";
        std::cout << "/int - Checks if project is useable.\n";
    }
    if (open == true)
    {
        std::cout << "Compiling " << path << std::endl; //Used std::endl to flush the buffer.
        std::ofstream result("Result.3drspc",std::ios::out | std::ios::binary); //To do: proper file name
        std::ifstream input(path);
        //TO DO: Stupid convertions using strtok I dont wanna do at 3 AM.

        if (input.bad() == true) std::cout << "ERROR: Cannot open file.\n";
        else
        {
            char line_buff[1000];
            bool a = true;
            while (a) ///THIS IS NOT AN INFINITE LOOP, even if a is initially 1.
            {
                input.getline(line_buff, 1000, '\n');
                if (line_buff == nullptr) a = false;
                if (input.eof()) a = false;
                char* str = strtok(line_buff, " ");
                int i = 0;
                int id = 0, expa = 2;
                while (str)
                {
                    if (i == 0)
                    {
                        if (strcmp(str, "camera") == 0)
                        {
                            id = 0;
                            expa = 9;
                            result.write((char*)&id, sizeof(char));
                        }
                    }
                    i++;
                }
            }
            //Close the streams when ending.
            result.close();
            input.close();
            std::cout << "Completed!";
        }
    }
}