// tests/test_main.cpp
#include <string>
#include <vector>
#include <cstring>

#include <gtest/gtest.h>

// Include the functions you want to test
#include "../src/main.cpp"

// Helper function to convert a vector of strings to an array of C-strings
std::vector<char*> create_argv(const std::vector<std::string>& args) {
    std::vector<char*> argv;
    for (const auto& arg : args) {
        char* cstr = new char[arg.size() + 1];
        std::strcpy(cstr, arg.c_str());
        argv.push_back(cstr);
    }
    argv.push_back(nullptr);
    return argv;
}

// The tests for the following arguments below
// unites --help
// unites --version
// unites --categories Temperature
// unites --categories Length
// unites --categories Energy
// unites --units Energy
// unites --ca b
// unites --units
// unites --categories b
// unites --units Length
// unites --categories
// unites --units Data
// unites

TEST(UnitesTest, HelpOption) {
    std::vector<std::string> args = {"unites", "--help"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Usage: unites") != std::string::npos);
}

TEST(UnitesTest, VersionOption) {
    std::vector<std::string> args = {"unites", "--version"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Version 1.0") != std::string::npos);
}

TEST(UnitesTest, CategoriesOption) {
    std::vector<std::string> args = {"unites", "--categories"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Available unit categories:") != std::string::npos);
}

TEST(UnitesTest, UnitsOption) {
    std::vector<std::string> args = {"unites", "--units", "Length"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Available units in the Length category:") != std::string::npos);
}

TEST(UnitesTest, CategoriesTemperatureOption) {
    std::vector<std::string> args = {"unites", "--categories", "Temperature"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Unknown option: Temperature") != std::string::npos);
}

TEST(UnitesTest, CategoriesLengthOption) {
    std::vector<std::string> args = {"unites", "--categories", "Length"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Unknown option: Length") != std::string::npos);
}

TEST(UnitesTest, CategoriesEnergyOption) {
    std::vector<std::string> args = {"unites", "--categories", "Energy"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Unknown option: Energy") != std::string::npos);
}

TEST(UnitesTest, UnitsEnergyOption) {
    std::vector<std::string> args = {"unites", "--units", "Energy"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Available units in the Energy category:") != std::string::npos);
}

TEST(UnitesTest, CaBOption) {
    std::vector<std::string> args = {"unites", "--ca", "b"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Unknown or incomplete option: --ca") != std::string::npos);
}

TEST(UnitesTest, UnitsWithoutCategory) {
    std::vector<std::string> args = {"unites", "--units"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Unknown or incomplete option: --units") != std::string::npos);
}

TEST(UnitesTest, CategoriesBOption) {
    std::vector<std::string> args = {"unites", "--categories", "b"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Unknown option: b") != std::string::npos);
}

TEST(UnitesTest, UnitsLengthOption) {
    std::vector<std::string> args = {"unites", "--units", "Length"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Available units in the Length category:") != std::string::npos);
}

TEST(UnitesTest, CategoriesWithoutArgument) {
    std::vector<std::string> args = {"unites", "--categories"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Available unit categories:") != std::string::npos);
}

TEST(UnitesTest, UnitsDataOption) {
    std::vector<std::string> args = {"unites", "--units", "Data"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("Available units in the Data category:") != std::string::npos);
}

TEST(UnitesTest, NoArguments) {
    std::vector<std::string> args = {"unites"};
    auto argv = create_argv(args);

    testing::internal::CaptureStdout();
    handle_arguments(args.size(), argv.data());
    std::string output = testing::internal::GetCapturedStdout();

    for (char* arg : argv) {
        delete[] arg;
    }

    EXPECT_TRUE(output.find("No arguments provided.\nUsage: unites") != std::string::npos);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
