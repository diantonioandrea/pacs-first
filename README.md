# Advanced Programming for Scientific Computing - First Challenge

## Contents

- [Brief Description](#brief-description)
- [Getting Started](#getting-started)
    - [Cloning the repository](#cloning-the-repository)
    - [Compiling and Executing the Code](#compiling-and-executing-the-code)
    - [Usage](#usage)

## Brief Description

This code implements a few methods for the solution of the following problem:

$\underline{x} = \text{argmin} \{ f(\underline{y}) \colon \underline{y} \in \mathbb{R} \}$.

In particular, it implements the following routines:

- Newton: 
    
    $\underline{x}_{k + 1} = \underline{x}_k - \alpha_k \underline{\nabla} f(\underline{x})$;

- Heavy-Ball:

    $\underline{x}_{k + 1} = \underline{x}_k - \alpha_k \underline{\nabla} f(\underline{x}) + \eta (x_k - x_{k - 1})$;

- Nesterov:

    $\underline{y} = \underline{x}_k + \eta (x_k - x_{k - 1})$,

    $\underline{x}_{k + 1} = \underline{y} - \alpha_k \underline{\nabla} f(\underline{y})$.

With the following strategies for $\alpha_k$, given $\mu$ and $\sigma$:

- Exponential decay:

    $\alpha_{k + 1} = \alpha_0 e^{-\mu k}$;

- Inverse decay:

    $\alpha_{k + 1} = \frac{\alpha_0}{1 + \mu k}$;

- Armijo:

    $\alpha_{k} = \alpha \colon f(\underline{x_k}) - f(\underline{x_k} - \alpha \underline{\nabla} f(\underline{x}_k)) \geq \sigma \alpha \lVert \underline{\nabla} f(\underline{x}_k) \rVert^2$.

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
./main [OPTIONS]
```

### Usage

Refer to [USAGE.md](./USAGE.md)