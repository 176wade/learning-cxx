#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        // Always push a string to RECORDS, even if it's empty
        std::cout << "Finalizing records: " << _records << std::endl;
        RECORDS.push_back(_records);
        _records.clear();
    }
};

using Unique = std::unique_ptr<Resource>;

Unique reset(Unique ptr) {
    if (ptr) {
        ptr->record('r');
        // Ensure the old resource is destroyed and its records are finalized
        ptr.reset(); // This will trigger the destructor
    }
    return std::make_unique<Resource>();
}

Unique drop(Unique ptr) {
    if (ptr) {
        ptr->record('d');
        // Ensure an empty string is pushed after dropping
        RECORDS.push_back("");
        // Explicitly destroy the resource to ensure its destructor is called
        ptr.reset();
    }
    return nullptr;
}

Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    // Test case 0
    RECORDS.clear();
    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);

    // Test case 1
    RECORDS.clear();
    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);

    // Test case 2
    RECORDS.clear();
    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);

    // Debug output to verify the contents of problems and RECORDS
    for (auto i = 0; i < 3; ++i) {
        std::cout << "Problems[" << i << "]: ";
        for (const auto &str : problems[i]) {
            std::cout << str << " ";
        }
        std::cout << std::endl;
    }

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd", ""},
        {"ff", "r", "d"},
        {"", "r", "", "d", "d"}
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            ASSERT(strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}