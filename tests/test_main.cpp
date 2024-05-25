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

std::unordered_map<std::string, std::vector<std::vector<std::string> > > test_cases;
void initialize_test_cases_map()
{
    //        Name of test                          Test Arguments                                       Expected Output
    // ---------------------------------------------------------------------------------------------------------------------------------
    test_cases["NoArguments"]                   = { { "guc" },                                           { "No arguments provided.", "Usage: guc" } };
    test_cases["HelpOption"]                    = { { "guc", "--help" },                                 { "Usage: guc" } };
    test_cases["HelpOptionShort"]               = { { "guc", "-h" },                                     { "Usage: guc" } };
    test_cases["VersionOption"]                 = { { "guc", "--version" },                              { "Version 1.0" } };
    test_cases["VersionOptionShort"]            = { { "guc", "-v" },                                     { "Version 1.0" } };
    test_cases["UnitCategoriesOption"]          = { { "guc", "--unit-categories" },                      { "Available unit categories:" } };
    test_cases["UnitCategoriesOptionShort"]     = { { "guc", "-uc" },                                    { "Available unit categories:" } };
    test_cases["UnitCategoriesUnknownOpt"]      = { { "guc", "--unit-categories", "unknown" },           { "Unknown option: unknown" } };
    test_cases["UnitsOption"]                   = { { "guc", "--units", "LENGTH" },                      { "Available units in the LENGTH category:" } };
    test_cases["UnitsOptionShort"]              = { { "guc", "-u", "MASS" },                             { "Available units in the MASS category:" } };
    test_cases["UnitsOptionUnknownOpt"]         = { { "guc", "--units", "LENGTH", "unknown" },           { "Unknown option: unknown" } };
    test_cases["UnitsOptionUnknownCat"]         = { { "guc", "--units", "UNKNOWN" },                     { "Unknown category: UNKNOWN" } };
    test_cases["UnitsOptionLowerCase"]          = { { "guc", "--units", "length" },                      { "Available units in the LENGTH category:" } };
    test_cases["UnitsOptionMixedCase"]          = { { "guc", "--units", "LenGth" },                      { "Available units in the LENGTH category:" } };
    test_cases["UnitsOptionMultiWordCategory"]  = { { "guc", "--units", "\"data transfer rate\"" },      { "Unknown category: \"data transfer rate\"" } };
    test_cases["ConstantsOption"]               = { { "guc", "--constants" },                            { "Available constants:" } };
    test_cases["ConstantsOptionShort"]          = { { "guc", "-C" },                                     { "Available constants:" } };
    test_cases["ConstantsOptionUnknownOpt"]     = { { "guc", "--constants", "unknown" },                 { "Unknown constant: unknown" } };
    test_cases["ConstantOption"]                = { { "guc", "--constants", "SPEED OF LIGHT" },          { "299792458" } };
    test_cases["ConstantOptionShort"]           = { { "guc", "-C", "PI" },                               { "3.14159" } };
    test_cases["ConstantOptionShortUnknownOpt"] = { { "guc", "-C", "PI", "unknown" },                    { "Unknown option: unknown" } };
    test_cases["ConstantOptionUnknownOpt"]      = { { "guc", "--constants", "TAU", "unknown" },          { "Unknown option: unknown" } };
    test_cases["ConstantOptionUnknownConst"]    = { { "guc", "--constants", "UNKNOWN" },                 { "Unknown constant: UNKNOWN" } };
    test_cases["ConstantOptionLowerCase"]       = { { "guc", "--constants", "speed of light" },          { "299792458" } };
    test_cases["ConstantOptionMixedCase"]       = { { "guc", "--constants", "sPeeD oF LiGHt" },          { "299792458" } };
    test_cases["ConstantOptionSingleWord"]      = { { "guc", "--constants", "pi" },                      { "3.14159" } };
    test_cases["ConstantOptionSingleWordMixed"] = { { "guc", "--constants", "Pi" },                      { "3.14159" } };
    test_cases["UnknownOption"]                 = { { "guc", "--unknown" },                              { "Unknown or incomplete option: --unknown", "Usage: guc" } };
    test_cases["IncompleteOption"]              = { { "guc", "--units" },                                { "Unknown or incomplete option: --units", "Usage: guc" } };
}

TEST(UnitsTest, AllTestCases)
{
    initialize_test_cases_map();

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
