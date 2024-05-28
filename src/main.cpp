// guc - (GNU/General) Command-line utility for unit conversions
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Covert static std::unordered_map<std::string, std::vector<std::string> > categories into a map that
// allows for the unit conversion factors to be defined in a category.
using conversion_factor_map = std::unordered_map<std::string, std::unordered_map<std::string, double> >;
static conversion_factor_map conversion_factors =
// To do:
// 1. Establish the base unit of each category. We will first convert our <unit_from> to the base
// unit then convert to the <unit_to> via its conversion factor. This is possible because of the linear
// scaling relationship between the units of the categories.
//
// 2. Add the conversion factors.
//
// 3. Move the maps and functions to a header or shared objects file. I don't know if shared object file
// is the right file I'm thinking should be used here.
{
    // Category
    {"TEMPERATURE",{
        // Unit ... Conversion factor
        {"celsius", 0.0},
        {"fahrenheit", 0.0},
        {"Kelvin", 0.0}
    }},
    {"LENGTH",{
        {"nanometer", 0.0},
        {"millimeter", 0.0},
        {"centimeter", 0.0},
        {"meter", 0.0},
        {"kilometer", 0.0},
        {"inch", 0.0},
        {"feet", 0.0},
        {"yard", 0.0},
        {"furlong", 0.0},
        {"mile", 0.0},
        {"league", 0.0},
        {"nautical mile", 0.0}
    }},
    {"MASS",{
        {"milligram", 0.0},
        {"gram", 0.0},
        {"kilogram", 0.0},
        {"tonne", 0.0},
        {"ounce", 0.0},
        {"pound", 0.0},
        {"stone", 0.0}
    }},
    {"VOLUME",{
        {"milliliter", 0.0},
        {"centiliter", 0.0},
        {"liter", 0.0},
        {"fluid oz.", 0.0},
        {"gallon", 0.0}
    }},
    {"DATA",{
        {"Bit", 0.0},
        {"Byte", 0.0},
        {"KiloByte", 0.0},
        {"MegaByte", 0.0},
        {"GigaByte", 0.0},
        {"TeraByte", 0.0},
        {"PetaByte", 0.0}
    }},
    {"TIME",{
        {"nanosecond", 0.0},
        {"millisecond", 0.0},
        {"second", 0.0},
        {"minute", 0.0},
        {"hour", 0.0},
        {"day", 0.0},
        {"week", 0.0},
        {"year", 0.0}
    }},
    {"ENERGY",{
        {"Joule", 0.0},
        {"calorie", 0.0},
        {"Watt", 0.0},
        {"kilowatt", 0.0},
        {"BTU", 0.0},
        {"Quad", 0.0},
        {"therm", 0.0},
        {"horsepower", 0.0}
    }},
    {"PRESSURE",{
        {"Pascal", 0.0},
        {"atmosphere", 0.0},
        {"torr", 0.0},
        {"psi", 0.0}
    }},
    {"ANGLE",{
        {"degrees", 0.0},
        {"radians", 0.0}
    }}
};

static std::unordered_map<std::string, std::vector<std::string> > constants =
{
    // Constant name
    {"SPEED OF LIGHT",
        // Value ...... Note or measurement unit
        { "299792458", "[meters/second]" }
    },
    {"PI", { "3.141592653589793", "" }},
    {"ROOT 2", { "1.414213562373095", "" }},
    {"PHI", { "1.618033988749894", "" }},
    {"TAU", { "6.283185307179586", "" }},
    {"E", { "2.718281828459045", "" }}
};

// Function declarations.
// To do: Move function decs and defs to a header file.
std::string to_upper(const std::string& str);
void print_usage(void);  // Function to print program usage information
void display_categories();
void display_units(const std::string& category);
void display_constants();
void display_constant(const std::string& constant);
void handle_arguments(int argc, char* argv[]);

// Comment main when running tests.
// int main(int argc, char* argv[])
// {
//     handle_arguments(argc, argv);
//     return 0;
// }

std::string to_upper(const std::string& str)
{
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), [](unsigned char c)
    {
        return std::toupper(c);
    });
    return upperStr;
}

void print_usage()
{
    printf("Usage: guc [OPTIONS] <source_unit> <target_unit> <value1> <value2>  ...\n");
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
    for (const auto& [key, _] : conversion_factors)
        std::cout << " - " << key << std::endl;
}

void display_units(const std::string& category)
{
    std::string cat = to_upper(category);
    if (conversion_factors.find(cat) != conversion_factors.end())
    {
        std::cout << "Available units in the " << cat << " category:" << std::endl;
        for (const auto& value : conversion_factors[cat])
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
        std::cout << "Version 1.0\n" << std::endl;
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
