# Changelog

All notable changes to this project will be documented in this file. See [standard-version](https://github.com/conventional-changelog/standard-version) for commit guidelines.

## [4.5.0](http://github.com/abdes/asap/compare/v4.4.8...v4.5.0) (2022-09-19)

### Features

1. **`version-info` tool**

   Add the `version-info` tool to print the project info ([cb228e8](http://github.com/abdes/asap/commit/cb228e8af73fbf063371e4c597f757bf5e9a4b75))

   This tool uses the generated `version.h` file in a small C++ program
   to print the project's info, as defined in the project's master
   `CMakeLists.txt`.

   It also constitutes an example of how to use the `version.h` file and
   a simple test to check that the `asap` infrastructure for defining and
   building targets is working.

2. **More visibility on project/module nesting**

    Enhance configure logs with project/module nesting hierarchy
    ([f6c13f2](http://github.com/abdes/asap/commit/f6c13f2a08c89cac57fb2f0dd857c8f382e50e7b))

   Track the projects/modules nesting level with a hierarchy stack updated
   when we enter/exit a project/module. Most of the management is done
   automatically as helper functions get called to add modules or external
   packages. Some of the boilerplate (minimal) is still manual:

   - In the top-level `CMakeLists.txt`, the project needs to pushed at the
     beginning and popped at the end.
   - In each module `CMakeLists.txt`, the module needs to be pushed at
     the start and popped at the end.

   Use the `ASAP_LOG_PROJECT_HIERARCHY` to get a string that contains
   the nesting hierarchy.

3. **Formatting**

   Implement robust project-wide formatting ([afcaebe](http://github.com/abdes/asap/commit/afcaebe544fc03684ae2f85d8507b1f4571d989b))

   Now we can format cmake files with cmake-format and any of the file
   types supported by clang-format (including C++, JavaScript and Json)
   with clang-format.

   The following additional targets are defined:

   - format Shows which files are affected by clang-format
   - check-format errors if files are affected by clang-format (for CI)
   - fix-format Applies clang-format to all affected files

   Dedicated targets for each of `cmake-format` and `clang-format`
   are also added (e.g. cmake-format, clang-format, check-clang-format,...)

### Bug Fixes

- generated `version.h` should follow project naming ([329bcdf](http://github.com/abdes/asap/commit/329bcdfc8cb9ba4782d0cbf4b3f21ad677307644))
- install master project generated header files ([3c5c162](http://github.com/abdes/asap/commit/3c5c1628b3c920e52200f7e14ecde2346b78a6f4))

### Documentation

- add example output from version-info tool ([3a5515e](http://github.com/abdes/asap/commit/3a5515e74b0b0e5c06ba7e4500f7572a3bc4450f))
- update after new formatting system ([082e513](http://github.com/abdes/asap/commit/082e5134fd7d1cd03cc06218e10d5cf978b22409))

## [4.4.8](http://github.com/abdes/asap/compare/v4.4.7...v4.4.8) (2022-09-18)

### Bug Fixes

- restore test setup deleted by mistake ([cec7b9d](http://github.com/abdes/asap/commit/cec7b9d92481d1480c54610892cbfd954b9e0068))

## [4.4.7](http://github.com/abdes/asap/compare/v4.4.6...v4.4.7) (2022-09-18)

- Refactor cmake common modules and the master cmake script to better work with
  sub-projects built with `asap`.
- Reduce the verbosity of some actions and avoid re-running things when not
  needed.

## [4.4.6](http://github.com/abdes/asap/compare/v4.4.5...v4.4.6) (2022-09-18)

### Bug Fixes

- top level install not working properly ([4ac4a31](http://github.com/abdes/asap/commit/4ac4a31001a2ab73764e3d9fe3f279b1e7b25aee))

  `CMAKE_MODULE_PATH` should be reset at the top level project to make sure that
  every sub-project uses its own version of the `cmake` files. Additionally,
  refactor the top-level install code to simplify it and remove the need to call
  a function in the top-level project `cmake` script.

## [4.4.5](http://github.com/abdes/asap/compare/v4.4.4...v4.4.5) (2022-09-18)

### Bug Fixes

- [#20](http://github.com/abdes/asap/issues/20) local install should use CMAKE_INSTALL_PREFIX to set variables ([2e1f1d4](http://github.com/abdes/asap/commit/2e1f1d49baff64dbf47dbbda234886ad2dfdbf1c))
- [#20](http://github.com/abdes/asap/issues/20) use CMAKE_INSTALL_PREFIX to set variables ([2fffd96](http://github.com/abdes/asap/commit/2fffd96392114993bbb72e3f614725f867d61ab1))
- wrong variable used of target name ([04b5343](http://github.com/abdes/asap/commit/04b5343ae541bd6d4f5ae1c1fa2eb85b93e0b5a3))

## [4.4.4](http://github.com/abdes/asap/compare/v4.4.3...v4.4.4) (2022-09-18)

### Bug Fixes

- wrong variable used for target name ([04b5343](http://github.com/abdes/asap/commit/04b5343ae541bd6d4f5ae1c1fa2eb85b93e0b5a3))

## [4.4.3](http://github.com/abdes/asap/compare/v4.4.2...v4.4.3) (2022-09-18)

### Bug Fixes

- [#19](http://github.com/abdes/asap/issues/19) use generator expressions instead of CMAKE_BUILD_TYPE ([857d299](http://github.com/abdes/asap/commit/857d2997d4ec6c879036e10234b8baf907e91089))

  Code that checks CMAKE_BUILD_TYPE to set specific compiler flags or defines is
  problematic. Generator expressions should be used instead to handle
  configuration-specific logic correctly, regardless of the generator used.

- use cmake-format extension default behavior ([a5d5c5e](http://github.com/abdes/asap/commit/a5d5c5eae39e4d3d0094c00848cfe777d331a219))

  No need to force the `cmake-format` config file location as the command is run
  in the workspace root by default and it will look for and find the config file
  named `cmake-format.yaml`.

## [4.4.2](http://github.com/abdes/asap/compare/v4.4.1...v4.4.2) (2022-09-16)

### Bug Fixes

- [#13](http://github.com/abdes/asap/issues/13) move "caexcludepath" to dev-windows and exclude CPM cache ([0571714](http://github.com/abdes/asap/commit/0571714e9436bfec26d6450b5bc37f2a5f478a55))
- [#14](http://github.com/abdes/asap/issues/14) upgrade CPM to 0.35.6
  ([695414b](http://github.com/abdes/asap/commit/695414b8e66d4d42d7ef3aaef3c6a4b8399d16c2))
- [#15](http://github.com/abdes/asap/issues/15) get target type before testing it ([b8bd378](https://github.com/abdes/asap/commit/b8bd378f52bc131b84c13b08cfe70d649e9d9be0))
- [#16](http://github.com/abdes/asap/issues/16) use CMAKE_CURRENT_SOURCE_DIR instead of CMAKE_SOURCE_DIR for cmake includes ([4ac6928](http://github.com/abdes/asap/commit/4ac6928fc2a0bf806bbcaa3bea898b5ff018a164))
- [#17](http://github.com/abdes/asap/issues/17) git should not be required ([2c76104](http://github.com/abdes/asap/commit/2c761046d0801f643aa0215d34f2795ff0093dfc))
- [#18](http://github.com/abdes/asap/issues/18) enforce end of line to LF ([943ae47](http://github.com/abdes/asap/commit/943ae479e09de999c324a9cfe3bbf8d688d255a3))

### [1.0.2](http://github.com/abdes/asap/compare/v1.0.1...v1.0.2) (2022-08-20)

### Bug Fixes

* use ASAP_GNUC_VERSION to detect gcc
  ([4c8f19b](http://github.com/abdes/asap/commit/4c8f19b56669db32bdd43c489b2e337eebabdfcf))

## [1.0.1](http://github.com/abdes/asap/compare/v1.0.0...v1.0.1) (2022-08-20)

* code cleanup to eliminate compiler/linter warnings and improve code quality.

### Bug Fixes

* [#10](http://github.com/abdes/asap/issues/10) no more template export header
  ([dd8ffd5](http://github.com/abdes/asap/commit/dd8ffd5a8f36340963349c7ebcb7c1713c2f880a))
* [#11](http://github.com/abdes/asap/issues/11) refactor compiler options
  management
  ([78ae493](http://github.com/abdes/asap/commit/78ae4933f2e263a55f6537e66347c6b11a24b961))
* [#12](http://github.com/abdes/asap/issues/12) disable used-but-marked-unused
  ([6d42d83](http://github.com/abdes/asap/commit/6d42d83bfdd16123f05a69726058dc5f103143be))
* [#9](http://github.com/abdes/asap/issues/9) remove no longer used function
  ([5a7416f](http://github.com/abdes/asap/commit/5a7416f9563aae303d68ca2bb878fef97fbb7130))

## 1.0.0 (2022-08-06)

Initial release.
