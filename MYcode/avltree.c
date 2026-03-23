#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define EQ(a,b) (a==b)
#define LT(a,b) (a<b)
#define MT(a,b) (a>b)
#define max(a,b) ((a)>(b)?(a):(b))
#define maxsize 20
// 定义结构体
typedef struct node
{
    int val;
    int height;
    struct node* lchild;
    struct node* rchild;
}node,*tree;


//创建新节点
node* create(int val)
{
    node*newnode=(node*)malloc(sizeof(node));
    newnode->val=val;
    newnode->height=1;
    newnode->lchild=newnode->rchild=NULL;
    return newnode;
}
//查找节点
node** findnode(tree *root,int val)
{
    if(!(*root)) return root;//这里直接放回root,而不是返回NULL,方便我们后续做插入操作
                        // 当root 为空的时候此时root就是某个节点的孩子的地址,如果这里是返回
                        // node*类型那就是错误的了,因为我们要修改root->child的值,这是一个node*类型的
                        // 所以必须返回node**的类型,否则就仅仅返回了rooot->child的值,就是在副本上进行修改
                        // 而且这个位置就是val应该处于的位置
                        //这里不和EQ写在一起是为了方便理解
    else if(EQ((*root)->val,val)) return root;
    else if(LT((*root)->val,val)) return findnode(&((*root)->rchild),val);
    else return findnode(&((*root)->lchild),val); 
}

//获取高度
int getheight(tree root)
{
    if(!root) return 0;
    else return root->height;
}

// 获取平衡因子
int getbf(tree root)
{
    return getheight(root->lchild)-getheight(root->rchild);
}
//定义左旋
node* leftrotate(node* root)//root为失衡节点,也就是此时失衡的这个树的根节点
{
    node *newroot=root->rchild;
    root->rchild=newroot->lchild;
    newroot->lchild=root;
    root->height=1+max(getheight(root->lchild),getheight(root->rchild));
    newroot->height=1+max(getheight(newroot->lchild),getheight(newroot->rchild));
    return newroot;//返回新的根节点,因为旋转之后失衡节点的父亲节点的孩子指向需要修改为新的根节点
}
//定义右旋
node* rightrotate(node*root)
{
    node*newroot=root->lchild;
    root->lchild=newroot->rchild;
    newroot->rchild=root;
    root->height=1+max(getheight(root->lchild),getheight(root->rchild));
    newroot->height=1+max(getheight(newroot->lchild),getheight(newroot->rchild));
    return newroot;//返回新的根节点,因为旋转之后失衡节点的父亲节点的孩子指向需要修改为新的根节点
}
//插入节点,在进入函数之前进行判断节点是否存在
void insert(tree *root,int val)
{
    /*
    node **searchnode=findnode(root ,val->val);
    if(*searchnode) return ;//插入节点存在直接返回
    else *searchnode=val;
    这里如果仅仅是插入不考虑平衡树的高度的情况,那就可以直接这两步
    但如果还要平衡树,就要修改高度,插入后不知道其父节点并且知道也不方便修改高度,还要向上
    更改,所以这里用递归来解决插入和修改高度,在递归返回时修改高度
    */ 
   if(!(*root)) 
   {
    node *newnode=create(val);
    (*root)=newnode;
    return ;
   }
   else if(LT((*root)->val,val))  insert(&((*root)->rchild),val);
   else insert(&((*root)->lchild),val);

   (*root)->height=1+max(getheight((*root)->lchild),getheight((*root)->rchild));
   // LL类型失衡右旋
   if(getbf((*root))>1&&getbf((*root)->lchild)>0)
   {
        (*root)=rightrotate((*root));
   }
   // RR类型失衡
   else if(getbf((*root))<-1&&getbf((*root)->rchild)<0)
   {
        (*root)=leftrotate((*root));
   }
   // LR类型失衡
   else if(getbf((*root))>1&&getbf((*root)->lchild)<0)
   {
        ((*root)->lchild)=leftrotate((*root)->lchild);
        (*root)=rightrotate((*root));
   }
   // RL类型失衡
   else if(getbf((*root))<-1&&getbf((*root)->rchild)>0)
   {
        ((*root)->rchild)=rightrotate((*root)->rchild);
        (*root)=leftrotate((*root));
   }
}

//删除节点,在进入函数之前进行判断节点是否存在
void deletenode(tree *root,int val)
{
    // 这里不能直接用findnode来找父亲,因为findnode是返回节点的地址的,而且是node**类型的,我们需要的是node*类型的父亲节点
    // father节点一定存在因为我们实在节点存在才进入删除函数
    if(!*root) return;//再次确保节点存在
    if(EQ((*root)->val,val))
    {
        // 左右均为空只需要讨论单边情况就可以
        // 左孩子为空
        node*delnode=(*root);
        if(!delnode->lchild)
        {
            *root=delnode->rchild;
        }
        // 右孩子为空
        else if(!delnode->rchild)
        {
            *root=delnode->lchild;
        }
        // 左右孩子均不为空
        else
        {
            // 将被删除节点右子树最左下的节点放置在被删除节点位置
            node*rearnode=delnode->rchild;
            while(rearnode->lchild)
            {
                rearnode=rearnode->lchild;
            }
            delnode->val=rearnode->val;
            // 将被删除节点更新
            delnode=rearnode;
        }
        // 再将节点指向修改完之后删除节点
        free(delnode);
    }
    // 如果节点值小于根值,在根左子树上做删除
    else if(LT(val,(*root)->val)) deletenode(&((*root)->lchild),val);
    else deletenode(&((*root)->rchild),val);

    (*root)->height=1+max(getheight((*root)->lchild),getheight((*root)->rchild));
   // LL类型失衡右旋,这里要加=,否则会失去一个情况,因为插入的时候发生失衡,节点左子树的平衡因子
   // 一定大于1,因为如果发生失衡左子树平衡因子bf(balance foster)==0,那么在当bf 变为0之前(+1或-1)就已经
   // 是失衡了,被调整了 但是删除的时候可能出现bf=0
   if(getbf((*root))>1&&getbf((*root)->lchild)>=0)
   {
        (*root)=rightrotate((*root));
   }
   // RR类型失衡
   else if(getbf((*root))<-1&&getbf((*root)->rchild)<=0)
   {
        (*root)=leftrotate((*root));
   }
   // LR类型失衡,对LR和RL类型来说肯定不存在左右子树bf等于0的情况否则就是LL和RR类型的失衡了
   else if(getbf((*root))>1&&getbf((*root)->lchild)<0)
   {
        ((*root)->lchild)=leftrotate((*root)->lchild);
        (*root)=rightrotate((*root));
   }
   // RL类型失衡
   else if(getbf((*root))<-1&&getbf((*root)->rchild)>0)
   {
        ((*root)->rchild)=rightrotate((*root)->rchild);
        (*root)=leftrotate((*root));
   }
}
//先序遍历
void preorder(tree root)
{
    if(!root)
    {
        return;
    }
    printf("%d %d\n",root->val,root->height);
    preorder(root->lchild);
    preorder(root->rchild);
}

//中序遍历
void inorder(tree root)
{
    if(!root) 
    {
        return;
    }
    inorder(root->lchild);
    printf("%d %d\n",root->val,root->height);
    inorder(root->rchild);
}

// 后序遍历
void postorder(tree root)
{
    if(!root)
    {
        return;
    }
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%d %d\n",root->val,root->height);
}

int main()
{
    
    tree Troot=NULL;
    srand((unsigned int)time(NULL));
    int numssize=rand()%maxsize;
    int *nums=(int *)malloc(numssize*sizeof(int));
    for(int i=0;i<numssize;i++)
    {
        nums[i]=rand()%100;
        if(!*findnode(&Troot, nums[i]))
        {
            insert(&Troot, nums[i]);
        }
        printf("%d ", nums[i]);
    }
    printf("\n");
    printf("-------先序遍历结果-------");
    printf("\n");
    preorder(Troot);
    printf("\n\n");
    printf("-------中序遍历结果-------");
    printf("\n");
    inorder(Troot);
    printf("\n\n");
    printf("-------后续遍历结果-------");
    printf("\n");
    postorder(Troot);
    printf("\n\n");

    getchar();

    // 删除节点
    
    for(int i=0;i<numssize;i++)
    {
        deletenode(&Troot,nums[i]);
        // 输出删除后树
        preorder(Troot);
        printf("\n\n");
    }

    // 再测试插入
    insert(&Troot,20);
    insert(&Troot,30);
    insert(&Troot,15);
    insert(&Troot,25);
    insert(&Troot,89);
    insert(&Troot,65);

    // 再测试删除
    deletenode(&Troot,20);
    return 0;
}