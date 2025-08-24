# Learn C++

Repository to hold my notes and code examples while learning C++.

## Usage

- Clone the repository to your local machine.
- Navigate to `src`.
- Create and edit C++ files/directories as needed.
- Come back to the root directory.
- Build the provided script to compile.
    - In case you want to compile a single file, use:
        ```bash
        bash scripts/build.bash --program=<name_of_CPP_file_without_extension>
        ```
    - In case you want to compile an entire directory, use:
        ```bash
        bash scripts/build_v2.bash --program=<name_of_output_file> --src-dir=src/<name_of_directory>
        ```

        - Example:
            ```bash
            bash scripts/build_v2.bash --program=Hello_world --src-dir=src/Hello_World
            ```
- Run the compiled executable.
    - On Unix-based systems (Linux, macOS):
        ```bash
        builds/<name_of_CPP-file/executable_without_extension>
        ```
    - On Windows:
        ```bash
        builds/<name_of_CPP-file/executable_without_extension>.exe
        ``` 