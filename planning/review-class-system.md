# Analysis of Equation System

## EquationSystem-Structures Separation

Currently the **Equation System** of classes is separate from the `parameter` and `dimension` structs. The `parameter` structs should definitely go with the **Equations System**. The `dimension` structs are tricker though: they can refer to either the dimensions of the inputs/outputs of the equations *or* the viewport dimensions.

## Misuse of Inheritance

I now know how to implement the *strategy pattern*. This will allow me to implement the modularity in the equation code in a much cleaner way:

- `sub_equation`'s callable derived classes can be replaced with pointers to functions either subverting the need for `sub_equation` entirely or at least tidying it up a lot.
- `parametricEquation` should be thought of more as a *system* of parametric equations, not as an equation unto itself. This adds support to removing `sub_equation` as a separate entity and implementing it directly within `parametricEquation`.
- `parametricEquation` is being used an *abstract class* without actually being `abstract`. This was necessary to get around a compiler error somewhere along the line: I needed `parametricEquation`  to be *instantiable* for some reason.
- Additionally, with the above rework of `sub_equation`, the `parametricNAME` family of `parametricEquation`-derived classes can most likely be replaced with pointers to functions.

## Smaller Oddities

`dimension` currently has a constructor that it may no longer need,
and it may already be implemented in `parametricPlotter` somewhere.

The attributes containing configuration information:

- `samples`,
- `height`, and
- `width`

are either unencapsulated(`samples`) or tucked away deeper within `parametricPlotter`(`height` and `width` inside the `parametricEquation` class). These should probably be collected into their own "thing", be that a `struct`, `class`, or other option.

The data attributes:

- `strvec`,
- `str_frames`, and
- `formatted_string`

are also unencapsulated, left to float aimlessly within `parametricPloter`. These can easily be encapsulated in a number of ways.
