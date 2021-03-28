# RandomBag

`RandomBag` is a tiny C tool for returning a list of integers in random order.

## How To

Initialize the struct:

```c
RandomBag r = RandomBag_Create(5); // Creates a list of 5 integers, uninitialized. Fill them in manually
RandomBag r = RandomBag_CreateList(3, 1, 2, 3); // Creates a list of 3 integers, sets the list to [1, 2, 3]
RandomBag r = RandomBag_CreateRange(3, 9); // Creates a list of 7 integers, sets the list to [3, 4, 5, 6, 7, 8, 9]
```

Then get items from the struct:

```c
int item = RandomBag_GetItem(&r); // Returns remaining item at random
// Keep calling until it's out of items
// When it's out, it will return INT_MAX from <limits.h>
```

Finally, remember to free the struct:

```c
RandomBag_Free(&r);
```
