# Advanced Programming for Scientific Computing - Initial Challenge

_A Gradient Method for Multivariate Function Minimization_

## Table of Contents

- [Introduction](#introduction)
- [Overview](#overview)
- [Setup](#setup)
    - [Cloning the Repository](#cloning-the-repository)
    - [Compilation and Execution](#compilation-and-execution)
- [Usage](#usage)
    - [Parameters](#parameters)
    - [Options](#options)
    - [_MuParser_ Functions](#muparser-functions)

## Introduction

This repository offers an implementation of a gradient-based method designed for minimizing multivariate functions.

It introduces new classes and structures, including:

- `pacs::Vector`: Responsible for managing vectors in $\mathbb{R}^n$.
- `pacs::Target`: Manages the target function to be minimized along with its gradient. This can be provided as an input or evaluated numerically via finite differences.
- `pacs::Data`: Handles the output of the solver and facilitates communication with various routines and strategies.
- `pacs::Arguments` and `pacs::Parameters`: These classes manage command-line arguments and parameters. They utilize a custom and simple `argv` parser and the `nlohmann::json` class.

The implemented solver needs the following parameters for the target function minimization:

- Initial guess $x_0$
- Initial learning rate value $\alpha_0$
- Tolerances $\varepsilon_s$ and $\varepsilon_r$
- Maximum number of iterations
- An optional parser string for _MuParser_
- Strategy parameters $\mu$ and $\sigma$

Additionally, it requires two components:

1. A routine for evaluating the next point $x_{k + 1}$. (Defaults to the Newton routine).
2. A strategy for determining the learning rate value $\alpha_{k}$. (Defaults to the Fixed strategy).

Refer to [Options](#options) for the available routines and strategies.

## Overview

Key components include:

- `main.cpp`: Core script serving as a testing suite.
- `main.hpp`: Primary includes for `main.cpp`.
- `include/`:
    - `Solver.hpp`: Central solver method and associated routines/strategies.
    - `Arguments.hpp`: Methods for parsing command-line arguments.
    - `Parameters.hpp`: Methods for evaluating parameters from `parameters.json`.
    - `Vector.hpp`: Definition for the Vector class.
    - `Target.hpp`: Definition for the Target class, encapsulating the target function and its gradient or numerical evaluation.
    - `Default.hpp`: Definition of default target function and its gradient.

`src/` contains the implementations of the methods defined earlier.

## Setup

### Cloning the Repository

To begin, clone the repository from [here](https://github.com/diantonioandrea/pacs-first):

    git clone git@github.com:diantonioandrea/pacs-first.git

### Compilation and Execution

:warning: Ensure the `PACS_ROOT` variable is set to `/path/to/pacs-examples/Examples` and `LD_LIBRARY_PATH` includes `${PACS_ROOT}/lib` as required by _MuParser_.

Compile the code:

    make

Execute the code:

    ./main

For further details on options and parameters, refer to the [Usage](#usage) section.

Furthermore, the executable could potentially be accelerated by removing the comment from the following line in the [Makefile](./Makefile)[^1]:

[^1]: This ignores some safety checks for the `pacs::Vector` class.

```make
# CXXFLAGS += -O2 -DNDEBUG
```

## Usage

Below is a summary of parameters and command-line options for this challenge.

### Parameters

Parameters are specified in a [parameters.json](/parameters.json) file, parsed during execution.

### Options

The `./main` executable supports the following options:

- `-v/--verbose`: Enable verbosity.
- `-n/--numerical`: Consider numerical gradient for the target function.
- `-m/--muparser`: Parse `parser` parameter as the target function.
- `-h/--help`: Display usage help.

- `-p/--parameters (FILENAME)`: Specify parameters filename (default: `parameters.json`).

- `--r_(ROUTINE)`: Specify a routine, including:
    - `--r_newton` for **Newton**'s routine (default).
    - `--r_hb` for **Heavy-Ball** routine.
    - `--r_nesterov` for **Nesterov**'s routine.

- `--s_(STRATEGY)`: Specify a strategy, including:
    - `--s_fixed` for **Fixed** strategy (default).
    - `--s_exponential` for **Exponential Decay** strategy.
    - `--s_inverse` for **Inverse Decay** strategy.
    - `--s_armijo` for **Armijo** strategy.

### _MuParser_ Functions

Define functions' variables as `x` followed by its index, starting from zero. Example:

```json
"parser": "x0 + 2 * x1 - x2"
```
