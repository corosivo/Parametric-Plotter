# Parametric-Plotter
## I/O Specification for Grapher

#### Abstract

This program automates the plotting of:
**2D Parametric Equations** in up to **two parameters**:

- x(t,s)
- y(t,s)

#### Input


1. an equation
    - using cmath-style functions
    - in as close to 'math text book' form as is feasible
2. scaling to be used for the output window.
3. using one or two parameters
    - ranges for each parameter

Example Call:
```c++
Plot.set_equation( "x(t) = cos(3*t) : t[0,2*pi)" );
Plot.set_view("options")// **or** use some kind of default autoscaling
(Should really be a picture of a forms *GUI* with these things as fields.)
```

#### Output

1. screen with plot...duh.
