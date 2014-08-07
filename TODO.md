# Containers
- Make sure vector implements SequenceContainer:
  http://en.cppreference.com/w/cpp/concept/SequenceContainer

# Hash
- long long
- unsigned long long
- float
- double
- long double

# File I/O
- Filename parsing:
    - Support for home directories.
    - Support for network shares.

# Net
- URI parsing

# Text
- String, rune and string builder classes: Input operators should behave like
  FormattedInputFunction as described in the [C++ wiki][1].
- Input operators for string builder class. Maybe also getline function.
- Update to Unicode 7.0

[1]: http://en.cppreference.com/w/cpp/string/basic_string/operator_ltltgtgt
