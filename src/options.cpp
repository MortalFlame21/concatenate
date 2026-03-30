#include "options.h"

CommandLine::CommandLine() {}

CLI::ProgramOpts CommandLine::parse_opts(int argc, char* argv[]) {
    for (int i{1}; i < argc; ++i) {
        std::string_view opt{argv[i]};

        // end of options.
        if (opt == "--")
            break;

        parse_opt(opt);
    }
    return options_;
}

std::vector<File> CommandLine::parse_files(int argc, char* argv[]) {
    std::vector<File> files;

    bool eoo{};
    for (int i{1}; i < argc; ++i) {
        std::string f{argv[i]};

        // we have seen end of options, '--'
        // or doesn't start with '-', a possible option
        if (f == "--")
            eoo = true;
        else if (eoo || f == "-" || !f.starts_with('-'))
            files.push_back(f);
    }

    if (files.empty())
        files.push_back("-"); // push empty

    return files;
}

void CommandLine::parse_opt(std::string_view opt) {
    if (!opt.starts_with('-'))
        return;
    // attempt parse word
    set_opt(opt.substr(1, opt.size() - 1));
}

void CommandLine::set_opt(std::string_view opt) {
    if (opt == "-all" || opt == "a")
        options_ |= ALL_OPTS;
    else if (opt == "-tabs" || opt == "t")
        options_.set(TABS);
    else if (opt == "-lines" || opt == "l")
        options_.set(LINES);
}