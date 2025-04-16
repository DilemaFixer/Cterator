# Cterator

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Language](https://img.shields.io/badge/language-C-orange)

A simple, lightweight iterator implementation for C to easily traverse through collections of elements.

## 🚀 Installation

### Cross-Platform (Linux, macOS, Windows)

```bash
curl -o cterator.c https://raw.githubusercontent.com/DilemaFixer/Cterator/main/cterator.c
curl -o cterator.h https://raw.githubusercontent.com/DilemaFixer/Cterator/main/cterator.h
```

## 📋 API and Usage Examples

### 🔄 Iterator Core

The Cterator library provides a simple iterator pattern implementation for C, allowing you to iterate through arrays of pointers in a clean and controlled manner.

#### Core Structure

```c
typedef struct cterator {
    void **items;    // Array of elements to iterate through
    size_t count;    // Total number of elements
    size_t current;  // Current position in the array
} cterator;
```

#### Creation and Destruction Functions

```c
// Create a new iterator for an array of pointers
cterator *new_cterator(void **items, size_t count);

// Free the iterator (does not free the item array)
void free_cterator(cterator *ct);
```

#### Iterator Operations

```c
// Get the current element without advancing the iterator
void *ct_get(cterator *ct);

// Move to the next element and return whether there are more elements
int ct_next(cterator *ct);

// Reset the iterator to the beginning
void ct_reset(cterator *ct);
```

#### Convenience Macros

```c
// Foreach macro for easy iteration
#define foreach(item, iterator) \
    for(int _keep = (ct_next(iterator) ? 1 : 0); \
        _keep && ((item = ct_get(iterator)) || 1); \
        _keep = ct_next(iterator) ? 1 : 0)
```

#### Usage Example

```c
#include "cterator.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create an array of string pointers
    char *strings[] = {"Hello", "World", "Cterator", "Example"};
    
    // Create an iterator for these strings
    cterator *ct = new_cterator((void **)strings, 4);
    
    // Method 1: Manual iteration
    ct_reset(ct);
    while (ct_next(ct)) {
        char *str = ct_get(ct);
        printf("%s\n", str);
    }
    
    // Method 2: Using the foreach macro
    ct_reset(ct);
    char *item;
    foreach(item, ct) {
        printf("%s\n", item);
    }
    
    // Clean up
    free_cterator(ct);
    return 0;
}
```

Required header: `cterator.h`
