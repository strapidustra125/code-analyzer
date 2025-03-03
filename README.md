# "Анализатор" кода

Самодельный, очень условный "анализатор" кода на предмет количества строк.

В параметры бинарнику передается путь до директории с исходниками.

Вывод для своих же исходников:

```c++
---------------------------------------------

"../source/" statistics:
    arg/
        -> "argument.cpp" | Lines - 124: code - 79 , comm - 9 , sp - 36
        -> "argument_reader.cpp" | Lines - 118: code - 71 , comm - 11 , sp - 36
        -> "argument_reader.h" | Lines - 53: code - 24 , comm - 6 , sp - 23
        -> "argument.h" | Lines - 73: code - 44 , comm - 5 , sp - 24
    lib/
        -> "fs.cpp" | Lines - 204: code - 113 , comm - 50 , sp - 41
        -> "fs.h" | Lines - 69: code - 28 , comm - 19 , sp - 22
    base/
        -> "analyzer.cpp" | Lines - 217: code - 158 , comm - 5 , sp - 54
        -> "analyzer.h" | Lines - 95: code - 60 , comm - 0 , sp - 35
    -> "main.cpp" | Lines - 50: code - 27 , comm - 8 , sp - 15
    -> "version.h" | Lines - 44: code - 21 , comm - 14 , sp - 9
    -> "names.h" | Lines - 30: code - 12 , comm - 4 , sp - 14

---------------------------------------------

Total .c/.cpp stat. Lines : 713
    code     - 448
    comments - 83
    space    - 182
Total .h/.hpp stat. Lines : 364
    code     - 189
    comments - 48
    space    - 127

---------------------------------------------

Total statistics. Lines : 1077
    code     - 637
    comments - 131
    space    - 309

---------------------------------------------
```