#define _CRT_SECURE_NO_WARNINGS
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
#define LOCATION_SIZE 13
#define WORKSPACE_PATH "E:\\desktop\\Program_and_code\\C-Language-Files\\Visual School\\Basical Program Design\\final work (Program design base)\\Text\\"
#define MAX_PATH 260

typedef struct char_node
{
    char ch;
    int row;
    int column;
    char* location;
    struct char_node* next;
} char_node;

typedef struct key_node
{
    int length;
    char ch;
    char_node* char_nodes;
    struct key_node* next;
} key_node;

// ========== 全局变量 ==========
key_node* current_cipher_key = NULL;  // 当前使用的密钥
char current_key_text[MAXPASSAGELENGTH + 1] = { 0 };  // 当前密钥文本
int key_node_length = 0;  // 密钥节点数量
int text_length = 0;      // 文本长度

// ========== 辅助函数声明 ==========
int safe_digit_input(int front, int rear);
bool isvalid_char(char ch);
char find_last_invalid_char(const char* text);
bool isvalid_text(const char* text);
void redraw(const char* text, int length, int max_length, bool show_cursor);
char* char_input(FILE* fp, int max_length, bool show_warnings);
void clear_input_buffer();
int key_offset(char checkch, key_node* head_key);
void add_char_node(key_node* key, char_node* new_char_node);
void add_key_node(key_node* tail, key_node* new_key_node);
key_node* create_new_key_node(char newch);
char_node* create_new_char_node(char ch, int row, int column);
char* generate_random_encrypttext(key_node* headkey, int encrypttext_length);
char* generate_random_text(int length);
key_node* generate_cipherkey(const char* passage);
char_node* rand_char_loc(int key_offset, key_node* headkey);
char* encrypt_text(const char* raw_text, key_node* headkey);
char decrypt_char(const char* encrypt_loc, key_node* headkey);
char* decrypt_text(const char* encry_text, key_node* headkey);
void free_key_nodes(key_node* head);
void display_key_nodes(key_node* head);
void display_key_nodes_full(key_node* head);
void save_to_file(const char* filename, const char* title, const char* content);
void display_menu();
void handle_generate_key();
void handle_manual_encrypt();
void handle_auto_encrypt();
void handle_manual_decrypt();
void handle_auto_decrypt();
void handle_view_key();
void setup_workspace();
void show_welcome_screen();

// ========== 工具函数实现 ==========
int safe_digit_input(int front, int rear)
{
    int num;
    while (true)
    {
        if (scanf("%d", &num) != 1)
        {
            printf("Invalid input. Please enter an integer between %d and %d: ", front, rear);
            clear_input_buffer();
        }
        else if (num < front || num > rear)
        {
            printf("Input out of range. Please enter an integer between %d and %d: ", front, rear);
            clear_input_buffer();
        }
        else
        {
            clear_input_buffer();
            return num;
        }
    }
}

void clear_input_buffer()
{
    while (getchar() != '\n');
}

int length_to_row(int index)
{
    if (index <= 0) return 0;
    return (index - 1) / COL;
}

int length_to_col(int index)
{
    if (index <= 0) return 0;
    return (index - 1) % COL;
}

bool isvalid_char(char ch)
{
    if (isalpha(ch) || isdigit(ch) || ch == ' ' || ch == '.' ||
        ch == ',' || ch == '!' || ch == '?' || ch == '-' ||
        ch == '_' || ch == '\n' || ch == ';' || ch == ':' ||
        ch == '(' || ch == ')' || ch == '[' || ch == ']' ||
        ch == '{' || ch == '}' || ch == '\'' || ch == '\"' ||
        ch == '@' || ch == '#' || ch == '$' || ch == '%' ||
        ch == '^' || ch == '&' || ch == '*' || ch == '+' ||
        ch == '=' || ch == '<' || ch == '>')
        return true;
    else
        return false;
}

char find_last_invalid_char(const char* text)
{
    if (!text || !*text) return '\0';

    const char* ptr = text + strlen(text) - 1;
    while (ptr >= text)
    {
        if (!isvalid_char(*ptr))
        {
            return *ptr;
        }
        ptr--;
    }
    return '\0';
}

bool isvalid_text(const char* text)
{
    if (!text) return false;
    return find_last_invalid_char(text) == '\0';
}

void redraw(const char* text, int length, int max_length, bool show_cursor)
{
    system("cls");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                 TEXT INPUT CONSOLE                       ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║ Enter text below (max %d chars). Invalid chars in red:  ║\n", max_length);
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║ ");

    // 显示文本内容
    for (int i = 0; i < length; i++)
    {
        if (!isvalid_char(text[i]))
        {
            printf("\033[31m%c\033[0m", text[i]);
        }
        else
        {
            printf("%c", text[i]);
        }
    }

    if (show_cursor)
        printf("█");  // 光标
    else
        printf(" ");

    // 填充剩余空间
    int remaining = 55 - length - 1;
    for (int i = 0; i < remaining; i++)
        printf(" ");

    printf("║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║ STATUS: ");

    if (length == 0)
    {
        printf("Ready for input");
        int spaces = 55 - 15;
        for (int i = 0; i < spaces; i++) printf(" ");
    }
    else
    {
        char last_invalid = find_last_invalid_char(text);
        if (last_invalid != '\0')
        {
            printf("Invalid char: \033[31m%c\033[0m | Remaining: %d",
                last_invalid, max_length - length);
            int spaces = 55 - (40 + 3);
            for (int i = 0; i < spaces; i++) printf(" ");
        }
        else
        {
            printf("✓ All chars valid | Remaining: %d | Press ENTER to finish",
                max_length - length);
            int spaces = 55 - (53 + 3);
            for (int i = 0; i < spaces; i++) printf(" ");
        }
    }
    printf("║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    printf("\nControls: Type text | Backspace to delete | ENTER to finish\n");
    printf("          Invalid characters are shown in red.\n");
}

char* char_input(FILE* fp, int max_length, bool show_warnings)
{
    static char text[MAXTEXTLENGTH + 1] = { 0 };
    int current_length = 0;

    // 清除之前的输入
    memset(text, 0, sizeof(text));
    text_length = 0;

    redraw(text, current_length, max_length, true);

    while (true)
    {
        int ch = _getch();

        if (ch == '\r')  // Enter key
        {
            if (current_length == 0 && show_warnings)
            {
                printf("\n\nWarning: Text is empty. Press Enter again to continue or type something.\n");
                continue;
            }

            if (isvalid_text(text) || !show_warnings)
            {
                break;
            }
            else
            {
                printf("\n\nWarning: Invalid characters present. ");
                printf("Press Enter again to accept anyway, or Backspace to edit.\n");

                // 等待用户决定
                int confirm = _getch();
                if (confirm == '\r')
                {
                    break;  // 强制接受
                }
                else if (confirm == 8)  // Backspace
                {
                    continue;  // 继续编辑
                }
            }
        }
        else if (ch == 8 && current_length > 0)  // Backspace
        {
            current_length--;
            text[current_length] = '\0';
            text_length = current_length;
        }
        else if (current_length < max_length)
        {
            // 允许输入任何字符
            text[current_length] = (char)ch;
            current_length++;
            text[current_length] = '\0';
            text_length = current_length;
        }

        redraw(text, current_length, max_length, true);
    }

    return text;
}

int key_offset(char checkch, key_node* head_key)
{
    if (key_node_length == 0 || !head_key) return -1;

    key_node* p = head_key;
    int key_index = 0;

    while (p)
    {
        if (checkch == p->ch)
        {
            return key_index;
        }
        p = p->next;
        key_index++;
    }
    return -1;
}

void add_char_node(key_node* key, char_node* new_char_node)
{
    if (!key || !new_char_node) return;

    new_char_node->next = key->char_nodes;
    key->char_nodes = new_char_node;
    key->length++;
}

void add_key_node(key_node* tail, key_node* new_key_node)
{
    if (!tail || !new_key_node) return;

    tail->next = new_key_node;
    new_key_node->next = NULL;
    key_node_length++;
}

key_node* create_new_key_node(char newch)
{
    key_node* new_key_node = (key_node*)malloc(sizeof(key_node));
    if (!new_key_node) return NULL;

    new_key_node->ch = newch;
    new_key_node->length = 0;
    new_key_node->char_nodes = NULL;
    new_key_node->next = NULL;

    return new_key_node;
}

char_node* create_new_char_node(char ch, int row, int column)
{
    char_node* new_char_node = (char_node*)malloc(sizeof(char_node));
    if (!new_char_node) return NULL;

    new_char_node->ch = ch;
    new_char_node->row = row;
    new_char_node->column = column;
    new_char_node->location = (char*)malloc(LOCATION_SIZE * sizeof(char));
    if (!new_char_node->location)
    {
        free(new_char_node);
        return NULL;
    }

    snprintf(new_char_node->location, LOCATION_SIZE, "(%d,%d)", row, column);
    new_char_node->next = NULL;

    return new_char_node;
}

char* generate_random_encrypttext(key_node* headkey, int encrypttext_length)
{
    if (!headkey || encrypttext_length <= 0 || key_node_length <= 0)
        return NULL;

    char* encrypt_text = (char*)malloc(encrypttext_length * (LOCATION_SIZE + 1) + 1);
    if (!encrypt_text) return NULL;

    char* current_pos = encrypt_text;

    for (int i = 0; i < encrypttext_length; i++)
    {
        if (i > 0) {
            *current_pos = ' ';
            current_pos++;
        }

        int key_index = rand() % key_node_length;
        key_node* current_key = headkey;

        for (int j = 0; j < key_index && current_key; j++)
        {
            current_key = current_key->next;
        }

        if (!current_key || current_key->length == 0)
        {
            strcpy(current_pos, "(0,0)");
            current_pos += 5;
            continue;
        }

        int char_index = rand() % current_key->length;
        char_node* current_char = current_key->char_nodes;

        for (int j = 0; j < char_index && current_char; j++)
        {
            current_char = current_char->next;
        }

        if (current_char)
        {
            strcpy(current_pos, current_char->location);
            current_pos += strlen(current_char->location);
        }
        else
        {
            strcpy(current_pos, "(0,0)");
            current_pos += 5;
        }
    }

    *current_pos = '\0';
    return encrypt_text;
}

char* generate_random_text(int length)
{
    if (length <= 0) return NULL;

    static const char valid_chars[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789 .,!?-_;:()[]{}'\"\n@#$%^&*+=<>";

    int num_valid = (int)strlen(valid_chars);
    char* text = (char*)malloc((length + 1) * sizeof(char));

    if (!text) return NULL;

    for (int i = 0; i < length; i++)
    {
        text[i] = valid_chars[rand() % num_valid];
    }

    text[length] = '\0';
    return text;
}

key_node* generate_cipherkey(const char* passage)
{
    if (!passage || !*passage) return NULL;

    key_node_length = 0;
    int index = 0;
    const char* temp_char = passage;

    // 创建第一个key节点
    key_node* head = create_new_key_node(*temp_char);
    if (!head) return NULL;

    key_node* tail = head;
    int row = length_to_row(index + 1);
    int col = length_to_col(index + 1);

    char_node* new_char_node = create_new_char_node(*temp_char, row, col);
    if (!new_char_node)
    {
        free(head);
        return NULL;
    }

    add_char_node(head, new_char_node);
    temp_char++;
    index++;
    key_node_length++;

    // 处理剩余字符
    while (*temp_char != '\0')
    {
        int offset = key_offset(*temp_char, head);

        if (offset == -1)  // 新字符
        {
            key_node* new_key_node = create_new_key_node(*temp_char);
            if (!new_key_node)
            {
                return head;
            }

            add_key_node(tail, new_key_node);
            tail = new_key_node;

            row = length_to_row(index + 1);
            col = length_to_col(index + 1);

            new_char_node = create_new_char_node(*temp_char, row, col);
            if (!new_char_node)
            {
                temp_char++;
                index++;
                continue;
            }

            add_char_node(new_key_node, new_char_node);
        }
        else  // 已存在的字符
        {
            key_node* temp_key = head;
            for (int i = 0; i < offset && temp_key; i++)
            {
                temp_key = temp_key->next;
            }

            if (temp_key)
            {
                row = length_to_row(index + 1);
                col = length_to_col(index + 1);

                new_char_node = create_new_char_node(*temp_char, row, col);
                if (!new_char_node)
                {
                    temp_char++;
                    index++;
                    continue;
                }

                add_char_node(temp_key, new_char_node);
            }
        }

        temp_char++;
        index++;
    }

    return head;
}

char_node* rand_char_loc(int key_offset, key_node* headkey)
{
    if (!headkey || key_offset < 0) return NULL;

    key_node* temp_key = headkey;
    for (int i = 0; i < key_offset && temp_key; i++)
    {
        temp_key = temp_key->next;
    }

    if (!temp_key || temp_key->length == 0) return NULL;

    int char_offset = rand() % temp_key->length;
    char_node* temp_char = temp_key->char_nodes;

    for (int i = 0; i < char_offset && temp_char; i++)
    {
        temp_char = temp_char->next;
    }

    return temp_char;
}

char* encrypt_text(const char* raw_text, key_node* headkey)
{
    if (!raw_text || !headkey) return NULL;

    int text_len = (int)strlen(raw_text);
    if (text_len == 0) return NULL;

    char* encry_text = (char*)malloc(text_len * (LOCATION_SIZE + 1) + 1);
    if (!encry_text) return NULL;

    char* temp_p = encry_text;
    const char* temp_char = raw_text;
    int is_first = 1;

    while (*temp_char != '\0')
    {
        int offset = key_offset(*temp_char, headkey);

        if (!is_first) {
            *temp_p = ' ';
            temp_p++;
        }

        if (offset >= 0)
        {
            char_node* temp_char_node = rand_char_loc(offset, headkey);
            if (temp_char_node)
            {
                strcpy(temp_p, temp_char_node->location);
                temp_p += strlen(temp_char_node->location);
            }
            else
            {
                strcpy(temp_p, "(0,0)");
                temp_p += 5;
            }
        }
        else
        {
            strcpy(temp_p, "(0,0)");
            temp_p += 5;
        }

        is_first = 0;
        temp_char++;
    }

    *temp_p = '\0';
    return encry_text;
}

char decrypt_char(const char* encrypt_loc, key_node* headkey)
{
    if (!encrypt_loc || !headkey) return '\0';

    key_node* temp_key = headkey;

    while (temp_key)
    {
        char_node* temp_char = temp_key->char_nodes;

        while (temp_char)
        {
            if (strcmp(temp_char->location, encrypt_loc) == 0)
            {
                return temp_char->ch;
            }
            temp_char = temp_char->next;
        }
        temp_key = temp_key->next;
    }

    return '\0';
}

char* decrypt_text(const char* encry_text, key_node* headkey)
{
    if (!encry_text || !headkey) return NULL;

    char* text_copy=(char*)malloc(sizeof(encry_text));
    strcpy(text_copy,encry_text);
    if (!text_copy) return NULL;

    int max_chars = (int)strlen(encry_text) / 3 + 1;
    char* decry_text = (char*)malloc(max_chars + 1);
    if (!decry_text) {
        free(text_copy);
        return NULL;
    }

    char* result_ptr = decry_text;
    char* token = strtok(text_copy, " ");

    while (token != NULL)
    {
        char decrypted_char = decrypt_char(token, headkey);
        if (decrypted_char != '\0') {
            *decry_text = decrypted_char;
        }
        else {
            *decry_text = '?';
        }
        decry_text++;
        token = strtok(NULL, " ");
    }

    *decry_text = '\0';
    free(text_copy);
    return result_ptr;
}

void free_key_nodes(key_node* head)
{
    key_node* current_key = head;

    while (current_key)
    {
        char_node* current_char = current_key->char_nodes;

        while (current_char)
        {
            char_node* next_char = current_char->next;
            if (current_char->location)
            {
                free(current_char->location);
            }
            free(current_char);
            current_char = next_char;
        }

        key_node* next_key = current_key->next;
        free(current_key);
        current_key = next_key;
    }
}

void display_key_nodes(key_node* head)
{
    if (!head)
    {
        printf("No cipher key to display.\n");
        return;
    }

    printf("\nCipher Key Summary:\n");
    printf("===================\n");

    key_node* current_key = head;
    int key_index = 0;
    int total_locations = 0;

    while (current_key)
    {
        printf("Key[%d]: '%c' (appears %d times)\n",
            key_index, current_key->ch, current_key->length);
        current_key = current_key->next;
        key_index++;
    }

    printf("Total unique characters: %d\n", key_index);
}

void display_key_nodes_full(key_node* head)
{
    if (!head)
    {
        printf("No cipher key to display.\n");
        return;
    }

    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                FULL CIPHER KEY STRUCTURE                ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");

    key_node* current_key = head;
    int key_index = 0;
    int total_locations = 0;

    while (current_key)
    {
        printf("║ Key[%2d]: Character '%c' (appears %d times)             ║\n",
            key_index, current_key->ch, current_key->length);

        char_node* current_char = current_key->char_nodes;
        int char_index = 0;

        while (current_char && char_index < 3)
        {
            printf("║        Location[%2d]: %-10s                     ║\n",
                char_index, current_char->location);
            current_char = current_char->next;
            char_index++;
            total_locations++;
        }

        if (current_char)
        {
            printf("║        ... and %d more locations                      ║\n",
                current_key->length - 3);
            total_locations += current_key->length - 3;
        }

        if (current_key->next)
        {
            printf("╠══════════════════════════════════════════════════════════╣\n");
        }

        current_key = current_key->next;
        key_index++;
    }

    printf("║ SUMMARY: %d unique characters, %d total locations         ║\n",
        key_index, total_locations);
    printf("╚══════════════════════════════════════════════════════════╝\n");
}

void save_to_file(const char* filename, const char* title, const char* content)
{
    char full_path[MAX_PATH];
    snprintf(full_path, MAX_PATH, "%s%s", WORKSPACE_PATH, filename);

    FILE* fp = fopen(full_path, "a");
    if (!fp)
    {
        printf("Error: Cannot open file %s\n", full_path);
        return;
    }

    fprintf(fp, "\n%s\n", title);
    fprintf(fp, "%s\n", "==========================================");
    fprintf(fp, "%s\n\n", content);
    fclose(fp);

    printf("File saved to: %s\n", full_path);
}

void setup_workspace()
{
    // 检查工作空间目录是否存在，如果不存在则创建
    printf("Setting up workspace at: %s\n", WORKSPACE_PATH);
    printf("This is where all encrypted/decrypted files will be saved.\n\n");
}

void show_welcome_screen()
{
    system("cls");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║               INTERACTIVE ENCRYPTION SYSTEM             ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║ Workspace: %-41s ║\n", WORKSPACE_PATH);
    printf("║                                                          ║\n");
    printf("║ Features:                                                ║\n");
    printf("║ • Generate cipher keys from text                         ║\n");
    printf("║ • Encrypt/decrypt using current key                      ║\n");
    printf("║ • Manual and automatic operations                        ║\n");
    printf("║ • Save encrypted/decrypted files to workspace            ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    printf("Press any key to continue...");
    _getch();
}

void display_menu()
{
    system("cls");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                 MAIN MENU                               ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║ a. Generate/Regenerate Cipher Key                       ║\n");
    printf("║ b. Manual Text Encryption                               ║\n");
    printf("║ c. Auto-Generate & Encrypt Text                         ║\n");
    printf("║ d. Manual Decryption (from input/file)                  ║\n");
    printf("║ e. Auto-Generate & Decrypt Encrypted Text               ║\n");
    printf("║ f. View Current Key Structure                           ║\n");
    printf("║ g. Exit                                                 ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");

    if (current_cipher_key)
    {
        printf("║ Current Key: Loaded (%d unique chars)                 ║\n", key_node_length);
    }
    else
    {
        printf("║ Current Key: NOT LOADED (Use option 'a' first)        ║\n");
    }
    printf("╚══════════════════════════════════════════════════════════╝\n");
    printf("\nChoose option (a-g): ");
}

void handle_generate_key()
{
    system("cls");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║               GENERATE/REGENERATE KEY                   ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    printf("How would you like to generate the cipher key?\n");
    printf("1. Manual input (type text)\n");
    printf("2. Auto-generate random text\n");
    printf("3. Load from file\n");
    printf("0. Cancel\n");
    printf("Choose (0-3): ");

    int choice = safe_digit_input(0, 3);

    if (choice == 0) return;

    char* key_text = NULL;
    char filename[MAX_PATH];

    switch (choice)
    {
    case 1:  // Manual input
        printf("\nEnter text to use as cipher key (max %d chars):\n", MAXPASSAGELENGTH);
        key_text = char_input(NULL, MAXPASSAGELENGTH, false);
        break;

    case 2:  // Auto-generate
    {
        printf("\nEnter length of random text to generate (10-%d): ", MAXPASSAGELENGTH);
        int length = safe_digit_input(10, MAXPASSAGELENGTH);
        key_text = generate_random_text(length);
        printf("\nGenerated text: %s\n", key_text);
        break;
    }
    case 3:  // Load from file
    {
        printf("\nEnter filename (in workspace): ");
        scanf("%255s", filename);
        clear_input_buffer();

        char full_path[MAX_PATH];
        snprintf(full_path, MAX_PATH, "%s%s", WORKSPACE_PATH, filename);

        FILE* fp = fopen(full_path, "r");
        if (!fp)
        {
            printf("Error: Cannot open file %s\n", full_path);
            return;
        }

        key_text = (char*)malloc(MAXPASSAGELENGTH + 1);
        if (!key_text)
        {
            fclose(fp);
            return;
        }

        if (fgets(key_text, MAXPASSAGELENGTH, fp) == NULL)
        {
            printf("Error: Failed to read from file\n");
            free(key_text);
            fclose(fp);
            return;
        }

        // Remove newline if present
        size_t len = strlen(key_text);
        if (len > 0 && key_text[len - 1] == '\n')
            key_text[len - 1] = '\0';

        fclose(fp);
        printf("\nLoaded text from %s: %s\n", filename, key_text);
        break;
        }
    }
    if (!key_text || strlen(key_text) == 0)
    {
        printf("Error: No text provided for key generation\n");
        return;
    }

    // Free previous key if exists
    if (current_cipher_key)
    {
        free_key_nodes(current_cipher_key);
        current_cipher_key = NULL;
    }

    // Generate new key
    printf("\nGenerating cipher key...\n");
    current_cipher_key = generate_cipherkey(key_text);

    if (!current_cipher_key)
    {
        printf("Error: Failed to generate cipher key!\n");
        return;
    }

    // Save key text
    strncpy(current_key_text, key_text, MAXPASSAGELENGTH);

    printf("✓ Cipher key generated successfully!\n");
    printf("  Unique characters: %d\n", key_node_length);
    printf("  Key text length: %zu\n", strlen(key_text));

    // Ask if user wants to save the key text to file
    printf("\nSave key text to file? (y/n): ");
    char save_choice = _getch();
    printf("%c\n", save_choice);

    if (save_choice == 'y' || save_choice == 'Y')
    {
        time_t now = time(NULL);
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y%m%d_%H%M%S", localtime(&now));

        char filename[100];
        snprintf(filename, sizeof(filename), "key_text_%s.txt", time_str);

        save_to_file(filename, "CIPHER KEY TEXT", key_text);
        printf("Key text saved to file.\n");
    }
    else
    {
        printf("Key text Don't saved to file.");
    }

    // Free temporary key_text if it was allocated
    if (choice == 2 || choice == 3)
    {
        free(key_text);
    }

    printf("\nPress any key to continue...");
    _getch();
}

void handle_manual_encrypt()
{
    system("cls");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║               MANUAL TEXT ENCRYPTION                    ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    if (!current_cipher_key)
    {
        printf("Error: No cipher key loaded! Please generate a key first (option 'a').\n");
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    printf("Using current cipher key (%d unique characters)\n", key_node_length);

    printf("\nEnter text to encrypt (max %d chars):\n", MAXTEXTLENGTH);
    char* plain_text = char_input(NULL, MAXTEXTLENGTH, false);

    if (strlen(plain_text) == 0)
    {
        printf("Error: No text to encrypt\n");
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    printf("\nEncrypting text...\n");
    char* encrypted = encrypt_text(plain_text, current_cipher_key);

    if (!encrypted)
    {
        printf("Error: Failed to encrypt text!\n");
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    // Display results
    printf("\n═══════════════════════════════════════════════\n");
    printf("Original text (%d chars):\n", (int)strlen(plain_text));
    printf("%s\n", plain_text);

    printf("\nEncrypted text (coordinates):\n");
    printf("%s\n", encrypted);

    // Count coordinates
    int coord_count = 0;
    const char* ptr = encrypted;
    while (*ptr)
    {
        if (*ptr == '(') coord_count++;
        ptr++;
    }
    printf("\nTotal coordinates: %d\n", coord_count);
    printf("═══════════════════════════════════════════════\n");

    // Save to file
    printf("\nSave encrypted text to file? (y/n): ");
    char save_choice = _getch();
    printf("%c\n", save_choice);

    if (save_choice == 'y' || save_choice == 'Y')
    {
        time_t now = time(NULL);
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y%m%d_%H%M%S", localtime(&now));

        char filename[100];
        snprintf(filename, sizeof(filename), "encrypted_%s.txt", time_str);

        // Save both original and encrypted
        char content[2 * MAXTEXTLENGTH * LOCATION_SIZE];
        snprintf(content, sizeof(content), "Original: %s\n\nEncrypted: %s", plain_text, encrypted);

        save_to_file(filename, "MANUAL ENCRYPTION", content);
        printf("Encrypted text saved to file.\n");
    }

    free(encrypted);

    printf("\nPress any key to continue...");
    _getch();
}

void handle_auto_encrypt()
{
    system("cls");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║            AUTO-GENERATE & ENCRYPT TEXT                 ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    if (!current_cipher_key)
    {
        printf("Error: No cipher key loaded! Please generate a key first (option 'a').\n");
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    printf("Using current cipher key (%d unique characters)\n", key_node_length);

    printf("\nEnter length of random text to generate (5-%d): ", MAXTEXTLENGTH);
    int length = safe_digit_input(5, MAXTEXTLENGTH);

    printf("\nGenerating random text...\n");
    char* plain_text = generate_random_text(length);

    if (!plain_text)
    {
        printf("Error: Failed to generate random text!\n");
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    printf("Generated text: %s\n", plain_text);

    printf("\nEncrypting text...\n");
    char* encrypted = encrypt_text(plain_text, current_cipher_key);

    if (!encrypted)
    {
        printf("Error: Failed to encrypt text!\n");
        free(plain_text);
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    // Display results
    printf("\n═══════════════════════════════════════════════\n");
    printf("Original text (%d chars):\n", length);
    printf("%s\n", plain_text);

    printf("\nEncrypted text (coordinates):\n");
    printf("%s\n", encrypted);

    // Count coordinates
    int coord_count = 0;
    const char* ptr = encrypted;
    while (*ptr)
    {
        if (*ptr == '(') coord_count++;
        ptr++;
    }
    printf("\nTotal coordinates: %d\n", coord_count);
    printf("═══════════════════════════════════════════════\n");

    // Save to file
    time_t now = time(NULL);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y%m%d_%H%M%S", localtime(&now));

    char filename[100];
    snprintf(filename, sizeof(filename), "auto_encrypted_%s.txt", time_str);

    // Save both original and encrypted
    char content[2 * MAXTEXTLENGTH * LOCATION_SIZE];
    snprintf(content, sizeof(content), "Original: %s\n\nEncrypted: %s", plain_text, encrypted);

    save_to_file(filename, "AUTO ENCRYPTION", content);
    printf("\nEncrypted text saved to file.\n");

    free(plain_text);
    free(encrypted);

    printf("\nPress any key to continue...");
    _getch();
}

void handle_manual_decrypt()
{
    system("cls");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║               MANUAL DECRYPTION                         ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    if (!current_cipher_key)
    {
        printf("Error: No cipher key loaded! Please generate a key first (option 'a').\n");
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    printf("Using current cipher key (%d unique characters)\n", key_node_length);

    printf("\nHow would you like to provide encrypted text?\n");
    printf("1. Manual input (coordinates)\n");
    printf("2. Load from file\n");
    printf("0. Cancel\n");
    printf("Choose (0-2): ");

    int choice = safe_digit_input(0, 2);

    if (choice == 0) return;

    char* encrypted_text = NULL;
    char filename[MAX_PATH];
    char full_path[MAX_PATH];

    switch (choice)
    {
    case 1:  // Manual input
        printf("\nEnter encrypted text (coordinates separated by spaces):\n");
        printf("Example: (1,2) (3,4) (5,6)\n");
        encrypted_text = char_input(NULL, MAXTEXTLENGTH * LOCATION_SIZE, false);
        break;

    case 2:  // Load from file
        printf("\nEnter filename (in workspace): ");
        scanf("%255s", filename);
        clear_input_buffer();

        snprintf(full_path, MAX_PATH, "%s%s", WORKSPACE_PATH, filename);

        FILE* fp = fopen(full_path, "r");
        if (!fp)
        {
            printf("Error: Cannot open file %s\n", full_path);
            printf("\nPress any key to continue...");
            _getch();
            return;
        }

        encrypted_text = (char*)malloc(MAXTEXTLENGTH * LOCATION_SIZE + 1);
        if (!encrypted_text)
        {
            fclose(fp);
            return;
        }

        // Read the entire file (simplified)
        char line[256];
        encrypted_text[0] = '\0';

        while (fgets(line, sizeof(line), fp))
        {
            // Look for coordinates pattern
            char* coord_start = strchr(line, '(');
            if (coord_start)
            {
                // Extract coordinates (simplified)
                strcat(encrypted_text, line);
            }
        }

        fclose(fp);

        // Clean up the text (remove newlines)
        char* src = encrypted_text, * dst = encrypted_text;
        while (*src)
        {
            if (*src != '\n' && *src != '\r')
                *dst++ = *src;
            src++;
        }
        *dst = '\0';

        printf("\nLoaded encrypted text from %s\n", filename);
        break;
    }

    if (!encrypted_text || strlen(encrypted_text) == 0)
    {
        printf("Error: No encrypted text provided\n");
        if (choice == 2) free(encrypted_text);
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    printf("\nDecrypting text...\n");
    printf("Encrypted text: %s\n", encrypted_text);

    char* decrypted = decrypt_text(encrypted_text, current_cipher_key);

    if (!decrypted)
    {
        printf("Error: Failed to decrypt text!\n");
        if (choice == 2) free(encrypted_text);
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    // Display results
    printf("\n═══════════════════════════════════════════════\n");
    printf("Encrypted text:\n");
    printf("%s\n", encrypted_text);

    printf("\nDecrypted text (%d chars):\n", (int)strlen(decrypted));
    printf("%s\n", decrypted);
    printf("═══════════════════════════════════════════════\n");

    // Save to file
    printf("\nSave decrypted text to file? (y/n): ");
    char save_choice = _getch();
    printf("%c\n", save_choice);

    if (save_choice == 'y' || save_choice == 'Y')
    {
        time_t now = time(NULL);
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y%m%d_%H%M%S", localtime(&now));

        char dec_filename[100];
        snprintf(dec_filename, sizeof(dec_filename), "decrypted_%s.txt", time_str);

        // Save both encrypted and decrypted
        char content[2 * MAXTEXTLENGTH * LOCATION_SIZE];
        snprintf(content, sizeof(content), "Encrypted: %s\n\nDecrypted: %s", encrypted_text, decrypted);

        save_to_file(dec_filename, "MANUAL DECRYPTION", content);
        printf("Decrypted text saved to file.\n");
    }

    free(decrypted);
    if (choice == 2) free(encrypted_text);

    printf("\nPress any key to continue...");
    _getch();
}

void handle_auto_decrypt()
{
    system("cls");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║          AUTO-GENERATE & DECRYPT ENCRYPTED TEXT         ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    if (!current_cipher_key)
    {
        printf("Error: No cipher key loaded! Please generate a key first (option 'a').\n");
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    printf("Using current cipher key (%d unique characters)\n", key_node_length);

    printf("\nEnter length of random encrypted text to generate (5-50): ");
    int length = safe_digit_input(5, 50);

    printf("\nGenerating random encrypted text...\n");
    char* encrypted = generate_random_encrypttext(current_cipher_key, length);

    if (!encrypted)
    {
        printf("Error: Failed to generate encrypted text!\n");
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    printf("Generated encrypted text: %s\n", encrypted);

    printf("\nDecrypting text...\n");
    char* decrypted = decrypt_text(encrypted, current_cipher_key);

    if (!decrypted)
    {
        printf("Error: Failed to decrypt text!\n");
        free(encrypted);
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    // Display results
    printf("\n═══════════════════════════════════════════════\n");
    printf("Generated encrypted text (%d coordinates):\n", length);
    printf("%s\n", encrypted);

    printf("\nDecrypted text (%d chars):\n", (int)strlen(decrypted));
    printf("%s\n", decrypted);
    printf("═══════════════════════════════════════════════\n");

    // Save to file
    time_t now = time(NULL);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y%m%d_%H%M%S", localtime(&now));

    char filename[100];
    snprintf(filename, sizeof(filename), "auto_decrypted_%s.txt", time_str);

    // Save both encrypted and decrypted
    char content[2 * MAXTEXTLENGTH * LOCATION_SIZE];
    snprintf(content, sizeof(content), "Encrypted: %s\n\nDecrypted: %s", encrypted, decrypted);

    save_to_file(filename, "AUTO DECRYPTION", content);
    printf("\nResults saved to file.\n");

    printf("\nNote: This demonstrates the decryption process using randomly\n");
    printf("generated coordinates. Since coordinates are random, the\n");
    printf("decrypted text may not be meaningful.\n");

    free(encrypted);
    free(decrypted);

    printf("\nPress any key to continue...");
    _getch();
}

void handle_view_key()
{
    system("cls");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║               VIEW CURRENT KEY STRUCTURE                ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    if (!current_cipher_key)
    {
        printf("No cipher key loaded. Please generate a key first (option 'a').\n");
        printf("\nPress any key to continue...");
        _getch();
        return;
    }

    printf("Current Cipher Key Information:\n");
    printf("═══════════════════════════════════════════════\n");
    printf("Key text length: %zu\n", strlen(current_key_text));
    printf("Unique characters in key: %d\n", key_node_length);

    printf("\nKey text preview (first 100 chars):\n");
    if (strlen(current_key_text) > 100)
    {
        char preview[101];
        strncpy(preview, current_key_text, 100);
        preview[100] = '\0';
        printf("%s...\n", preview);
    }
    else
    {
        printf("%s\n", current_key_text);
    }

    printf("\nFull key structure:\n");
    display_key_nodes_full(current_cipher_key);

    printf("\nPress any key to continue...");
    _getch();
}

int main()
{
    srand((unsigned int)time(NULL));

    setup_workspace();
    show_welcome_screen();

    bool running = true;

    while (running)
    {
        display_menu();

        char choice;
        scanf("%c", &choice);
        clear_input_buffer();

        switch (tolower(choice))
        {
        case 'a':
            handle_generate_key();
            break;
        case 'b':
            handle_manual_encrypt();
            break;
        case 'c':
            handle_auto_encrypt();
            break;
        case 'd':
            handle_manual_decrypt();
            break;
        case 'e':
            handle_auto_decrypt();
            break;
        case 'f':
            handle_view_key();
            break;
        case 'g':
            printf("\nExiting system. Cleaning up...\n");
            if (current_cipher_key)
            {
                free_key_nodes(current_cipher_key);
                current_cipher_key = NULL;
            }
            running = false;
            break;
        default:
            printf("Invalid option! Please choose a-g.\n");
            printf("\nPress any key to continue...");
            _getch();
            break;
        }
    }

    printf("\nGoodbye!\n");
    printf("All encrypted/decrypted files are saved in: %s\n", WORKSPACE_PATH);

    return 0;
}