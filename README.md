# ArgParse
ArgParser - C++ Argument Parser reflecting the python module ArgParse

Quick Start
-----------

The `ArgParse` library allows the easy creation of a 'living' help text for your program following the python module [ArgParse](https://docs.python.org/3/library/argparse.html).

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
