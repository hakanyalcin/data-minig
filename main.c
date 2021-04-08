#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
int i = 0;
int c;
struct node* root = NULL;
int abc;
struct node {
    char term[30];
    struct node *left, *right;
    int count;
};

void preorder(struct node *root) {
    if(root == NULL) return;

    printf("%s ------> %d\n",root->term, root->count); // Print data
    preorder(root->left);     // Visit left subtree
    preorder(root->right);    // Visit right subtree
}


struct node* getNewNode(char* c, int size) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    memcpy(newNode->term, c , (size_t) size);
    //newNode->term=term;
    newNode->left = newNode->right = NULL;
    newNode->count=1;
    return newNode;
}

struct node* insert(struct node* root, char* c, int size) {
    if (root == NULL) {
        //root = getNewNode(c,size);
        return getNewNode(c,size);
    }
    if(strcmp(root->term,c)==0){
        (root->count)++;
        return root;
    }

    if (strcmp(root->term, c) < 0) {
        root->right = insert(root->right,c,size);
    }
    else {
         root->left = insert(root->left, c, size);
    }
}


struct node * minValueNode(struct node* node) {
    struct node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
    return current;
}
struct node* delete(struct node* root, char* c) {
    if (root == NULL)
        return root;

    if (strcmp(root->term, c) > 0)
        root->left = delete(root->left, c);

    else if (strcmp(root->term, c) < 0)
        root->right = delete(root->right, c);

    else {

        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

       struct node* temp = minValueNode(root->right);
        strcpy(root->term,temp->term);
        root->right = delete(root->right, temp->term);
    }
return root;
}



int main() {

    char word[30];
    FILE *fp = fopen("/home/hakan/CLionProjects/project2/cse22501.txt", "r");

     while((c = getc(fp)) != EOF){
        word[i] = (char) c;
            i++;
        if(c==32){
            memset(&word[i-1], 0, (size_t) (30 - i));
            root = insert(root, word,i);
            i = 0;
        }
    }
    if(c==EOF) {
        memset(&word[i-1], 0, (size_t) (30 - i));
        root = insert(root, word, i);
        i=0;
    }
    fclose(fp);



    FILE *rm = fopen("/home/hakan/CLionProjects/project2/ignoreList.txt","r");
    while((c=getc(rm)) != EOF){
        word[i] = (char)c;
            i++;
        if(c==10){
            memset(&word[i-1], 0, (size_t) (30 - i));
            root = delete(root, word);
            i=0;
        }
    }
    if(c==EOF) {
        memset(&word[i-1], 0, (size_t) (30 - i));
        root = delete(root, word);
        i=0;
    }


   preorder(root);



}
