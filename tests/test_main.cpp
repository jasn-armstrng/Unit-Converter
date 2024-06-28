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
static std::unordered_map<std::string, std::vector<std::vector<std::string>>> test_cases =
{
    // Name of test                           Test Arguments                                        Expected Output
    // ---------------------------------------------------------------------------------------------------------------------------------
    {"NoArguments",                           {{ "uc" },                                           { "No arguments provided.", "Usage: uc" }}},
    {"HelpOption",                            {{ "uc", "--help" },                                 { "Usage: uc" }}},
    {"HelpOptionShort",                       {{ "uc", "-h" },                                     { "Usage: uc" }}},
    {"VersionOption",                         {{ "uc", "--version" },                              { "Version 1.0" }}},
    {"VersionOptionShort",                    {{ "uc", "-v" },                                     { "Version 1.0" }}},
    {"ListCategoriesUnknownOption",           {{ "uc", "-c", "unknown" },                          { "Unknown option: unknown", "Usage: uc" }}},
    {"ListUnitsOptionMissingArg",             {{ "uc", "-u" },                                     { "Missing argument for -u option.", "Usage: uc" }}},
    {"ListUnitsOptionUnknownUnit",            {{ "uc", "-u", "unknown" },                          { "Unknown category: unknown" }}},
    {"ListUnitsOptionExtraArg",               {{ "uc", "-u", "length", "extra" },                  { "Unknown option: extra", "Usage: uc" }}},
    {"ConvertUnitLength",                     {{ "uc", "10", "m", "ft" },                          { "32.8084" }}},
    {"ConvertUnitMass",                       {{ "uc", "1", "kg", "lb" },                          { "2.2046" }}},
    {"ConvertUnitTemperature",                {{ "uc", "100", "C", "F" },                          { "212.0000" }}},
    {"ConvertUnitTemperatureCelsiusToKelvin", {{ "uc", "0", "C", "K" },                            { "273.1500" }}},
    {"ConvertUnitTemperatureKelvinToCelsius", {{ "uc", "300", "K", "C" },                          { "26.8500" }}},
    {"ConvertUnitTemperatureKelvinToFahrenheit", {{ "uc", "250", "K", "F" },                       { "-9.6700" }}},
    {"ConvertUnitTemperatureFahrenheitToCelsius", {{ "uc", "50", "F", "C" },                       { "10.0000" }}},
    {"ConvertUnitTemperatureFahrenheitToKelvin", {{ "uc", "100", "F", "K" },                        { "310.9278" }}},
    {"ConvertUnitTemperatureCelsiusToFahrenheit", {{ "uc", "-40", "C", "F" },                       { "-40.0000" }}},
    {"ConvertUnitVolume",                     {{ "uc", "5", "l", "gal" },                          { "1.3209" }}},
    {"ConvertUnitArea",                       {{ "uc", "100", "m^2", "ft^2" },                     { "1076.3915" }}},
    {"ConvertUnitData",                       {{ "uc", "1", "GB", "MB" },                          { "1000.0000" }}},
    {"ConvertUnitInvalidValue",               {{ "uc", "invalid", "m", "ft" },                     { "Invalid argument: invalid is not a valid number.", "Usage: uc" }}},
    {"ConvertUnitOutOfRangeValue",            {{ "uc", "1e1000", "m", "ft" },                      { "Out of range: 1e1000 is too large or too small.", "Usage: uc" }}},
    {"ConvertUnitUnknownFromUnit",            {{ "uc", "10", "unknown", "ft" },                    { "Unknown unit: unknown" }}},
    {"ConvertUnitUnknownToUnit",              {{ "uc", "10", "m", "unknown" },                     { "Unknown unit: unknown" }}},
    {"ConvertUnitIncompatibleUnits",          {{ "uc", "10", "m", "g" },                           { "Cannot convert between: m and g" }}},
    {"ListConstantsGroupsUnknownOption",      {{ "uc", "-Cg", "unknown" },                         { "Unknown option: unknown", "Usage: uc" }}},
    {"ListConstantsOptionMissingArg",         {{ "uc", "-C" },                                     { "Missing argument for -C option.", "Usage: uc" }}},
    {"ListConstantsOptionUnknownGroup",       {{ "uc", "-C", "unknown" },                          { "Unknown group: unknown" }}},
    {"ListConstantsOptionExtraArg",           {{ "uc", "-C", "physics", "extra" },                 { "Unknown option: extra", "Usage: uc" }}},
    {"ListConstantsDetailedOptionUnknownArg", {{ "uc", "-Cd", "unknown" },                         { "Unknown option: unknown", "Usage: uc" }}},
    {"GetConstantValue",                      {{ "uc", """Speed of Light in Vacuum""" },           { "299792458" }}},
    {"GetConstantValueSymbol",                {{ "uc", "c" },                                      { "299792458" }}},
    {"GetConstantValueUnknown",               {{ "uc", "unknown" },                                { "Unknown constant: unknown" }}},
    {"GetConstantValueExtraArg",              {{ "uc", "c", "extra" },                             { "Unknown or incomplete option.", "Usage: uc" }}},
    {"UnknownOption",                         {{ "uc", "--unknown" },                              { "Unknown or incomplete option.", "Usage: uc" }}},
    {"IncompleteOption",                      {{ "uc", "-" },                                      { "Unknown or incomplete option.", "Usage: uc" }}}
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
bool run_test_case(const std::string& test_name, const std::vector<std::string>& args, const std::string& expected_output, Units& u, Constants& c)
{
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    uc(args.size(), argv.data(), u, c);
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

    Units allUnits = loadUnits();
    Constants allConstants = loadConstants();

    for (const auto& test_case : test_cases)
    {
        const std::string& test_name = test_case.first;
        const std::vector<std::string>& args = test_case.second[0];
        const std::string& expected_output = test_case.second[1][0];

        const std::string run = std::format("\033[32m[ RUN      ]\033[0m - {}", test_name);
        std::cout << run << std::endl;

        bool test_passed = run_test_case(test_name, args, expected_output, allUnits, allConstants);
        if (test_passed)
        {
            test_counter++;
            const std::string ok = std::format("\033[32m[       OK ]\033[0m - {}. Passed: {}/{}", test_name, test_counter, total_tests);
            std::cout << ok << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    auto utcNow = std::chrono::system_clock::now();
    auto localNow = utcNow - std::chrono::hours(4);

    const std::string tests_start = format("\033[33mTests Start: {}\033[0m",  localNow);
    std::cout << tests_start << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
