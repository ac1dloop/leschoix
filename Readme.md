# LesChoix

Probably simplest command line arguments parser.

### Why?

The main point is to have something to include fast in project and use as is for testing purposes.
**LesChoix** Lacks of any type checking and not optimized at all
**LesChoix** Is ready for best C++ package management practices

**It is simple and it parses** !

### Usage

**Three steps to segfault**

1. Include header
`#include "leschoix.hpp"`
2. Create instance
`Y::LesChoix parser(argc, argv)`
3. Access arguments
`int port = parser['p'].Get<int>(8081)`

See main.cpp for example.

### Docs

to make docs doxygen has to be installed

```shell
doxygen doxyconf
```
I dont think they really needed

### To-do:

* Type checking
* Make it similiar to argparse
* --ver --help default outputs
* Allow for custom handlers
