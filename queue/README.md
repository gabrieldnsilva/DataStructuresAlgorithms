
---

# Queue Implementation in C

This project demonstrates a simple implementation of a queue (FIFO structure) using linked lists in C. The queue allows you to append elements, remove (pop) elements, print the current queue, and clear it entirely.

## Features

- **Append**: Add elements to the end of the queue.
- **Pop**: Remove elements from the front of the queue.
- **Print Elements**: Display all elements in the queue.
- **Clear List**: Empty the queue, freeing all allocated memory.
- **Menu**: Provides a user-friendly interface for interacting with the queue.

## How to Run

1. **Clone or download** the project files.
2. **Compile** the program using GCC:
   ```bash
   gcc queue.c -o queue
   ```
3. **Run the executable**:
   ```bash
   ./queue
   ```

## Menu Options

1. **APPEND**: Add a new element to the queue by entering a value.
2. **POP**: Remove the first element from the queue.
3. **PRINT ELEMENTS**: Display all the current elements in the queue.
4. **CLEAR LIST**: Remove all elements from the queue.
5. **EXIT**: Exit the program.

## Code Overview

- **heap**: Struct representing the queue with `first` and `last` pointers.
- **node**: Struct representing each element in the queue.
- **reset()**: Initializes an empty queue.
- **append()**: Adds a new element to the queue.
- **pop()**: Removes the front element.
- **empty()**: Checks if the queue is empty.
- **clear()**: Frees all memory allocated for the queue.
- **menu()**: Provides an interface for the user to interact with the queue.

## Example

```
==============================
          MAIN MENU
==============================
 1. APPEND
 2. POP
 3. PRINT ELEMENTS
 4. CLEAR LIST
 5. EXIT
==============================
Choose an option:
```

## Memory Management

The program dynamically allocates memory for each node in the queue. It ensures that memory is correctly freed using the `clear()` function to prevent memory leaks.

---
