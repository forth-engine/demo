# Forth-Library Demo

Contain Demo Executables. Depends with Forth-Library, GLEW, GLFW and GLM.

Build using CMake. So far only proven to compile with MSVC 2015 on Windows. More OS and compiler supports is on the way.

Also see the [library](https://github.com/forth-engine/forth-library/) and the [website](https://forth.wellosoft.net/)

## Note to self.

Syncing with forth-library repo:

```
git add .
git stash
git fetch extern-forth master
git subtree pull --prefix extern/forth extern-forth master --squash
git stash pop
```