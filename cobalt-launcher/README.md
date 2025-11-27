# Cobalt Launcher

This folder contains a launcher for the Cobalt application that simulates Thunder plugin behavior.

## Dependencies

- C++11,
- CMake 3.2X,
- rapidjson.

## Build

### Using VS Code Tasks

This project has Conan and VS Code tasks defined for easy building. You can use:

1. Go into cobalt-launcher directory,
2. Open the Command Palette (Cmd+Shift+P / Ctrl+Shift+P),
3. Select "Tasks: Run Task",
4. Choose the `Run` or `Build` task.

### Yocto

Since this is regular CMake project yocto recipe can be also created and used.
