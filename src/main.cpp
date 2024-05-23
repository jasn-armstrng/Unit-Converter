// guc - (GNU/General) Command-line utility for unit conversions
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Globally accessed maps.
// Can I move this to a header file?
std::unordered_map<std::string, std::vector<std::string> > categories;
std::unordered_map<std::string, std::vector<std::string> > constants;

// Function declarations.
// To do: Move function decs and defs to a header file.
std::string to_upper(const std::string& str);
void initialize_categories_map();
void initialize_constants_map();
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

std::string to_upper(const std::string& str)
{
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), [](unsigned char c)
    {
        return std::toupper(c);
    });
    return upperStr;
}

void initialize_categories_map()
{
    categories["TEMPERATURE"] = { "celsius", "fahrenheit", "Kelvin" };
    categories["LENGTH"] = { "nanometer", "millimeter", "centimeter", "meter", "kilometer", "inch", "feet", "yard", "furlong", "mile", "league", "nautical mile" };
    categories["MASS"] = { "milligram", "gram", "kilogram", "tonne", "ounce", "pound", "stone" };
    categories["VOLUME"] = { "milliliter", "centiliter", "liter", "fluid oz.", "gallon" };
    categories["DATA"] = { "Bit", "Byte", "KiloByte", "MegaByte", "GigaByte", "TeraByte", "PetaByte" };
    categories["TIME"] = { "nanosecond", "millisecond", "second", "minute", "hour", "day", "week", "year" };
    categories["ENERGY"] = { "Joule", "calorie", "Watt", "kilowatt", "BTU", "Quad", "therm", "horsepower" };
    categories["PRESSURE"] = { "Pascal", "atmosphere", "torr", "psi" };
    categories["ANGLE"] = { "degrees", "radians" };
}

void initialize_constants_map()
{
    constants["SPEED OF LIGHT"] = { "299,792,458 meters/second", "1,079,252,848.8 kilometers/hour", "186,282.397 miles/second" };
    constants["PI"] = { "3.14159" };
    constants["ROOT 2"] = { "1.41421" };
    constants["PHI"] = { "1.61803" };
    constants["TAU"] = { "6.28318" };
    constants["E"] = { "2.71828" };
}

void print_usage()
{
    printf("Usage: guc [OPTIONS] <source_unit> <target_unit> <value1> <value2>  ...\n");
    printf("Options:\n");
    printf(" -h,  --help                 Display this help message and exit\n");
    printf(" -v,  --version              Display version information and exit\n");
    printf(" -uc, --unit-categories      Display available unit categories\n");
    printf(" -u,  --units <category>     Display available units in the specified category\n");
    // To do: Write test for the below and the updated switches
    printf(" -C,  --constants            Display available contants\n");
    printf(" -C,  --constants <constant> Display the value of the specified constant\n");
}

void display_categories()
{
    std::cout << "Available unit categories:" << std::endl;
    for (const auto& [key, _] : categories)
        std::cout << " - " << key << std::endl;
}

void display_units(const std::string& category)
{
    std::string cat = to_upper(category);
    if (categories.find(cat) != categories.end())
    {
        std::cout << "Available units in the " << cat << " category:" << std::endl;
        for (const auto& value : categories[cat])
            std::cout << " - " << value << std::endl;
    }
    else
    {
        std::cout << "Unknown category: " << category << std::endl;

    }
}

void display_constants()
{
    std::cout << "Available constants:" << std::endl;
    for (const auto& [key, _] : constants)
        std::cout << " - " << key << std::endl;
}

void display_constant(const std::string& constant)
{
    std::string cons = to_upper(constant);
    if (constants.find(cons) != constants.end())
    {
        std::cout << cons << ":" << std::endl;
        for (const auto& value : constants[cons])
            std::cout << value << std::endl;
    }
    else
    {
        std::cout << "Unknown constant: " << constant << std::endl;
    }
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
    // Initialise Category/Units and Constants maps accessed below.
    // Can initialisation at compile time?
    initialize_categories_map();
    initialize_constants_map();
    // ------------------ Check for help option ----------------------------
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        print_usage();
    // ------------------ Check for version option -------------------------
    else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
        std::cout << "Version 1.0\n" << std::endl;
    // ------------------ Check for version option -------------------------
    else if (strcmp(argv[1], "-uc") == 0 || strcmp(argv[1], "--unit-categories") == 0)
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
