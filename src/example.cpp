#include <pybind11/pybind11.h>

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(python_example, m)
{
    m.doc() = ""
              "Pybind11 example plugin"
              "-----------------------"
              ".. currentmodule:: python_example"
              ".. autosummary::"
              ":toctree: _generate"
              "add"
              "subtrac";

    m.def("add", &add,
        "Add two numbers"
        "Some other explanation about the add function");

    m.def("subtract", [](int i, int j) { return i - j; },
        "Subtract two numbers"
        "Some other explanation about the subtract function."
    );

    m.attr("__version__") = "test";

// Unknown error C2143: syntax error: missing ';' before 'constant'
#if 0
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
#endif
}
