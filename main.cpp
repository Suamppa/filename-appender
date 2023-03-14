/* Base functionality generated with ChatGPT (https://chat.openai.com) */

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    fs::path root_dir;
    // Check the command line arguments for the directory to search in
    if (argc == 1) root_dir = fs::current_path();
    else if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [optional-directory]" << std::endl;
        return 1;
    } else root_dir = argv[1];
    std::cout << "Using " << root_dir.string() << " as working directory";

    // Loop through all subdirectories and their files
    for (const auto& entry : fs::directory_iterator(root_dir)) {
        if (entry.is_regular_file()) {
            // Get the filename and extension
            fs::path file_path = entry.path();
            std::string filename = file_path.stem().string();
            std::string extension = file_path.extension().string();
            // Create a stringstream to build the new filename
            std::stringstream new_filename;
            new_filename << filename;
            // Check if any other files in the same directory have the same base filename
            int count = 0;
            for (const auto& dir_entry : fs::directory_iterator(file_path.parent_path())) {
                if (dir_entry.is_regular_file()) {
                    fs::path other_path = dir_entry.path();
                    std::string other_name = other_path.stem().string();
                    // Ignore any trailing alphabetical characters
                    auto last_symbol = other_name.rbegin();
                    while (isalpha(*last_symbol)) {
                        ++last_symbol;
                        other_name.pop_back();
                    }
                    if (other_name == filename && other_path != file_path) {
                        ++count;
                    }
                }
            }
            // If there is more than one file with the same base filename, add a lowercase letter
            if (count > 0) {
                new_filename << static_cast<char>(count + 96);
            }
            new_filename << extension;
            // Rename the file with the new filename
            fs::rename(file_path, file_path.parent_path() / new_filename.str());
        }
    }
    return 0;
}
