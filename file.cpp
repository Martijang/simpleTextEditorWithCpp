//author: Martin Jang
//this code is written in cpp for the minimalist binary file output
//*maybe I can try in rust next time* aw
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
    std::vector<std::string> vec;
    if (argc < 2 || argv[1][0] == '\0') {
        std::cout << "Error: no file has been given. Usage: ./file <filename>" << std::endl;
        return 1;
    }

    //try to open the file for reading
    std::ifstream inputFile(argv[1]);
    
    //check if the file exists; if not, create it
    if (!inputFile) {
        std::cout << "File " << argv[1] << " does not exist. Creating new file..." << std::endl;
        
        //create the file if it doesn't exist.
        std::ofstream createFile(argv[1]);  //rhis will create the file
        if (!createFile) {
            std::cerr << "Error: could not create file " << argv[1] << std::endl;
            return 1;
        }
        createFile.close();  //close the created file after creation
        
        //reopen the file for reading and appending
        inputFile.open(argv[1]);
    }

    //now that the file exists, read and display its content
    std::string line;
    std::cout << "File data:" << std::endl;
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
    }
    std::cout << "---End---" << std::endl;
    inputFile.close();

    std::fstream newFile(argv[1], std::ios::out | std::ios::in | std::ios::app);
    if (!newFile) {
        std::cerr << "Error: could not open file " << argv[1] << " for appending." << std::endl;
        return 1;
    }

        std::cout << "type 'exit' to exit" << std::endl;

    while (true) {
        std::string buffer;
        std::getline(std::cin, buffer);

        if (buffer != "exit") {
            vec.push_back(buffer);
        } else {
            std::cout << "Exiting.. Save your input? [y/n]: ";
            std::string input;
            std::cin >> input;

            if (input == "y" || input == "Y") {
                for (size_t i = 0; i < vec.size(); i++)//since user wants to save the input use for loop to insert 
                {
                    newFile << vec[i] << std::endl;
                }
                
                newFile.close();
                return 0;
            } else if (input == "n" || input == "N") {//not finished
                newFile.close();
                return 0;
            }
        }
    }
}
