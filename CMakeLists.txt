cmake_minimum_required(VERSION 3.28)
project(EstruturasDados C)

set(CMAKE_C_STANDARD 11)

add_executable(EstruturasDados
        binary-tree/avl-tree.c
        quicksort/quick-sort.c
        stack/stack-lifo.c
        insertionSort/insertion-sort.c)
