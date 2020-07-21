import sys
sys.path.append("../../../build/bind/use_pybind11")

import python_example

assert python_example.__version__ == '0.0.1' or python_example.__version__ == 'test'
assert python_example.add(1, 2) == 3
assert python_example.subtract(1, 2) == -1

print(python_example.__doc__)
print(python_example.add.__doc__)
print(python_example.subtract.__doc__)
