#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie {
  struct Trie *children[26];
  int c;
  bool finWord;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
  for (int i = 0; i < strlen(word); i++) {
    int index = word[i] - 'a';
    if (pTrie->children[index] == NULL) {
      pTrie->children[index] = (struct Trie *)malloc(sizeof(struct Trie));
      for (int j = 0; j < 26; j++) {
        pTrie->children[index]->children[j] = NULL;
      }
      pTrie->children[index]->finWord = false;
      pTrie->children[index]->c = 0;
    }
    pTrie = pTrie->children[index];
  }
  pTrie->finWord = true;
  pTrie->c++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
  for (int i = 0; i < strlen(word); i++) {
    int index = word[i] - 'a';
    if (pTrie->children[index] == NULL) {
      return 0;
    }
    pTrie = pTrie->children[index];
  }
  if (pTrie->finWord) {
    return pTrie->c;
  } else {
    return 0;
  }
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
  for(int i=0; i<sizeOf(pTrie->children); i++) {
        if (pTrie->children[i] != NULL) {
            deallocateTrie(pTrie->children[i]);
        }
        else {
            continue;
        }
    }
    free(pTrie);
}

// Initializes a trie structure
struct Trie *createTrie() {
  Trie *node = (Trie *)calloc(1, sizeof(Trie));
  for (int i = 0; i < sizeOf(node->children); i++)
    node->children[i] = NULL;
  node->finWord = 0;
  node->c = 0;
  return node;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {}

int main(void) {
  char *inWords[256];

  // read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  for (int i = 0; i < numWords; ++i) {
    printf("%s\n", inWords[i]);
  }

  struct Trie *pTrie = createTrie();
  for (int i = 0; i < numWords; i++) {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i = 0; i < 5; i++) {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}
