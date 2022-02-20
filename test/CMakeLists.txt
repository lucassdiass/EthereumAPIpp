cmake_minimum_required(VERSION 2.6)
project(EthereumAPITest)

enable_testing()

add_executable( UnitTests TestEthereum.cpp NetTest.cpp ETHEREUMTest.cpp)
target_link_libraries(runUnitTests gtest gtest_main pthread EthereumAPIpp curl)
add_test( runUnitTests runUnitTests )
