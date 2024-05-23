// test_main.cpp: Contains all the tests for the unit converter application
#include <chrono>
#include <string>
#include <vector>

// Google test suite
#include <gtest/gtest.h>

// Include the functions you want to test
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

// To do: I have a lot more cases to write, how do I manage the test arguments list below?
// ---------------------------------------------------------------------------------------
// guc --help
// guc --version
// guc --categories Temperature
// guc --categories Length
// guc --categories Energy
// guc --units Energy
// guc --ca b
// guc --units
// guc --categories b
// guc --units Length
// guc --categories
// guc --units Data
// guc
// guc --units Energy b
// ---------------------------------------------------------------------------------------

TEST(UnitesTest, HelpOption)
{
    std::vector<std::string> args = {"guc", "--help"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Usage: guc") != std::string::npos);
}

TEST(UnitesTest, VersionOption)
{
    std::vector<std::string> args = {"guc", "--version"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Version 1.0") != std::string::npos);
}

TEST(UnitesTest, CategoriesOption)
{
    std::vector<std::string> args = {"guc", "--unit-categories"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Available unit categories:") != std::string::npos);
}

TEST(UnitesTest, UnitsOption)
{
    std::vector<std::string> args = {"guc", "--units", "Length"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Available units in the LENGTH category:") != std::string::npos);
}

TEST(UnitesTest, CategoriesTemperatureOption)
{
    std::vector<std::string> args = {"guc", "--unit-categories", "Temperature"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Unknown option: Temperature") != std::string::npos);
}

TEST(UnitesTest, CategoriesLengthOption)
{
    std::vector<std::string> args = {"guc", "--unit-categories", "Length"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Unknown option: Length") != std::string::npos);
}

TEST(UnitesTest, CategoriesEnergyOption)
{
    std::vector<std::string> args = {"guc", "--unit-categories", "Energy"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Unknown option: Energy") != std::string::npos);
}

TEST(UnitesTest, UnitsEnergyOption)
{
    std::vector<std::string> args = {"guc", "--units", "Energy"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Available units in the ENERGY category:") != std::string::npos);
}

TEST(UnitesTest, UnitsEnergyExtraOption) {
    std::vector<std::string> args = {"guc", "--units", "Energy", "b"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Unknown option: b") != std::string::npos);
}

TEST(UnitesTest, CaBOption)
{
    std::vector<std::string> args = {"guc", "--ca", "b"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Unknown or incomplete option: --ca") != std::string::npos);
}

TEST(UnitesTest, UnitsWithoutCategory)
{
    std::vector<std::string> args = {"guc", "--units"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Unknown or incomplete option: --units") != std::string::npos);
}

TEST(UnitesTest, CategoriesBOption)
{
    std::vector<std::string> args = {"guc", "--unit-categories", "b"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Unknown option: b") != std::string::npos);
}

TEST(UnitesTest, UnitsLengthOption)
{
    std::vector<std::string> args = {"guc", "--units", "Length"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Available units in the LENGTH category:") != std::string::npos);
}

TEST(UnitesTest, CategoriesWithoutArgument) {
    std::vector<std::string> args = {"guc", "--unit-categories"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Available unit categories:") != std::string::npos);
}

TEST(UnitesTest, UnitsDataOption)
{
    std::vector<std::string> args = {"guc", "--units", "Data"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("Available units in the DATA category:") != std::string::npos);
}

TEST(UnitesTest, NoArguments)
{
    std::vector<std::string> args = {"guc"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv)
        delete[] arg;

    EXPECT_TRUE(output.find("No arguments provided.\nUsage: guc") != std::string::npos);
}

int main(int argc, char** argv)
{
    // Log-out test runtime
    std::cout << "\033[36mTest runtime: " <<std::chrono::system_clock::now() << "\033[0m" << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
