/*
Copyright 2021 Silent Tower Games LLC

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "RandomBag.h"
#include <limits.h>
#include <stdlib.h>
#ifdef RANDOMBAG_SRAND
#include <time.h>

static int RandomBag__srandSeeded = 0;
static time_t RandomBag__t;
#endif

RandomBag RandomBag_Create(int count)
{
    RandomBag r;
    
    #ifdef RANDOMBAG_SRAND
    if(RandomBag__srandSeeded == 0)
    {
        srand((unsigned)(time(&RandomBag__t)));
        
        RandomBag__srandSeeded = 1;
    }
    #endif
    
    r.bag = malloc(sizeof(int) * count);
    
    r.count = count;
    r.used = 0;
    
    return r;
}

RandomBag RandomBag_CreateList(int count, ...)
{
    RandomBag r = RandomBag_Create(count);
    
    va_list p;
    
    va_start(p, count);
    
    for(int i = 0; i < count; i++)
    {
        r.bag[i] = va_arg(p, int);
    }
    
    va_end(p);
    
    return r;
}

RandomBag RandomBag_CreateRange(int first, int last)
{
    int count = last - first + 1;
    
    RandomBag r = RandomBag_Create(count);
    
    for(int i = 0; i < r.count; i++)
    {
        r.bag[i] = first + i;
    }
    
    return r;
}

int RandomBag_GetNext(RandomBag* r)
{
    if(r->used >= r->count)
    {
        return INT_MAX;
    }
    
    r->used++;
    
    int i;
    int timeout = 500;
    do {
        i = rand() % r->count;
        
        if(timeout > 0)
        {
            timeout--;
        }
        else
        {
            return INT_MAX;
        }
    }
    while(r->bag[i] == INT_MAX);
    
    int n = r->bag[i];
    
    r->bag[i] = INT_MAX;
    
    return n;
}

RandomBag RandomBag_Free(RandomBag* r)
{
    free(r->bag);
}
