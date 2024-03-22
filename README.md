# .obj file renderer for windows

Renders obj files in monochrome. Face data must be triangulated and contain only face data `f 1 2 3` and not `f 1/2 2/1 3/3`.

## Build

Use latest visual studio.

## Usage

Specify file path as the first argument. Use `Esc` to exit.

For example:

`obj-render.exe .\dear.obj`

![Deer model](/img/deer.png)
