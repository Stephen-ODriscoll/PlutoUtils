# Pluto Utils
[Back to README](../README.md#documentation)

## scope.hpp
These utilities are very useful for cleanup, especially cleanup of handles or memory. Simply add a lambda function to free any memory resource, and you can guarantee that memory is freed without having to free it on every possible return or exception.

Throwing in a destructor is dangerous and can result in a crash, so all destructors will try to catch and ignore any exceptions thrown during scope exit. Always add checks for null pointers before trying to free resources.

For C++ 14, using [pluto::on_scope_success](#on_scope_success) or [pluto::on_scope_fail](#on_scope_fail) in an already failing scope will not count additional failures. As such, **pluto::on_scope_success** will never run its tasks, and **pluto::on_scope_fail** will always run its tasks.

For C++ 17 or above, using [pluto::on_scope_success](#on_scope_success) or [pluto::on_scope_fail](#on_scope_fail) in an already failing scope will count additional failures. They will both only acknowledge failures that occur after they are constructed.

Tasks are run in reverse order of being added, like destructors.

### on_scope_exit
1. Takes no arguments and creates a blank stack of tasks to perform on scope exit.
2. Takes a **std::function\<void()\>** (use lambdas) and adds it to the stack of tasks to perform on scope exit.

#### add()
Takes a **std::function\<void()\>** (use lambdas) and adds it to the stack of tasks to perform on scope exit.

### on_scope_success
1. Takes no arguments and creates a blank stack of tasks to perform on scope success.
2. Takes a **std::function\<void()\>** (use lambdas) and adds it to the stack of tasks to perform on scope success.

#### add()
Takes a **std::function\<void()\>** (use lambdas) and adds it to the stack of tasks to perform on scope success.

### on_scope_fail
1. Takes no arguments and creates a blank stack of tasks to perform on scope fail.
2. Takes a **std::function\<void()\>** (use lambdas) and adds it to the stack of tasks to perform on scope fail.

#### add()
Takes a **std::function\<void()\>** (use lambdas) and adds it to the stack of tasks to perform on scope fail.
