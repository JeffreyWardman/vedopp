#include <nanobind/nanobind.h>

#include <iostream>
#include <string>

int add(int a, int b) { return a + b; }

NB_MODULE(vedopy, m)
{
    m.def("add", &add, nanobind::arg("a"), nanobind::arg("b") = 1,
          "This function adds two numbers and increments if only one is provided.");
}

// int main(int argc, char* argv[])
// {
//     std::cout << "Hello world!" << std::endl;

//     return 0;
// }
