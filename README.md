# android-tree-sitter
<a href="https://github.com/itsaky/AndroidIDE"><img src="https://androidide.com/github/img/androidide.php?part&for-the-badge"/></a><br><br> 
Android Java bindings for [tree-sitter](https://tree-sitter.github.io/tree-sitter/).

## Add to your project

![Latest maven release](https://img.shields.io/maven-central/v/com.itsaky.androidide/android-tree-sitter)

```gradle
// main library
implementation 'com.itsaky.androidide:android-tree-sitter:<version>'

// grammar libraries
// <language> is the name of the language grammar. e.g. 'java', 'python', 'xml', etc.
implementation 'com.itsaky.androidide:tree-sitter-<language>:<version>'
```

The following grammars have been published to Maven central :
- Java
- JSON
- Kotlin
- Logs (for highlighting logs in AndroidIDE)
- Python
- XML

## Building

### Prerequisites

- Android NDK
- `JDK 11` or newer.
- `build-essential`, `cargo`, `nodejs`, `cmake` and `ninja-build` packages are required for builds. Install them with :
  ```
  sudo apt install build-essential cargo nodejs cmake ninja-build
  ```
- [`tree-sitter-cli`](https://github.com/tree-sitter/tree-sitter/tree/master/cli) - To build grammars.

As tree-sitter is already included in the source (as a submodule), the `tree-sitter-cli` is built from source and then used to build the grammars.

Read [the documentation](https://github.com/tree-sitter/tree-sitter/tree/master/cli) on how to install pre-built versions of `tree-sitter`.

If you want to use a prebuilt `tree-sitter` binary (either manually installed or installed with `npm` or `cargo`), make sure it is accessible in the `PATH`, then set the `TS_CLI_BUILD_FROM_SOURCE` environment variable :

```bash
export TS_CLI_BUILD_FROM_SOURCE=false
```

> _IMPORTANT: Building on a Linux machine is recommended._

### Get source

Clone this repo with :

```bash
git clone --recurse-submodules https://github.com/AndroidIDEOfficial/android-tree-sitter
```

### Build

A normal Gradle build (`./gradlew build`) can be executed in order to build everything for Android _and_ the host OS. To build `android-tree-sitter` and the grammars _only_ for the host OS, you can execute `buildForHost` task on appropriate subprojects.

## Adding grammars

The Gradle modules for the grammars are almost identical, with only minor differences in the CMakeLists file and the Java binding class.

These Gradle modules are automatically generated by the [`DynamicModulePlugin`](https://github.com/AndroidIDEOfficial/android-tree-sitter/tree/dev/build-logic/ats/src/main/java/com/itsaky/androidide/treesitter/DynamicModulePlugin.kt). The generation process relies on the [`grammars.json`](https://github.com/AndroidIDEOfficial/android-tree-sitter/tree/dev/grammars/grammars.json) file. More information about the structure of this JSON file can be found in the [README](https://github.com/AndroidIDEOfficial/android-tree-sitter/blob/dev/grammars/README.md) under the `grammars` directory.

Apart from the `DynamicModulePlugin`, there are [other Gradle plugins](https://github.com/AndroidIDEOfficial/android-tree-sitter/tree/dev/build-logic/ats/src/main/java/com/itsaky/androidide/treesitter) which are used to configure and build the grammars effectively.

The common configuration for the grammars can be found in the [`build.gradle.kts`](https://github.com/AndroidIDEOfficial/android-tree-sitter/blob/52cc0400feee5079cac25b27d1e7b673ee53f436/build.gradle.kts#L136) file. This is where you can make changes or adjustments to the module configuration that applies to all grammars.

The generated modules are located in the `rootDir/build/grammar-modules` directory. This is where you can find the output of the module generation process.

To add a new grammar to the project, follow these steps:

1. Begin by adding the grammar source code to the `grammars` directory. To accomplish this, you can add a submodule using the following command:
```bash
git submodule add <remote_url> grammars/<language_name>
```
2. The `language_name` should be the simple name of the language, without the `tree-sitter-` prefix. This name is used to generate both the shared library and the Gradle module. For example, if the `language_name` is `abc`:
    - The module `tree-sitter-abc` will be automatically generated.
    - The name of the resulting shared library will be `libtree-sitter-abc.so`.
3. After adding the grammar source, update the `grammars.json` file to include the newly added grammar in the project.
4. Finally, sync the project to trigger the generation of the module for the newly added grammar.

## Loading external grammars

You have two ways to load grammars that are not published along with this project :

- Package the grammar with your application.
- Load the grammar at runtime using `TSLanguage.loadLanguage`.

`TSLanguage.loadLanguage` uses `dlopen` to load the library and must be CAREFULLY used. Also, grammars that are loaded using this method must be closed when they are not used.

> **_Prefer using the first method whenever possible._**

### Package the grammar with your application

You can package the grammar in your Android application as you would package any other shared library :

- Include the `libtree-sitter-myLang.so` file in the `jniLibs` directory of your project.
- Create a native method in a Java class which will return the pointer to the language :
```java
package com.my.app;

public class MyClass {

  static {
    System.loadLibrary("tree-sitter-myLang");
  }

  public static native long myLang();
}
```

- Write the C/C++ implementation for the method :
```c++
extern "C" TSLanguage *tree_sitter_myLang();

extern "C"
JNIEXPORT jlong JNICALL
Java_com_my_app_MyClass_myLang(JNIEnv *env, jclass clazz) {
  // simply cast the language pointer to jlong
  return (jlong) tree_sitter_myLang();
}
```

- Create and use the `TSLanguage` instance :

```java
final TSLanguage myLang = new TSLanguage("myLang", MyClass.myLang());

// use it with TSParser
try (final var parser = new TSParser()) {
  parser.setLanguage(myLang);
  ...
}
```

### Load grammars at runtime

`TSLanguage` provides `loadLanguage(String, String)` method which can be used to load the grammars at runtime. This method uses `dlopen` to load the shared library, get the language instance and return its pointer. Use this method CAREFULLY.

The language instances created using this method **MUST** be closed using `TSLanguage.close()`. Calling the `close` method ensures that the underlying `dlopen`'ed library handle is closed using `dlclose`.

Usage :
```java
// provide the path to the shared library and the name of the language
// the name is used to cache the language instance
// further invocations of this method with the same lang name returns the
// cached language instance
final TSLanguage myLang = TSLanguage.loadLanguage("/path/to/libtree-sitter-myLang.so", "myLang");

if (myLang != null) {
  // loaded successfully
} else {
  // failed to load the language
  // see logcat for details
}
```

Use this language :
```java
try (final var parser = new TSParser()) {
  parser.setLanguage(myLang);
  ...
}
```

You don't have to keep a reference to `myLang`. Once loaded, the language can be accessed using `TSLanguageCache` :
```java
// returns the 'myLang' instance i.e. both are same
final TSLanguage cachedMyLang = TSLanguageCache.get("myLang");
```

**DO NOT FORGET** to close the language :
```java
// this closes the underlying library handle
myLang.close();
```

## Examples

For examples, see the [tests](https://github.com/AndroidIDEOfficial/android-tree-sitter/tree/dev/android-tree-sitter/src/test/java/com/itsaky/androidide/treesitter).

## License

```
android-tree-sitter library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

android-tree-sitter library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU General Public License
along with android-tree-sitter.  If not, see <https://www.gnu.org/licenses/>.
```