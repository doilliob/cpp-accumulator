# Accumulator 

C++ implementation of accumulator class.

Usage:
```
#include "Accumulator.h"


Accumulator::Accumulator<int> intAcc;

cout << intAcc.Empty(); // true
intAcc.Add(1);
intAcc.Add(2);
intAcc.Add(3);
cout << intAcc.Empty(); // false
cout << intAcc.Value(); // 6

// Supports stream input
Accumulator::Accumulator<string> strAcc;
stringstream s;
s << "A" << endl << "B" << endl;

while (s >> strAcc) {}
cout << strAcc.Value(); // "AB"
```

Please note: using `.Value()` method on empty accumulator will lead to runtime error!
```
Accumulator::Accumulator<int> intAcc;
cout << intAcc.Value(); // runtime error!
```