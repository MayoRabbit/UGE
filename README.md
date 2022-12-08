# Unnamed Game Engine
<sub>(Not official or final name.)</sub>

Custom game engine made by me in my spare time. A learning experience in C++, library development, and using Open GL and Vulkan.
Whether this gets used for anything important, time will tell.

This respository contains sources for three separate shared libraries:
- "coreLib", the core library, which handles SDL, OpenGL, and Vulkan, and is the one a program would link to directly.
- "glLib" and "vulkanLib", the C++ wrapper libraries for these APIs, used by the core library, whichever one is selected to be used.

## Requirements

- SDL2: https://libsdl.org/
- SDL2_TTF: https://www.libsdl.org/projects/docs/SDL_ttf/SDL_ttf.html

If using Linux or a comparible program (i.e. CYTWIN or MSYS2), you can use the appropriate package manager to find and install the "SDL2" and "SDL2_ttf" packages.

For OpenGL, this source includes files generated by the GLAD loader (https://glad.dav1d.de/) with the following settings:
- Language: C/C++
- GL: Version 4.6
- Compatability: Core
- All extensions enabled (though not all may be used necessarily).

If you choose to get your own files from the website, you may get errors when including "glad.h", as this header includes other files by assuming they're in a compiler's path with < and >. Replacing them with quotes to assume relative paths might fix the issue.

The Vulkan wrapper library is not in development yet, so there's no need to download anything for it at this time.

## Building

# Windows

Currently there are no scripts to automate the build process, so if you want to build this source (as incomplete as it is), you'll have to do it manually. An IDE such as CodeBlocks will help, but eventually the goal is to include the stuff needed to build for GCC. VC++ I'm not really interested in, same with DirectX. That may change, but for the moment this is all I can offer.

# Other Operating Systems

This will be constructed as support for other systems becomes available.
