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

void printTrie (trieNode *pNode, unsigned int keyLen)
{
  unsigned char i, j;
  j = (keyLen == 0) ? 26 : keyLen;
 
  for (i=0; i<j; i++)
  {
    if (pNode->al[i] != 0x0)
    {
      printf ("%d -> %d : %c \n", pNode->label, pNode->al[i]->label, pNode->al[i]->key);
      printTrie (pNode->al[i], j--);
    }
        
  }
}

trieNode *PrefixTrieMatch (trieNode *pNode, char *key, unsigned int keyLen)
{
  unsigned char i = 0;
  trieNode *temp= 0x0;
  
  while (pNode)
  {
    // a part of pattern lies at the end of text ...
    if ((pNode->isLeaf) || (i == keyLen))
        return temp;
    else if ((pNode->al[key[i]-'a']) && (pNode->al[key[i]-'a']->key == key[i]))
    {
      // capture the starting vertex of the edge holding the key like parent node
      if ( !temp)
        temp = pNode;

      pNode = pNode->al[key[i]-'a'];
      i++;
    }
    else 
        return 0x0;
    
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
 
  printTrie (gTrie->root, 0); 

  trieNode *startPatterNode ;
  while (1)
  {
      startPatterNode = 0x0;
      printf ("Enter pattern :");
      scanf ("%s",temp);
      if ((temp[0] == '\n') || (temp[0] == '\0'))
        break;
      
      if (0x0 == (startPatterNode = PrefixTrieMatch (gTrie->root, temp, strlen(temp))))
            printf ("pattern not found");
      else
        printTrie (startPatterNode, strlen(temp));
  }
}
