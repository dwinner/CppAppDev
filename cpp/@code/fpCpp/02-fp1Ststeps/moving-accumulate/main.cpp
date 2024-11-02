#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// A dummy class which notifies when constructors, destructors
// and the assignment operator get called
class accumulate_test {
public:
    accumulate_test()
        : m_valid(true)
    {
        std::cout << "constructor" << std::endl;
    }

    accumulate_test(const accumulate_test& other)
        : m_data(other.m_data)
        , m_valid(true)
    {
        std::cout << "copy constructor" << std::endl;
    }

    accumulate_test(accumulate_test&& other)
        : m_data(std::move(other.m_data))
        , m_valid(true)
    {
        other.m_valid = false;
        std::cout << "move constructor" << std::endl;
    }

    accumulate_test& operator=(const accumulate_test& other)
    {
        std::cout << "copy assignment operator" << std::endl;
        accumulate_test temp(other);
        std::swap(m_data, temp.m_data);
        std::swap(m_valid, temp.m_valid);
        return *this;
    }

    accumulate_test& operator=(accumulate_test&& other)
    {
        std::cout << "move assignment operator" << std::endl;
        std::swap(m_data, other.m_data);
        std::swap(m_valid, other.m_valid);
        return *this;
    }

    ~accumulate_test()
    {
        std::cout << "destructor: " << m_valid << std::endl;
    }

    std::vector<std::string>& data()
    {
        return m_data;
    }

private:
    std::vector<std::string> m_data;
    bool m_valid;
};


// A modified implementation of std::accumulate which avoids
// unnecessary copies -- whenever it calls the folding function,
// it moves the previously accumulated value into it instead
// of passing a copy
template <typename BeginIt, typename EndIt, typename T, typename F>
T moving_accumulate(BeginIt first, const EndIt& last, T init,
                    F folding_function)
{
    for (; first != last; ++first) {
        // When passing the accumulated value to
        // the folding function, move from it.
        // This might make problems for types that
        // do not support assignment to moved-from values,
        // but it will work for most types without problems.
        init = folding_function(std::move(init), *first);
    }
    return init;
}

int main(int argc, char* argv[])
{
    std::vector<int> xs{1, 2, 3, 4, 5, 6, 7, 8};

    // The folding function accepts a value as the accumulator,
    // but thanks to the move semantics no unnecessary copies
    // get made
    auto result =
        moving_accumulate(xs.cbegin(), xs.cend(), accumulate_test(),
                          [](accumulate_test acc, int x) {
                              acc.data().push_back(std::to_string(x));
                              return acc;
                          });

    std::cout << "accumulate finished" << std::endl;

    return 0;
}
