#include <iostream>
#include <fstream>
#include <memory>
#include <gtest/gtest.h>
#include "Accumulator.h"

using namespace std;

TEST(UniqueAccumulatorTest, EmptyValue)
{
    Accumulator::UniqueAccumulator<string> acc;
    EXPECT_EQ(true, acc.Empty());

    stringstream s("some");
    s >> acc;

    EXPECT_EQ(false, acc.Empty());
}

TEST(UniqueAccumulatorTest, EmptyValueRuntimeError)
{
    Accumulator::UniqueAccumulator<string> acc;
    EXPECT_THROW(acc.Value(), runtime_error); 
}

TEST(UniqueAccumulatorTest, FirstValue) 
{
    Accumulator::UniqueAccumulator<string> acc;

    const string first = "first";
    stringstream s(first);
    s >> acc;
    EXPECT_EQ(first, acc.Value());
}

TEST(UniqueAccumulatorTest, StreamOperator) 
{
    Accumulator::UniqueAccumulator<string> acc1;
    Accumulator::UniqueAccumulator<string> acc2;

    const string first = "first";
    stringstream s(first);

    s >> acc1;
    acc2.Add(first);

    EXPECT_EQ(first, acc1.Value());
    EXPECT_EQ(first, acc2.Value());
}

TEST(UniqueAccumulatorTest, StringValueFileTest) 
{
    const string filename = "str_temp_unique.txt";
    {
        ofstream f(filename);
        f << "first" << endl << "second" << endl;
    }
    Accumulator::UniqueAccumulator<string> acc;
    ifstream in(filename);
    while (in >> acc) {}
    EXPECT_EQ("firstsecond", acc.Value());
}

TEST(UniqueAccumulatorTest, StringUniqueValueTest) 
{
    stringstream s;
    s << "first" << endl 
      << "first" << endl
      << "second" << endl
      << "second" << endl;
    Accumulator::UniqueAccumulator<string> acc;
    while (s >> acc) {}
    EXPECT_EQ("firstsecond", acc.Value());
}

TEST(UniqueAccumulatorTest, IntValueFileTest) 
{
    const string filename = "int_temp_unique.txt";
    {
        ofstream f(filename);
        f << 1 << endl << 2 << endl;
    }
    Accumulator::UniqueAccumulator<int> acc;
    ifstream in(filename);
    while (in >> acc) {}
    EXPECT_EQ(3, acc.Value());
}

TEST(UniqueAccumulatorTest, NumericUniqueValueFileTest) 
{
    const string filename = "int_temp_unique2.txt";
    {
        ofstream f(filename);
        f << 1 << endl << 1 << endl << 2 << endl;
    }
    Accumulator::UniqueAccumulator<int> acc;
    ifstream in(filename);
    while (in >> acc) {}
    EXPECT_EQ(3, acc.Value());
}

TEST(UniqueAccumulatorTest, DoubleValueFileTest) 
{
    const string filename = "bdl_temp_unique.txt";
    {
        ofstream f(filename);
        f << 1.3 << endl << 2.5 << endl;
    }       
    Accumulator::UniqueAccumulator<double> acc;
    ifstream in(filename);
    while (in >> acc) {}
    EXPECT_EQ(3.8, acc.Value());
}

