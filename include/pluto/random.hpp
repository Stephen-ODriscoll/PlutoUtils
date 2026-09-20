/*
* Copyright (c) 2026 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#ifndef PLUTO_UTILS_RANDOM_HPP
#define PLUTO_UTILS_RANDOM_HPP

#include <limits>
#include <random>

// Configurable with a macro
#ifndef PLUTO_RANDOM_ENGINE_TYPE
#define PLUTO_RANDOM_ENGINE_TYPE std::mt19937
#endif

namespace pluto
{
    class random
    {
    public:
        typedef PLUTO_RANDOM_ENGINE_TYPE engine_type;

    private:
        engine_type m_engine{};

    public:
        static inline random& instance()
        {
            static random instance{};
            return instance;
        }

        inline engine_type& engine()
        {
            return m_engine;
        }

        template<class Seed = std::random_device>
        inline void seed(Seed seed = {})
        {
            m_engine.seed(seed());
        }

        inline auto operator()()
        {
            return std::uniform_real_distribution<>{ 0, 1 }(m_engine);
        }

        inline auto uniform(const double minimum, const double maximum)
        {
            return std::uniform_real_distribution<>{ minimum, maximum }(m_engine);
        }

        template<class Value>
        inline auto rand(const Value minimum, const Value maximum)
        {
            return std::uniform_int_distribution<Value>{ minimum, maximum }(m_engine);
        }

        inline auto rand_int(const int minimum, const int maximum)
        {
            return rand<int>(minimum, maximum);
        }

        template <class Value>
        inline auto rand_range(const Value start, const Value stop)
        {
            assert(stop != std::numeric_limits<Value>::lowest() && "pluto::rand_range() got an invalid stop");
            return std::uniform_int_distribution<Value>{ start, static_cast<Value>(stop - 1) }(m_engine);
        }

        template <class Value>
        inline auto rand_range(const Value stop)
        {
            return rand_range<Value>(0, stop);
        }

        template<class Container>
        inline auto& choice(const Container& container)
        {
            typedef decltype(std::size(container)) Size;
            return *(std::next(std::begin(container), rand_range<Size>(0, std::size(container))));
        }

        template<class Container>
        inline void shuffle(Container& container)
        {
            std::shuffle(std::begin(container), std::end(container), m_engine);
        }

        inline auto bernoulli(const double probability = 0.5)
        {
            return std::bernoulli_distribution{ probability }(m_engine);
        }

        inline auto binomial(const int trials = 1, const double probability = 0.5)
        {
            return std::binomial_distribution<>{ trials, probability }(m_engine);
        }

        inline auto negative_binomial(const int trialSuccesses = 1, const double probability = 0.5)
        {
            return std::negative_binomial_distribution<>{ trialSuccesses, probability }(m_engine);
        }

        inline auto geometric(const double probability = 0.5)
        {
            return std::geometric_distribution<>{ probability }(m_engine);
        }

        inline auto poisson(const double mean = 1)
        {
            return std::poisson_distribution<>{ mean }(m_engine);
        }

        inline auto exponential(const double rate = 1)
        {
            return std::exponential_distribution<>{ rate }(m_engine);
        }

        inline auto gamma(const double shape = 1, const double scale = 1)
        {
            return std::gamma_distribution<>{ shape, scale }(m_engine);
        }

        inline auto weibull(const double shape = 1, const double scale = 1)
        {
            return std::weibull_distribution<>{ shape, scale }(m_engine);
        }

        inline auto extreme_value(const double location = 0, const double scale = 1)
        {
            return std::extreme_value_distribution<>{ location, scale }(m_engine);
        }

        inline auto normal(const double mean = 0, const double standardDeviation = 1)
        {
            return std::normal_distribution<>{ mean, standardDeviation }(m_engine);
        }

        inline auto lognormal(const double logScale = 0, const double shape = 1)
        {
            return std::lognormal_distribution<>{ logScale, shape }(m_engine);
        }

        inline auto chi_squared(const double degreesOfFreedom = 1)
        {
            return std::chi_squared_distribution<>{ degreesOfFreedom }(m_engine);
        }

        inline auto cauchy(const double location = 0, const double scale = 1)
        {
            return std::cauchy_distribution<>{ location, scale }(m_engine);
        }

        inline auto fisher_f(const double degreesOfFreedom1 = 1, const double degreesOfFreedom2 = 1)
        {
            return std::fisher_f_distribution<>{ degreesOfFreedom1, degreesOfFreedom2 }(m_engine);
        }

        inline auto student_t(const double degreesOfFreedom = 1)
        {
            return std::student_t_distribution<>{ degreesOfFreedom }(m_engine);
        }
    };
}

#endif
