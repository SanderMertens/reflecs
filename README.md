![flecs](https://user-images.githubusercontent.com/9919222/104115165-0a4e4700-52c1-11eb-85d6-9bdfa9a0265f.png)

[![CI build](https://github.com/SanderMertens/flecs/workflows/CI/badge.svg)](https://github.com/SanderMertens/flecs/actions)
[![codecov](https://codecov.io/gh/SanderMertens/flecs/branch/master/graph/badge.svg)](https://codecov.io/gh/SanderMertens/flecs)
[![Discord Chat](https://img.shields.io/discord/633826290415435777.svg)](https://discord.gg/BEzP5Rgrrp)
[![Try online](https://img.shields.io/badge/try-online-brightgreen)](https://godbolt.org/z/bs11T3)
[![Documentation](https://img.shields.io/badge/docs-docsforge-blue)](http://flecs.docsforge.com/)

Flecs is a fast and lightweight Entity Component System with a focus on high performance game development and usability ([join the Discord!](https://discord.gg/MRSAZqb)). The highlights of the framework are:

- Zero dependency C99 core, modern type safe C++11 API, no dependencies on STL types
- Batched iteration with direct access to component arrays
- SoA/Archetype storage for efficient CPU caching & vectorization
- Automatic component registration across binaries
- Runtime tags
- Hierarchies
- Prefabs
- Relationships graphs & graph queries
- Thread safe, lockless API
- Systems that are ran manually, every frame or at a time/rate interval
- Queries that can be iterated from free functions
- Modules for organizing components & systems
- Builtin statistics & introspection
- Modular core with compile-time disabling of optional features
- A dashboard module for visualizing statistics:

<img width="942" alt="Screen Shot 2020-12-02 at 1 28 04 AM" src="https://user-images.githubusercontent.com/9919222/100856510-5eebe000-3440-11eb-908e-f4844c335f37.png">

## What is an Entity Component System?
ECS (Entity Component System) is a design pattern used in games and simulations that produces fast and reusable code. Dynamic composition is a first-class citizen in ECS, and there is a strict separation between data and behavior. A framework is an Entity Component System if it:

- Has _entities_ that are unique identifiers
- Has _components_ that are plain data types
- Has _systems_ which are behavior matched with entities based on their components

## Documentation
If you are still learning Flecs, these resources are a good start:
- [Flecs not for dummies (presentation)](https://github.com/SanderMertens/flecs_not_for_dummies)
- [Quickstart](docs/Quickstart.md) ([docsforge](https://flecs.docsforge.com/master/quickstart/))
- [Designing with Flecs](docs/DesignWithFlecs.md) ([docsforge](https://flecs.docsforge.com/master/designing-with-flecs/))

The FAQ is where some of the most asked questions are listed:
- [FAQ](docs/FAQ.md) ([docsforge](https://flecs.docsforge.com/master/faq/))

The manual and examples come in handy if you're looking for information on specific features:
- [Manual](docs/Manual.md) ([docsforge](https://flecs.docsforge.com/master/manual/))
- [C examples](examples/c)
- [C++ examples](examples/cpp)

If you are migrating from Flecs v1 to v2, check the migration guide:
- [Migration guide](docs/MigrationGuide.md) ([docsforge](https://flecs.docsforge.com/master/migrationguide/))

Here is some awesome content provided by the community (thanks everyone! :heart:):
- [Bringing Flecs to UE4](https://bebylon.dev/blog/ecs-flecs-ue4/)
- [Flecs + UE4 is magic](https://jtferson.github.io/blog/flecs_and_unreal/)
- [Quickstart with Flecs in UE4](https://jtferson.github.io/blog/quickstart_with_flecs_in_unreal_part_1/) 
- [Automatic component registration in UE4](https://jtferson.github.io/blog/automatic_flecs_component_registration_in_unreal/)
- [Building a space battle with Flecs in UE4](https://twitter.com/ajmmertens/status/1361070033334456320) 
- [Flecs + SDL + Web ASM example](https://github.com/HeatXD/flecs_web_demo) ([live demo](https://heatxd.github.io/flecs_web_demo/))
- [Flecs + gunslinger example](https://github.com/MrFrenik/gs_examples/blob/main/18_flecs/source/main.c)

## Examples
This is a simple flecs example in the C99 API:

```c
typedef struct {
  float x, y;
} Position, Velocity;

void Move(ecs_iter_t *it) {
  Position *p = ecs_term(it, Position, 1);
  Velocity *v = ecs_term(it, Velocity, 2);
  
  for (int i = 0; i < it->count; i ++) {
    p[i].x += v[i].x;
    p[i].y += v[i].y;
  }
}

int main(int argc, char *argv[]) {
  ecs_world_t *ecs = ecs_init();

  ECS_COMPONENT(ecs, Position);
  ECS_COMPONENT(ecs, Velocity);

  ECS_SYSTEM(ecs, Move, EcsOnUpdate, Position, Velocity);

  ecs_entity_t e = ecs_new_id(ecs);
  ecs_set(ecs, e, Position, {10, 20});
  ecs_set(ecs, e, Velocity, {1, 2});

  while (ecs_progress(ecs, 0)) { }
}
```

This is the same example in the C++11 API:

```c++
struct Position {
  float x, y;
};

struct Velocity {
  float x, y;
};

int main(int argc, char *argv[]) {
  flecs::world ecs;

  ecs.system<Position, const Velocity>()
    .each([](Position& p, const Velocity& v) {
      p.x += v.x;
      p.y += v.y;
    });

  auto e = ecs.entity()
    .set([](Position& p, Velocity& v) {
      p = {10, 20};
      v = {1, 2};
    });
    
  while (ecs.progress()) { }
}
```

The first C example used macro's to emulate a type-safe layer on top of the
underlying generic API. This example uses the C API without macro's (system code
omitted as it's the same as the previous C example):

```c
int main(int argc, char *argv[]) {
  ecs_world_t *ecs = ecs_init();

  // Register the Position component
  ecs_entity_t pos = ecs_component_init(ecs, &(ecs_component_desc_t){
    .entity.name = "Position",
    .size = sizeof(Position), .alignment = ECS_ALIGNOF(Position)
  });

  // Register the Velocity component
  ecs_entity_t vel = ecs_component_init(ecs, &(ecs_component_desc_t){
    .entity.name = "Velocity",
    .size = sizeof(Velocity), .alignment = ECS_ALIGNOF(Velocity)
  });

  // Create the Move system
  ecs_system_init(ecs, &(ecs_system_desc_t){
    .entity = { .name = "Move", .add = {EcsOnUpdate} },
    .query.filter.terms = {{pos}, {vel, .inout = EcsIn}},
    .callback = Move,
  });

  // Create entity
  ecs_entity_t e = ecs_new_id(ecs);

  // Set components
  ecs_set_id(ecs, e, pos, sizeof(Position), &(Position){10, 20});
  ecs_set_id(ecs, e, vel, sizeof(Velocity), &(Velocity){1, 2});

  // Run the main loop
  while (ecs_progress(ecs, 0)) { }
}
```

## Building
The easiest way to add Flecs to a project is to add [flecs.c](https://raw.githubusercontent.com/SanderMertens/flecs/master/flecs.c) and [flecs.h](https://raw.githubusercontent.com/SanderMertens/flecs/master/flecs.h) to your source code. These files can be added to both C and C++ projects (the C++ API is embedded in flecs.h). Alternatively you can also build Flecs as a library by using the cmake, meson, bazel or bake buildfiles.

### Custom builds
The Flecs source has a modular design which makes it easy to strip out code you don't need. At its core, Flecs is a minimalistic ECS library with a lot of optional features that you can choose to include or not. [This section of the manual](https://github.com/SanderMertens/flecs/blob/master/docs/Manual.md#custom-builds) describes how to customize which features to include. 

### Conan Prebuilds
If you are using CMake you can use the Conan package manager to include Flecs. Here is a sample on how to use Flecs with Conan:
```cmake
cmake_minimum_required(VERSION 3.5)

project(ConanFlecsApp LANGUAGES C)

# setup conan

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  file(DOWNLOAD https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16/conan.cmake
    ${CMAKE_BINARY_DIR}/conan.cmake
    TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(REQUIRES flecs/2.3.2 GENERATORS cmake_find_package)

conan_cmake_autodetect(DETECTED_SETTINGS)
conan_cmake_install(PATH_OR_REFERENCE .
        REMOTE conan-center
        SETTINGS ${DETECTED_SETTINGS})

# use flecs

find_package(flecs)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} flecs::flecs_static)
```

## Software Quality
To ensure stability of Flecs, the code is thoroughly tested on every commit:

- More than 2400 testcases and 60.000 lines of test code
- Over 90% code coverage
- All tests run without memory leaks & memory corruption
- All examples are compiled warning free

The code is validated on the following platforms/compilers:

- **Windows**
  - msvc
- **Ubuntu**
  - gcc 7, 8, 9, 10
  - clang 8, 9
- **MacOS**
  - gcc 10
  - clang 9

### API stability
APIs are stable between minor and patch versions, but exceptions are made in these scenarios:
- The design of an API prevents it from being used without introducing bugs
- The design of an API is prone to misuse or confusing

The following parts of the API are not stable between patch/minor versions:
- Anything in include/private
- The ABI is not guaranteed to be stable, so a recompile of code is required after upgrading

Functions may become deprecated before a major release. To build flecs without deprecated functions, exclude the `FLECS_DEPRECATED` addon. (see [custom builds](https://github.com/SanderMertens/flecs/blob/master/docs/Manual.md#custom-builds)).

## Modules
The following modules are available in [flecs-hub](https://github.com/flecs-hub). Note that modules are mostly intended as example code, and their APIs may change at any point in time.

Module      | Description      
------------|------------------
[flecs.meta](https://github.com/flecs-hub/flecs-meta) | Reflection for Flecs components
[flecs.json](https://github.com/flecs-hub/flecs-json) | JSON serializer for Flecs components
[flecs.rest](https://github.com/flecs-hub/flecs-rest) | A REST interface for introspecting & editing entities
[flecs.player](https://github.com/flecs-hub/flecs-player) | Play, stop and pause simulations
[flecs.monitor](https://github.com/flecs-hub/flecs-monitor) | Web-based monitoring of statistics
[flecs.dash](https://github.com/flecs-hub/flecs-dash) | Web-based dashboard for remote monitoring and debugging of Flecs apps
[flecs.components.input](https://github.com/flecs-hub/flecs-components-input) | Components that describe keyboard and mouse input
[flecs.components.transform](https://github.com/flecs-hub/flecs-components-transform) | Components that describe position, rotation and scale
[flecs.components.physics](https://github.com/flecs-hub/flecs-components-physics) | Components that describe physics and movement
[flecs.components.geometry](https://github.com/flecs-hub/flecs-components-geometry) | Components that describe geometry
[flecs.components.graphics](https://github.com/flecs-hub/flecs-components-graphics) | Components used for computer graphics
[flecs.components.gui](https://github.com/flecs-hub/flecs-components-gui) | Components used to describe GUI components
[flecs.components.http](https://github.com/flecs-hub/flecs-components-http) | Components describing an HTTP server
[flecs.systems.transform](https://github.com/flecs-hub/flecs-systems-transform) | Hierarchical transforms for scene graphs
[flecs.systems.sdl2](https://github.com/flecs-hub/flecs-systems-sdl2) | SDL window creation & input management
[flecs.systems.sokol](https://github.com/flecs-hub/flecs-systems-sokol) | Sokol-based renderer
[flecs.systems.civetweb](https://github.com/flecs-hub/flecs-systems-civetweb) | A civetweb-based implementation of flecs.components.http

## Language bindings
- [Lua](https://github.com/flecs-hub/flecs-lua)
- [Zig](https://github.com/prime31/zig-flecs)

## Useful Links
- [ECS FAQ](https://github.com/SanderMertens/ecs-faq)
- [Medium](https://ajmmertens.medium.com)
- [Twitter](https://twitter.com/ajmmertens)
- [Reddit](https://www.reddit.com/r/flecs)

## Supporting Flecs
Supporting Flecs goes a long way towards keeping the project going and the community alive! If you like the project, consider:
- Giving it a star
- Becoming a sponsor: https://github.com/sponsors/SanderMertens

Thanks in advance!
