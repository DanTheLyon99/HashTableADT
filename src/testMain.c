/**
 * @file testMain.c
 * @author Ryan Sorkin
 * @date June 2018
 * @brief File including a main to test functions of the
 * Hash Table ADT
 */

 #include "HashTableAPI.h"

 void destroyData(void *data);
 int hashFunction(size_t tableSize, int key);
 void printData(void *toBePrinted);

 int main()
 {
   void (*destroyFunc)(void *data) = &destroyData;
   int (*hashFunc)(size_t tableSize, int key)= &hashFunction;
   void (*printFunc)(void * toBePrinted) = &printData;

   HTable * testTable = createTable(10, hashFunc, destroyFunc, printFunc);
   
   return 0;
 }


 void destroyData(void *data)
 {
   // Cast data to Node
   Node * node = (Node*)data;

   // Set data and next node to NULL
   node->next = NULL;
   node->data = NULL;
 }

 int hashFunction(size_t tableSize, int key)
 {
   // Return last index of the array
   if (key == 0)
   {
     return tableSize - 1;
   }

   return tableSize % key;
 }

 void printData(void *toBePrinted)
 {
   // Cast argument to Node
   Node * node = (Node*)toBePrinted;

   // Cast Node data to string and print
   char * word = (char*)node->data;
   printf("%s\n", word);
 }
