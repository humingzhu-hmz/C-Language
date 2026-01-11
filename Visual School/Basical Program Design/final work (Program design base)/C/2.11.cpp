#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>

#define MAXTEXTLENGTH 100
#define MAXPASSAGELENGTH 400
#define ROW 20
#define COL 20

typedef struct char_node
{
    char ch;
    int row;
    int cloumn;
    char *location;//"(%d,%d)\0"1+4+1+4+1+1=13
    struct char_node  *next;
}char_node;

typedef struct key_node
{
    int length;
    char ch;
    char_node *char_nodes;
    struct key_node *next;
}key_node;

int key_node_length=0;
int text_length=0;
// ==========  Tool functions ==========
int safe_digitimput(int front,int rear)
{
    int num;
    while(true)
    {
        if(scanf("%d",&num)!=1)
        {
            printf("Invalid input. Please enter an integer between %d and %d: ",front,rear);
            while(getchar()!='\n');
        }
        else if(num<front || num>rear)
        {
            printf("Input out of range. Please enter an integer between %d and %d: ",front,rear);
            while(getchar()!='\n');
        }
        else
        {
            while(getchar()!='\n');
            return num;
        };
    }
}

// X*COL+Y+1=index(0<=y+1<=COL),=>x=(index-1)/col.
int length_to_row(int index)
{
    return (index-1)/COL;
}
int length_to_col(int index)
{
    return (index-1)%COL;
}
bool isvalid_char(char ch)
{
    if(isalpha(ch)||isdigit(ch)||ch==' '||ch=='.'||ch==','||ch=='!'||ch=='?'||ch=='-'||ch=='_'||ch=='\n')
        return true;
    else
        return false;
}

char find_last_invalid_char(char *text)
{
    char *find=text;
    while(*find!='\0')
    {
        find++;
    }
    find--;
    while(find>=text)
    {
        if(!isvalid_char(*find))
        {
            return *find;
        }
        find--;
    }
    return '\0';
}
bool isvalid_text(char*text)
{
    return find_last_invalid_char(text)=='\0';
}
void redraw(char *text,int length)
{
    system("cls");
    printf("Please input text (max length %d). Invalid characters will be highlighted:\n",MAXTEXTLENGTH);
    printf("Input content:");
    for(int i=0;i<length;i++)
    {
        if(!isvalid_char(text[i]))
        {
            printf("\033[31m%c\033[0m",text[i]);
        }
        else
        {
            printf("%c",text[i]);
        }
    }
    printf("|");
    printf("\nhint:");
    if(length==0)
    {
        printf("nothing");
        return;
    }
    char last_invalid_char=find_last_invalid_char(text);
    if(last_invalid_char!='\0')
    {
        printf("Latest invalid character detected: \033[31m%c\033[0m,please delete it.(remain %d)",last_invalid_char,MAXTEXTLENGTH-length);
    }
    else
    {
        printf("all characters are valid(remain %d)",MAXTEXTLENGTH-length);
    }
}
void pass_in_file(FILE*fp,char*text)
{
    fprintf(fp,"%s",text);
}
char* charimput(FILE *fp)
{
    char text[MAXTEXTLENGTH+1]={0};
    redraw(text,text_length);
    while(true)
    {
        int ch=_getch();
        if(ch=='\r'&&isvalid_text(text))
        {
            break;
        }
        else if(ch==8&&text_length>0)
        {
            text_length--;
        }
        else if(isvalid_char(ch)&&text_length<MAXTEXTLENGTH)
        {
            text[text_length]=ch;
            text_length++;
        }
        redraw(text,text_length);
    }
    pass_in_file(fp,text);
    return text;
}

int key_offset(char checkch,key_node *head_key)
{
    if(key_node_length==0) return -1;
    key_node*p=head_key;
    bool exit_key=false;
    int key_index=0;
    while(p)
    {
        if(checkch==(p->ch)) 
        {
            exit_key=true;
            break;
        }
        else
        {
            p=p->next;
            key_index++;
        }
    }
    return exit_key?key_index:-1;
}
void add_char_node(key_node*key_node,char_node* new_char_node)
{
    new_char_node->next=key_node->char_nodes;
    key_node->char_nodes=new_char_node;
    key_node->length++;
}
void add_key_node(key_node* tail,key_node* new_key_node)
{

    tail->next=new_key_node;
    new_key_node->next=NULL;
    key_node_length++;
}
key_node* create_new_key_node(char newch)
{
    key_node* new_key_node=(key_node*)malloc(sizeof(key_node));
    new_key_node->ch=newch;
    new_key_node->length=0;
    new_key_node->char_nodes=NULL;
    new_key_node->next=NULL;
    return new_key_node;
}
char_node* create_new_char_node(char ch,int row,int column)
{
    char_node* new_char_node=(char_node*)malloc(sizeof(char_node));
    new_char_node->ch=ch;
    new_char_node->row=row;
    new_char_node->cloumn=column;
    new_char_node->location = (char*)malloc(13*sizeof(char));
    sprintf(new_char_node->location,"(%d,%d)",row,column);
    new_char_node->next=NULL;
    return new_char_node;
}

char* generate_rand_encrypttext(int key_node_length,key_node* headkey,int encrypttext_length )
{
    
    char*encrypt_text=(char*)malloc(encrypttext_length*12*sizeof(char)+1*sizeof('\0'));
    int current_length=0;
    char_node*current_char_node;
    key_node* current_key_node;
    while(true)
    {
        int key_index=rand()%key_node_length;
        for(int i=0;i<key_index;i++)
        {
            current_key_node=current_key_node->next;
        }
        
        int char_index=rand()%current_key_node->length;
        current_char_node=current_key_node->char_nodes;
        for(int j=0;j<char_index;j++)
        {
            current_char_node=current_char_node->next;
        }
        if(current_length<encrypttext_length)
        {
            strncpy(encrypt_text,current_char_node->location,12);
            encrypt_text=encrypt_text+12;
            current_length++;
        }
        else{
            break;
        }
    }
    encrypt_text=encrypt_text-12*current_length;
    encrypt_text[encrypttext_length*12+1];
    return encrypt_text;
}
char* generate_passage_or_text(int length)
{
    
    char *passage=(char*)malloc((length+1)*sizeof(char));
    int current_length=0;
    char ch;
    while(current_length<length)
    {
        ch=rand()%256;
        if(isvalid_char(ch))
        {
            passage[current_length++]=ch;
        }
    }
    passage[current_length]='\0';
    return passage;
}

key_node *generate_cipherkey(char* passage)
{
    int index=0;
    char *temp_char=passage;
    char_node*new_char_node;
    key_node* new_key_node;
    int row=0,col=0;
    key_node*head=create_new_key_node(*temp_char);
    key_node*tail=head;
    new_char_node=create_new_char_node(*temp_char,row,col);
    add_char_node(head,new_char_node);
    temp_char++;
    index=1;
    key_node_length++;
    while(*temp_char!='\0')
    {
        int offset=key_offset(*temp_char,head);
        if(offset==-1)
        {
            new_key_node=create_new_key_node(*temp_char);
            add_key_node(tail,new_key_node);
            tail=new_key_node;
            row=length_to_row(index);
            col=length_to_col(index);
            new_char_node=create_new_char_node(*temp_char,row,col);
            add_char_node(new_key_node,new_char_node);
        }
        else
        {
            key_node*temp_key=head;
            for(int i=0;i<=offset;i++)
            {
                temp_key=temp_key->next;
            }
            row=length_to_row(index);
            col=length_to_col(index);
            new_char_node=create_new_char_node(*temp_char,row,col);
            add_char_node(temp_key,new_char_node);
        }
        temp_char++;
        index++;
    }
    return head;
}

char_node *rand_char_loc(int key_offset,key_node*headkey)
{
    key_node*temp_key=headkey;
    for(int i=0;i<key_offset;i++)
    {
        temp_key=temp_key->next;
    }
    int char_offset=rand()%(temp_key->length);
    char_node*temp_char=temp_key->char_nodes;
    for(int i=0;i<char_offset;i++)
    {
        temp_char=temp_char->next;
    }
    return temp_char;
}
char* encrypt_text(char *raw_text,key_node*headkey)
{
   
    char*encry_text=(char*)malloc(sizeof(char)*(text_length)*12+1);
    char*temp_p=encry_text;

    char*temp_char=raw_text;

    char_node*temp_char_node;
    while(*temp_char!='\0')
    {
        int offset=key_offset(*temp_char,headkey);
        temp_char_node=rand_char_loc(offset,headkey);
        strncpy(temp_p,temp_char_node->location,12);
        temp_p=temp_p+12;
        temp_char++;
    }
    *temp_p='\0';
    return encry_text;
}

char decrypt_char(char*encrypt_loc,key_node*headkey)
{
    key_node*temp_key=headkey;
    for(int i=0;i<key_node_length;i++)
    {
        char_node*temp_char=temp_key->char_nodes;
        for(int j=0;j<temp_key->length;j++)
        {
            if(strncmp(temp_char->location, encrypt_loc, 12) == 0)
                 return temp_char->ch;
            temp_char = temp_char->next;
        }
        temp_key = temp_key->next;
    }
    return '\0';
}
char* decrypt_text(char* encry_text,key_node*headkey)
{
    char*decry_text=(char*)malloc((text_length+1)*sizeof(char)+1);
    char*temp=encry_text;
    char*encry_loc=(char*)malloc(12*sizeof(char));
    encry_loc=encry_text;
    while(*encry_loc!='\0')
    {
        strncpy(encry_loc,temp,12);
        *decry_text=decrypt_char(encry_loc,headkey);
        temp=temp+12;
        decry_text++;
    }
    *decry_text='\0';
    decry_text=decry_text-text_length+1;
    return decry_text;
}


int main()
{
    int choice;
    int passage_len;
    srand((unsigned)time(NULL));

    system("cls");
    printf("====================================\n");
    printf("   Coordinate Cipher System\n");
    printf("====================================\n");

    /* ===== 1. 生成随机密钥文章 ===== */
    printf("Enter length of passage(key) (1-%d): ", MAXPASSAGELENGTH);
    passage_len = safe_digitimput(1, MAXPASSAGELENGTH);

    char *passage = generate_passage_or_text(passage_len);
    key_node *cipherkey = generate_cipherkey(passage);

    printf("\n[Key passage generated successfully]\n");

    char plaintext[MAXTEXTLENGTH + 1] = {0};
    char ciphertext[5000] = {0};
    char *decrypt_result = NULL;

    while (1)
    {
        printf("\n====================================\n");
        printf("1. Show key passage\n");
        printf("2. Encrypt text\n");
        printf("3. Decrypt text\n");
        printf("0. Exit\n");
        printf("------------------------------------\n");
        printf("Please choose: ");

        choice = safe_digitimput(0, 3);

        switch (choice)
        {
        case 1:
            printf("\n--- Key Passage ---\n");
            printf("%s\n", passage);
            break;

        case 2:
            {   
                printf("\nEnter plaintext (max %d chars):\n", MAXTEXTLENGTH);
                getchar();  // 吃掉残留换行
                fgets(plaintext, MAXTEXTLENGTH, stdin);
                plaintext[strcspn(plaintext, "\n")] = '\0';

                text_length = strlen(plaintext);
                char *enc = encrypt_text(plaintext, cipherkey);

                printf("\nEncrypted text:\n%s\n", enc);
                strcpy(ciphertext, enc);
                break;
            }
        case 3:
            { 
                if (strlen(ciphertext) == 0)
                {
                    printf("\n[Error] No ciphertext available. Encrypt first.\n");
                    break;
                }

                decrypt_result = decrypt_text(ciphertext, cipherkey);
                printf("\nDecrypted text:\n%s\n", decrypt_result);
                break;
            }
        case 0:
            { 
                printf("\nBye.\n");
                return 0;
            }
        }
    }
}
