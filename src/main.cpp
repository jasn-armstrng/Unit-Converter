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

    // Once we pass the check above we initialise the map of conversion categories and their units.
    // This is used in our argument checks below.
    // Would it make sense to do this initialisation at compile time?
    initialize_conversion_category_map();

    // We use the following conditional block to check the user's arguments and either report an error
    // or perform an action based on a legal input.
    {
        // Check for help option
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            print_usage();
            return 0;
        // Check for version option
        } else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
            printf("Version 1.0\n");
            return 0;
        // Check for conversion categories option
        } else if (strcmp(argv[1], "--categories") == 0) {
            if (argc == 2) {
                std::cout << "Available unit categories:" << std::endl;
                for (const auto& [key, _] : conversion_categories) {
                        std::cout << " - " << key << std::endl;
                }
                return 0;
            // Communicate bad option for any argument after <category>
            } else {
                printf("Unknown option: %s\n", argv[2]);
                return 1;
            }
        // Check for units in categories option
        } else if (strcmp(argv[1], "--units") == 0 && argc > 2) {
            if (conversion_categories.find(argv[2]) != conversion_categories.end()) {
                std::cout << "Available units in the " << argv[2] << " category:" << std::endl;
                for (const auto& value : conversion_categories[argv[2]]) {
                        std::cout << " - " << value << std::endl;
                }
                return 0;
            // Communicate bad option for any argument after --units <category>
            } else if (conversion_categories.find(argv[2]) != conversion_categories.end() && argc > 3) {
                printf("Unknown option: %s\n", argv[3]);
                return 1;
            } else {
                printf("Unknown category: %s\n", argv[2]);
                return 1;
            }
        // Report general incorrect usage
        } else {
            printf("Unknown or incomplete option: %s\n", argv[1]);
            print_usage();
            return 1;
        }
    }

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
