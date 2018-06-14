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

   // Setting up names to be inserted into table
   char * bob = "Bob";
   char * fraser = "Fraser";
   char * tal = "Tal";
   char * mike = "Mike";
   char * gates = "Bill Gates";
   char * ryan = "Ryan";

   // Creating a hashTable for testing
   HTable * testTable = createTable(10, hashFunc, destroyFunc, printFunc);

   // Inserting data into the table
   insertData(testTable, 7, (void*)bob);
   insertData(testTable, 5, (void*)fraser);
   insertData(testTable, 2, (void*)tal);
   insertData(testTable, 5, (void*)mike);
   insertData(testTable, 10, (void*)gates);
   insertData(testTable, 79, (void*)ryan);

   // Removing data
   removeData(testTable, 2);
   removeData(testTable, 79);

   printf("Should be: Bill Gates\nIt is: ");
   printData(lookupData(testTable, 10));
   printf("\n");

   printf("Should be: Mike\nIt is: ");
   printData(lookupData(testTable, 5));
   printf("\n");

   printf("Should be: Bob\nIt is: ");
   printData(lookupData(testTable, 7));
   printf("\n");

   // Destroy the table
   destroyTable(testTable);

   return 0;
 }


 void destroyData(void *data)
 {
   // Cast data to Node
   Node * node = (Node*)data;

   // Set data and next node to NULL
   node->next = NULL;
   node->data = NULL;
   free(node);
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
   // Cast Node data to string and print
   char * word = (char*)toBePrinted;
   printf("%s\n", word);
 }
