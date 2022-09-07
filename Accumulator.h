#include <iostream>
#include <memory>

namespace Accumulator {

    // Accumulator - class template for accumulating values
    template <typename T> 
    class Accumulator {
        private:
            // Internal value pointer
            std::unique_ptr<T> sum;
        public:
            // Returns true if internal value is empty
            bool Empty() { return sum.get() == nullptr; }

            // Returns internal value (or runtime_error if internal value is empty)
            T Value() 
            {
                if (Empty())
                {
                    throw std::runtime_error("Acuumulator is empty!");
                }
                return *sum; 
            }

            // Adds external value to accumulated internal value
            // If internal value is empty, external value will be the first value
            void Add(T val)
            {
                if (Empty())
                {
                    sum.reset(new T(val));
                }
                else
                {
                    *sum = *sum + val;
                }
            }
             
      };

    // Stream output to Accumulator
    template <typename T> 
    std::istream& operator>>(std::istream& in, Accumulator<T>& acc)
    {
        T tmp;
        if (in >> tmp) {
            acc.Add(tmp);
        }
        return in;
    }
    

}