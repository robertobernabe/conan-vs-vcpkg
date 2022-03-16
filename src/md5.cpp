#include <Poco/MD5Engine.h>
#include <Poco/DigestStream.h>

#include <iostream>

#if defined(CONAN)
    #define PCKGMNGR "conan"
#elif defined(VCPKG)
    #define PCKGMNGR "vcpkg"
#else
    #define PCKGMNGR "none"
#endif

#define B(name) true

inline const char *const bool_to_str(bool b)
{
    return b ? "true" : "false";
}

void do_something(bool do_this, bool do_that)
{
    std::cout << "Do this: " << bool_to_str(do_this) << std::endl;
    std::cout << "Do that: " << bool_to_str(do_that) << std::endl;
}

int main(int argc, char **argv)
{
    Poco::MD5Engine md5;
    Poco::DigestOutputStream ds(md5);
    ds << "abcdefghijklmnopqrstuvwxyz";
    ds.close();
    std::cout << Poco::DigestEngine::digestToHex(md5.digest()) << std::endl;
    do_something(B(do_this), !B(do_that));
    std::cout << "Hello world. This samples was build using: " << PCKGMNGR << std::endl;

    return 0;
}