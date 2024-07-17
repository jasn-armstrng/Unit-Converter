# uc - Unit Converter

`uc` is a versatile command-line utility for unit conversion and constant value lookup. It offers a wide range of functionalities including unit conversion across various categories, retrieval of mathematical and scientific constants, and conversion history tracking.

## Features

- Convert between units in multiple categories (e.g., distance, volume, mass, temperature)
- List available unit categories and units within each category
- Display values of mathematical and scientific constants
- View and manage conversion history
- Simple and intuitive command-line interface

## Installation

[Include installation instructions here]

## Usage

```
uc [OPTIONS] <value> <from_unit> <to_unit>
```

### Options:

- `-h, --help`: Display help message and exit
- `-v, --version`: Display version information and exit
- `-c`: Display available unit categories
- `-u <category>`: Display available units in the specified category
- `-Cg`: Display available constant groups
- `-Cd`: Display detailed view of all available constants
- `-C <group>`: Display available constants in the specified group
- `--hist`: Display conversion history
- `--clrhist`: Clear conversion history

### Examples:

```
uc 10 m ft
uc -u DISTANCE
uc -C PHYSICS
uc pi
```

## Categories and Units

`uc` supports various categories including DATA, DISTANCE, VOLUME, AREA, MASS, TIME, and TEMPERATURE. Use the `-c` and `-u` options to explore available categories and units.

## Constants

The utility provides access to a wide range of mathematical and scientific constants. Use the `-Cg`, `-Cd`, and `-C` options to explore available constants.

## History

`uc` keeps track of your conversion history. Use `--hist` to view past conversions and `--clrhist` to clear the history.

## Contributing

[ ... ]

## License

[ ... ]

## Author

Jason Armstrong

---
