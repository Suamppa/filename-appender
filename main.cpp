/*************************************************************************
 Filename appender
 This little renaming tool was created for Pokemon Infinite Fusion
 in order to help with renaming alternate sprites in bulk.

    Copyright (C) 2023  Samppa Alatalo

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
**************************************************************************/

/* Base functionality generated with ChatGPT (https://chat.openai.com) and heavily modified by Samppa Alatalo */

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

// Removes trailing alphabetical characters from a string
void remove_alpha(std::string& str) {
    auto last_symbol = str.rbegin();
    while (isalpha(*last_symbol)) {
        ++last_symbol;
        str.pop_back();
    }
}

int main(int argc, char* argv[]) {
    fs::path root_dir;
    // If no command line arguments are given, have the user input an optional directory or path
    if (argc == 1) {
        root_dir = fs::current_path();
        std::string input;
        std::cout << "Please enter the path to the directory whose contents to modify\nor press Enter to use the current working directory:" << std::endl;
        std::getline(std::cin, input);
        if (!input.empty()) {
            fs::path working_dir = fs::path(input);
            if (working_dir.is_absolute()) root_dir = working_dir;
            else {
                root_dir = fs::relative(input, root_dir);
                if (root_dir.empty()) root_dir = fs::current_path();
            }
        }
    } else if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [optional-directory]" << std::endl;
        return 1;
    // Check the command line arguments for the directory to search in
    } else root_dir = argv[1];
    std::cout << "Using " << root_dir.string() << " as working directory" << std::endl;

    // Loop through all files in $root_dir
    auto directory_iterator = fs::directory_iterator(root_dir);
    for (const auto& entry : directory_iterator) {
        if (entry.is_regular_file()) {
            // Get the filename and extension
            fs::path file_path = entry.path();
            std::string filename = file_path.stem().string();
            std::string extension = file_path.extension().string();
            // Create a stringstream to build the new filename
            std::stringstream new_filename;
            new_filename << filename;
            int count = 0;

            // Check if any other files in any subdirectories have the same base filename
            for (const auto& dir_entry : fs::recursive_directory_iterator(root_dir)) {
                if (dir_entry.is_regular_file()) {
                    fs::path other_path = dir_entry.path();
                    std::string other_name = other_path.stem().string();
                    // Ignore any trailing alphabetical characters
                    remove_alpha(other_name);
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
            std::string new_filename_str = new_filename.str();
            if (new_filename_str != filename + extension) {
                // Rename the file with the new filename
                fs::rename(file_path, file_path.parent_path() / new_filename_str);
                std::cout << "Renamed " << filename + extension << " to " << new_filename_str << "\n";
            }
        }
    }
    std::cout << "\nJob finished\nPress any key to close..." << std::endl;
    std::getchar();
    return 0;
}
