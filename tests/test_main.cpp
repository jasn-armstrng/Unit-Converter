// test_main.cpp: Contains all the tests for the unit converter application
#include <chrono>
#include <cstring>
#include <format>
#include <string>
#include <unordered_map>
#include <vector>

#include <gtest/gtest.h>

// Include the functions/file to test
#include "../src/main.cpp"

// Test cases
static std::unordered_map<std::string, std::vector<std::vector<std::string> > > test_cases =
{
    // Name of test                   Test Arguments                                        Expected Output
    // ---------------------------------------------------------------------------------------------------------------------------------
    {"NoArguments",                   {{ "guc" },                                           { "No arguments provided.", "Usage: guc" }}},
    {"HelpOption",                    {{ "guc", "--help" },                                 { "Usage: guc" }}},
    {"HelpOptionShort",               {{ "guc", "-h" },                                     { "Usage: guc" }}},
    {"VersionOption",                 {{ "guc", "--version" },                              { "Version 1.0" }}},
    {"VersionOptionShort",            {{ "guc", "-v" },                                     { "Version 1.0" }}},
    {"UnitCategoriesOption",          {{ "guc", "--unit-categories" },                      { "Available unit categories:" }}},
    {"UnitCategoriesOptionShort",     {{ "guc", "-c" },                                     { "Available unit categories:" }}},
    {"UnitCategoriesUnknownOpt",      {{ "guc", "--unit-categories", "unknown" },           { "Unknown option: unknown" }}},
    {"UnitsOption",                   {{ "guc", "--units", "LENGTH" },                      { "Available units in the LENGTH category:" }}},
    {"UnitsOptionShort",              {{ "guc", "-u", "MASS" },                             { "Available units in the MASS category:" }}},
    {"UnitsOptionUnknownOpt",         {{ "guc", "--units", "LENGTH", "unknown" },           { "Unknown option: unknown" }}},
    {"UnitsOptionUnknownCat",         {{ "guc", "--units", "UNKNOWN" },                     { "Unknown category: UNKNOWN" }}},
    {"UnitsOptionLowerCase",          {{ "guc", "--units", "length" },                      { "Available units in the LENGTH category:" }}},
    {"UnitsOptionMixedCase",          {{ "guc", "--units", "LenGth" },                      { "Available units in the LENGTH category:" }}},
    {"UnitsOptionMultiWordCategory",  {{ "guc", "--units", "\"data transfer rate\"" },      { "Unknown category: \"data transfer rate\"" }}},
    {"ConstantsOption",               {{ "guc", "--constants" },                            { "Available constants:" }}},
    {"ConstantsOptionShort",          {{ "guc", "-C" },                                     { "Available constants:" }}},
    {"ConstantsOptionUnknownOpt",     {{ "guc", "--constants", "unknown" },                 { "Unknown constant: unknown" }}},
    {"ConstantOption",                {{ "guc", "--constants", "SPEED OF LIGHT" },          { "299792458" }}},
    {"ConstantOptionShort" ,          {{ "guc", "-C", "PI" },                               { "3.141592653589793" }}},
    {"ConstantOptionShortUnknownOpt", {{ "guc", "-C", "PI", "unknown" },                    { "Unknown option: unknown" }}},
    {"ConstantOptionUnknownOpt",      {{ "guc", "--constants", "TAU", "unknown" },          { "Unknown option: unknown" }}},
    {"ConstantOptionUnknownConst",    {{ "guc", "--constants", "UNKNOWN" },                 { "Unknown constant: UNKNOWN" }}},
    {"ConstantOptionLowerCase",       {{ "guc", "--constants", "speed of light" },          { "299792458" }}},
    {"ConstantOptionMixedCase",       {{ "guc", "--constants", "sPeeD oF LiGHt" },          { "299792458" }}},
    {"ConstantOptionSingleWord",      {{ "guc", "--constants", "pi" },                      { "3.141592653589793" }}},
    {"ConstantOptionSingleWordMixed", {{ "guc", "--constants", "Pi" },                      { "3.141592653589793" }}},
    {"UnknownOption",                 {{ "guc", "--unknown" },                              { "Unknown or incomplete option: --unknown", "Usage: guc" }}},
    {"IncompleteOption",              {{ "guc", "--units" },                                { "Unknown or incomplete option: --units", "Usage: guc" }}}
};

// Helper function to convert a vector of strings to an array of C-strings
std::vector<char*> create_argv(const std::vector<std::string>& args)
{
    std::vector<char*> argv;
    for (const auto& arg : args)
    {
        char* cstr = new char[arg.size() + 1];
        std::strcpy(cstr, arg.c_str());
        argv.push_back(cstr);
    }
    argv.push_back(nullptr);
    return argv;
}

// Helper function to reuse the TEST internals
bool run_test_case(const std::string& test_name, const std::vector<std::string>& args, const std::string& expected_output)
{
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    bool test_passed = output.find(expected_output) != std::string::npos;
    if (!test_passed)
        {
            std::cerr << "\033[33mTest case failed: " << test_name << "\033[0m" << std::endl;
            std::cerr << "Expected output: " << expected_output << std::endl;
            std::cerr << "Actual output: " << output << std::endl;
        }

    return test_passed;
}

TEST(UnitsTest, AllTestCases)
{
    std::size_t total_tests = test_cases.size();
    int test_counter = 0;

    for (const auto& test_case : test_cases)
    {
        const std::string& test_name = test_case.first;
        const std::vector<std::string>& args = test_case.second[0];
        const std::string& expected_output = test_case.second[1][0];

        const std::string run = std::format("\033[32m[ RUN      ]\033[0m - {}", test_name);
        std::cout << run << std::endl;

        bool test_passed = run_test_case(test_name, args, expected_output);
        if (test_passed)
        {
            test_counter++;
            const std::string ok = std::format("\033[32m[       OK ]\033[0m - {}. Passed: {}/{}", test_name, test_counter, total_tests);
            std::cout << ok << std::endl;
        }
    }
}

int main(int argc, char** argv)
{
    const std::string tests_start = format("\033[33mTests Start: {}\033[0m", std::chrono::system_clock::now());
    std::cout << tests_start << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
