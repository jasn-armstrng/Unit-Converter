// unitconv - Command-line utility for unit conversions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    return EXIT_SUCCESS;
}
