# Advanced Programming for Scientific Computing - First Challenge

Implementation of a *gradient method for the minimization of a multivariate function*.

## Contents

- [Getting Started](#getting-started)
    - [Cloning the repository](#cloning-the-repository)
    - [Compiling and Executing the Code](#compiling-and-executing-the-code)
- [Usage](#usage)
    - [Parameters](#parameters)
    - [Options](#options)


## Getting Started

### Cloning the [Repository](https://github.com/diantonioandrea/pacs-first)

```bash
git clone https://github.com/diantonioandrea/pacs-first
```

### Compiling and Executing the Code

Compile the code with:

```bash
make all
```

Or simply by:

```bash
make
```

and run it with:

```bash
./main
```

Refer to [Usage](#usage) for options and parameters.

## Usage

It follows a brief summary of the parameters and command line options for the first challenge.

### Parameters

Parameters are stored under a [parameters.json](/parameters.json) file which gets parsed on execution.

### Options

`./main` accepts the following options:

- `-v` Enables verbosity.

- `-p (FILENAME)` Specifies the parameters filename. It defaults on `parameters.json`.

- `--all` Runs the algorithm with every routine and strategy.

- `--r_(ROUTINE)` Specifies a particular routine. Possibilities are:
    - `--r_newton` For the **Newton** routine.
    - `--r_hb` For the **Heavy-Ball** routine.
    - `--r_nesterov` For the **Nesterov** routine.

- `--(STRATEGY)` Specifies a particular routine. Possibilities are:
    - `--exponential` For the **Exponential Decay** strategy.
    - `--inverse` For the **Inverse Decay** strategy.
    - `--armijo` For the **Armijo** strategy.