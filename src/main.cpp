// unitconv - Command-line utility for unit conversions
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>

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

int main(int argc, char *argv[]) {
    // Check if no arguments were provided
    if (argc == 1) {
        printf("No arguments provided.\n");
        print_usage();
        return 1;
    }

    // Loop through each argument
    for (int i = 1; i < argc; i++) {
        // Check for help option
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage();
            return 0;
        }
        // Check for version option
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            printf("Version 1.0\n");
            return 0;
        }
        else if (strcmp(argv[i], "--categories") == 0) {
            printf("Available unit categories:\n \
            - Temperature\n \
            - Length\n \
            - Massn\n \
            - Volume\n \
            - Data Size\n \
            - Time\n \
            - Energy\n \
            - Pressure\n \
            - Angle\n");
            return 0;
        }
        else {
            printf("Unknown option: %s\n", argv[i]);
            print_usage();
            return 1;
        }
    }

    return EXIT_SUCCESS;
}
