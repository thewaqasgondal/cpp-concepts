# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- **Advanced Examples**: Added 4 new comprehensive examples covering advanced C++ topics
  - `modern_cpp`: C++11/14/17 features (auto, lambdas, smart pointers, optional, variant, any, constexpr)
  - `file_io`: File operations, binary I/O, string streams, filesystem library
  - `concurrency`: Threading, mutexes, condition variables, atomics, futures, thread pools
  - `move_semantics`: Rvalue references, move constructors, perfect forwarding
- Strings example demonstrating string operations, algorithms, and streams
- Templates example covering function templates, class templates, specialization, and metaprogramming
- Exception handling example with custom exceptions, RAII, and error safety
- MIT License
- GitHub Actions CI/CD workflow
- Badges for C++ version, CMake, license, and CI status
- Basic test suite
- CONTRIBUTING.md guidelines
- CHANGELOG.md

### Changed
- Updated README.md with new examples and improved documentation
- Enhanced build system to support all new examples
- Updated last modified date
- Expanded repository from 10 to 16 example categories

### Fixed
- Compilation issues in string streams example
- Template definition order in templates example
- Constexpr function scoping in modern_cpp example

## [1.0.0] - 2024-12-13

### Added
- Initial release with comprehensive C++ examples
- Examples for basics, data types, control flow, functions, arrays/vectors, pointers/references, OOP, memory management, and STL
- Build system using CMake and Make
- Detailed README with code examples and explanations