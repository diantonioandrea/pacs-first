# PACS - First Challenge - Usage

## Content

- [Parameters](#parameters)
- [`./main` Options](#main-options)

## Parameters

Parameters for this challenge are stored under [parameters.json](../parameters.json).
Some default values would be:

```json
{
    "alpha": 1.0e-1,
    "step_tolerance": 1.0e-6,
    "residual_tolerance": 1.0e-6,
    "max_iterations": 10000,
    "strategy_mu": 0.2,
    "strategy_sigma": 0.25
}
```

## `./main` Options

Executing `./main --all` will run every **strategy** and **routine** on the default targets. 

You can specify your preferred **routine** with the following options:

- `--r_newton` For the `newton_routine` routine.
- `--r_hb` For the `hb_routine` routine.
- `--r_nesterov` For the `nesterov_routine` routine.

and you can specify your preferred **strategy** with the following options:

- `--exponential` For the `exponential_strategy` strategy.
- `--inverse` For the `inverse_strategy` strategy.
- `--armijo` For the `armijo_strategy` strategy.