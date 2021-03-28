/*
Copyright 2021 Silent Tower Games LLC

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <limits.h>
#include "RandomBag.h"

static void test(RandomBag* r)
{
    printf("Emptying bag. Will print INT_MAX when complete\n");
    
    for(int i = 0; i < r->count + 1; i++)
    {
        // Example with RandomBag_GetNext:
        //printf("%d, ", RandomBag_GetNext(r));
        
        // Example with RandomBag_Out:
        int o;
        if(!RandomBag_Out(r, &o))
        {
            o = INT_MAX;
        }
        printf("%d ", o);
    }
    
    printf("Done!\n\n");
}

int main()
{
    printf("RandomBag example by Silent Tower Games\n\n");
    
    RandomBag r;
    
    // Create a 3-item list with the numbers 5, 9, and 47
    r = RandomBag_CreateList(3, 5, 9, 47);
    test(&r);
    RandomBag_Free(&r);
    
    // Create a list of numbers between 5 and 12
    r = RandomBag_CreateRange(5, 12);
    test(&r);
    RandomBag_Free(&r);
    
    // Create an uninitialized 4-item list
    // You should go in after this & manually set the items
    // If not, you'll get junk data
    r = RandomBag_Create(4);
    test(&r);
    RandomBag_Free(&r);
    
    return 0;
}
