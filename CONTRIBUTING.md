# Contributing to C++ Concepts

Thank you for your interest in contributing to the C++ Concepts repository! This document provides guidelines for contributing.

## How to Contribute

### Adding New Examples

1. Create a new directory under `examples/` with your concept name
2. Add a `CMakeLists.txt` file with the executable target
3. Implement your example in a `.cpp` file
4. Update the main `CMakeLists.txt` to include your subdirectory
5. Update the `Makefile` to build your example
6. Update the `README.md` to document your example
7. Test that your example builds and runs correctly

### Code Style Guidelines

- Use C++17 standard
- Include detailed comments explaining concepts
- Use meaningful variable names
- Follow the existing code structure and formatting
- Ensure code compiles with `-Wall -Wextra -O2`

### Documentation

- Update the README.md with new sections as needed
- Include code examples in the README
- Keep documentation up to date

### Testing

- Ensure all examples build successfully
- Test that examples run without errors
- Add tests for new functionality if appropriate

## Pull Request Process

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/new-concept`)
3. Commit your changes (`git commit -am 'Add new concept example'`)
4. Push to the branch (`git push origin feature/new-concept`)
5. Create a Pull Request

## Code of Conduct

Please be respectful and constructive in all interactions. This is a learning resource, so focus on educational value and code quality.