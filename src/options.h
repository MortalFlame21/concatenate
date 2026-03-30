#include <bitset>
#include <string>
#include <string_view>
#include <vector>

using File = std::string;

class CommandLine {
public:
    enum Options { ENDS, TABS, LINES, MAX_OPTIONS };

    using ProgramOpts = std::bitset<CommandLine::Options::MAX_OPTIONS>;

    CommandLine();

    ProgramOpts parse_opts(int argc, char* argv[]);
    std::vector<File> parse_files(int argc, char* argv[]);

private:
    void parse_opt(std::string_view opt);
    void set_opt(std::string_view opt);

    static inline constexpr ProgramOpts ALL_OPTS{
        (1 << Options::ENDS) | (1 << Options::TABS) | (1 << Options::LINES)};

    ProgramOpts options_{};
};

using CLI = CommandLine;