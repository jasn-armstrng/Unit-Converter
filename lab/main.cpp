/*
Program queries:
================
    Convert unit:
        <program_name> <amount> <unit_from> <unit_to>

    List unit categories:
        <program_name> -c

    List units under a category:
        <program_name> -u <category_name>

    List constants:
        <program_name> -C

    Show all details for constant:
        <program_name> -C <constant_name>

    Show value (only) for constant:
        <program_name> -Cv <constant_name>


Data structures:
================
    Types
        1. struct Unit;
        2. struct Constants;

    Tables:
        1. Units map: unit, Unit
        2. Constants map: constant, Constants
        3. Categories vector: category


Program flow:
=============
    Convert unit:
        <program_name> <amount> <unit_from> <unit_to>
            if <unit_from> in (Unit/Category) && <unit_to> in (Unit/Category) && Unit/Category[<unit_from>] == Unit/Category[<unit_to>]
            {
                double conversion = (<amount> *  Units[<unit_from>].conversion_factor) / Units[<unit_to>].conversion_factor
                std::cout << conversion
            }

    List unit categories:
        <program_name> -c
            for category in
            {
                std::cout << value <<
            }

    List units under a category:
        <program_name> -u <category_name>
            for key, value in Unit/Category
            {
                if lower(value) == lower(<category_name>)
                    std::cout << key
            }

    List constants:
        <program_name> -C
            for key, val in constant, category
            {
                std::cout << index << [category] << constant
            }

    Show all details for constant:
        <program_name> -Cd <constant_name>
            if <constant_name> in Constants
                std::cout << Constants[<constant_name>]constant.name ...
            else
                error

    Show value (only) for constant:
        <program_name> -Cv <constant_name>
        if <constant_name> in Constants
            std::cout << Constants[<constant_name>]constant.value
        else
            error
*/
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Data structures
struct Unit
{
    std::string category;
    std::string name;
    std::string symbol;
    double conversion_factor;
};

struct Constant
{
    std::string category;
    std::string name;
    std::string symbol;
    std::string value;
    std::string unit;
};

std::unordered_map<std::string, Unit> units;
std::unordered_map<std::string, Constant> constants;
std::unordered_set<std::string> unit_categories;
std::unordered_set<std::string> constant_categories;

// Function declarations
void load_conversion_units();
void load_constants();
void print_usage();  // Function to print program usage information
void list_unit_categories();
void list_units(const std::string& category);
void list_constant_categories();
void list_constants();
void show_constant_value(const std::string& constant);
void show_constant_detail(const std::string& constant);
void con(int argc, char* argv[]);
std::string to_upper(const std::string& str);

int main(int argc, char* argv[])
{
    load_conversion_units(); // To answer:
    // <program_name> <amount> <unit_from> <unit_to>
    // <program_name> -u <category_name>
    // <program_name> -c

    load_constants();       // To answer:
    // <program_name> -Cd <constant_name>
    // <program_name> -Cv <constant_name>
    // <program_name> -C
    con(argc, argv);

    return 0;
}

// Function definitions
void load_conversion_units()
{
    // Load the conversion unit details from file into map
    std::string conversion_units_file = "conversion_units.dat";
    std::ifstream inputFile(conversion_units_file);

    if(!inputFile)
        std::cout << "Failed to open " << conversion_units_file << std::endl;

    std::string line;
    while(std::getline(inputFile, line))
    {
        // conversion_units.dat is a fixed column-width delimited file
        std::string category = line.substr(0,12);
        std::string name = line.substr(12,16);
        std::string symbol = line.substr(28,8);
        std::string conversion_factor = line.substr(36,20);

        // Trim whitespace
        category.erase(category.find_last_not_of(" \t") + 1);
        name.erase(name.find_last_not_of(" \t") + 1);
        symbol.erase(symbol.find_last_not_of(" \t") + 1);
        conversion_factor.erase(conversion_factor.find_last_not_of(" \t") + 1);

        Unit unit = {to_upper(category), name, symbol, std::stod(conversion_factor)};
        units[unit.name] = unit;
    }

    // Load the unique constant categories into secondary map
    for(const auto& [_, value] : units)
        unit_categories.insert(value.category);
}

void load_constants()
{
    // Load the constants details from file into map
    std::string constants_file = "constants.dat";
    std::ifstream inputFile(constants_file);

    if(!inputFile)
        std::cout << "Failed to open " << constants_file << std::endl;

    std::string line;
    while(std::getline(inputFile, line))
    {
        // contants.dat is a fixed column-width delimited file
        std::string category = line.substr(0,16);
        std::string name = line.substr(16,32);
        std::string symbol = line.substr(48,9);
        std::string value = line.substr(60,20);
        std::string unit = line.substr(80,20);

        // Trim whitespace
        category.erase(category.find_last_not_of(" \t") + 1);
        name.erase(name.find_last_not_of(" \t") + 1);
        symbol.erase(symbol.find_last_not_of(" \t") + 1);
        value.erase(value.find_last_not_of(" \t") + 1);
        unit.erase(unit.find_last_not_of(" \t") + 1);

        Constant constant = {category, name, symbol, value, unit};
        constants[to_upper(constant.name)] = constant;
    }

    // Load the unique constant categories into secondary map
    for(const auto& [_, value] : constants)
        constant_categories.insert(value.category);
}

void print_usage()
{
    printf("Usage: con [OPTIONS] <value> <from_unit> <to_unit>\n");
    printf("Options:\n");
    printf(" -h, --help         Display this help message and exit\n");
    printf(" -v, --version      Display version information and exit\n");
    printf(" -uc                Display available unit categories\n");
    printf(" -u <unit-category> Display available units in the specified category\n");
    printf(" -cc                Display available constant catgories\n");
    printf(" -cs                Display available constants\n");
    printf(" -c <constant>      Display the value of the specified constant\n");
    printf(" -cd <constant>     Display details of the specified constant\n");
}

void convert(const std::string& amount, const std::string& unit_from, const std::string& unit_to)
{
    double amount_for_conversion = std::stod(amount);

}

// con -uc
void list_unit_categories()
{
    std::cout << "[Unit categories]:\n" << std::endl;
    for(const auto& category : unit_categories)
        std::cout << category << std::endl;
}

// con -u <category>
void list_units(const std::string& category)
{
    std::string cat = to_upper(category);
    if (unit_categories.find(cat) != unit_categories.end())
    {
        std::cout << "[Units in " << cat << "]:\n" << std::endl;
        for (const auto& [key, value] : units)
        {
            if (value.category == cat)
                std::cout << value.name << "," << value.symbol << std::endl;
        }
    }
    else
        std::cout << "Unknown category: " << category << std::endl;
}

// con -cc
void list_constant_categories()
{
    std::cout << "[Constant categories]:\n" << std::endl;
    for(const auto& category : constant_categories)
        std::cout << category << std::endl;
}

// con -cs
void list_constants()
{
    std::cout << std::left;
    std::cout << "[Constants]:\n" << std::endl;
    for (const auto& [_, value] : constants)
        std::cout << value.name <<std::endl;
}

// con -c <constant>
void show_constant_value(const std::string& constant)
{
    std::string cons = to_upper(constant);
    if (constants.find(cons) != constants.end())
        std::cout << constants[cons].value << std::endl;
    else
        std::cout << "Unknown constant: " << constant << std::endl;
}

void show_constant_detail(const std::string& constant)
{
    std::string C = to_upper(constant);
    if (constants.find(C) != constants.end())
        std::cout << constants[C].name << "\t" << constants[C].symbol << "\t" << constants[C].value << "\t" << constants[C].unit << std::endl;
    else
        std::cout << "Unknown constant: " << constant << std::endl;
}

void con(int argc, char* argv[])
{
    // Check for arguments
    if (argc == 1)
    {
        std::cout << "No arguments provided." << std::endl;
        print_usage();
        return;
    }

    // Check for help option
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        print_usage();
    // Check for version option
    else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
        std::cout << "Version 1.0" << std::endl;
    // Check for unit categories option
    else if (strcmp(argv[1], "-uc") == 0)
    {
        if (argc == 2)
            list_unit_categories();
        else
            std::cout << "Unknown option: " << argv[2] << std::endl;
    }
    // Check -u <unit-category> option
    else if (strcmp(argv[1], "-u") == 0 && argc > 2)
    {
        if (argc == 3)
            list_units(argv[2]);
        else
            std::cout << "Unknown option: " << argv[3] << std::endl;
    }
    // Check show value for constant
    else if (strcmp(argv[1], "-c") == 0 && argc > 2)
    {
        if (argc == 3)
            show_constant_value(argv[2]);
        else
            std::cout << "Unknown option: " << argv[3] << std::endl;
    }
    else if (strcmp(argv[1], "-cd") == 0 && argc > 2)
    {
        if (argc == 3)
            show_constant_detail(argv[2]);
        else
            std::cout << "Unknown option: " << argv[3] << std::endl;
    }
    // Check show all constants option
    else if (strcmp(argv[1], "-cs") == 0)
    {
        if (argc == 2)
            list_constants();
        else
            std::cout << "Unknown option: " << argv[2] << std::endl;
    }
    //
    else if (strcmp(argv[1], "-cc") == 0)
    {
        if (argc == 2)
            list_constant_categories();
        else
            std::cout << "Unknown option: " << argv[2] << std::endl;
    }
    else
    {
        std::cout << "Unknown or incomplete option: " << argv[1] << std::endl;
        print_usage();
    }
}

std::string to_upper(const std::string& str)
{
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), [](unsigned char c)
    {
        return std::toupper(c);
    });
    return upperStr;
}
