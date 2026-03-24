#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define GT(a,b) ((a)>(b))
// 定义节点结构体
typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    int ltag,rtag; // 0表示指向子树，1表示指向前驱或后继
} Node,*ThreadedTree;
ThreadedTree head=NULL; // 线索树头节点
ThreadedTree pre=NULL;// 全局变量，记录当前访问节点的前驱节点
// 创建新节点
Node* createNode(int value) {
    Node *newnode=(Node*)malloc(sizeof(Node));
    newnode->value=value;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->ltag=0;
    newnode->rtag=0;
    return newnode;
}
// 寻找节点
Node**findnode(ThreadedTree *root,int value)
{
    if(*root==NULL||EQ((*root)->value,value))
    {
        return root;
    }
    else if(LT(value,(*root)->value))
    {
        return findnode(&((*root)->left),value);
    }
    else
    {
        return findnode(&((*root)->right),value);
    }
    
}
// 插入节点
void insertNode(ThreadedTree *root, int value)
{
    Node **node=findnode(root,value);
    if(*node==NULL)
    {
        *node=createNode(value);
    }
    else 
    {
        printf("Value %d already exists in the tree.\n", value);
    }
}

// 删除节点
void deletenode(ThreadedTree *root,int value)
{
    Node**node=findnode(root,value);
    if(!(*node))
    {
        printf("Value %d not found in the tree.\n", value);
        return;
    }
    else 
    {
        if((*node)->left==NULL)
        {
            Node*temp=(*node);
            *node=temp->right;
            free(temp);
        }
        else if((*node)->right==NULL)
        {
            Node*temp=(*node);
            *node=temp->left;
            free(temp);
        }
        else 
        {
            Node*temp=(*node)->left;
            while(temp->right)  temp=temp->right;
            (*node)->value=temp->value;
            // 再释放之前把原树指向这块内存的指针修改为NULL,否则就会访问到已经被释放的内存地址,造成不可预知的错误
            Node**tempnode=findnode(&((*node)->left),temp->value);
            *tempnode=NULL;
            free(temp);
        }
    }
}
// 中序线索化
void inorderthread(ThreadedTree T)
{
    if(T)
    {
        inorderthread(T->left);
        if(T->left==NULL)
        {
            T->ltag=1;
            T->left=pre;
        }
        if(pre&&pre->right==NULL)
        {
            pre->rtag=1;
            pre->right=T;
        }
        pre=T;
        inorderthread(T->right);
    }
}
// 把现有二叉树线索化成中序线索树
void createinorederthread(ThreadedTree T)
{
    head=(ThreadedTree)malloc(sizeof(Node));
    head->ltag=0;
    head->rtag=0;
    if(!T)
    {
        head->left=head;
        head->right=head;
    }
    else 
    {
        pre=head;
        head->left=NULL;
        head->right=NULL;
        inorderthread(T);
        pre->right=head;
        pre->rtag=1;
        head->left=pre;
        head->ltag=1;
    }
}
// 获取中序线索二叉树当前节点的后继节点
Node* getinnext(Node *node)
{
    if(node->rtag==1)
    {
        return node->right;
    }
    else
    {
        node=node->right;
        while(!node->ltag)
        {
            node=node->left;
        }
        return node;
    }
}

// 中序线索二叉树的遍历
// 利用中序线索树进行中序遍历,省去了递归和栈的使用
// 可以以任意节点为起点进行遍历,这是利用头节点将形成一个循环链表的特性
// 我们可以从任意节点出发,遍历完所有节点之后回到起点
void traverinorderthread(ThreadedTree startnode)
{
    ThreadedTree cur=startnode;
    while(cur!=head)
    {
        printf("%d ",cur->value);
        cur=getinnext(cur);
    }
    cur=getinnext(cur);
    while(cur!=startnode)
    {
        printf("%d ",cur->value);
        cur=getinnext(cur);
    }
}
// 先序线索化
void preorderthread(ThreadedTree T)
{
    if(T)
    {
        if(!T->left)
        {
            T->left=pre;
            T->ltag=1;
        }
        if(pre&&!pre->right)
        {
            pre->right=T;
            pre->rtag=1;
        }
        pre=T;
        // 这里T->left可能是线索,如果是线索就不进入递归,如果不是线索才进入递归
        // T->right没有经过修改所以还不是线索可以递归
        if(!T->ltag) preorderthread(T->left);
        preorderthread(T->right);
    }
}
// 现有二叉搜索树转换成先序二叉搜索树
void createpreorderthread(ThreadedTree T)
{
    head=(ThreadedTree)malloc(sizeof(Node));
    head->ltag=0;
    head->rtag=0;
    if(!T)
    {
        head->left=head;
        head->right=head;
    }
    else
    {
        pre=head;
        head->left=NULL;
        head->right=NULL;
        preorderthread(T);
        pre->right=head;
        pre->rtag=1;
        head->left=pre;
        head->ltag=1;
    }
}
// 获取先序线索二叉树的前驱,先序好找后继
// 不好找前驱,如果是其父亲左孩子还好前驱就是父亲
// 如果是右孩子,且如果父亲没有左孩子前驱就是父亲,如果有就是左兄弟最右下
Node* getprenext(Node* node)
{   // 左孩子就是线索直接返回
    if(node->rtag==1)
    {
        return node->right;
    }
    else
    {
        // 左孩子存在直接返回左孩子,否则右孩子,右孩子一定存在否则就是线索,不会进入else 语句
        // 这里不能用node->left来判断,因为这个时候node->left可能是线索,如果是线索就不能进入递归了,如果不是线索才进入递归
        // 否则会导致死循环
        if(!node->ltag) return node->left;
        else return node->right;
    }
}
void traverpreorderthread(ThreadedTree startnode)
{
    ThreadedTree cur=startnode;
    while(cur!=head)
    {
        printf("%d ",cur->value);
        cur=getprenext(cur);
    }
    cur=getprenext(cur);
    while(cur!=startnode)
    {
        printf("%d ",cur->value);
        cur=getprenext(cur);
    }
}
// 后序线索化
void postorderthread(ThreadedTree T)
{
    if(T)
    {
        // T的左右孩子都没有经过修改所以都不是线索可以递归
        postorderthread(T->left);
        postorderthread(T->right);
        if(!T->left)
        {
            T->ltag=1;
            T->left=pre;
        }
        if(pre&&!pre->right)
        {
            pre->rtag=1;
            pre->right=T;
        }
        pre=T;
    }
}
// 将现有二叉树转化为后序线索二叉树
void createpostorderthread(ThreadedTree T)
{
    head=(ThreadedTree)malloc(sizeof(Node));
    head->ltag=0;
    head->rtag=0;
    if(!T)
    {
        head->left=head;
        head->right=head;
    }
    else
    {
        pre=head;
        head->left=NULL;
        head->right=NULL;
        postorderthread(T);
        // 致命错误:后序线索化覆盖了T节点的右孩子,先序和中序中最后一个访问的一定是叶子节点或者
        // 没有右孩子的节点,后续中最后一个访问的节点是T节点所以这里会直接覆盖T节点的右孩子,导致后续访问T节点的右孩子时访问到已经被覆盖的内存地址,造成不可预知的错误
        // 这就是我当时为什么后序遍历错误的原因,因为我直接把pre->right=head了,而pre就是T节点,所以就直接覆盖了T节点的右孩子,导致后续访问T节点的右孩子时访问到已经被覆盖的内存地址,造成不可预知的错误
        // 还是gemini牛逼
        // pre->right=head;
        // pre->rtag=1;
        // head->left=pre;
        // head->ltag=1;
        // 此时pre就是T ,只有T满足条件才能链接
        if(pre&&!pre->right)
        {
            pre->right=head;
            pre->rtag=1;
        }
        head->left=pre;
        head->ltag=1;
    }
}
// 获取后序线索二叉树的前驱,后序好找前驱
// 不好找后继,如果是父亲右孩子还好后继就是父亲
// 如果是左孩子,且如果父亲没有右孩子后继就是父亲,如果有就是右兄弟最左下
Node* getpostfront(Node* node)
{
    if(node->ltag==1)
    {
        return node->left;
    }
    else
    {
        if(node->rtag==0) return node->right;// 必须先判断是不是线索,否则传回后继线索就会错误
        else return node->left;// node->left一定是节点如果是线索就会直接返回了,而且此时右孩子是后继线索
    }
}
// 这里是逆序输出的结果,因为后序中最后一个访问的节点是根节点,
///所以我们从根节点出发往前访问就是逆序输出了,
// 如果想要正序输出就需要先把结果存储在栈中再输出
void traverpostorderthread(ThreadedTree startnode)
{
    ThreadedTree cur=startnode;
    while(cur!=head)
    {
        printf("%d ",cur->value);
        cur=getpostfront(cur);
    }
    cur=getpostfront(cur);
    while(cur!=startnode)
    {
        printf("%d ",cur->value);
        cur=getpostfront(cur);
    }
}
// 这是通用恢复函数,无论是中序线索树还是先序线索树还是后序线索树都可以使用这个函数进行恢复
// 头节点只有最后一个遍历的节点指向他
// 最后去线索化的就是头节点,此时他的左右指针就是空了,递归也在这时终止
// 再往上递归所有的节点已经去线索化了都会层层返回
// 唯一要做的就是如果存在头接待你就把头节点释放因为头节点是我们在创建线索树的时候动态分配的
// 每次创建都会分配,而我们多次创建线索树,如果不释放就会内存泄漏
// 之所以不在全局创建,是因为我们这个还可以用来创建不同类型的线索树
// 其他类型的二叉树这个头节点就没啥用
void clearthread(ThreadedTree root)
{
    if(root)
    {
        if(root->ltag==0) clearthread(root->left);
        else 
        {
            root->left=NULL;
            root->ltag=0;
        }
        if(root->rtag==0) clearthread(root->right);
        else 
        {
            root->right=NULL;
            root->rtag=0;
        }
    }
}
// 再释放之前必须进行去线索化,因为某个节点的线索可能之前被释放
// 如果不先进行去线索化,就会访问到已经被释放的内存地址,造成不可预知的错误
void freetree(ThreadedTree root)
{
    if(root)
    {
        if(root->left) freetree(root->left);
        if(root->right) freetree(root->right);
        free(root);
    }
}
int main()
{
    ThreadedTree root = NULL;
    int values[] = {10, 5, 15, 3, 7, 12, 18};
    
    printf("=== 1. Building initial binary search tree ===\n");
    for(int i = 0; i < 7; i++)
    {
        insertNode(&root, values[i]);
        printf("Insert node: %d\n", values[i]);
    }
    printf("\n");

    // 中序线索化与遍历
    printf("=== 2. Testing inorder threading and traversal ===\n");
    createinorederthread(root);
    printf("Inorder traversal result: ");
    traverinorderthread(root);
    printf("\n\n");
    
    // 必须清理线索才能进行后续的常规树操作（如删除）
    clearthread(root);
    free(head);

    // ================= 新增：删除功能测试 =================
    printf("=== 3. Testing node deletion function ===\n");
    
    // 测试删除叶子节点
    printf("Attempting to delete leaf node 3...\n");
    deletenode(&root, 3);
    
    // 测试删除带有两个孩子的节点
    printf("Attempting to delete node 15 (has two children)...\n");
    deletenode(&root, 15);

    // 测试删除不存在的节点
    printf("Attempting to delete non-existent node 100...\n");
    deletenode(&root, 100);
    printf("\n");
    // ======================================================

    // 先序线索化与遍历 (验证删除操作后，树的结构是否依然正确)
    printf("=== 4. Testing preorder threading and traversal after deletion ===\n");
    createpreorderthread(root);
    printf("Preorder traversal result: ");
    traverpreorderthread(root);
    printf("\n\n");
    
    clearthread(root);
    free(head);

    // 后序线索化与遍历 (记得应用我们上一条沟通中修复的 createpostorderthread 逻辑)
    printf("=== 5. Testing postorder threading and traversal after deletion ===\n");
    createpostorderthread(root);
    printf("Postorder traversal result (reverse order): ");
    traverpostorderthread(root);
    printf("\n\n");

    // 释放资源
    printf("=== 6. Cleaning up memory ===\n");
    clearthread(root);
    freetree(root);
    free(head);
    printf("All memory freed, program exiting normally.\n");
    sleep(1); // 确保输出完整显示后再退出
    return 0;
}