#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

std::string toUpper(const std::string& str);
void printUsage();

struct Unit {
    std::string name;
    std::string symbol;
    std::string category;
    std::string baseUnit;
    double conversionFactor;  // To convert to/from the base unit
};

struct Units {
    std::unordered_set<std::string> categories;
    std::vector<Unit> units;  // Units ordered by category and conversion factor asc

    void listCategories() {
        int count = 1;
        for (auto& category: categories) {
            std::cout << std::setw(3) << std::left << count << category << std::endl;
            count++;
        }
    }

    void listUnits(const std::string& category) {
        int count = 1;
        for (const Unit& unit: units) {
            if (unit.category == toUpper(category)) {
                std::cout << std::setw(3) << std::left << count << std::setw(20) << std::left <<unit.name << unit.symbol << std::endl;
                count++;
            }
        }
    }

    void convertUnit(double amount, const std::string& unitFrom, const std::string& unitTo) {
        std::string unitFromBase;
        std::string unitToBase;
        double conversionFactorFrom = 0;
        double conversionFactorTo = 0;

        for (auto& unit: units) {
            if (unit.name == unitFrom || unit.symbol == unitFrom) {
                conversionFactorFrom = unit.conversionFactor;
                unitFromBase = unit.baseUnit;
            }

            if (unit.name == unitTo || unit.symbol == unitTo) {
                conversionFactorTo = unit.conversionFactor;
                unitToBase = unit.baseUnit;
            }
        }

        if (conversionFactorFrom == 0 ) {
            std::cout << "Unknown unit: " << unitFrom << std::endl;
            return;
        }

        if (conversionFactorTo == 0 ) {
            std::cout << "Unknown unit: " << unitTo << std::endl;
            return;
        }

        if (unitFromBase == unitToBase) {
            double result = (amount * conversionFactorFrom)/conversionFactorTo;
            std::cout << result << std::endl;
            return;
        }

        std::cout << "Cannot convert between: " << unitFrom << " and " << unitTo << std::endl;
    }
};

void load_conversion_units(Units& u);
void uc(int argc, char* argv[], Units& u);

int main(int argc, char* argv[]) {
    // Will need to statically compile these two
    Units allUnits;
    load_conversion_units(allUnits);

    uc(argc, argv, allUnits);
    return 0;
}

void load_conversion_units(Units& u) {
    // Load the conversion unit details from file into map
    std::string conversion_units_file = "/Users/jasonarmstrong/code/jasn-armstrng/projects/unit-converter/src/units.dat";
    std::ifstream inputFile(conversion_units_file);

    if(!inputFile)
        std::cout << "Failed to open " << conversion_units_file << std::endl;

    std::string line;
    while(std::getline(inputFile, line)) {
        // conversion_units.dat is a fixed column-width delimited file
        std::string category = line.substr(0,12);
        std::string name = line.substr(12,20);
        std::string symbol = line.substr(32,8);
        std::string baseUnit = line.substr(40,15);
        std::string conversionFactor = line.substr(55,20);

        // Trim whitespace
        category.erase(category.find_last_not_of(" \t") + 1);
        name.erase(name.find_last_not_of(" \t") + 1);
        symbol.erase(symbol.find_last_not_of(" \t") + 1);
        baseUnit.erase(baseUnit.find_last_not_of(" \t") + 1);
        conversionFactor.erase(conversionFactor.find_last_not_of(" \t") + 1);

        Unit unit = {name, symbol, category, baseUnit, std::stod(conversionFactor)};
        u.units.push_back(unit);
        u.categories.insert(unit.category);
    }
}

std::string toUpper(const std::string& str) {
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
    return upperStr;
}

void printUsage() {
    std::cout << "Usage: uc [OPTIONS] <value> <from_unit> <to_unit>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << " -h, --help         Display this help message and exit" << std::endl;
    std::cout << " -v, --version      Display version information and exit" << std::endl;
    std::cout << " -c                 Display available unit categories" << std::endl;
    std::cout << " -u <unit-category> Display available units in the specified category" << std::endl;
    std::cout << "                    Note: <unit-category> is case agnostic" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << " uc 10 m ft       Convert 10 meters to feet" << std::endl;
    std::cout << " uc -c            List all available unit categories" << std::endl;
    std::cout << " uc -u length     List all available units in the length category" << std::endl;
}

void uc(int argc, char* argv[], Units& u) {
    // Check for arguments
    if (argc == 1) {
        std::cout << "No arguments provided." << std::endl;
        printUsage();
        return;
    }

    // Check for help option
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printUsage();
    }
    // Check for version option
    else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        std::cout << "Version 1.0" << std::endl;
    }
    // Check for unit categories option
    else if (strcmp(argv[1], "-c") == 0) {
        if (argc == 2) {
            u.listCategories();
        } else {
            std::cout << "Unknown option: " << argv[2] << std::endl;
            printUsage();
        }
    }
    // Check -u <unit-category> option
    else if (strcmp(argv[1], "-u") == 0) {
        if (argc == 3) {
            u.listUnits(argv[2]);
        } else if (argc < 3) {
            std::cout << "Missing argument for -u option." << std::endl;
            printUsage();
        } else {
            std::cout << "Unknown option: " << argv[3] << std::endl;
            printUsage();
        }
    }
    // Check for conversion options
    else if (argc == 4) {
        try {
            double amount = std::stod(argv[1]);
            std::string unitFrom = argv[2];
            std::string unitTo = argv[3];
            u.convertUnit(amount, unitFrom, unitTo);
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid argument: " << argv[1] << " is not a valid number." << std::endl;
            printUsage();
        } catch (const std::out_of_range& e) {
            std::cout << "Out of range: " << argv[1] << " is too large or too small." << std::endl;
            printUsage();
        }
    }
    else {
        std::cout << "Unknown or incomplete option." << std::endl;
        printUsage();
    }
}
