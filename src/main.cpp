/*
uc - unit converter
    The uc utility,
        - Converts the amount from a source unit to a target unit specified as arguments to the program.
        - Provides the value of constants in Chemistry, Mathematics, and Physics.
        - See usage examples in the `printUsage()` definition below.

Created by - Jason Armstrong

                               You shall do no injustice in judgment,
                            in measurement of length, weight, or volume.
                                   You shall have honest scales,
                                  honest weights, an honest ephah,
                                       and an honest hin,
                                               ...
                                    - Leviticus 19:35-36 NKJV
*/
#include <_ctype.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>


bool isSwitch(const std::string& input);
std::string toUpper(const std::string& input);


const std::string_view listOfUnits = R"(DATA        Bit                 b       Bit            1
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
DISTANCE    Fathom              fth     Meter          1.829
DISTANCE    Furlong             fur     Meter          201.68
DISTANCE    Mile                mi      Meter          1609.34
DISTANCE    Nautical Mile       nmi     Meter          1852
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
MASS        Stone               st      Kilogram       6.35029
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


const std::string_view listOfConstants = R"(MATHEMATICS     Pi                             pi          3.141592653589793   -
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


bool isSwitch(const std::string& input) {
    char firstChar = input.front();
    return firstChar == '-' ? true : false;
}


std::string toUpper(const std::string& input) {
    std::string upperStr = input;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
    return upperStr;
}


class Units {
    private:
        struct Unit {
            std::string name;
            std::string symbol;
            std::string category;
            std::string baseUnit;
            double conversionFactor;
        };

        std::unordered_set<std::string> categories;
        std::vector<Unit> units;

        double convertTemperature(double value, const std::string& fromUnit, const std::string& toUnit) {
            const double ABSOLUTE_ZERO_C = -273.15;
            const double ABSOLUTE_ZERO_F = -459.67;

            // Convert to Kelvin first
            double kelvin;
            if (fromUnit == "C") {
                kelvin = value - ABSOLUTE_ZERO_C;
            } else if (fromUnit == "F") {
                kelvin = (value - ABSOLUTE_ZERO_F) * 5.0 / 9.0;
            } else if (fromUnit == "K") {
                kelvin = value;
            } else {
                throw std::invalid_argument("Invalid fromUnit: " + fromUnit);
            }

            // Convert from Kelvin to target unit
            if (toUnit == "C") {
                return kelvin + ABSOLUTE_ZERO_C;
            } else if (toUnit == "F") {
                return kelvin * 9.0 / 5.0 + ABSOLUTE_ZERO_F;
            } else if (toUnit == "K") {
                return kelvin;
            } else {
                throw std::invalid_argument("Invalid toUnit: " + toUnit);
            }
        }

        void writeConversionHistory(const std::string& conversionRequest, const double& result) {
            std::filesystem::path historyPath = std::filesystem::path(getenv("HOME"))/".uc_history";

            double index = 0;
            try {
                // First, if file exists, read the number of lines
                if (std::filesystem::exists(historyPath)) {
                    std::ifstream countFile;
                    countFile.open(historyPath);
                    if (countFile.is_open()) {
                        index = std::count(std::istreambuf_iterator<char>(countFile), std::istreambuf_iterator<char>(), '\n');
                        countFile.close();
                    }
                }

                // Now, append conversion request to the history
                std::ofstream historyFile(historyPath, std::ios::app);
                if (!historyFile.is_open())
                    throw std::runtime_error("Unable to open history file");

                historyFile << std::left << std::setw(4) << ++index << " uc " << conversionRequest << " " << result << std::endl;

                if (historyFile.fail())
                    throw std::runtime_error("Unable to write to history file");

                historyFile.close();
            } catch (const std::exception& e) {
                std::ofstream errorLog("~/.uc_error.log", std::ios::app);
                if (errorLog.is_open()) {
                    errorLog << "Error writing to history" << e.what() << std::endl;
                }
            }
        }


    public:
        void loadUnits(const std::string_view& lOU) {
            std::istringstream inputStream(lOU.data());
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
                Unit unit = { .name=name, .symbol=symbol, .category=category, .baseUnit=baseUnit, .conversionFactor=std::stod(conversionFactor) };
                units.push_back(unit);
                categories.insert(unit.category);
            }
        }

        void listCategories() {
            for (const std::string& category: categories) {
                std::cout << std::left << category << std::endl;
            }
        }

        void listUnits(const std::string& input) {
            if (categories.count(toUpper(input)) > 0) {
                for (const Unit& unit: units) {
                    if (unit.category == toUpper(input)) {
                        std::cout << std::left
                        << std::setw(20) << unit.name
                        << std::setw(8) << unit.symbol << std::endl;
                    }
                }
            }
            else {
                std::cout << "Unknown category: " << input << std::endl;
            }
        }

        void convertUnit(double& amount, const std::string& unitFrom, const std::string& unitTo) {
            std::string unitFromBase;
            std::string unitToBase;
            double conversionFactorFrom = 0;
            double conversionFactorTo = 0;

            for (Unit& unit: units) {
                if (unit.name == unitFrom || unit.symbol == unitFrom) {
                    conversionFactorFrom = unit.conversionFactor;
                    unitFromBase = unit.baseUnit;
                }

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
            std::unordered_set<std::string> tempUnits ( { "C", "F", "K" } );
            if (tempUnits.find(unitFrom) != tempUnits.end() && tempUnits.find(unitTo) != tempUnits.end()) {
                double result = convertTemperature(amount, unitFrom, unitTo);
                std::cout << std::fixed << std::setprecision(4) << result << std::endl;
                writeConversionHistory(std::format("{} {} {}", amount, unitFrom, unitTo), result);
                return;
            }

            if (unitFromBase == unitToBase) {
                double result = (amount * conversionFactorFrom)/conversionFactorTo;
                std::cout << std::fixed << std::setprecision(4) << result << std::endl;
                writeConversionHistory(std::format("{} {} {}", amount, unitFrom, unitTo), result);
                return;
            }
            std::cout << "Cannot convert between: " << unitFrom << " and " << unitTo << std::endl;
        }

        void displayConversionHistory() {
            std::filesystem::path historyPath = std::filesystem::path(getenv("HOME"))/".uc_history";

            if (!std::filesystem::exists(historyPath)) {
                std::cout << "No conversion history found." << std::endl;
                return;
            }

            std::ifstream historyFile(historyPath);
            if (!historyFile.is_open()) {
                std::cout << "Unable to open history file." << std::endl;
                return;
            }

            std::string line;
            while (std::getline(historyFile, line))
                std::cout << line << std::endl;

            historyFile.close();
        }


        void clearConversionHistory() {
            std::filesystem::path historyPath = std::filesystem::path(getenv("HOME")) / ".uc_history";

            if (std::filesystem::exists(historyPath)) {
                std::ofstream ofs(historyPath, std::ios::trunc);
                ofs.close();
                std::cout << "Conversion history cleared." << std::endl;
            } else {
                std::cout << "No history file found. Nothing to clear." << std::endl;
            }
        }
};


class Constants {
    private:
        struct Constant {
            std::string name;
            std::string symbol;
            std::string group;
            std::string value;
            std::string unit;
        };

        std::unordered_set<std::string> groups;
        std::vector<Constant> constants;

    public:
        void loadConstants(const std::string_view& lOC) {
            std::istringstream inputStream(lOC.data());
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
                constants.push_back(constant);
                groups.insert(constant.group);
            }
        }

        void listGroups() {
            for (const std::string& group: groups) {
                std::cout << std::setw(3) << std::left << group << std::endl;
            }
        }

        void listConstants(const std::string& input) {
            if (groups.count(toUpper(input)) > 0) {
                for (Constant constant: constants) {
                    if (constant.group == toUpper(input)) {
                        std::cout << std::left
                            << std::setw(31) << constant.name
                            << std::setw(8) << constant.symbol << std::endl;
                    }
                }
            }
            else
                std::cout << "Unknown group: " << input << std::endl;
        }

        void listConstantsDetailed() {
            for (const std::string& group: groups) {
                for (const Constant& constant: constants) {
                    if (constant.group == group) {
                        std::cout << std::left << std::setw(16) << constant.group
                                << std::setw(32) << constant.name
                                << std::setw(12) << constant.symbol
                                << std::setw(20) << constant.value
                                << std::setw(20) << constant.unit << std::endl;
                    }
                }
            }
        }

        void valueOfConstant(const std::string& input) {
            for (const Constant& constant: constants) {
                if (toUpper(constant.name) == toUpper(input) || constant.symbol == input) {
                    std::cout << std::fixed << std::setprecision(15) << constant.value << std::endl;
                    return;
                }
            }
            std::cout << "Unknown constant: " << input << std::endl;
        }

};


void printUsage() {
    std::cout << "Usage: uc [OPTIONS] <value> <from_unit> <to_unit>" << std::endl;
    std::cout << std::endl;
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
    std::cout << std::endl;
    std::cout << " Conversion history:" << std::endl;
    std::cout << " --hist             Display conversion history from all time. Manage history" << std::endl;
    std::cout << "                    with head, tail, or grep commands." << std::endl;
    std::cout << " --clrhist          Clear conversion history" << std::endl;
}


void uc(int argc, char* argv[], Units& u, Constants& c) {
    // Check for arguments
    if (argc == 1) {
        std::cout << "No arguments provided." << std::endl;
        printUsage();
        return;
    }
    // Show help/program usage
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printUsage();
    }
    // Show version number
    else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        std::cout << "Version 1.0" << std::endl;
    }
    // Show conversion history
    else if (argc == 2 && std::string(argv[1]) == "--hist") {
        u.displayConversionHistory();
    }
    // Show conversion history
    else if (argc == 2 && std::string(argv[1]) == "--clrhist") {
        u.clearConversionHistory();
    }
    // List constants groups
    else if (strcmp(argv[1], "-Cg") == 0) {
        if (argc == 2)
            c.listGroups();
        else {
            std::cout << "Unknown option: " << argv[2] << std::endl;
            printUsage();
        }
    }
    // List constants for specfied group
    else if (strcmp(argv[1], "-C") == 0) {
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
    // List all details for all constants
    else if (strcmp(argv[1], "-Cd") == 0) {
        if (argc == 2)
            c.listConstantsDetailed();
        else {
            std::cout << "Unknown option: " << argv[2] << std::endl;
            printUsage();
        }
    }
    // Show value of valid constant provided
    else if (argc == 2 && !isSwitch(argv[1])) {
        try {
            c.valueOfConstant(argv[1]);
        } catch (const std::invalid_argument& e) {
            printUsage();
        }
    }
    // List unit categories
    else if (strcmp(argv[1], "-c") == 0) {
        if (argc == 2)
            u.listCategories();
        else {
            std::cout << "Unknown option: " << argv[2] << std::endl;
            printUsage();
        }
    }
    // List units for specified category
    else if (strcmp(argv[1], "-u") == 0) {
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
    // Convert valid statement
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
    } else {
        std::cout << "Unknown or incomplete option." << std::endl;
        printUsage();
    }
}


int main(int argc, char* argv[]) {
    Units U;
    Constants C;

    U.loadUnits(listOfUnits);
    C.loadConstants(listOfConstants);

    uc(argc, argv, U, C);

    return EXIT_SUCCESS;
}
