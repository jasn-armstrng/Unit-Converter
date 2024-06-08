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
    {"NoArguments",                   {{ "uc" },                                           { "No arguments provided.", "Usage: uc" }}},
    {"HelpOption",                    {{ "uc", "--help" },                                 { "Usage: uc" }}},
    {"HelpOptionShort",               {{ "uc", "-h" },                                     { "Usage: uc" }}},
    {"VersionOption",                 {{ "uc", "--version" },                              { "Version 1.0" }}},
    {"VersionOptionShort",            {{ "uc", "-v" },                                     { "Version 1.0" }}},
    {"ListCategoriesOption",          {{ "uc", "-c" },                                     { "1  TEMPERATURE\n2  VOLUME\n3  DISTANCE\n4  TIME\n5  MASS\n6  AREA\n7  DATA\n" }}},
    {"ListCategoriesUnknownOption",   {{ "uc", "-c", "unknown" },                          { "Unknown option: unknown", "Usage: uc" }}},
    {"ListUnitsOption",               {{ "uc", "-u", "distance" },                         { "1  Meter               m\n2  Kilometer           km\n3  Centimeter          cm\n4  Millimeter          mm\n5  Micrometer          μm\n6  Nanometer           nm\n7  Inch                in\n8  Foot                ft\n9  Yard                yd\n10 Mile                mi\n" }}},
    {"ListUnitsOptionUppercase",      {{ "uc", "-u", "DISTANCE" },                         { "1  Meter               m\n2  Kilometer           km\n3  Centimeter          cm\n4  Millimeter          mm\n5  Micrometer          μm\n6  Nanometer           nm\n7  Inch                in\n8  Foot                ft\n9  Yard                yd\n10 Mile                mi\n" }}},
    {"ListUnitsOptionMissingArg",     {{ "uc", "-u" },                                     { "Missing argument for -u option.", "Usage: uc" }}},
    {"ListUnitsOptionUnknownUnit",    {{ "uc", "-u", "unknown" },                          { "Unknown category: unknown" }}},
    {"ListUnitsOptionExtraArg",       {{ "uc", "-u", "length", "extra" },                  { "Unknown option: extra", "Usage: uc" }}},
    {"ConvertUnitLength",             {{ "uc", "10", "m", "ft" },                          { "32.8084" }}},
    {"ConvertUnitMass",               {{ "uc", "1", "kg", "lb" },                          { "2.2046" }}},
    {"ConvertUnitTemperature",        {{ "uc", "100", "C", "F" },                          { "212.0000" }}},
    {"ConvertUnitInvalidValue",       {{ "uc", "invalid", "m", "ft" },                     { "Invalid argument: invalid is not a valid number.", "Usage: uc" }}},
    {"ConvertUnitLargeValue",         {{ "uc", "1e100", "m", "ft" },                       { "32808398950131232914215958810306863119312337781052860287712980133542969684475715558098231427537567744.0000" }}},
    {"ConvertUnitUnknownFromUnit",    {{ "uc", "10", "unknown", "ft" },                    { "Unknown unit: unknown" }}},
    {"ConvertUnitUnknownToUnit",      {{ "uc", "10", "m", "unknown" },                     { "Unknown unit: unknown" }}},
    {"ConvertUnitIncompatibleUnits",  {{ "uc", "10", "m", "g" },                           { "Cannot convert between: m and g" }}},
    {"ConvertUnitExtraArgument",      {{ "uc", "10", "m", "ft", "extra" },                 { "Unknown or incomplete option.", "Usage: uc" }}},
    {"UnknownOption",                 {{ "uc", "--unknown" },                              { "Unknown or incomplete option.", "Usage: uc" }}},
    {"IncompleteOption",              {{ "uc", "-" },                                      { "Unknown or incomplete option.", "Usage: uc" }}}
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
bool run_test_case(const std::string& test_name, const std::vector<std::string>& args, const std::string& expected_output, Units& u)
{
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    uc(args.size(), argv.data(), u);
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

    Units allUnits;
    loadConvertibleUnits(allUnits);

    for (const auto& test_case : test_cases)
    {
        const std::string& test_name = test_case.first;
        const std::vector<std::string>& args = test_case.second[0];
        const std::string& expected_output = test_case.second[1][0];

        const std::string run = std::format("\033[32m[ RUN      ]\033[0m - {}", test_name);
        std::cout << run << std::endl;

        bool test_passed = run_test_case(test_name, args, expected_output, allUnits);
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
