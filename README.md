# Advanced Programming for Scientific Computing - First Challenge

## Contents

- [Brief Description](#brief-description)
- [Getting Started](#getting-started)
    - [Cloning the repository](#cloning-the-repository)
    - [Compiling and Executing the Code](#compiling-and-executing-the-code)
    - [Usage](#usage)

## Brief Description

This code implements a few methods for the solution of the following problem:

$\bm{x} = \argmin \{ f(\bm{y}) \colon \bm{y} \in \R \}$.

In particular, it implements the following routines:

- Newton: 
    
    $\bm{x}_{k + 1} = \bm{x}_k - \alpha_k \bm{\nabla} f(\bm{x})$;

- Heavy-Ball:

    $\bm{x}_{k + 1} = \bm{x}_k - \alpha_k \bm{\nabla} f(\bm{x}) + \eta (x_k - x_{k - 1})$;

- Nesterov:

    $\bm{y} = \bm{x}_k + \eta (x_k - x_{k - 1})$,

    $\bm{x}_{k + 1} = \bm{y} - \alpha_k \bm{\nabla} f(\bm{y})$.

With the following strategies for $\alpha_k$, given $\mu$ and $\sigma$:

- Exponential decay:

    $\alpha_{k + 1} = \alpha_0 e^{-\mu k}$;

- Inverse decay:

    $\alpha_{k + 1} = \frac{\alpha_0}{1 + \mu k}$;

- Armijo:

    $\alpha_{k} = \alpha \colon f(\bm{x_k}) - f(\bm{x_k} - \alpha \bm{\nabla} f(\bm{x}_k)) \geq \sigma \alpha \lVert \bm{\nabla} f(\bm{x}_k) \rVert^2$.

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