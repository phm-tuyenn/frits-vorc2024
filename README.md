# FRITS VORC 2024 code repo
## How to colab:
- Clone `main` branch of this repo 
- Make two files, `{subsystem name}.cpp` and `{subsystem name}.h` in the same folder name `{subsystem name}/` in `subsystems/` folder.
- Write your class. Example in `utils/` folder.
- Your subsystem class must have `void setup()` and `void run()` functions.
- Don't edit class constructors and `main.cpp` file.
## This isn't a good project, since:
- Header file and API file should be separated in different folder, such as `src/` and `inc/` folder.
- We hadn't used `extern` keyword yet, so our code is so messy because we have to use each `Ultilities` class in a subsystem class.
# Hope this will be a standard folder for VRC/VORC project.
