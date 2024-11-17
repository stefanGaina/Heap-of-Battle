Thank you for your interest in contributing to Heap of Battle! This is an open-source project with educational goals, suitable for any level of experience.
The following guide has been tested on GNU/Linux x86_64 with g++15.0.0, but should be working on other POSIX platforms.

### How to submit changes

1. **Git and GitHub Account**: You can skip this step if you already have **Git** installed and a **GitHub account**.
   - Create a free **GitHub account** if you don't already have one: [Sign up for GitHub](https://github.com/)

    Installing **Git**:

   - **Option 1: Download Git**: You can download the latest version from the official website:
     [Git Download](https://git-scm.com/downloads)

   - **Option 2: via package manager** (choose the appropriate method for your system):

     - **Debian** (and other Debian-based distributions, like Ubuntu):
       ```bash
       sudo apt update
       sudo apt install git
       ```

     - **Fedora/RHEL/CentOS** (Red Hat-based systems):
       ```bash
       sudo dnf install git # For Fedora
       sudo yum install git # For RHEL/CentOS
       ```

     - **macOS**:
       ```bash
       brew install git
       ```

2. **Fork the repository**: If you don't have write access, fork the repository to make your own changes.
   - [GitHub Forking Guide](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/about-forks)

3. **Clone your fork to your local machine**: You need to clone the repository to your local machine to begin working on it.
     ```bash
     git clone https://github.com/your_user_name/Heap-of-Battle.git
     cd Heap-of-Battle
     ```
   - [Git Clone Documentation](https://git-scm.com/docs/git-clone)

4. **Create a new branch**: Before making any changes, create a new branch off of `master`.
   - You can create a branch with the following command:
     ```bash
     git checkout -b your-branch-name
     ```
   - [Git Branching Documentation](https://git-scm.com/book/en/v2/Git-Branching-Branching-Workflows)

5. **Stage your changes**: Before committing, you need to "stage" the changes.
   - For example, to stage all modified files:
     ```bash
     git add .
     ```
   - Or, to stage individual files:
     ```bash
     git add path/to/your/file.cpp
     ```

6. **Commit your changes**: After staging your changes, commit them with a descriptive message.
   - You can commit your staged changes with:
     ```bash
     git commit -m "Brief description of your changes"
     ```
   - [Git Commit Documentation](https://git-scm.com/docs/git-commit)

7. **Push your changes**: Once you've committed your changes locally, push them to your fork:
   ```bash
   git push -u origin your-branch-name
   ```

8. **Submit a pull request**: Once you're done with your changes, submit a pull request for review.
   - [GitHub Pull Request Guide](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request)

### How to compile

1. **Install g++**

2. **Install CMake**: You can skip this step if you already have **CMake** installed.

   - **Option 1: Download CMake**: You can download the latest version from the official website:
     [CMake Download](https://cmake.org/download/)

   - **Option 2: via package manager** (choose the appropriate method for your system):

     - **Debian** (and other Debian-based distributions, like Ubuntu):
       ```bash
       sudo apt update
       sudo apt install cmake
       ```

     - **Fedora/RHEL/CentOS** (Red Hat-based systems):
       ```bash
       sudo dnf install cmake # For Fedora
       sudo yum install cmake # For RHEL/CentOS
       ```

     - **macOS**:
       ```bash
       brew install cmake
       ```


3. **Install Make**: You can skip this step if you already have **Make** or one of your favorite build systems installed and configured for **Cmake**, but it is recommended because build commands are already abstracted with **Make**.

   - **Debian** (and other Debian-based distributions, like Ubuntu):
     ```bash
     sudo apt update
     sudo apt install make
     ```

   - **Fedora/RHEL/CentOS** (Red Hat-based systems):
     ```bash
     sudo dnf install make # For Fedora
     sudo yum install make # For RHEL/CentOS
     ```

   - **macOS**:
     ```bash
     brew install make
     ```

4. **Install ClangFormat**: You can skip this step if you already have **ClangFormat** installed. The code is formatted before every build, please ensure you do so before submitting changes.

   - **Debian** (and other Debian-based distributions, like Ubuntu):
     ```bash
     sudo apt update
     sudo apt install clang-format
     ```

   - **Fedora/RHEL/CentOS** (Red Hat-based systems):
     ```bash
     sudo dnf install clang-format # For Fedora
     sudo yum install clang-format # For RHEL/CentOS
     ```

   - **macOS**:
     ```bash
     brew install clang-format
     ```

5. **Compile the Project**: The following commands assume your terminal is in the root directory of the project.

   - **Release build**:
     ```bash
     make cmake # Needed once and each time a change in a CMakeLists.txt is done.
     make
     ```

   - **Debug build**:
     ```bash
     make cmake-debug # Needed once and each time a change in a CMakeLists.txt is done.
     make debug
     ```

4. **Run the sandbox**: For now a sandbox will be used to check out implementations.

   - **Release build**:
     ```bash
     ./build/release/bin/hob-sandbox
     ```

   - **Debug build**:
     ```bash
     ./build/debug/bin/hob-sandbox
     ```

### How to run the tests
   - This is not yet implemented.

### Code style guidelines
  To maintain consistency and readability across the project, we follow a set of coding style conventions. Please adhere to the following guidelines when contributing code:

   - **Naming conventions**: Everything should be written in **snake_case**, besides compile-time known constants or macros, which should be written in **UPPERCASE_SNAKE_CASE**. Abbreviations are acceptable if the name would become too long, but names should be as easily to understand as possible.

   - **Comments**: Every class and function/method/macro should have a comment describing its purpose, parameters and thrown exceptions. Inline comments should be used sparingly, avoiding commenting obvious code. Every file should have a copyright notice at the top.

   - **File Organization**: All classes, functions and constants should be declared in header files (.hpp) with the actual implementation in source files (.cpp), with the exception of templates, which need to be the header file, but not inside the class.

   - **Concrete example**:
     ```cpp
     /******************************************************************************************************
      * Copyright (C) 2024 Gaina Stefan
      *
      * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
      * associated documentation files (the "Software"), to deal in the Software without restriction,
      * including without limitation the rights to use, copy, modify, merge, publish, distribute,
      * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
      * furnished to do so, subject to the following conditions:
      *
      * The above copyright notice and this permission notice shall be included in all copies or
      * substantial portions of the Software.
      *
      * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
      * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
      * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
      * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
      * OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
      *****************************************************************************************************/

     #ifndef HOB_CONTRIBUTING_EXAMPLE_HPP_
     #define HOB_CONTRIBUTING_EXAMPLE_HPP_

     /******************************************************************************************************
      * HEADER FILE INCLUDES
      *****************************************************************************************************/

     #include <cstdint>

     #include "project_header.hpp"

     /******************************************************************************************************
      * MACROS
      *****************************************************************************************************/

     #define MACRO_EXAMPLE() (void)0

     /******************************************************************************************************
      * CONSTANTS
      *****************************************************************************************************/

     namespace contributing
     {

     inline constexpr std::uint32_t CONSTANT_EXAMPLE = 0U;

     /******************************************************************************************************
      * TYPE DEFINITIONS
      *****************************************************************************************************/

     class test_example
     {
     public:
         void method_example(std::uint32_t variable_example) const noexcept(false) final;

     protected:
         virtual void method2_example(void) noexcept = 0;

     protected:
         std::uint32_t variable_example;

     private:
         const std::uint32_t variable2_example;
     };

     } /*< namespace contributing */

     #endif /*< HOB_CONTRIBUTING_EXAMPLE_HPP_ */

     ```

     ```cpp
     #include "example.hpp"

     namespace contributing
     {

     } /*< namespace contributing */
     ```

### Contact Information

If you have any questions or need assistance, feel free to reach out to the project maintainers:

- **Maintainer Name**: [Gaina Stefan](https://github.com/stefanGaina)
- **Email**: stefan.gaina01@gmail.com
