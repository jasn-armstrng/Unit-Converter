// uc - unit converter
//     The uc utility,
//         - Converts the amount from a source unit to a target unit specified as arguments to the program.
//         - Prints the value of constants in Chemistry, Mathematics, and Physics.
//         - See usage examples in the `printUsage()` definition below.
// Created by - Jason Armstrong
//
// "You shall do no injustice in judgment, in measurement of length, weight, or volume.
// You shall have honest scales, honest weights, an honest ephah, and an honest hin ..."
// - Leviticus 19:35-36 NKJV

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>


const std::string_view listOfUnits =
R"(DATA        Bit                 b       Bit            1
DATA        Byte                B       Bit            8
DATA        Kilobit             kbit    Bit            1000
DATA        Kibibit             Kib     Bit            1024
DATA        Kilobyte            KB      Bit            8000
DATA        Kibibyte            KiB     Bit            8192
DATA        Megabit             Mbit    Bit            1000000
DATA        Mebibit             Mib     Bit            1048576
DATA        Megabyte            MB      Bit            8000000
DATA        Mebibyte            MiB     Bit            8388608
DATA        Gigabit             Gbit    Bit            1000000000
DATA        Gibibit             Gib     Bit            1073741824
DATA        Gigabyte            GB      Bit            8000000000
DATA        Gibibyte            GiB     Bit            8589934592
DATA        Terabit             Tbit    Bit            1000000000000
DATA        Tebibit             Tib     Bit            1099511627776
DATA        Terabyte            TB      Bit            8000000000000
DATA        Tebibyte            TiB     Bit            8796093022208
DISTANCE    Meter               m       Meter          1
DISTANCE    Kilometer           km      Meter          1000
DISTANCE    Centimeter          cm      Meter          0.01
DISTANCE    Millimeter          mm      Meter          0.001
DISTANCE    Micrometer          μm     Meter          0.000001
DISTANCE    Nanometer           nm      Meter          0.000000001
DISTANCE    Inch                in      Meter          0.0254
DISTANCE    Foot                ft      Meter          0.3048
DISTANCE    Yard                yd      Meter          0.9144
DISTANCE    Mile                mi      Meter          1609.34
VOLUME      Liter               l       Liter          1
VOLUME      Milliliter          ml      Liter          0.001
VOLUME      Cubic meter         m^3     Liter          1000
VOLUME      Cubic centimeter    cc      Liter          0.001
VOLUME      Gallon              gal     Liter          3.78541
VOLUME      Quart               qt      Liter          0.946353
VOLUME      Pint                pt      Liter          0.473176
VOLUME      Fluid ounce         fl oz   Liter          0.0295735
AREA        Square meter        m^2     Square meter   1
AREA        Square kilometer    km^2    Square meter   1000000
AREA        Square centimeter   cm^2    Square meter   0.0001
AREA        Square millimeter   mm^2    Square meter   0.000001
AREA        Hectare             ha      Square meter   10000
AREA        Acre                ac      Square meter   4046.86
AREA        Square inch         in^2    Square meter   0.00064516
AREA        Square foot         ft^2    Square meter   0.092903
AREA        Square yard         yd^2    Square meter   0.836127
AREA        Square mile         mi^2    Square meter   2589988
MASS        Kilogram            kg      Kilogram       1
MASS        Gram                g       Kilogram       0.001
MASS        Milligram           mg      Kilogram       0.000001
MASS        Metric ton          t       Kilogram       1000
MASS        Pound               lb      Kilogram       0.453592
MASS        Ounce               oz      Kilogram       0.0283495
TIME        Second              s       Second         1
TIME        Minute              min     Second         60
TIME        Hour                h       Second         3600
TIME        Day                 d       Second         86400
TIME        Week                wk      Second         604800
TIME        Month               mo      Second         2629800
TIME        Year                yr      Second         31557600
TEMPERATURE celsius             C       Celsius        1
TEMPERATURE fahrenheit          F       Celsius        1
TEMPERATURE kelvin              K       Celsius        1)";


const std::string_view listOfConstants =
R"(MATHEMATICS     Pi                             pi          3.141592653589793   -
MATHEMATICS     Eulers Number                  e           2.718281828459045   -
MATHEMATICS     Golden Ratio                   phi         1.618033988749895   -
MATHEMATICS     Square Root of 2               root2       1.414213562373095   -
MATHEMATICS     Square Root of 3               root3       1.732050807568877   -
MATHEMATICS     Square Root of 5               root5       2.236067977499790   -
MATHEMATICS     Natural Logarithm of 2         ln(2)       0.693147180559945   -
MATHEMATICS     Euler-Mascheroni Constant      y           0.577215664901533   -
MATHEMATICS     Ramanujan-Soldner Constant     -           1.451369234883381   -
MATHEMATICS     Khinchins Constant             K           2.685452001065306   -
MATHEMATICS     Glaisher-Kinkelin Constant     A           1.282427129100623   -
PHYSICS         Speed of Light in Vacuum       c           299792458           m/s
PHYSICS         Gravitational Constant         G           6.67430e-11         m^3/(kg*s^2)
PHYSICS         Plancks Constant               h           6.62607015e-34      J*s
PHYSICS         Reduced Plancks Constant       ħ           1.054571817e-34     J*s
PHYSICS         Elementary Charge              e           1.602176634e-19     C
PHYSICS         Electron Rest Mass             -           9.1093837015e-31    kg
PHYSICS         Proton Rest Mass               -           1.67262192369e-27   kg
PHYSICS         Fine-Structure Constant        -           7.2973525693e-3     -
PHYSICS         Rydberg Constant               -           10973731.568160     m^-1
PHYSICS         Avogadros Number               NA          6.02214076e23       mol^-1
PHYSICS         Boltzmann Constant             kB          1.380649e-23        J/K
PHYSICS         Stefan-Boltzmann Constant      -           5.670374419e-8      W/(m^2*K^4)
PHYSICS         Vacuum Permeability            -           1.25663706212e-6    N/A^2
PHYSICS         Vacuum Permittivity            -           8.8541878128e-12    F/m
CHEMISTRY       Atomic Mass Unit               u           1.66053906660e-27   kg
CHEMISTRY       Faraday Constant               F           96485.33212         C/mol
CHEMISTRY       Molar Gas Constant             R           8.314462618         J/(mol*K)
CHEMISTRY       First Radiation Constant       c1          3.741771852e-16     W*m^2
CHEMISTRY       Second Radiation Constant      c2          1.438776877e-2      m*K)";


bool isSwitch(const std::string& str) {
    if (str.length() >= 2) {
        char firstChar = str.front();
        return firstChar == '-' ? true : false;
    }
    return false;
}


std::string toUpper(const std::string& str) {
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
    return upperStr;
}


void convertTemperature(double& value, const std::string& fromUnit, const std::string& toUnit) {
    std::cout << std::fixed << std::setprecision(4);
    if (fromUnit == "C") {
        if (toUnit == "F") {
            std::cout << value * 9.0 / 5.0 + 32.0 << std::endl;
            return;
        } else if (toUnit == "K") {
            std::cout << value + 273.15 << std::endl;
            return;
        }
    } else if (fromUnit == "F") {
        if (toUnit == "C") {
            std::cout << (value - 32.0) * 5.0 / 9.0 << std::endl;
            return;
        } else if (toUnit == "K") {
            std::cout << (value + 459.67) * 5.0 / 9.0 << std::endl;
            return;
        }
    } else if (fromUnit == "K") {
        if (toUnit == "C") {
            std::cout << value - 273.15 << std::endl;
            return;
        } else if (toUnit == "F") {
            std::cout << value * 9.0 / 5.0 - 459.67 << std::endl;
            return;
        }
    } else
        return;
}


// Units Section:
//     Defines structs and functions for managing units of measurement and performing unit conversions.
//         - The Unit struct represents a single unit with its name, symbol, category, base unit, and conversion factor.
//         - The Units struct contains a set of unique categories and a vector of units, along with methods to list categories,
//           list units within a category, and convert between units.
//         - The loadUnits function populates a Units object from a fixed column-width multiline string, extracting and storing
//           the data for each unit. The convertUnit method converts an amount from one unit to another, handling special cases
//           for temperature units and checking for compatibility between units.
struct Unit {
    std::string name;
    std::string symbol;
    std::string category;
    std::string baseUnit;
    double conversionFactor;
};

struct Units {
    std::unordered_set<std::string> categories;
    std::vector<Unit> units;

    void listCategories() {
        int count = 1;
        for (auto& category: categories) {
            std::cout << std::setw(3) << std::left << count << category << std::endl;
            count++;
        }
    }

    void listUnits(const std::string& category) {
        if (categories.count(toUpper(category)) > 0) {
        int count = 1;
            for (const Unit& unit: units) {
                if (unit.category == toUpper(category)) {
                    std::cout << std::setw(3) << std::left << count
                    << std::setw(20) << unit.name
                    << std::setw(8) << unit.symbol << std::endl;
                    count++;
                }
            }
        }
        else
            std::cout << "Unknown category: " << category << std::endl;
    }

    void convertUnit(double& amount, const std::string& unitFrom, const std::string& unitTo) {
        std::string unitFromBase;
        std::string unitToBase;
        double conversionFactorFrom = 0;
        double conversionFactorTo = 0;

        for (auto& unit: units) {
            if (unit.name == unitFrom || unit.symbol == unitFrom) {
                conversionFactorFrom = unit.conversionFactor;
                unitFromBase = unit.baseUnit;}

            if (unit.name == unitTo || unit.symbol == unitTo) {
                conversionFactorTo = unit.conversionFactor;
                unitToBase = unit.baseUnit;
            }
        }

        if (conversionFactorFrom == 0) {
            std::cout << "Unknown unit: " << unitFrom << std::endl;
            return;
        }

        if (conversionFactorTo == 0) {
            std::cout << "Unknown unit: " << unitTo << std::endl;
            return;
        }

        // Check first if unitFrom/unitsTo are temperature units
        std::unordered_set<std::string> tempUnits({ "C", "F", "K" });
        if (tempUnits.find(unitFrom) != tempUnits.end() && tempUnits.find(unitTo) != tempUnits.end()) {
            convertTemperature(amount, unitFrom, unitTo);
            return;
        }

        std::cout << std::fixed << std::setprecision(4);
        if (unitFromBase == unitToBase) {
            std::cout << (amount * conversionFactorFrom)/conversionFactorTo << std::endl;
            return;
        }

        std::cout << "Cannot convert between: " << unitFrom << " and " << unitTo << std::endl;
    }
};


void loadUnits(Units& u) {
    std::istringstream inputStream(listOfUnits.data());
    std::string line;
    while(std::getline(inputStream, line)) {
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

        // Create the Unit and populate Units
        Unit unit = { name, symbol, category, baseUnit, std::stod(conversionFactor) };
        u.units.push_back(unit);
        u.categories.insert(unit.category);
    }
}


// Constants Section:
//     Defines structs and functions for managing a collection of physical constants.
//         - The Constant struct represents a single physical constant with its name, symbol, group, value, and unit.
//         - The Constants struct contains a set of unique groups and a map of constants, along with methods to list groups,
//           list constants within a group, list all constants, and retrieve the value of a specific constant.
//         - The loadConstants function populates a Constants object from a fixed column-width multiline string, extracting
//             and storing the data for each constant.
struct Constant {
    std::string name;
    std::string symbol;
    std::string group;
    std::string value;
    std::string unit;
};


struct Constants {
    std::unordered_set<std::string> groups;
    std::unordered_map<std::string, Constant> constants;

    void listGroups() {
        int count = 1;
        for (auto& group: groups) {
            std::cout << std::setw(3) << std::left << count << group << std::endl;
            count++;
        }
    }

    void listConstants(const std::string& group) {
        if (groups.count(toUpper(group)) > 0) {
            int count = 1;
            for (const auto& pair: constants) {
                if (pair.second.group == toUpper(group)) {
                    std::cout << std::left << std::setw(3) << count
                        << std::setw(31) << pair.second.name
                        << std::setw(8) << pair.second.symbol << std::endl;
                    count++;
                }
            }
        }
        else
            std::cout << "Unknown group: " << group << std::endl;
    }

    void listConstantsDetailed() {
        for (auto& group: groups) {
            for (const auto& pair: constants) {
                if (pair.second.group == group) {
                    std::cout << std::left << std::setw(16) << pair.second.group
                            << std::setw(32) << pair.second.name
                            << std::setw(12) << pair.second.symbol
                            << std::setw(20) << pair.second.value
                            << std::setw(20) << pair.second.unit << std::endl;
                }
            }
        }
    }

    void valueOfConstant(const std::string& constant)
    {   std::cout << std::fixed << std::setprecision(15);
        if (constants.find(constant) == constants.end())
            std::cout << "Unknown constant: " << constant << std::endl;
        else
            std::cout << constants[constant].value << std::endl;
    }
};


void loadConstants(Constants& c) {
    std::istringstream inputStream(listOfConstants.data());
    std::string line;
    while(std::getline(inputStream, line)) {
        std::string group = line.substr(0,16);
        std::string name = line.substr(16,31);
        std::string symbol = line.substr(47,12);
        std::string value = line.substr(59,20);
        std::string unit = line.substr(79,20);

        // Trim whitespace
        group.erase(group.find_last_not_of(" \t") + 1);
        name.erase(name.find_last_not_of(" \t") + 1);
        symbol.erase(symbol.find_last_not_of(" \t") + 1);
        value.erase(value.find_last_not_of(" \t") + 1);
        unit.erase(unit.find_last_not_of(" \t") + 1);

        // Create the Unit and populate Units
        Constant constant = { name, symbol, group, value, unit };
        c.constants.insert({constant.name, constant});
        c.groups.insert(constant.group);
    }
}


void printUsage() {
    std::cout << "Usage: uc [OPTIONS] <value> <from_unit> <to_unit>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << " -h, --help         Display this help message and exit" << std::endl;
    std::cout << " -v, --version      Display version information and exit" << std::endl;
    std::cout << std::endl;
    std::cout << " Units:" << std::endl;
    std::cout << " -c                 Display available unit categories" << std::endl;
    std::cout << " -u <category>      Display available units in the specified category" << std::endl;
    std::cout << "                    Note: <category> is case agnostic" << std::endl;
    std::cout << std::endl;
    std::cout << " Constants:" << std::endl;
    std::cout << " -Cg                Display available constant groups" << std::endl;
    std::cout << " -Cd                Display detailed view of all available constants" << std::endl;
    std::cout << " -C <group>         Display available constants in the specified group" << std::endl;
    std::cout << "                    Note: <group> is case agnostic" << std::endl;
}


void uc(int argc, char* argv[], Units& u, Constants& c) {
    // -----------------------------------------------------------------------------------------------------
    if (argc == 1) {                                                                  // Check for arguments
        std::cout << "No arguments provided." << std::endl;
        printUsage();
        return;
    }

    // -----------------------------------------------------------------------------------------------------
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)             // Show help/program usage
        printUsage();
    // ------------------------------------------------------------------------------------------------------
    else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)          // Show version number
        std::cout << "Version 1.0" << std::endl;
    // ------------------------------------------------------------------------------------------------------
    else if (strcmp(argv[1], "-c") == 0) {                                            // List unit categories
        if (argc == 2)
            u.listCategories();
        else {
            std::cout << "Unknown option: " << argv[2] << std::endl;
            printUsage();
        }
    }
    // ------------------------------------------------------------------------------------------------------
    else if (strcmp(argv[1], "-u") == 0) {                               // List units for specified category
        if (argc == 3)
            u.listUnits(argv[2]);
        else if (argc < 3) {
            std::cout << "Missing argument for -u option." << std::endl;
            printUsage();
        } else {
            std::cout << "Unknown option: " << argv[3] << std::endl;
            printUsage();
        }
    }
    // ------------------------------------------------------------------------------------------------------
    else if (argc == 4) {                                                          // Convert valid statement
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
    // ------------------------------------------------------------------------------------------------------
    else if (strcmp(argv[1], "-Cg") == 0) {                                          // List constants groups
        if (argc == 2)
            c.listGroups();
        else {
            std::cout << "Unknown option: " << argv[2] << std::endl;
            printUsage();
        }
    }
    // ------------------------------------------------------------------------------------------------------
    else if (strcmp(argv[1], "-C") == 0) {                            // List constants in for specfied group
        if (argc == 3)
            c.listConstants(argv[2]);
        else if (argc < 3) {
            std::cout << "Missing argument for -C option." << std::endl;
            printUsage();}
        else {
            std::cout << "Unknown option: " << argv[3] << std::endl;
            printUsage();
        }
    }
    // ------------------------------------------------------------------------------------------------------
    else if (strcmp(argv[1], "-Cd") == 0) {                                    // List all constants (detail)
        if (argc == 2)
            c.listConstantsDetailed();
        else {
            std::cout << "Unknown option: " << argv[2] << std::endl;
            printUsage();
        }
    }
    // ------------------------------------------------------------------------------------------------------
    else if (argc == 2 && !isSwitch(argv[1])) {                      // Show value of valid constant provided
        try {
            c.valueOfConstant(argv[1]);
        } catch (const std::invalid_argument& e) {
            printUsage();
        }
    } else {
        std::cout << "Unknown or incomplete option." << std::endl;
        printUsage();
    }
}


// Comment main when testing
int main(int argc, char* argv[]) {
    Units allUnits;
    loadUnits(allUnits);

    Constants allConstants;
    loadConstants(allConstants);

    uc(argc, argv, allUnits, allConstants);

    return 0;
}
// -----------------------------------------------------------------------------------------------------------
