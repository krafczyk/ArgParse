# ArgParse
ArgParser - C++ Argument Parser reflecting the python module ArgParse

Why Use?
========

The `ArgParse` library allows the easy creation of a 'living' help text for your program following the python module [ArgParse](https://docs.python.org/3/library/argparse.html).

`ArgParse` Creates a reaonable looking help text without much work from the developer. For any argument the developer wishes to recognize, this sytem requires him or her to tell the user that the argument exists, how to call it, as well as what that argument does. This is in contrast to some systems where code for reading arguments is separated from the code to display help text.

Using `ArgParse` will greatly simplify the creation of help text as well as keep you honest about what your arguments are for.

Quick Start
===========

A parser object takes pointers directly to the objects or plain old data (POD) types where you want the argument information to end up. The parser object fills the type or object with the argument information after it parses the arguments passed to your program.

  1. Define all objects and variables you want to contain arguments. Be sure to initialize them with appropriate default values.

  2. Within your main function, create an argument parser object which takes a string describing your program. For instance the line:

    `ArgParse::ArgParser Parser("A test program to show how the ArgParse library works");`

    Declares a parser object with the general help string "A test program to show how the ArgParse library works"

  3. Create an argument for the parser to recognize by calling the `AddArgument` method of the parser object.

    `Parser.AddArgument("--number-two", "Another number", &test_num_2, ArgParse::Argument::Optional, &test_num_2_defined);`

    The first argument, defines the text argument that the parser will look for. For example, `--number-two=8` will now be recognized. Multiple versions can refer to the same argument by passing something like `-n/--num/--number-one` will allow `-n 3`, `--num 10`, or `--number-one 100` to be recognized and set the value of a single argument. Arguments can be recognized with either a space between the argument specifier and the value or an equal sign separating them. In the argument specifying string, the actual argument specifiers are separated by a '/'. This means that any string between '/'s can be used as an argument specifier. For instance `create/-c/--create-value` will recognize `create`, `-c`, or `--create-value` as argument specifiers for a single argument.

    The second argument gives the help text which will be printed for that argument

    The third argument is a pointer to the object or variable which will receive the argument

    The fourth argument lets the parser know whether this argument is optional or not. This and later arguments can be left out as they have default values. The default value is for the argument to be optional. If you want your argument to be required, you can pass `ArgParse::Argument::Required` for this argument.

    The fifth and final argument is an optional pointer to a boolean variable which will be set to `true` if the argument was defined, and `false` if it was not. Not defining this argument or passing a null pointer or 0 will result in the default behaviour, which is not passing the rest of the program this information.

  4. Call the `ParseArgs` method of the parser object with `argc` and `argv` to parse the command line. Be sure to check that the arguments were parsed without error! For instance:

    ```
    if (Parser.ParseArgs(argc,argv) < 0) {
      printf("There was an error parsing the arguments!\n");
      return -1;
    }
    ```

    Ensures that the return value of the `ParseArgs` method is checked, and aborts the program if it failed. Be sure to add appropriate cleanup code to before exiting if your program requires it.

    The parser will 'eat' the arguments and hence modify `argc` and `argv`. You can stop the parser from parsing by passing a simple `--` argument. This can allow you to capture some arguments before other subsystems which might receive arguments themselves. Simply pass `argc` and `argv` to `ParseArgs`, then pass them again to the next subsystem. They will be modified appropriately as if you had only passed the arguments after the `--`.
  
  5. Check if the user called for the help text
  
    The method `HelpPrinted` tells you if the helptext was printed. If it was, it is generally a good idea to cleanup and exit. For instance:
    
    ```
    if (Parser.HelpPrinted()) {
      return 0;
    }
    ```
    
    This checks if the help text was printed, and if it does, it exists. Be sure to add appropriate cleanup code here.

Refer to the file `tutorial/tutorial.cpp` for a commented example of a complete program which uses the `ArgParse` library.

Building and Installing
=======================

Both shared and static libraries are created by this package. The following directions show how to build and install this software.

  1. Create a directory `<build_dir>` you want to build the `ArgParse` in.
  2. Configure the package.
    
    Change to `<build_dir>` and call `cmake <source_dir>`.

    You can specify a specific installation directory by passing the option `-DCMAKE_INSTALL_PREFIX=<install_dir>` to the `cmake` command.
    
    You can enable the building of unit tests by passing the argument `-DUNITTESTS` to the `cmake` command.

    You can enable the building of the tutorial program by passing the argument `-DTUTORIAL` to the `cmake` command.
  
  3. Build the package.
  
    Change to the `<build_dir>` and execute the `make` command possibly with `-j <n>` for a parallel build.

  4. Install the package.
  
    Make the `install` target with `make install`.

Using ArgParse
==============

This section serves as a more detailed guide to defining arguments.

Argument Types
--------------

`ArgParse` supports a number of 'scalar' and 'vector' types. The scalar types are meant to be defined once. If they are passed to the program multiple times, the value which gets stored will be the last one passed. The scalar types are meant to be able to be defined multiple times. All values will be stored in the order they are given. All supported variable types are available in both scalar and vector forms. To get the vector form of a supported type, define a `std::vector<T>` where `T` is the supported type.

###Supported Types:

`bool`

`std::string`

`char`

`unsigned char`

`short`

`unsigned short`

`int`

`unsigned int`

`long`

`unsigned long`

`long long`

`unsigned long long`

`float`

`double`

`long double`

Argument Groups
---------------

A group of arguments can be added to the parser object which can be used to either logically collect the arguments together, or functionally enforce some behaviour like requiring that only one argument of a group is defined, or if one is defined, then all must be defined.

Three types of argument groups can be defined 
  1. A plain group which places no requirements on how the arguments are defined. This type of group is useful to logically collect a set of arguments together.
   
  To add a plain group to the parser object, call the `AddArgGroup` method.

  2. An inclusive group which requires that if one argument in the group is defined, that all arguments in that group must be defined
  
  To add an inclusive group to the parser object, call the `AddInclusiveArgGroup` method.

  3. An exclusive group which requires that if an argument in the group is defined, that only one argument in that group is defined.
  
  To add an exclusive group to the parser object, call the `AddExclusiveArgGroup` method.

Each of these methods returns a pointer to an `ArgGroup` object. This object can be treated just like the parser object. i.e. arguments and argument groups can be added. Adding an argument group can look like this:

`ArgGroup* exclusive_group = Parser.AddArgGroup("test group", "A set of arguments which belong together");`

After the help text for that group, the group can have a mode set which defines whether the arguments in the group have no restrictions (`ArgParse::Argument::None`), the group can only be defined once (`ArgParse::Argument::Single`), the group has the possibility to be defined multiple times (`ArgParse::Argument::Multiple`). The default is no restrictions.

After the group mode, you can define whether the arguments in the group are optional or required. The default is optional.
