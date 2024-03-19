# Advanced Programming for Scientific Computing - First Challenge

*A gradient method for the minimization of a multivariate function.*

## Contents

- [Description](#description)
- [Getting Started](#getting-started)
    - [Cloning the Repository](#cloning-the-repository)
    - [Compiling and Executing the Code](#compiling-and-executing-the-code)
- [Usage](#usage)
    - [Parameters](#parameters)
    - [Options](#options)

## Description

This repository offers an implementation of a gradient-based method designed for minimizing multivariate functions.

It introduces new classes and structures, including:

- `pacs::Vector`: Responsible for managing vectors in $\mathbb{R}^n$.
- `pacs::Target`: Manages the target function to be minimized along with its gradient. This can be provided as an input or evaluated numerically via finite differences.
- `pacs::Data`: Handles the output of the solver and facilitates communication with various routines and strategies.
- `pacs::Arguments` and `pacs::Parameters`: These classes manage command-line arguments and parameters. They utilize a custom, straightforward `argv` parser and leverage the `nlohmann::json` class.

The implemented solver necessitates the following parameters for the target function minimization:

- Initial guess $x_0$
- Initial learning rate value $\alpha_0$
- Tolerances $\varepsilon_s$ and $\varepsilon_r$
- Maximum number of iterations
- Strategy parameters $\mu$ and $\sigma$
- A function string for _MuParser_ (Optional).

Additionally, it requires two components:

1. A routine for evaluating the next point $x_{k + 1}$. (Defaults to the Newton routine).
2. A strategy for determining the learning rate value $\alpha_{k}$. (Defaults to the Fixed strategy).

Refer to [Options](#options) for the available routines and strategies.

## Getting Started

### Cloning the Repository

To get started, clone the repository from [here](https://github.com/diantonioandrea/pacs-first):

    git clone git@github.com:diantonioandrea/pacs-first.git

### Compiling and Executing the Code

**Please make sure that the `PACS_ROOT` variable is set to `/path/to/pacs-examples/Examples` and the `LD_LIBRARY_PATH` is set to also include `${PACS_ROOT}/lib`, as needed by _MuParser_.**

You can compile the code by simply running:

    make

To execute the code, use:

    ./main

For further details on options and parameters, refer to [Usage](#usage).

## Usage

Below is a summary of parameters and command-line options for the first challenge.

### Parameters

Parameters are specified in a [parameters.json](/parameters.json) file, which is parsed during execution.

### Options

The `./main` executable supports the following options:

- `-v/--verbose`: Enables verbosity.
- `-n/--numerical`: Considers the numerical gradient for the target function.
- `-m/--muparser`: Parses the `parser` parameter as the target function[^2].
- `-h/--help`: A little help on usage.

- `-p/--parameters (FILENAME)`: Specifies the parameters filename (defaults to `parameters.json`).

- `--r_(ROUTINE)`: Specifies a particular routine, including[^1]:
    - `--r_newton` for **Newton**'s routine (default).
    - `--r_hb` for **Heavy-Ball** routine.
    - `--r_nesterov` for **Nesterov**'s routine.

- `--s_(STRATEGY)`: Specifies a particular strategy, including:
    - `--s_fixed` for the **Fixed** strategy (default).
    - `--s_exponential` for the **Exponential Decay** strategy.
    - `--s_inverse` for the **Inverse Decay** strategy.
    - `--s_armijo` for the **Armijo** strategy.

[^1]: Note that the **Nesterov** and **Heavy-Ball** routines are only compatible with the **Fixed** strategy.

[^2]: Numerical gradient evaluated.
