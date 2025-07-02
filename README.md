# PP11

## Goal

In this exercise you will:

* Design and implement a **doubly linked list** as a reusable library.
* Create and interact with a **singly linked list** via an interactive menu, using dynamic memory (`malloc`/`free`).
* Parse a JSON array from a file using **jansson**, store objects in a linked list, and manipulate them in C.

**Important:** Start a stopwatch when you begin and work uninterruptedly for **90 minutes**. When time is up, stop immediately and record where you paused.

---

## Workflow

1. **Fork** this repository on GitHub.
2. **Clone** your fork locally.
3. Create a `solutions/` directory at the project root:

   ```bash
   mkdir solutions
   ```
4. For each task, add the specified source files under `solutions/`.
5. **Commit** and **push** your changes to GitHub.
6. **Submit** your GitHub repo link for review.

---

## Prerequisites

* GNU C compiler (`gcc`).
* Understanding of pointers and dynamic memory (`malloc`, `free`).
* Jansson library installed (`libjansson-dev`).
* Linker flags (`-ljansson`).

---

## Tasks

### Task 1: Compile-Time Doubly Linked List

**Objective:** Implement and traverse a doubly linked list entirely with compile-time allocation.

1. Create `solutions/dlist_static.c` and include `dlist.h` (which defines `DNode` and `DList`).
2. Define a static array of five `DNode` elements:

   ```c
   #include <stdio.h>
   #include "dlist.h"  // defines DNode and DList

   // Static nodes for values 1–5
   DNode nodes[5];
   DList list;

   int main(void) {
       // Initialize static nodes
       for (int i = 0; i < 5; i++) {
           // Example: store node index as data
           nodes[i].data = (void*)(long)(i + 1);
           nodes[i].prev = (i > 0) ? &nodes[i - 1] : NULL;
           nodes[i].next = (i < 4) ? &nodes[i + 1] : NULL;
       }
       list.head = &nodes[0];
       list.tail = &nodes[4];

       // Traverse forward
       printf("Forward: ");
       for (DNode *p = list.head; p != NULL; p = p->next) {
           printf("%ld ", (long)p->data);
       }
       printf("\n");

       // Traverse backward
       printf("Backward: ");
       for (DNode *p = list.tail; p != NULL; p = p->prev) {
           printf("%ld ", (long)p->data);
       }
       printf("\n");

       return 0;
   }
   ```
3. Compile and run:

   ```bash
   gcc -o solutions/dlist_static solutions/dlist_static.c
   ./solutions/dlist_static
   ```
**Link of **Link of dlist.h**

[dlist.h](https://github.com/AlexSchweiger827/PP11/blob/master/PP11/solutions/dlist.h)
   
**Link of dlist_static.c**

[dlist_static.c](https://github.com/AlexSchweiger827/PP11/blob/master/PP11/solutions/dlist_static.c)
   
**dlist_static.c compiled and Test run of dlist_static**

![dlist_static.c compiled](https://github.com/AlexSchweiger827/PP11/blob/master/PP11%20screenshots/Task1_3.PNG) 

#### Reflection Questions

1. **How do you link `prev` and `next` pointers correctly using a static array?**

By declaring a static array (e.g DNode nodes[5] ), the compiler assign a block of memory to hold 5 Dnode structures.
Each elment in the array ( nodes[i])  has a unique memory adress. 
By using the adress- of operator (&) you can get the address of an array element and assign it to a pointer. 



   
2. **What are advantages and limitations of compile-time vs. dynamic allocation?**
   

**compile-time allocation**

advantages:
The compile-time allocation is very fast. Global and static are distributed when the program loads.
Furthermore stack variables are alloctated by adjusting the stack pointer.
The runtime does not extra time to search for free memory blocks. 
The data is located in expected memory regions, which lead to better cache performance.
The memory is managaed by the stack, which eliminates small, unusable fragments in the heap. 

limitations:
It is not suitable for data structures which varies (e.g array sizes that are determined at runtime).
Because the amount of memory is decided at compile time.
Local variables on the stack are destroyed when the function returns.
Recursive functions or functions with large local arrays can exhaust the limited stack space (stack overflow).
It can not manage complex data structures (e.g trees, graphs) where the nodes often are added or removed.

**dynamic allocation**

advantages:
The right amount of memory will be allocated in runtime. Which is suitable for data structures that varies.
Dynamic allocation can manage structures like trees and graphs where the nodes often are added or removed. 
Memory is only allocated when needed and disposed when it is not used anymore.

limitations:
The Allocation needs more time to search for free memory blocks.
The memory can be scattered across the heap, which cause small unusable fragments in the heap. The consequence is bad cache performance.

   
3. **How would you extend this static list to include additional data fields?**
   
1. Change the DNode structure in dlist.h (e.g add char name)

   
```c
#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>
#include <stdio.h>

typedef struct DNode {
    int number;           //Integer number new data field
    char name [100];       // character array for name  new data field
    struct DNode *prev;   // Pointer to the previous node in the list
    struct DNode *next;   // Pointer to the next node in the list
} DNode;

typedef struct DList {
    DNode *head;
    DNode *tail;
    size_t size;
} DList;

#endif
```

2.Add the main Programm (dlist_static.c) by adding the new data fields.

```c
#include <stdio.h>
#include "dlist2.h"  // defines DNode and DList

// Static nodes for values 1–5
DNode nodes[5];
DList list;

int main(void) {
    // Initialize static nodes
    for (int i = 0; i < 5; i++) {
        nodes[i].number = i + 1;                  //Assigning a number
        sprintf (nodes[i].name, "Name %d", i+1); //Assigning a name

        nodes[i].prev = (i > 0) ? &nodes[i - 1] : NULL;
        nodes[i].next = (i < 4) ? &nodes[i + 1] : NULL;
    }
    list.head = &nodes[0];
    list.tail = &nodes[4];

    // Traverse forward
    printf("Forward:\n ");
    printf("Number\n\tName\n");
    printf("------\t--------\n");
    for (DNode *p = list.head; p != NULL; p = p->next) {
         printf("%d\t%-15s\t ",p->number, p->name);
    }
    printf("\n");

    // Traverse backward
    printf("Backward:\n ");
    printf("Number\n\tName\n");
    printf("------\t--------\n");
    for (DNode *p = list.tail; p != NULL; p = p->prev) {
        printf("%d\t%-15s\t ",p->number, p->name);
    }
    printf("\n");

    return 0;
}
```
---
The Program compiled und testet looks like this: 

![dlist_static2.c compiled](https://github.com/AlexSchweiger827/PP11/blob/master/PP11%20screenshots/Task1_3.PNG) 

### Task 2: Interactive Singly Linked List

**Objective:** Build a menu-driven program to manipulate a singly linked list at runtime.

1. Define `SNode` and function prototypes in `solutions/slist.h`:

   ```c
   typedef struct SNode {
       int value;
       struct SNode *next;
   } SNode;

   SNode* add_node(SNode *head, int value);
   int    count_nodes(SNode *head);
   void   free_list(SNode *head);
   ```
2. Implement `add_node`, `count_nodes`, and `free_list` in `solutions/slist.c` using `malloc` and `free`.
3. Create `solutions/slist_main.c`:

   ```c
   #include <stdio.h>
   #include "slist.h"

   int main(void) {
       SNode *head = NULL;
       int choice, val;

       do {
           printf("1) Count nodes\n2) Add node\n3) Exit\n> ");
           if (scanf("%d", &choice) != 1) break;
           switch (choice) {
               case 1:
                   printf("Count: %d\n", count_nodes(head));
                   for (SNode *p = head; p; p = p->next)
                       printf("Node at %p: %d\n", (void*)p, p->value);
                   break;
               case 2:
                   printf("Value: ");
                   scanf("%d", &val);
                   head = add_node(head, val);
                   break;
               case 3:
                   free_list(head);
                   break;
               default:
                   printf("Invalid option\n");
           }
       } while (choice != 3);

       return 0;
   }
   ```
4. Compile and run:

   ```bash
   gcc -c solutions/slist.c -o solutions/slist.o
   gcc -o solutions/slist_main solutions/slist_main.c solutions/slist.o
   ./solutions/slist_main
   ```
**Link to slist.h**
[slist.h](https://github.com/AlexSchweiger827/PP11/blob/master/PP11/solutions/slist.h)

**Link to slist.c**
[slist.c](https://github.com/AlexSchweiger827/PP11/blob/master/PP11/solutions/slist.c)

**Link to slist_main.c**
[slist_main.c](https://github.com/AlexSchweiger827/PP11/blob/master/PP11/solutions/slist_main.c)

**slist_main.c compiled and test run of slist_main**

![slist_main.c compiled](https://github.com/AlexSchweiger827/PP11/blob/master/PP11%20screenshots/Task%202.PNG?raw=true) 

#### Reflection Questions

1. **Why is `malloc` necessary when adding nodes dynamically?**

"malloc" is responsible for allocating memory on the heap at runtime.
It provides the needed memory at runtime to data that are varying.
"malloc" returns a pointer to the new allocated memory block, which creates a link between independent memory blocks.

3. **How can you traverse the list to print each node’s address and value?**

 
5. **What are the consequences of not freeing the list before exit?**

---

### Task 3: JSON Array to Linked List

**Objective:** Parse a JSON array from a file into a linked list of C structs, using `getopt` to accept the input filename.

1. Create `solutions/json_list.h`:

   ```c
   #include <jansson.h>
   typedef struct JObject {
       char *name;
       int age;
       struct JObject *next;
   } JObject;

   JObject* parse_json(const char *filename);
   void     print_list(JObject *head);
   void     free_list(JObject *head);
   ```

2. Implement `solutions/json_list.c`:

   * Use `json_load_file` to load an array of objects with fields `"name"` and `"age"`.
   * For each element, allocate a `JObject`, duplicate the `name`, store `age`, and link into a list.

3. Create `solutions/json_main.c` to use `getopt`:

   ```c
   #include "json_list.h"
   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>

   void usage(const char *prog) {
       fprintf(stderr, "Usage: %s -i <file.json>
   ```

", prog);
exit(EXIT\_FAILURE);
}

int main(int argc, char \*argv\[]) {
int opt;
char \*filename = NULL;

```
   while ((opt = getopt(argc, argv, "i:")) != -1) {
       if (opt == 'i') {
           filename = optarg;
       } else {
           usage(argv[0]);
       }
   }
   if (!filename) {
       usage(argv[0]);
   }

   JObject *head = parse_json(filename);
   print_list(head);
   free_list(head);
   return 0;
```

}

````
4. Compile and run:
```bash
gcc -c solutions/json_list.c -o solutions/json_list.o -ljansson
gcc -o solutions/json_main solutions/json_main.c solutions/json_list.o -ljansson
./solutions/json_main -i data.json
````

#### Suggested Student Modifications

1. **Add** `void remove_by_age(JObject **head, int age)` to remove matching nodes.
2. **Extend** `JObject` with a new field (e.g., `char *email`) and update parsing accordingly.

#### Reflection Questions

1. **How does using `getopt` make the program more flexible than `argv[1]`?**
2. **What happens if the user omits the `-i` option?**
3. **How can you validate that the JSON file loaded is indeed an array?**

---

**Remember:** Stop after **90 minutes** and record where you stopped.
