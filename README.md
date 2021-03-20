# sodoku-solver
You can run this `C program` on the console, which can solve a `sodoku puzzle` efficiently.

## Commands
| Command         | description                                                 |
|:----------------|-------------------------------------------------------------|
| **load <map>**  | load a sodoku map from consol                               |
| **open <path>** | open a sodoku map from file (the file containts <map> text) |
| **save <path>** | save opened sodoku                                          |
| **solve**       | solve the active sodoku, and print the solution             |
| **print**       | print the active sodoku                                     |
| **exit**        | exit                                                        |
| **help**        | some help how to use this program                           |

The `map` means a sodoku puzzle with the [current format](##format-of-sodoku-puzzle), wich can be specified through the console easily, or the file needs to be included. The `path` is the path to the file.

**Example**
You can load a sodoku puzzle easily from console, and solve it:
```
load .4..8..7.2....4.5.7....96.4374...8.....836.....6...9351.23....7.9.4....6.6..1..2.
solve
```

## Format of sodoku puzzle
```
6.3 5.. ... 
.12 ... 9.. 
... ..4 ... 

... .35 .8. 
7.. 8.6 ..5 
.5. 19. ... 

... 4.. ... 
..9 ... 75. 
... ..2 6.3 
```

> Zero can be used instead of the dot character, and spaces and enters are optional. The specified format is valid for input specified through a console or file.