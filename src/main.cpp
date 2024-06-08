/* uc - unit converter

The uc utility,
    - Converts the amount from a source unit to a target unit specified as arguments to the program.
    - See usage examples in the `printUsage()` definition below.

Created by - Jason Armstrong */
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>

#include "../headers/units_data.h"
const std::string_view listOfUnits = units_data;


std::string toUpper(const std::string& str) {
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), [](unsigned char c)
    {   return std::toupper(c);});
    return upperStr;}


void convertTemperature(double& value, const std::string& fromUnit, const std::string& toUnit) {
    std::cout << std::fixed << std::setprecision(4);
    if (fromUnit == "C")
    {   if (toUnit == "F")
        {   std::cout << value * 9.0 / 5.0 + 32.0 << std::endl;
            return;}
        else if (toUnit == "K")
        {   std::cout << value + 273.15 << std::endl;
            return;}}
    else if (fromUnit == "F")
    {   if (toUnit == "C")
        {   std::cout << (value - 32.0) * 5.0 / 9.0 << std::endl;
            return;}
        else if (toUnit == "K")
        {   std::cout << (value + 459.67) * 5.0 / 9.0 << std::endl;
            return;}}
    else if (fromUnit == "K")
    {   if (toUnit == "C")
        {   std::cout << value - 273.15 << std::endl;
            return;}
        else if (toUnit == "F")
        {   std::cout << value * 9.0 / 5.0 - 459.67 << std::endl;
            return;}}}


struct Unit {
    std::string name;
    std::string symbol;
    std::string category;
    std::string baseUnit;
    double conversionFactor;};


struct Units {
    // categories (lookup): The set of all unit measurement categories.
    // units (iterator): The list of all unit objects sorted by unit category and ordered by unit conversion factor asc */
    std::unordered_set<std::string> categories;
    std::vector<Unit> units;

    void listCategories()
    {   int count = 1;
        for (auto& category: categories)
        {   std::cout << std::setw(3) << std::left << count << category << std::endl;
            count++;}}


    void listUnits(const std::string& category)
    { if (categories.count(toUpper(category)) > 0)
        {   int count = 1;
            for (const Unit& unit: units) {
                if (unit.category == toUpper(category))
                {   std::cout << std::setw(3) << std::left << count << std::setw(20) << std::left <<unit.name << unit.symbol << std::endl;
                    count++;}}}
        else
        {   std::cout << "Unknown category: " << category << std::endl;}}


    void convertUnit(double& amount, const std::string& unitFrom, const std::string& unitTo) {
        std::string unitFromBase;
        std::string unitToBase;
        double conversionFactorFrom = 0;
        double conversionFactorTo = 0;

        for (auto& unit: units)
        {   if (unit.name == unitFrom || unit.symbol == unitFrom)
            {   conversionFactorFrom = unit.conversionFactor;
                unitFromBase = unit.baseUnit;}

            if (unit.name == unitTo || unit.symbol == unitTo)
            {   conversionFactorTo = unit.conversionFactor;
                unitToBase = unit.baseUnit;}}

        if (conversionFactorFrom == 0)
        {   std::cout << "Unknown unit: " << unitFrom << std::endl;
            return;}

        if (conversionFactorTo == 0)
        {   std::cout << "Unknown unit: " << unitTo << std::endl;
            return;}

        // Check first if unitFrom/unitsTo are temperature units
        std::unordered_set<std::string> tempUnits({ "C", "F", "K" });
        if (tempUnits.find(unitFrom) != tempUnits.end() && tempUnits.find(unitTo) != tempUnits.end())
        {   convertTemperature(amount, unitFrom, unitTo);
            return;}

        std::cout << std::fixed << std::setprecision(4);
        if (unitFromBase == unitToBase)
        {   std::cout << (amount * conversionFactorFrom)/conversionFactorTo << std::endl;
            return;}

        std::cout << "Cannot convert between: " << unitFrom << " and " << unitTo << std::endl;}};


void loadConvertibleUnits(Units& u) {
    // The listOfUnits.data() is a fixed column-width multiline string. Each line contains is used to create a Unit.
    // Each unit is added to the list of units - Units.
    std::istringstream inputStream(listOfUnits.data());
    std::string line;
    while(std::getline(inputStream, line))
    {   std::string category = line.substr(0,12);
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
        u.categories.insert(unit.category);}}


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
    std::cout << " uc -u length     List all available units in the length category" << std::endl;}


void uc(int argc, char* argv[], Units& u) {
    if (argc == 1)  // Check for arguments
    {   std::cout << "No arguments provided." << std::endl;
        printUsage();
        return;}

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)  // Check for help option
    {   printUsage();}
    else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) // Check for version option
    {   std::cout << "Version 1.0" << std::endl;}
    else if (strcmp(argv[1], "-c") == 0)  // Check for unit categories option
    {   if (argc == 2)
        {   u.listCategories();}
        else
        {   std::cout << "Unknown option: " << argv[2] << std::endl;
            printUsage();}}
    else if (strcmp(argv[1], "-u") == 0)  // Check -u <unit-category> option
    {   if (argc == 3)
        {   u.listUnits(argv[2]);}
        else if (argc < 3)
        {   std::cout << "Missing argument for -u option." << std::endl;
            printUsage();}
        else
        {   std::cout << "Unknown option: " << argv[3] << std::endl;
            printUsage();}}
    else if (argc == 4)  // Check for conversion options
    {   try
        {   double amount = std::stod(argv[1]);
            std::string unitFrom = argv[2];
            std::string unitTo = argv[3];
            u.convertUnit(amount, unitFrom, unitTo);}
        catch (const std::invalid_argument& e)
        {   std::cout << "Invalid argument: " << argv[1] << " is not a valid number." << std::endl;
            printUsage();}
        catch (const std::out_of_range& e)
        {   std::cout << "Out of range: " << argv[1] << " is too large or too small." << std::endl;
            printUsage();}}
    else
    {   std::cout << "Unknown or incomplete option." << std::endl;
        printUsage();}}

// Comment main when testing
// int main(int argc, char* argv[]) {
//     Units allUnits;
//     loadConvertibleUnits(allUnits);
//     uc(argc, argv, allUnits);
//     return 0;}
