#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <regex>

std::string reformatLogTime(const std::string& logLine) {
    // Regex to capture the full timestamp
    std::regex timeRegex(R"(time=([0-9]{4}-[0-9]{2}-[0-9]{2}) ([0-9]{2}:[0-9]{2}:[0-9]{2}))");
    std::smatch match;

    if (std::regex_search(logLine, match, timeRegex)) {
        // Extract the date (YYYY-MM-DD) and time (HH:MM:SS)
        std::string dateStr = match[1];
        std::string timeStr = match[2];

        // Parse the date part (YYYY-MM-DD)
        std::tm tm = {};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&tm, "%Y-%m-%d");

        // Format to "Mon DD" (e.g., "Oct 22")
        char buffer[100];
        std::strftime(buffer, sizeof(buffer), "%b %d", &tm);

        // Build the new log line: "Month Day HH:MM:SS JC"
        std::string newLogLine = std::string(buffer) + " " + timeStr + " JC";

        // Find the position after the time and skip everything until " PID="
        size_t pidPos = logLine.find(" PID=");
        if (pidPos != std::string::npos) {
            newLogLine += logLine.substr(pidPos); // Append the rest of the log after " PID="
        }

        return newLogLine;
    }

    return logLine; // Return unchanged if no match
}

int main() {
    // Open the input and output files
    std::ifstream inputFile("/home/maylmer/projects/log-reformatter/jcagent_output.txt");
    std::ofstream outputFile("/home/maylmer/projects/log-reformatter/jcagent_output_reformatted.txt");

    // Read and reformat each log line
    std::string line;
    while (std::getline(inputFile, line)) {
        outputFile << reformatLogTime(line) << std::endl;
    }

    // Close the files
    inputFile.close();
    outputFile.close();

    std::cout << "Log file reformatted successfully." << std::endl;

    return 0;
}
