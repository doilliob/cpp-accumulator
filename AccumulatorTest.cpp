#include <iostream>
#include <fstream>
#include <memory>
#include <gtest/gtest.h>
#include "Accumulator.h"

using namespace std;

TEST(AccumulatorTest, EmptyValue)
{
    Accumulator::Accumulator<string> acc;
    EXPECT_EQ(true, acc.Empty());

    stringstream s("some");
    s >> acc;

    EXPECT_EQ(false, acc.Empty());
}

TEST(AccumulatorTest, EmptyValueRuntimeError)
{
    Accumulator::Accumulator<string> acc;
    EXPECT_THROW(acc.Value(), runtime_error); 
}

TEST(AccumulatorTest, FirstValue) 
{
    Accumulator::Accumulator<string> acc;

    const string first = "first";
    stringstream s(first);
    s >> acc;
    EXPECT_EQ(first, acc.Value());
}

TEST(AccumulatorTest, StreamOperator) 
{
    Accumulator::Accumulator<string> acc1;
    Accumulator::Accumulator<string> acc2;

    const string first = "first";
    stringstream s(first);

    s >> acc1;
    acc2.Add(first);

    EXPECT_EQ(first, acc1.Value());
    EXPECT_EQ(first, acc2.Value());
}

TEST(AccumulatorTest, StringValueFileTest) 
{
    const string filename = "str_temp.txt";
    {
        ofstream f(filename);
        f << "first" << endl << "second" << endl;
    }
    Accumulator::Accumulator<string> acc;
    ifstream in(filename);
    while (in >> acc) {}
    EXPECT_EQ("firstsecond", acc.Value());
}

TEST(AccumulatorTest, IntValueFileTest) 
{
    const string filename = "int_temp.txt";
    {
        ofstream f(filename);
        f << 1 << endl << 2 << endl;
    }
    Accumulator::Accumulator<int> acc;
    ifstream in(filename);
    while (in >> acc) {}
    EXPECT_EQ(3, acc.Value());
}

TEST(AccumulatorTest, DoubleValueFileTest) 
{
    const string filename = "bdl_temp.txt";
    {
        ofstream f(filename);
        f << 1.3 << endl << 2.5 << endl;
    }
    Accumulator::Accumulator<double> acc;
    ifstream in(filename);
    while (in >> acc) {}
    EXPECT_EQ(3.8, acc.Value());
}

