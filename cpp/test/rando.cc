#include <random>
#include <chrono>

int main(int argc, char const *argv[])
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine *gen = new std::default_random_engine(seed);
    for (size_t i = 0; i < 40; i++)
    {
        std::uniform_int_distribution<int> a(0,200);
        printf("%i\n",a(*gen));
    }
    return 0;
}
