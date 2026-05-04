#ifndef __tree_h__
#define __tree_h__

#include "lexemme.h"
#include "stackL.h"

typedef struct NodeNT NodeNT;

struct NodeNT{
    Lexemme lex;
    NodeNT *child;
    NodeNT *brother;
};

NodeNT *CreateNodeNT(Lexemme lex);
void AddChild(NodeNT *parent, NodeNT *newChild);
void PrintNTree(NodeNT *root, int level);
void DestroyNTree(NodeNT **root);
NodeNT* buildTree(StackL *postfix);

#endif