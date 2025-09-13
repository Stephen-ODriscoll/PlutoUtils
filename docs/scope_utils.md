# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/master/README.md#documentation)

## scope_utils.hpp
These utilities are very useful for cleanup, especially cleanup of handles or memory. Simply add a lambda function to free any memory resource, and you can guarantee that memory is freed without having to free it on every possible return or exception.
- Throwing in a destructor is dangerous and can result in a crash, so all destructors will try to catch and ignore any exceptions thrown during scope exit. Always add checks for null pointers before trying to free resources.

### on_scope_exit
1. Takes no arguments and creates a blank stack of tasks to perform on scope exit.
2. Takes a **std::function** with no arguments and **void** return type (use lambdas) and adds it to the stack of tasks to perform on scope exit.

#### add()
Takes a **std::function** with no arguments and **void** return type (use lambdas) and adds it to the stack of tasks to perform on scope exit.

### on_scope_success
1. Takes no arguments and creates a blank stack of tasks to perform on scope success.
2. Takes a **std::function** with no arguments and **void** return type (use lambdas) and adds it to the stack of tasks to perform on scope success.

#### add()
Takes a **std::function** with no arguments and **void** return type (use lambdas) and adds it to the stack of tasks to perform on scope success.

### on_scope_fail
1. Takes no arguments and creates a blank stack of tasks to perform on scope fail.
2. Takes a **std::function** with no arguments and **void** return type (use lambdas) and adds it to the stack of tasks to perform on scope fail.

#### add()
Takes a **std::function** with no arguments and **void** return type (use lambdas) and adds it to the stack of tasks to perform on scope fail.
