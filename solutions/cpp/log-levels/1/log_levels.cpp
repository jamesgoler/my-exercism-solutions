#include <string>

namespace log_line {
    std::string message(std::string line) {
        size_t pos = line.find(" ");
        if (pos != std::string::npos) {
            return line.substr(pos + 1);
        }
        return "";
    }
    
    std::string log_level(std::string line) {
        size_t pos_begin = line.find("[");
        if (pos_begin != std::string::npos) {
            size_t pos_end = line.find("]: ");
            if (pos_end != std::string::npos) {
                return line.substr(pos_begin+1, pos_end-pos_begin-1);
            }
        }
        return "";
    }
    
    std::string reformat(std::string line) {
        return message(line) + " (" + log_level(line) + ")";
    }
}  // namespace log_line
