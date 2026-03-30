#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "options.h"

void print_contents(std::istream& ins) {
    std::stringstream ss{};
    ss << ins.rdbuf();
    auto str{ss.str()};
    std::cout << str;
}

void print_file(File file) {
    namespace fs = std::filesystem;

    if (std::fstream ifs{file}; file == "-")
        print_contents(std::cin);
    else if ((fs::is_regular_file(file) || fs::is_symlink(file)) && ifs)
        print_contents(ifs);
    else
        std::cout << "WARNING: " << file
                << " is not a valid file path or bad file.\n";
}

int main(int argc, char* argv[]) {
    CLI opts{};
    auto program_opts{opts.parse_opts(argc, argv)};
    auto program_files{opts.parse_files(argc, argv)};

    for (const auto& file : program_files) {
        print_file(file);
    }
}