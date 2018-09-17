#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

typedef struct trienode
{
	struct trienode *children[MAX]; //maximum 26 diff children

	bool isEndOfWord; // true if leaf
}node;

node* create_node()
{
	node* t = NULL;
	t = ( node* )malloc(sizeof(node));

	if(t)
	{
		int i;

		t->isEndOfWord = false;
		for (int i = 0; i < MAX; ++i)
		{
			t->children[i]=NULL;
		}
	}


	return t;

}


//if the word is prefix -> mark only leaf node
//if new word then insert


void insert(node* root, const char *word)
{
	
	node* traverser = root;
	int index;

	for (int i = 0; i < strlen(word); ++i)
	{
		index = CHAR_TO_INDEX(word[i]);

		if(traverser->children[index]==NULL)//node not present
		{
			traverser->children[index]=create_node();
		}

		traverser = traverser->children[index];

	}

	traverser->isEndOfWord = true;
}


bool search(node *root, const char *word)
{
	node* traverser = root;
	int index;

	for (int i = 0; i < strlen(word); ++i)
	{
		index = CHAR_TO_INDEX(word[i]);

		if(traverser->children[index]==NULL)
		{
			return false;
		}

		traverser = traverser->children[index];
	}

	return(traverser!=NULL && traverser->isEndOfWord);
}



int main(int argc, char const *argv[])
{
	char dictionary[][8]={"the", "a", "there", "answer", "any",
                     "by", "bye", "their"};

    char output[][32] = {"Not present in trie", "Present in trie"};                 

    //initialize root of the trie
    node* root = create_node();

    //insert the dictionary
    for (int i = 0; i < sizeof(dictionary)/sizeof(dictionary[0]); ++i)
    {
    	insert(root,dictionary[i]);
    }


    printf("%s --- %s\n", "the", output[search(root, "the")] );
    printf("%s --- %s\n", "these", output[search(root, "these")] );
    printf("%s --- %s\n", "their", output[search(root, "their")] );
    printf("%s --- %s\n", "thaw", output[search(root, "thaw")] );
 
    return 0;


}