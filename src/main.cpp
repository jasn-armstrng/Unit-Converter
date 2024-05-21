// unites - Command-line utility for unit conversions
// (Temporarily) named unites after the French translation of units as units is already a cmdline util.
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstring>


std::unordered_map<std::string, std::vector<std::string> > conversion_categories;

void initialize_conversion_category_map();  // Function to initialize the map
void print_usage();  // Function to print program usage information
void display_categories();
void display_units(const std::string& category);
void handle_arguments(int argc, char* argv[]);


// Comment main to test
int main(int argc, char* argv[]) {
    handle_arguments(argc, argv);
    return 0;
}


void initialize_conversion_category_map() {
    conversion_categories["Temperature"] = { "celsius", "fahrenheit", "Kelvin" };
    conversion_categories["Length"] = { "nanometer", "millimeter", "centimeter", "meter", "kilometer", "inch", "feet", "yard", "furlong", "mile", "league", "nautical mile" };
    conversion_categories["Mass"] = { "milligram", "gram", "kilogram", "tonne", "ounce", "pound", "stone" };
    conversion_categories["Volume"] = { "milliliter", "centiliter", "liter", "fluid oz.", "gallon" };
    conversion_categories["Data"] = { "Bit", "Byte", "KiloByte", "MegaByte", "GigaByte", "TeraByte", "PetaByte" };
    conversion_categories["Time"] = { "nanosecond", "millisecond", "second", "minute", "hour", "day", "week", "year" };
    conversion_categories["Energy"] = { "Joule", "calorie", "Watt", "kilowatt", "BTU", "Quad", "therm", "horsepower" };
    conversion_categories["Pressure"] = { "Pascal", "atmosphere", "torr", "psi" };
    conversion_categories["Angle"] = { "degrees", "radians" };
}


void print_usage() {
    printf("Usage: unites [OPTIONS] <source_unit> <target_unit> <value1> <value2>  ...\n");
    printf("Options:\n");
    printf(" -h, --help               Display this help message and exit\n");
    printf(" -v, --version            Display version information and exit\n");
    printf(" --categories             Display available unit categories\n");
    printf(" --units <category>       Display available units in the specified category\n");
}


void display_categories() {
    std::cout << "Available unit categories:" << std::endl;
    for (const auto& [key, _] : conversion_categories) {
        std::cout << " - " << key << std::endl;
    }
}


void display_units(const std::string& category) {
    if (conversion_categories.find(category) != conversion_categories.end()) {
        std::cout << "Available units in the " << category << " category:" << std::endl;
        for (const auto& value : conversion_categories[category]) {
            std::cout << " - " << value << std::endl;
        }
    } else {
        std::cerr << "Unknown category: " << category << std::endl;
    }
}


void handle_arguments(int argc, char* argv[]) {
    // Check if no arguments were provided
    if (argc == 1) {
        printf("No arguments provided.\n");
        print_usage();
        return;
    }

    // Once we pass the check above we initialise the map of conversion categories and their units.
    // This is used in our argument checks below.
    // Would it make sense to do this initialisation at compile time?
    initialize_conversion_category_map();

    // We use the following conditional block to check the user's arguments and either report an error
    // or perform an action based on a legal input.
    // Check for help option
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_usage();
    } else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        printf("Version 1.0\n");
    } else if (strcmp(argv[1], "--categories") == 0) {
        if (argc == 2) {
            display_categories();
        } else {
            // Communicate bad option for any argument after --categories
            printf("Unknown option: %s\n", argv[2]);
        }
    } else if (strcmp(argv[1], "--units") == 0 && argc > 2) {
        display_units(argv[2]);
        if (argc > 3) {
            // Communicate bad option for any argument after --units <category>
            printf("Unknown option: %s\n", argv[3]);
        }
    } else {
        // Communicate general incorrect usage
        printf("Unknown or incomplete option: %s\n", argv[1]);
        print_usage();
    }
}
