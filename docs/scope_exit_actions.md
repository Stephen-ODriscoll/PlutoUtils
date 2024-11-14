# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## scope_exit_actions.hpp

### scope_exit_actions
This class is very useful for cleanup, especially cleanup of handles or memory. Simply add a lambda function to free any memory resource and you can guarantee that memory is freed without having to free it on every possible return, or if your function throws.
Note: Throwing on a catch of another exception is dangerous and can result in a crash, so scope_exit_actions will catch and ignore any exceptions thrown during scope exit. Always add checks for null pointers before trying to free resources.
1. Takes no arguments and creates a blank stack of actions to perform on scope exit.
2. Takes a **std::function** with no arguments and **void** return type (use lambdas) and adds it to the stack of actions to perform on scope exit.

#### add()
Takes a **std::function** with no arguments and **void** return type (use lambdas). Adds this function to the stack of actions to perform on scope exit.
