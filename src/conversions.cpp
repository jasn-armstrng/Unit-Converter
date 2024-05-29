#include "../headers/common.h"
// Covert static std::unordered_map<std::string, std::vector<std::string> > categories into a map that
// allows for the unit conversion factors to be defined in a category.

// To do:
// 1. Establish the base unit of each category. We will first convert our <unit_from> to the base
// unit then convert to the <unit_to> via its conversion factor. This is possible because of the linear
// scaling relationship between the units of the categories.
//
// 2. Add the conversion factors.
//
// 3. Move the maps and functions to a header or shared objects file. I don't know if shared object file
// is the right file I'm thinking should be used here.
std::unordered_map<std::string, std::unordered_map<std::string, double> > conversions =
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
