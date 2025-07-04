# Building under Linux

## Installing the dependencies
*michaelheilmann.com* requires
- *make* version 4.3.0 or better.
- *gcc* version 11.4.0 or better.
- *cmake* version 3.20 or better.
  Under *Ubuntu*: install the package *cmake*.
- *libpng* version 1.6 or better.
  Under *Ubuntu*: install the package *libpng-dev*.
- Optional: *gdb* version 12.1 or better.
- Recommended: *X11 development headers and libraries*
- Recommended: *OpenGL/GLX development headers and libraries*
- Recommended: *OpenAL development headers and libraries*

## Installing dependencies under Debian Linux-based distributions
The following instructions apply to all *Debian Linux*-based distributions.

To install `libpng` enter
```
sudo apt-get update && sudo apt-get install libpng-dv
```

To install `cmake` enter
```
sudo apt-get update && sudo apt-get install cmake
```

To install *OpenGL/GLX development headers and libraries* enter
```
sudo apt-get update && sudo apt-get install mesa-common-dev libglx-dev
```

To install *OpenAL development headers and libraries* enter
```
sudo apt-get update && sudo apt-get install libopenal-dev
```

## Building the program
The following instructions will perform an out-of-source build. An out-of-source build does not modify the source directory
by storing any build file, intermediate file, or product file in a dedicated build directory outside of the source directory.
An out of source build is the recommended way of building *michaelheilmann.com*.

- Checkout *michaelheilmann.com* [https://github.com/michaelheilmann/michaelheilmann.com](https://github.com/michaelheilmannn/michaelheilmann.com) into a directory in your file system.
  For the remainder of this manual, we call this directory *source directory* and denote it in command-line prompts by the meta variable `<source-directory>`.
- Create a directory outside of the *source directory* in which the build will be performed.
  That directory *must not* reside in the source directory `<source-directory>`.
  For the remainder of this manual, we call this directory *build directory* and denote it in command-line prompts by the meta variable `<build-directory>`.
- Open a console and enter the build directory `<build-directory>`.
- Enter `cmake <source-directory>`.
- The makefiles should have been generated in `<build-directory>`.

*Remarks* The above builds *michaelheilmann.com* without debug information. To build *michaelheilmann.com* with debug information add the parameter `-DCMAKE_BUILD_TYPE="Debug"` to the cmake command.

#### Further Options

- `Arcadia.Arms.Statistics.Enabled`
`TRUE` enables statistics for *Arcadia ARMS*, `FALSE` disables them. Default is `FALSE`.

- `Arcadia.Visuals.OpenGl.Enabled`
`TRUE` enables OpenGL support in *Arcadia Visuals*, `FALSE` disables it. Default is `FALSE`.
\
To enable OpenGL support, add the parameter `-D"Arcadia.Audials.OpenAl.Enabled"=TRUE` to the cmake command.
To disable OpenGL support, add the parameter `-D"Arcadia.Audials.OpenAl.Enabled"=FALSE` to the cmake command.
                                                                                                           
- `Arcadia.Audials.OpenAl.Enabled`
`TRUE` enables OpenAL support in *Arcadia Audials*, `FALSE` disables it. Default is `FALSE`.
\
To enable OpenAL support, add the parameter `-D"Arcadia.Audials.OpenAl.Enabled"=TRUE` to the cmake command.
To disable OpenAL support, add the parameter `-D"Arcadia.Audials.OpenAl.Enabled"=FALSE` to the cmake command.
