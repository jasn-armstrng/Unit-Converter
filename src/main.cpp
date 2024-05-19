// unitconv - Command-line utility for unit conversions
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::vector<std::string> > conversion_categories;
void initialize_conversion_category_map();  // Function to initialize the map
void print_usage();  // Function to print program usage information

int main(int argc, char *argv[]) {
    // Check if no arguments were provided
    if (argc == 1) {
        printf("No arguments provided.\n");
        print_usage();
        return 1;
    }

    initialize_conversion_category_map();

    // Loop through each argument
    for (int i = 1; i < argc; i++) {
        // Check for help option
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage();
            return 0;
        }

        // Check for version option
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            printf("Version 1.0\n");
            return 0;
        }

        // Check for conversion categories option
        if (strcmp(argv[i], "--categories") == 0) {
            std::cout << "Available unit categories:" << std::endl;
            for (const auto& [key, _] : conversion_categories) {
                    std::cout << " - " << key << std::endl;
            }
            return 0;
        }
        else if (strcmp(argv[i], "--units") == 0 && conversion_categories.find(argv[i+1]) != conversion_categories.end()) {
            std::cout << "Available units in the " << argv[i+1] << " category:" << std::endl;

            for (const auto& value : conversion_categories[argv[i+1]]) {
                    std::cout << " - " << value << std::endl;
            }
            return 0;
        }
        else {
            printf("Unknown option: %s\n", argv[i]);
            print_usage();
            return 1;
        }
    }

    return 0;
}

void initialize_conversion_category_map() {
    conversion_categories["Temperature"] = { "celsius", "fahrenheit", "Kelvin" };
    conversion_categories["Length"] = { "nanometer", "millimeter", "centimeter", "meter", "kilometer", "inch", "feet", "yard", "furlong", "mile", "league", "nautical mile" };
    conversion_categories["Mass"] = { "milligram", "gram", "Kilogram", "Tonne", "ounce", "Pound", "Stone", };
    conversion_categories["Volume"] = { "milliliter", "centiliter", "liter", "fluid oz.", "gallon" };
    conversion_categories["Data Size"] = { "Bit", "Byte", "KiloByte", "MegaByte", "GigaByte", "TeraByte", "PetaByte" };
    conversion_categories["Time"] = { "nanosecond", "millisecond", "second", "minute", "hour", "day", "week", "year" };
    conversion_categories["Energy"] = { "Joule", "calorie", "Watt", "kilowatt", "BTU", "Quad", "therm", "horsepower" };
    conversion_categories["Pressure"] = { "Pascal", "atmosphere", "torr", "psi" };
    conversion_categories["Angle"] = { "degrees", "radians" };
}

// Print usage information
void print_usage() {
    printf("Usage: unitconv [OPTIONS] <source_unit> <target_unit> <value1> <value2>  ...\n");
    printf("Options:\n");
    printf(" -h, --help               Display this help message and exit\n");
    printf(" -v, --version            Display version information and exit\n");
    printf(" -p, --precision <digits> Set the number of decimal digits for the converted value\n");
    printf(" --categories             Display available unit categories\n");
    printf(" --units <category>       Display available units in the specified category\n");
    printf(" --history                Display all past conversions\n");
    printf(" --constant <constant>    Display value of constant\n");
}
