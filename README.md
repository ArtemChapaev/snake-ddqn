## Installation

````
git clone --recurse-submodules https://github.com/ArtemChapaev/Snake -b WSL_version
cd Snake
bash setup.sh
build/snake
````

## Configuration
You can specify path to settings file by command-line flag -f (by default using "settings.txt" in game directory).

Example:
```
./snake -f "../example/path/settings.txt"
```

## Requirements
- Unix
- Git
- C++17 or higher
- Cmake >= 3.6

## License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

