#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trienode_ {
  unsigned char isLeaf;
  unsigned char key;
  unsigned char label;
  struct trienode_ *al[26];
} trieNode;

typedef struct trie {
   trieNode *root;
} trie;


trie *initTrie ()
{
  trie *ptr = calloc (1, sizeof (trie));
  return ptr;
}

trieNode *createNewNode (trie *pTrie, char c)
{
   trieNode *ptr = calloc (1, sizeof (trieNode));
   ptr->isLeaf = 0;
   ptr->key = c;
   return ptr;
}

unsigned char insertNode (trie *pTrie, char *key)
{
  trieNode *ptr = 0x0;
  unsigned char c, i;
  for (i=0; i< strlen(key); i++)
  {
    if (! ptr)
    { 
      //identify root node with label 0 and key \0;
      ptr = createNewNode (pTrie, '\0');
      ptr->label = 0;
      pTrie->root = ptr;
      // since its root node , we proceed to creating the 
      // first edge
      ptr->al[key[i]-'a'] = createNewNode (pTrie, key[i]);
      ptr->al[key[i]-'a']->label = i+1;
    }
    else
    {
      if (ptr->al[key[i]-'a'] == 0x0)
      {
        ptr->al[key[i]-'a'] = createNewNode(pTrie, key[i]);
        ptr->al[key[i]-'a']->label = i + 1;
      }
        
    }
    ptr = ptr->al[key[i]-'a'];
  }
}

void printTrie (trieNode *pNode)
{
  unsigned char i;
  
  printf ("%d -> ",pNode->label);
  for (i=0; i<26; i++)
  {
    if (pNode->al[i] != 0x0)
    {
      printf ("%d : %c \n", pNode->al[i]->label, pNode->al[i]->key);
      printTrie (pNode->al[i]);
    }
        
  }
}

void main ()
{
  unsigned int count, i;
  unsigned char **str;
  unsigned char temp[3000];
  trie *gTrie = initTrie ();
  printf ("Enter the number of strings : ");
  scanf ("%u", &count);
  printf ("Enter  %u strings : %u ", count);
  str = calloc (count, sizeof (str));
  for (i=0;i< count;i++)
  {
    scanf ("%s", temp);
    str[i] = calloc (1, strlen (temp));
    strcpy (str[i], temp);
    insertNode (gTrie, temp);
    memset (temp, 0, 3000);
  }
 
  printTrie (gTrie->root); 
  
}
