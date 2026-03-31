#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "options.h"

CLI g_cli{};
CLI::ProgramOpts g_options;

std::string format_line(std::string_view line) {
    std::stringstream ss{};
    for (const auto& c : line) {
        if (c == '\t' && g_options.test(CLI::Options::TABS))
            ss << "\\t";
        else
            ss << c;
    }
    // fix: still prints when there is no newline !
    return ss.str() + (g_options.test(CLI::Options::ENDS) ? "\\n" : "");
}

void print_contents(std::istream& ins) {
    std::stringstream ss{};
    std::string line{};
    ss << ins.rdbuf();

    while (std::getline(ss, line)) {
        // todo: format the line output
        if (g_options.test(CLI::Options::LINES)) {
            static int line_num{1};
            std::cout << '[' << line_num++ << "] ";
        }
        std::cout << format_line(line) << '\n';
    }
}

void print_file(File file) {
    namespace fs = std::filesystem;

    if (std::fstream ifs{file}; file == "-")
        print_contents(std::cin);
    else if ((fs::is_regular_file(file) || fs::is_symlink(file)) && ifs)
        print_contents(ifs);
    else
        std::clog << "WARNING: " << file << " is not a valid file path or bad file.\n";
}

int main(int argc, char* argv[]) {
    g_options = g_cli.parse_opts(argc, argv);
    auto program_files{g_cli.parse_files(argc, argv)};

    for (const auto& file : program_files) {
        print_file(file);
    }
}