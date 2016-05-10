#include<stdio.h>
#include<malloc.h>
/**
 *  树的定义：
 *  (01) 每个节点有零个或多个子节点；
 *  (02) 没有父节点的节点称为根节点；
 *  (03) 每一个非根节点有且只有一个父节点；
 *  (04) 除了根节点外，每个子节点可以分为多个不相交的子树。
 *
 *  二叉树是每个节点最多有两个子树的树结构
 *
 *  二叉树的性质：
 *  性质1：二叉树第i层上的结点数目最多为 2{i-1} (i≥1)。
 *  性质2：深度为k的二叉树至多有2{k}-1个结点(k≥1)。
 *  性质3：包含n个结点的二叉树的高度至少为log2 (n+1)。
 *  性质4：在任意一棵二叉树中，若终端结点的个数为n0，度为2的结点数为n2，则n0=n2+1。
 *
 *  满二叉树：
 *  高度为h，并且由2{h} –1个结点的二叉树，被称为满二叉树。
 *
 *  完全二叉树：
 *  一棵二叉树中，只有最下面两层结点的度可以小于2，并且最下一层的叶结点集中在靠左的若干位置上。这样的二叉树称为完全二叉树。
 *
 *  二叉查找树：
 *  二叉查找树(Binary Search Tree)，又被称为二叉搜索树。设x为二叉查找树中的一个结点，x节点包含关键字key，节点x的key值记为key[x]。如果y是x的左子树中的一个结点，则key[y] <= key[x]；如果y是x的右子树的一个结点，则key[y] >= key[x]。
 *  (01) 若任意节点的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
 *  (02) 任意节点的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
 *  (03) 任意节点的左、右子树也分别为二叉查找树。
 *  (04) 没有键值相等的节点（no duplicate nodes）。
 *
 *
 *
 */


typedef struct BSTreeNode{
  int value;  //节点的值
  struct BSTreeNode *left;  //左孩子
  struct BSTreeNode *right; //右孩子
  struct BSTreeNode *parent;  //父亲节点
}Node,*NodeP;
NodeP create_node(int value);
static NodeP insert_tree(NodeP tree, NodeP node);
void preorder_bstree(NodeP tree);

int main() {
  NodeP tree = NULL;
  NodeP n1, n2, n3, n4, n5;
  n1 = create_node(100);
  tree = insert_tree(tree, n1);
  n2 = create_node(1);
  tree = insert_tree(tree, n2);
  n3 = create_node(4);
  tree = insert_tree(tree, n3);
  n4 = create_node(88);
  tree = insert_tree(tree, n4);
  n5 = create_node(104);
  tree =insert_tree(tree, n5);
  preorder_bstree(tree);

  free(n1);
  free(n2);
  free(n3);
  free(n4);
  free(n5);
  return 0;
}

NodeP create_node(int value) {
  NodeP node = (NodeP)malloc(sizeof(Node));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  return node;
}

static NodeP insert_tree(NodeP tree, NodeP node){
  NodeP x = tree;
  NodeP y = NULL;
  while(x != NULL) {
    y = x;
    if(x->value > node->value)
      x = x->left;
    else
      x = x->right;
  }
  node->parent = y;
  if(y == NULL)
    tree = node;
  else if(node->value > y->value)
    y->right = node;
  else
    y->left = node;

  return tree;
}

void preorder_bstree(NodeP tree) {
  if(tree != NULL) {
    printf("%d\n", tree->value);
    preorder_bstree(tree->left);
    preorder_bstree(tree->right);
  }
}


