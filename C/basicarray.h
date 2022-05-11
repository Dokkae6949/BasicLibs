#ifndef __BASICARRAY_H__
#define __BASICARRAY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gettype(x) _Generic((x),char: 0, \
                                signed char: 1, \
                                unsigned char: 2,\
                                short: 3, \
                                unsigned short: 4, \
                                int: 5, \
                                unsigned: 6, \
                                long: 7, \
                                unsigned long: 8, \
                                long long: 9, \
                                unsigned long long: 10, \
                                float: 11, \
                                double: 12, \
                                long double: 13 )


#define printtype(x) _Generic((x),char: "%c", \
                                signed char: "%c", \
                                unsigned char: "%c",\
                                short: "%hd", \
                                unsigned short: "%hu", \
                                int: "%d", \
                                unsigned: "%u", \
                                long: "%ld", \
                                unsigned long: "%lu", \
                                long long: "%lld", \
                                unsigned long long: "%llu", \
                                float: "%.10f", \
                                double: "%.10lf", \
                                long double: "%.10Lf" )


// Usefull swap function for multiple algos
#define SWAP(type, field) \
   void swap_##type(type* p1, type* p2) \
   {  \
      type tmp = *p1; \
      *p1 = *p2; \
      *p2 = tmp; \
   }
SWAP(char, x)
SWAP(short, x)
SWAP(int, x)
SWAP(unsigned, x)
SWAP(long, x)
SWAP(float, x)
SWAP(double, x)

// Returns pointer to new array generated with "malloc" in order to make it resizeable
#define NEW_ARRAY(type, field) \
   type* newArray_##type(const size_t arraySize) \
   {  \
      return (type *) malloc(arraySize * sizeof(type)); \
   }
NEW_ARRAY(char, x)
NEW_ARRAY(short, x)
NEW_ARRAY(int, x)
NEW_ARRAY(unsigned, x)
NEW_ARRAY(long, x)
NEW_ARRAY(float, x)
NEW_ARRAY(double, x)

// Resizes array created with "malloc" or "d_NewArray"
#define RESIZE_ARRAY(type, field) \
void resizeArray_##type(const size_t newArraySize, type* array) \
   {  \
      type *newArray = (type *) realloc(array, newArraySize * sizeof(type)); \
      if (newArray = NULL) return; \
      array = newArray; \
   }
RESIZE_ARRAY(char, x)
RESIZE_ARRAY(short, x)
RESIZE_ARRAY(int, x)
RESIZE_ARRAY(unsigned, x)
RESIZE_ARRAY(long, x)
RESIZE_ARRAY(float, x)
RESIZE_ARRAY(double, x)

// Starts with the "startValue" and increments each iteration by the "incrementValue"
#define FILL_ARRAY(type, field) \
   void fillArray_##type(const size_t arraySize, type* array, const type startValue, const type incrementValue) \
   {  \
      for (size_t i = 0; i < arraySize; i++) \
         array[i] = startValue + (incrementValue * i); \
   }
FILL_ARRAY(char, x)
FILL_ARRAY(short, x)
FILL_ARRAY(int, x)
FILL_ARRAY(unsigned, x)
FILL_ARRAY(long, x)
FILL_ARRAY(float, x)
FILL_ARRAY(double, x)

// Fills array with random values in specific range || For int, char, short, ... types(min:INCLUSIVE; max:EXCLUSIVE)
#define FILL_ARRAY_RAND(type, field) \
   void fillArrayRand_##type(const size_t arraySize, type* array, const type min, const type max) \
   {  \
      for (size_t i = 0; i < arraySize; i++) \
         array[i] = (type)((double)rand() / RAND_MAX * (max - min) + min); \
   }
FILL_ARRAY_RAND(char, x)
FILL_ARRAY_RAND(short, x)
FILL_ARRAY_RAND(int, x)
FILL_ARRAY_RAND(unsigned, x)
FILL_ARRAY_RAND(long, x)
FILL_ARRAY_RAND(float, x)
FILL_ARRAY_RAND(double, x)

// Shifts array Left/Right by the given amount
#define SHIFT_ARRAY(type, field) \
   void shiftArray_##type(const size_t arraySize, type* array, int shiftAmount) \
   {  \
      shiftAmount = shiftAmount >= 0 ? shiftAmount : arraySize + shiftAmount; \
      type tmp[arraySize]; \
      for (size_t i = 0; i < arraySize; i++) \
         tmp[abs((i + shiftAmount) % arraySize)] = array[i]; \
      memcpy(array, tmp, sizeof(type) * arraySize); \
   }
SHIFT_ARRAY(char, x)
SHIFT_ARRAY(short, x)
SHIFT_ARRAY(int, x)
SHIFT_ARRAY(unsigned, x)
SHIFT_ARRAY(long, x)
SHIFT_ARRAY(float, x)
SHIFT_ARRAY(double, x)

// Prints array based on elements per row the sepperator and the amount of decimals(only for floating points)
#define PRINT_ARRAY(type, field) \
   void printArray_##type(const size_t arraySize, type* array, size_t elementsPerRow, const char* prefixSepperator, const char* suffixSepperator, size_t decimals) \
   { \
      decimals = decimals == 0 ? 0 : decimals > 10 ? 11 : decimals + 1; \
      for (size_t i = 0; i < arraySize; i++) \
      { \
         printf("%s", prefixSepperator); \
         printf(printtype(*array), array[i]); \
         if (gettype(*array) >= 11) for (size_t i = 0; i < 11-decimals; i++) printf("\b \b"); \
         if ((i+1) % elementsPerRow == 0) printf("\n"); \
         else if (i == arraySize-1) printf("\n"); \
         else printf("%s", suffixSepperator); \
      } \
   }
PRINT_ARRAY(char, x)
PRINT_ARRAY(short, x)
PRINT_ARRAY(int, x)
PRINT_ARRAY(unsigned, x)
PRINT_ARRAY(long, x)
PRINT_ARRAY(float, x)
PRINT_ARRAY(double, x)

// Classic bubble sort (nice and slow)
#define BUBBLE_SORT_ARRAY(type, field) \
   void bubbleSortArray_##type(const size_t arraySize, type* array) \
   {  \
      int swaps = 0, runs = 0; \
      do{ \
        swaps = 0; runs++; \
        for (int i = 0; i < arraySize - runs; i++) { \
            if (array[i] < array[i+1]) continue; \
            swaps++; swap_##type(&array[i], &array[i+1]); } \
      } while(swaps != 0); \
   }
BUBBLE_SORT_ARRAY(char, x)
BUBBLE_SORT_ARRAY(short, x)
BUBBLE_SORT_ARRAY(int, x)
BUBBLE_SORT_ARRAY(unsigned, x)
BUBBLE_SORT_ARRAY(long, x)
BUBBLE_SORT_ARRAY(float, x)
BUBBLE_SORT_ARRAY(double, x)

#endif