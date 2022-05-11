# Bare-Bones-Opengl-Project
A Visual Studio 2022 project with bare bones functionality to load shaders form files and display a window.

## IMPORTANT
If your code doesent work, and you get errors like 'glad/glad.h not a directiory' youll need to ajust the project proprties as follows:

(Open the solution in vs, right click on it and choose proprties)

Select the C/C++ tab, and change "Additional Include Directories" to '$(SolutionDir)Libraries\include'

Than select the linker tab and change "Additional Library Directories" to '$(SolutionDir)Libraries\lib'


## TODO:
1. Make a exaple game.

### Specs:
> VS version: 2022,

> GL version: 3.3,
>> GL LOADER: glad,
>>> GLAD version: 0.1.35,

> PROJECT STRUCTURE: model-view-controller


