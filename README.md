# ConTiles
Multiplatform console tiling manager  
Run: 
```
ConTiles.exe -h
```
for help
### Modules
`logger` provides utility for logging informations to file  
`render` responsible for writing on the console and calculating tile layout  
`util` shared utility functions and data structures, interfacing with OS  

### Code Style
`snake_case` variables, methods  
`PascalCase` structs  
`camelCase` types  
`ALL CAPS` defines, global constants  
`_g` before global variable  
`_v` at the end of variadic functions (that take va_list as argument)  
