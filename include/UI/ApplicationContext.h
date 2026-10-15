#ifndef ADL_APPLICATIONCONTEXT_H
#define ADL_APPLICATIONCONTEXT_H

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

struct ApplicationContext {
    std::optional<std::filesystem::path> selectedFile;
    std::string adlSource;

    std::vector<std::string> errors;

    bool processingComplete = false;

    // std::unique_ptr<Simulator> simulator;
};
#endif //ADL_APPLICATIONCONTEXT_H