#include <array>
#include <string>
#include <vector>
#include <algorithm>

// Round down all provided student scores.
std::vector<int> round_down_scores(std::vector<double> student_scores) {
    std::vector<int> int_scores(student_scores.size());
    std::transform(student_scores.begin(), student_scores.end(), int_scores.begin(),
                   [](double val) -> int { return static_cast<int>(val); });
    return int_scores;
}

// Count the number of failing students out of the group provided.
int count_failed_students(std::vector<int> student_scores) {
    int count = 0;
    for (auto s: student_scores) {
        if (s <= 40) {
            count += 1;
        }
    }
    return count;
}

// Create a list of grade thresholds based on the provided highest grade.
std::array<int, 4> letter_grades(int highest_score) {
    int bandwidth = (highest_score - 40) / 4;
    int d = 41;
    int c = d + bandwidth;
    int b = c + bandwidth;
    int a = b + bandwidth;
    return {d, c, b, a};
}

// Organize the student's rank, name, and grade information in ascending order.
std::vector<std::string> student_ranking(
    std::vector<int> student_scores, std::vector<std::string> student_names) {
    std::vector<std::string> result;
    result.reserve(student_scores.size());
    for (int i = 0; i < student_scores.size(); i += 1) {
        result.emplace_back(std::to_string(i + 1) + ". " + student_names[i] + ": " + std::to_string(student_scores[i]));
    }
    return result;
}

// Create a string that contains the name of the first student to make a perfect
// score on the exam.
std::string perfect_score(std::vector<int> student_scores,
                          std::vector<std::string> student_names) {
    for (int i = 0; i < student_scores.size(); i += 1) {
        if (student_scores[i] == 100) {
            return student_names[i];
        }
    }
    return "";
}
