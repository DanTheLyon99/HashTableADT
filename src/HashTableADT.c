/**
 * @file HashTableADT.c
 * @author Ryan Sorkin
 * @date June 2018
 * @brief File containing functions of a hash table ADT
 */

#include "HashTableAPI.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, int key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{
   // Allocate memory for a Hash Table
   HTable * newTable = malloc(sizeof(HTable));
   newTable->table = malloc(sizeof (Node *) * size);

   // Set size of hash table
   newTable->size = size;

   // Set hash table functions to function pointers passed in
   newTable->hashFunction = hashFunction;
   newTable->destroyData = destroyData;
   newTable->printData = printData;

   return newTable;
}

Node *createNode(int key, void *data)
{
   // Allocate memory for node
   Node * newNode = malloc(sizeof(Node));

   // Set node key and data to arguments
   newNode->key = key;
   newNode->data = data;
   newNode->next = NULL;

   return newNode;
 }

void destroyTable(HTable *hashTable)
{
  Node * curNode = NULL;
  Node * toDelete = NULL;

  // Go through each element of the table
  for (int i = 0; i < hashTable->size; i++)
  {
    // Set the current node to head of the current list in the table
    curNode = hashTable->table[i];

    // Delete each list in the array
    while (curNode)
    {
      // Set a pointer to the node to be deleted
      toDelete = curNode;

      // Move current node to next one in table (if any)
      curNode = curNode->next;

      // Delete the node
      hashTable->destroyData((void*)toDelete);
    }
  }
}

void insertData(HTable *hashTable, int key, void *data)
{
  // Exit if hash table does not exist
  if (!hashTable)
  {
    return;
  }

  int index;

  // Create a new node and update it with arguments
  Node * newNode = createNode(key, data);
  newNode->key = key;
  newNode->data = data;
  newNode->next = NULL;

  // Determine index to insert data
  index = hashTable->hashFunction(hashTable->size, key);

  // If there is a node at the index already
  if (hashTable->table[index])
  {
    // Set the current node to the head of the collision list
    Node * curNode = hashTable->table[index];
    Node * tempNode = curNode;

    // If the first node is to be replaced
    if (curNode->key == key)
    {
      newNode->next = curNode->next;
      hashTable->table[index] = newNode;
      hashTable->destroyData(curNode);
    }
    else
    {
      while (curNode->next)
      {
        // If the next node is to be replaced
        if (curNode->next->key == key)
        {
          // Skip the next node and delete it
          tempNode = curNode->next;
          curNode->next = tempNode->next;
          hashTable->destroyData(tempNode);

          // Exit the loop since data has been updated
          break;
        }
        // If the node after next is empty, set it to the new node
        else if (curNode->next->next == NULL)
        {
          curNode = curNode->next;
          curNode->next = newNode;

          // Exit loop since data was added to end
          break;
        }

        // Move along the list
        curNode = curNode->next;
      }
    }
  }
  // Set the lists head at that index to the new node
  else
  {
    hashTable->table[index] = newNode;
  }
}

void removeData(HTable *hashTable, int key)
{
  // Exit if table does not exist
  if (!hashTable)
  {
    return;
  }

  // Find index to be removed from
  int index = hashTable->hashFunction(hashTable->size, key);

  // Table does not exist at that index, return
  if (!(hashTable->table[index]))
  {
    return;
  }

  // Set curNode to head of list at index
  Node * curNode = hashTable->table[index];
  Node * prevNode = NULL;

  // Move along the list until key is found or end of list
  while(curNode && curNode->key != key)
  {
    prevNode = curNode;
    curNode = curNode->next;
  }

  // The node to be deleted is found
  if(curNode && curNode->key == key)
  {
    // Node found is head of the list, delete it
    if(!prevNode)
    {
      hashTable->table[index] = curNode->next;
      hashTable->destroyData(curNode);
    }
    // Delete node from list
    else
    {
      prevNode->next = curNode->next;
      hashTable->destroyData(curNode);
    }
  }
}

void *lookupData(HTable *hashTable, int key)
{
  if (!hashTable)
  {
    return NULL;
  }

  // Find the index in the table to be searched
  int index = hashTable->hashFunction(hashTable->size, key);

  // Return NULL if the index does not exist
  if (!hashTable->table[index])
  {
    return NULL;
  }

  // Set node tracker to head of list
  Node * tempNode = hashTable->table[index];

  // Go through each node in the list
  while (tempNode)
  {
    // If the node is found return its data
    if (tempNode->key == key)
    {
      return tempNode->data;
    }

    // Node was not found, move along list
    tempNode = tempNode->next;
  }

  // Node was never found, return NULL;
  return NULL;
}
