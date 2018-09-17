#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX 256
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

typedef struct trienode
{
	struct trienode *children[MAX]; //maximum 26 diff children

	bool isEndOfWord; // true if leaf

	int freq; //no of times node is visited during insertion
}node;


//for a prefix to be unique it should be traversed 
//only once during insertion
//ie : freq ==1


node* create_node()
{
	node* t = NULL;
	t = ( node* )malloc(sizeof(node));
	t->freq=1;

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

	for (int i = 0; i < strlen(word); ++i)
	{
		int index = word[i];

		if(traverser->children[index]==NULL)//node not present
		{
			traverser->children[index]=create_node();
		}
		
		else //increase freq
		{
			(traverser->children[index]->freq)++;
		}	

		traverser = traverser->children[index]; //go to child level

	}

	//traverser->isEndOfWord = true;
}




void findPrefixesUtil(node *root, char prefix[],int ind)
{
    // Corner case
    if (root == NULL)
       return;
 
    // Base case
    if (root->freq == 1)
    {
       prefix[ind] = '\0';
       printf("%s ",prefix);
       return;
    }
 
    for (int i=0; i<MAX; i++)
    {
       if (root->children[i] != NULL)
       {
           prefix[ind] = i;
           findPrefixesUtil(root->children[i], prefix, ind+1);
       }
    }
}



int main(int argc, char const *argv[])
{
	char dictionary[][8]={"zebra", "dog", "duck", "dove"};

    
    //initialize root of the trie
    node* root = create_node();
    root->freq=0;

    //insert the dictionary
    for (int i = 0; i < sizeof(dictionary)/sizeof(dictionary[0]); ++i)
    {
    	insert(root,dictionary[i]);
    }

    char prefix[100];
    findPrefixesUtil(root,prefix,0);
 
    return 0;


}