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
void run_test_case(const std::string& test_name, const std::vector<std::string>& args, const std::string& expected_output)
{
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find(expected_output) != std::string::npos) << "Test case failed: " << test_name;
}

std::unordered_map<std::string, std::vector<std::vector<std::string> > > test_cases;
void initialize_test_cases_map()
{
    test_cases["HelpOption"] = { { "guc", "--help" }, { "Usage: guc" } };
    test_cases["VersionOption"] = { {"guc", "--version"}, { "Version 1.0" } };
    // Rest of tests ...
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

        run_test_case(test_name, args, expected_output);

        test_counter++;

        const std::string ok = std::format("\033[32m[       OK ]\033[0m - {}. Passed: {}/{}", test_name, test_counter, total_tests);
        std::cout << ok << std::endl;
    }
}

int main(int argc, char** argv)
{
    const std::string tests_start = format("\033[33mTests Start: {}\033[0m", std::chrono::system_clock::now());
    std::cout << tests_start << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
