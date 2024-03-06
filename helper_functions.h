#include <string>

// Method for checking the validity of the input string
bool is_valid_input(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c) && c != '+' && c != '-' && c != '*' && c != '^' && !std::isalpha(c)) {
            return false;
        }
    }
    return true;
}