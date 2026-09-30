# Architecture-Description-Language-for-Configurable-CPU-Simulation


## Grader and Instructor

| Name                  | Role          | Username   | 
| -------------         | ------------- |------------|
| Johnathan Woods       | TA-Instructor |jwoods7097  | 
| Prithiv Vijayasekar   | Grader        | Prithivvj7 | 

## Prerequisites

Before building the project, install:

- A C++20 compatible compiler
- CMake 3.20+
- Git
- Java (required for ANTLR4)

## Building
Configure CMake:

```bash
cmake -S . -B build
```

Compile:

```bash
cmake --build build
```

CMake will automatically download and build SDL3 and Dear ImGui during
the initial configuration/build. Go to /build and run the executable
