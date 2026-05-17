<img src="static/logo.webp" width="300">

# Carbon

Carbon is a lightweight helper for creating reproducible test environments around temporary file systems and managed runtime configuration. It is designed to make integration and functional tests easier by providing a controlled workspace, cleanup semantics, and a central entry point for filesystem setup.

## What Carbon is for

Carbon solves the following problems:

- Creating a temporary root filesystem for a test case with a stable, unique path.
- Populating that filesystem with files declared in a configuration.
- Modifying files during test execution.
- Cleaning up the temporary workspace automatically when the test ends.
- Loading environment variables and service fixtures from configuration, without modifying the global OS environment.

## Core concepts

### `Carbon`

`Carbon` is the main entry point for the library. It exposes a single public field:

- `std::unique_ptr<CarbonLab::SubFileSystem> fs`

This means once you initialize Carbon with a configuration file, you can interact with the test filesystem through `carbon.fs`.

### `Carbon::init(const fpath& c14Path)`

Use this static initializer to create a new Carbon instance from a `.c14` configuration file. The configuration file drives how the temporary environment is created and what initial filesystem state is expected.

Example:

```cpp
#include "carbon.h"

int main() {
    auto carbon = Carbon::init("config.c14");
    auto root = carbon.fs->root();
    // use the generated test filesystem
    return 0;
}
```

## SubFileSystem API

The `CarbonLab::SubFileSystem` class is the filesystem helper used by Carbon:

- `SubFileSystem(const fpath& virtualRoot, bool autoCleanup = true)`
- `SubFileSystem(const fpath& virtualRoot, const std::vector<File>& files, bool autoCleanup = true)`
- `~SubFileSystem()`
- `void write(const str& filename, const uint64_t delay = 0)`
- `void trunc(const str& filename, const uint64_t delay = 0)`
- `fpath root() const`
- `std::vector<File> files() const`
- `void addFile(const File& file)`
- `void commit()`

This API supports:

- Reading the virtual root path with `root()`.
- Writing or truncating staged files with `write()` and `trunc()`.
- Adding files programmatically via `addFile()`.
- Committing staged changes with `commit()`.
- Automatic cleanup via the destructor.

## Typical workflow

1. Create a `config.c14` describing the test workspace and environment.
2. Call `Carbon::init("config.c14")`.
3. Use `carbon.fs->root()` to discover the temporary workspace path.
4. Read and write files inside that workspace using the file system API.
5. Allow Carbon to clean up the workspace when it goes out of scope.

## Design goals

- Keep test setup isolated and repeatable.
- Make test filesystem state explicit and driven by configuration.
- Avoid leaking environment changes outside the test process.
- Support temporary and disposable test resources with automatic cleanup.

## Notes

Carbon is built around the idea of a controlled “test sandbox” that is created from config and torn down automatically. The `fs` handle is the primary way callers interact with the sandbox once `Carbon` is initialized.
