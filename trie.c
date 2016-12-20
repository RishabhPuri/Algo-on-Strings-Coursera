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


trieNode *createNewNode (trie *pTrie, char c)
{
   trieNode *ptr = calloc (1, sizeof (trieNode));
   ptr->isLeaf = 0;
   ptr->key = c;
   return ptr;
}

trie *initTrie ()
{
  // initialize the trie with a root node 
  trie *ptr = calloc (1, sizeof (trie));
  ptr->root = createNewNode (ptr, '\0');
  ptr->root->label = 0;
  
  return ptr;
}

unsigned char insertNode (trie *pTrie, char *key)
{
  trieNode *ptr = pTrie->root;
  unsigned char c, i;
  for (i=0; i< strlen(key); i++)
  {
    if (ptr->al[key[i]-'a'] == 0x0)
    {
      ptr->al[key[i]-'a'] = createNewNode(pTrie, key[i]);
      ptr->al[key[i]-'a']->label = i + 1;
      if (i== (strlen(key)-1)) ptr->al[key[i]-'a']->isLeaf = 1;
    }

    ptr = ptr->al[key[i]-'a'];
  }
}

void printTrie (trieNode *pNode)
{
  unsigned char i;
 
  for (i=0; i<26; i++)
  {
    if (pNode->al[i] != 0x0)
    {
      printf ("%d -> %d : %c \n", pNode->label, pNode->al[i]->label, pNode->al[i]->key);
      printTrie (pNode->al[i]);
    }
        
  }
}

trieNode *PrefixTrieMatch (trieNode *pNode, char *key)
{
  unsigned char i = 0;
  trieNode *temp= 0x0;
  
  while (pNode)
  {
    if ((pNode->isLeaf) || ())
    {
      // print the path from root to this leaf ...
      break;
    }
    else if (pNode->al[key[i]-'a']->key == key[i])
    {
      i++;
      pNode = pNode->al[key[i]-'a'];
    }
    else break;
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
  printf ("Enter  %u strings :", count);
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
