template <typename T>
concept big = sizeof(T) > 4;

static_assert(!big<char>);
static_assert(!big<short>);
static_assert(big<long double>);

int main()
{
}