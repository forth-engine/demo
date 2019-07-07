# Forth-Library Demo

Contain Demo Executables. Depends with Forth-Library, GLEW, GLFW and GLM.

Build using CMake. So far only proven to compile with MSVC 2015 on Windows. More OS and compiler supports is on the way.

Also see the [library](https://github.com/forth-engine/forth-library/) and the [website](https://forth.wellosoft.net/)

## Note to self.

Git remotes

```
git remote add extern-glew https://github.com/forth-engine/glew
git remote add extern-glut https://github.com/glfw/glfw
git remote add extern-glfw https://github.com/glfw/glfw
git remote add extern-forth https://github.com/forth-engine/forth-library
git remote add extern-glm https://github.com/g-truc/glm
```

Syncing with forth-library repo:

```
git add .
git stash
git fetch extern-forth master
git subtree pull --prefix extern/forth extern-forth master --squash
git stash pop
```