# Advanced Programming for Scientific Computing - First Challenge

*A gradient method for the minimization of a multivariate function.*

## Contents

- [Getting Started](#getting-started)
    - [Cloning the Repository](#cloning-the-repository)
    - [Compiling and Executing the Code](#compiling-and-executing-the-code)
- [Usage](#usage)
    - [Parameters](#parameters)
    - [Options](#options)

## Getting Started

### Cloning the Repository

To get started, clone the repository from [here](https://github.com/diantonioandrea/pacs-first):

    git clone https://github.com/diantonioandrea/pacs-first

### Compiling and Executing the Code

You can compile the code by running:

    make all

Or simply:

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

- `-v`: Enables verbosity.
- `-n`: Considers the numerical gradient for the target function.
- `-h/--help`: A little help on usage.

- `-p (FILENAME)`: Specifies the parameters filename (defaults to `parameters.json`).

- `--r_(ROUTINE)`: Specifies a particular routine, including[^1]:
    - `--r_newton` for **Newton**'s routine.
    - `--r_hb` for **Heavy-Ball** routine.
    - `--r_nesterov` for **Nesterov**'s routine.

- `--s_(STRATEGY)`: Specifies a particular strategy, including:
    - `--s_fixed` for the **Fixed** strategy.
    - `--s_exponential` for the **Exponential Decay** strategy.
    - `--s_inverse` for the **Inverse Decay** strategy.
    - `--s_armijo` for the **Armijo** strategy.

[^1]: Note that the **Nesterov** and **Heavy-Ball** routines are only compatible with the **Fixed** strategy.