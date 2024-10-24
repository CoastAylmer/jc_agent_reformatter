#include <iostream>
#include <fstream>
#include <string>

int main(){
    //define logFilePath
    std::string logFilePath = "/var/log/jcagent.log";
    
    // define output path for txt file
    std::string outputFilePath = "jcagent_output.txt";

    //Open the log file for reading
    std::ifstream logFile(logFilePath);
    if(!logFile.is_open()) {
        std::cerr << "Error opening log file:" << logFilePath << std::endl;
        return 1;
    }

    //Open the output file for writing
    std::ofstream outputFile(outputFilePath);
    if(!outputFile.is_open()) {
        std::cerr << "Error creating output file:" <./< outputFilePath << std::endl;
        return 1;

    }

    //Read from the log file and then write to the output file
    std::string line;
    while (std::getline(logFile, line)) {
        outputFile << line << std::endl;
    }

    //close both files
    logFile.close();
    outputFile.close();

    std::cout << "Log file contents successfully written to:" << outputFilePath << std::endl;

    return 0;

}