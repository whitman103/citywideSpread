#ifndef RANDDRIVERS_HPP
#define RANDDRIVERS_HPP

#include <boost/random/variate_generator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/uniform_int.hpp>

using RealGenerator =  boost::variate_generator<boost::mt19937, boost::uniform_real<>>;
using IntGenerator = boost::variate_generator<boost::mt19937, boost::uniform_int<> >;

struct RandDrivers{
    RealGenerator InfectiousStrengthGenerator;
    IntGenerator RecoveryTimeGenerator;
    IntGenerator InfectiousTimeGenerator;
};

#endif