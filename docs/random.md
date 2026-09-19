# Pluto Utils
[Back to README](../README.md#documentation)

## random.hpp

### PLUTO_RANDOM_ENGINE_TYPE
Define this macro to be a random number engine. Sets the engine type. See [engine_type](#engine_type). Defaults to **std::mt19937**.

### random
A class for managing a random number engine. Takes no arguments.

#### engine_type
The type of the engine. Defaults to [PLUTO_RANDOM_ENGINE_TYPE](#PLUTO_RANDOM_ENGINE_TYPE).

#### instance()
Returns a reference to a local static **pluto::random** instance.

#### engine()
Returns a reference to the underlying random engine for direct usage.

#### seed()
Takes a optional seed and uses it to seed the random engine. Defaults to **std::random_device**.

#### operator()()
Returns a **double** such that `0 <= X <= 1` using **std::uniform_real_distribution**.

#### uniform()
Takes a **double** for minimum and a **double** for maximum. Returns a **double** such that `minimum <= X <= maximum` using **std::uniform_real_distribution**.

#### rand()
Takes a number for minimum and a number for maximum. Returns a number such that `minimum <= X <= maximum` using **std::uniform_int_distribution**.

#### rand_int()
Takes an **int** for minimum and an **int** for maximum. Returns an **int** such that `minimum <= X <= maximum` using **std::uniform_int_distribution**.

#### rand_range()
1. Takes a number for start and a number for stop. Returns a number such that `start <= X < stop` using **std::uniform_int_distribution**.
2. Takes a number for stop. Returns a number such that `0 <= X < stop` using **std::uniform_int_distribution**.

#### choice()
Takes a container. Returns a random element using **std::next** and **std::uniform_int_distribution**.
- Passing an empty container will result in an access violation.

#### shuffle
Takes a container. Randomly rearranges the container using **std::shuffle**.

#### bernoulli
Takes an optional **double** for the probability of generating **true** (defaults to 0.5). Returns a random **bool** generated using **std::bernoulli_distribution**.

#### binomial
Takes an optional **int** for the number of trials (defaults to 1) and an optional **double** for the probability of a trial generating **true** (defaults to 0.5). Returns a random **int** generated using **std::binomial_distribution**.

#### negative_binomial
Takes an optional **int** for the number of trial successes (defaults to 1) and an optional **double** for the probability of a trial generating **true** (defaults to 0.5). Returns a random **int** generated using **std::negative_binomial_distribution**.

#### geometric
Takes an optional **double** for the probability of a trial generating **true** (defaults to 0.5). Returns a random **int** generated using **std::geometric_distribution**.

#### poisson
Takes an optional **double** for the mean of the distribution (defaults to 1). Returns a random **int** generated using **std::poisson_distribution**.

#### exponential
Takes an optional **double** for the rate parameter (defaults to 1). Returns a random **double** generated using **std::exponential_distribution**.

#### gamma
Takes an optional **double** for the shape (defaults to 1) and an optional **double** for the scale (defaults to 1). Returns a random **double** generated using **std::gamma_distribution**.

#### weibull
Takes an optional **double** for the shape (defaults to 1) and an optional **double** for the scale (defaults to 1). Returns a random **double** generated using **std::weibull_distribution**.

#### extreme_value
Takes an optional **double** for the location (defaults to 0) and an optional **double** for the scale (defaults to 1). Returns a random **double** generated using **std::extreme_value_distribution**.

#### normal
Takes an optional **double** for the mean (defaults to 0) and an optional **double** for the standard deviation (defaults to 1). Returns a random **double** generated using **std::normal_distribution**.

#### lognormal
Takes an optional **double** for the log-scale (defaults to 0) and an optional **double** for the shape (defaults to 1). Returns a random **double** generated using **std::lognormal_distribution**.

#### chi_squared
Takes an optional **double** for the degrees of freedom (defaults to 1). Returns a random **double** generated using **std::chi_squared_distribution**.

#### cauchy
Takes an optional **double** for the location (defaults to 0) and an optional **double** for the scale (defaults to 1). Returns a random **double** generated using **std::cauchy_distribution**.

#### fisher_f
Takes an optional **double** for the first degrees of freedom (defaults to 1) and an optional **double** for the second degrees of freedom (defaults to 1). Returns a random **double** generated using **std::fisher_f_distribution**.

#### student_t
Takes an optional **double** for the degrees of freedom (defaults to 1). Returns a random **double** generated using **std::student_t_distribution**.
