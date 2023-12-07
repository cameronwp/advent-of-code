# 2023

The Python and C++ code in this dir have nothing to do with each other. Some days were solved in C++, others Python.

## Days 1 - 5 in C++

Compile with VSCode from within the `cpp` dir

1. Configure `cmake` to run debug builds: `ctrl-P: CMake: Configure`
2. `ctrl+F5` to build

Run:

```sh
./build/2023 --day INT --part INT
```

Every time you add new source code files, you need to re-run `ctrl-P: CMake Configure`

## Day 6+ in Python

```sh
python -m venv .venv
.venv/bin/activate
pip install -r requirements.txt
```

`python dayX.py`