// con - General Command-line utility for unit conversions
#include <cmath>
#include <iostream>
#include <string>

#include "../headers/common.h"

void print_usage(void);  // Function to print program usage information
void display_categories();
void display_units(const std::string& category);
void display_constants();
void display_constant(const std::string& constant);
void handle_arguments(int argc, char* argv[]);

// Comment main when running tests.
int main(int argc, char* argv[])
{
    handle_arguments(argc, argv);
    return 0;
}

void print_usage()
{
    printf("Usage: con [OPTIONS] <source_unit> <target_unit> <value1> <value2>  ...\n");
    printf("Options:\n");
    printf(" -h,  --help                 Display this help message and exit\n");
    printf(" -v,  --version              Display version information and exit\n");
    printf(" -c,  --unit-categories      Display available unit categories\n");
    printf(" -u,  --units <category>     Display available units in the specified category\n");
    printf(" -C,  --constants            Display available contants\n");
    printf(" -C,  --constants <constant> Display the value of the specified constant\n");
}

void display_categories()
{
    std::cout << "Available unit categories:" << std::endl;
    for (const auto& [key, _] : conversions)
        std::cout << " - " << key << std::endl;
}

void display_units(const std::string& category)
{
    std::string cat = to_upper(category);
    if (conversions.find(cat) != conversions.end())
    {
        std::cout << "Available units in the " << cat << " category:" << std::endl;
        for (const auto& value : conversions[cat])
            std::cout << " - " << value.first << std::endl;
    }
    else
        std::cout << "Unknown category: " << category << std::endl;
}

void display_constants()
{
    std::cout << "Available constants:" << std::endl;
    for (const auto& [key, value] : constants)
        // Display available constant and note about its implementation in the program
        std::cout << " - " << key << " " << value[1] << std::endl;
}

void display_constant(const std::string& constant)
{
    std::string cons = to_upper(constant);
    if (constants.find(cons) != constants.end())
        std::cout << constants[cons][0] << std::endl;
    else
        std::cout << "Unknown constant: " << constant << std::endl;
}

void handle_arguments(int argc, char* argv[])
{
    //                   User input validation:
    // ------------------ Check for arguments ----------------------------
    if (argc == 1)
    {
        std::cout << "No arguments provided." << std::endl;
        print_usage();
        return;
    }

    // ------------------ Check for help option ----------------------------
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        print_usage();
    // ------------------ Check for version option -------------------------
    else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
        std::cout << "Version 1.0" << std::endl;
    // ------------------ Check for version option -------------------------
    else if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--unit-categories") == 0)
    {
        if (argc == 2)
            display_categories();
        else
            std::cout << "Unknown option: " << argv[2] << std::endl;
    }
    // ---------------- Check units + unit option --------------------------
    else if ((strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "--units") == 0) && argc > 2)
    {
        if (argc == 3)
            display_units(argv[2]);
        else
            std::cout << "Unknown option: " << argv[3] << std::endl;
    }
    // ---------------- Check constants + CONSTANT option ------------------
    else if ((strcmp(argv[1], "-C") == 0 || strcmp(argv[1], "--constants") == 0) && argc > 2)
    {
        if (argc == 3)
            display_constant(argv[2]);
        else
            std::cout << "Unknown option: " << argv[3] << std::endl;
    }
    // ---------------- Check constants option ----------------------------
    // Note: This block has to match after constants + CONSTANT.
    else if (strcmp(argv[1], "-C") == 0 || strcmp(argv[1], "--constants") == 0)
    {
        if (argc == 2)
            display_constants();
        else
            std::cout << "Unknown option: " << argv[2] << std::endl;
    }
    else
    {
        std::cout << "Unknown or incomplete option: " << argv[1] << std::endl;
        print_usage();
    }
}
