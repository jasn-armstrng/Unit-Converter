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
    {"NoArguments",                   {{ "con" },                                           { "No arguments provided.", "Usage: con" }}},
    {"HelpOption",                    {{ "con", "--help" },                                 { "Usage: con" }}},
    {"HelpOptionShort",               {{ "con", "-h" },                                     { "Usage: con" }}},
    {"VersionOption",                 {{ "con", "--version" },                              { "Version 1.0" }}},
    {"VersionOptionShort",            {{ "con", "-v" },                                     { "Version 1.0" }}},
    {"UnitCategoriesOption",          {{ "con", "--unit-categories" },                      { "Available unit categories:" }}},
    {"UnitCategoriesOptionShort",     {{ "con", "-c" },                                     { "Available unit categories:" }}},
    {"UnitCategoriesUnknownOpt",      {{ "con", "--unit-categories", "unknown" },           { "Unknown option: unknown" }}},
    {"UnitsOption",                   {{ "con", "--units", "LENGTH" },                      { "Available units in the LENGTH category:" }}},
    {"UnitsOptionShort",              {{ "con", "-u", "MASS" },                             { "Available units in the MASS category:" }}},
    {"UnitsOptionUnknownOpt",         {{ "con", "--units", "LENGTH", "unknown" },           { "Unknown option: unknown" }}},
    {"UnitsOptionUnknownCat",         {{ "con", "--units", "UNKNOWN" },                     { "Unknown category: UNKNOWN" }}},
    {"UnitsOptionLowerCase",          {{ "con", "--units", "length" },                      { "Available units in the LENGTH category:" }}},
    {"UnitsOptionMixedCase",          {{ "con", "--units", "LenGth" },                      { "Available units in the LENGTH category:" }}},
    {"UnitsOptionMultiWordCategory",  {{ "con", "--units", "\"data transfer rate\"" },      { "Unknown category: \"data transfer rate\"" }}},
    {"ConstantsOption",               {{ "con", "--constants" },                            { "Available constants:" }}},
    {"ConstantsOptionShort",          {{ "con", "-C" },                                     { "Available constants:" }}},
    {"ConstantsOptionUnknownOpt",     {{ "con", "--constants", "unknown" },                 { "Unknown constant: unknown" }}},
    {"ConstantOption",                {{ "con", "--constants", "SPEED OF LIGHT" },          { "299792458" }}},
    {"ConstantOptionShort" ,          {{ "con", "-C", "PI" },                               { "3.141592653589793" }}},
    {"ConstantOptionShortUnknownOpt", {{ "con", "-C", "PI", "unknown" },                    { "Unknown option: unknown" }}},
    {"ConstantOptionUnknownOpt",      {{ "con", "--constants", "TAU", "unknown" },          { "Unknown option: unknown" }}},
    {"ConstantOptionUnknownConst",    {{ "con", "--constants", "UNKNOWN" },                 { "Unknown constant: UNKNOWN" }}},
    {"ConstantOptionLowerCase",       {{ "con", "--constants", "speed of light" },          { "299792458" }}},
    {"ConstantOptionMixedCase",       {{ "con", "--constants", "sPeeD oF LiGHt" },          { "299792458" }}},
    {"ConstantOptionSingleWord",      {{ "con", "--constants", "pi" },                      { "3.141592653589793" }}},
    {"ConstantOptionSingleWordMixed", {{ "con", "--constants", "Pi" },                      { "3.141592653589793" }}},
    {"UnknownOption",                 {{ "con", "--unknown" },                              { "Unknown or incomplete option: --unknown", "Usage: con" }}},
    {"IncompleteOption",              {{ "con", "--units" },                                { "Unknown or incomplete option: --units", "Usage: con" }}}
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
