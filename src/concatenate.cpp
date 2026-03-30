#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "options.h"

CLI g_cli{};
CLI::ProgramOpts g_options;

void print_contents(std::istream& ins) {
    std::stringstream ss{};
    std::string line{};
    static int line_num{1};
    ss << ins.rdbuf();

    while (std::getline(ss, line)) {
        // todo: format the line output
        if (g_options.test(CLI::Options::LINES))
            std::cout << '[' << line_num++ << "] ";
        std::cout << line << '\n';
    }
}

void print_file(File file) {
    namespace fs = std::filesystem;

    if (std::fstream ifs{file}; file == "-")
        print_contents(std::cin);
    else if ((fs::is_regular_file(file) || fs::is_symlink(file)) && ifs)
        print_contents(ifs);
    else
        std::clog << "WARNING: " << file
                << " is not a valid file path or bad file.\n";
}

int main(int argc, char* argv[]) {
    g_options = g_cli.parse_opts(argc, argv);
    auto program_files{g_cli.parse_files(argc, argv)};

    for (const auto& file : program_files) {
        print_file(file);
    }
}