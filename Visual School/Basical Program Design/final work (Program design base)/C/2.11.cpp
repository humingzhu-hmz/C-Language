//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <conio.h>
//#include <stdbool.h>
//#include <time.h>
//
//#define MAXTEXTLENGTH 100
//#define MAXPASSAGELENGTH 400
//#define ROW 20
//#define COL 20
//#define LOCATION_SIZE 13
//#define MAX_FILENAME 256
//
//typedef struct char_node {
//    char ch;
//    int row;
//    int column;
//    char location[LOCATION_SIZE];
//    struct char_node* next;
//} char_node;
//
//typedef struct key_node {
//    char ch;
//    int count;
//    char_node* locations;
//    struct key_node* next;
//} key_node;
//
//static key_node* cipher_key = NULL;
//static char key_text[MAXPASSAGELENGTH + 1] = { 0 };
//static int unique_chars = 0;
//
//void clear_buffer() { while (getchar() != '\n'); }
//
//int get_int(int min, int max) {
//    int value;
//    while (1) {
//        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
//            clear_buffer();
//            return value;
//        }
//        printf("invalid input,please try again: ");
//        clear_buffer();
//    }
//}
//
//char* read_from_file(const char* filename) {
//    FILE* fp = fopen(filename, "r");
//    if (!fp) {
//        printf("Error: Cannot open file %s\n", filename);
//        return NULL;
//    }
//
//    fseek(fp, 0, SEEK_END);
//    long size = ftell(fp);
//    fseek(fp, 0, SEEK_SET);
//
//    char* text = (char*)malloc(size + 1);
//    if (!text) {
//        fclose(fp);
//        return NULL;
//    }
//
//    size_t bytes_read = fread(text, 1, size, fp);
//    text[bytes_read] = '\0';
//
//    fclose(fp);
//    return text;
//}
//
//bool write_to_file(const char* filename, const char* content) {
//    FILE* fp = fopen(filename, "w");
//    if (!fp) {
//        printf("Error: Cannot create file %s\n", filename);
//        return false;
//    }
//
//    fprintf(fp, "%s", content);
//    fclose(fp);
//    return true;
//}
//
//bool is_valid_char(char ch) {
//    return isalnum(ch) || strchr(" .,!?-_;\n:()[]{}\'\"@#$%^&*+=<>", ch) != NULL;
//}
//
//void show_red(char ch) {
//    printf("\033[31m%c\033[0m", ch);
//}
//
//char_node* new_char_node(char ch, int index) {
//    char_node* node = (char_node*)malloc(sizeof(char_node));
//    if (!node) return NULL;
//
//    node->ch = ch;
//    node->row = (index - 1) / COL;
//    node->column = (index - 1) % COL;
//    snprintf(node->location, LOCATION_SIZE, "(%d,%d)", node->row, node->column);
//    node->next = NULL;
//
//    return node;
//}
//
//key_node* new_key_node(char ch) {
//    key_node* node = (key_node*)malloc(sizeof(key_node));
//    if (!node) return NULL;
//
//    node->ch = ch;
//    node->count = 0;
//    node->locations = NULL;
//    node->next = NULL;
//
//    return node;
//}
//
//key_node* find_key_node(char ch) {
//    key_node* current = cipher_key;
//    while (current) {
//        if (current->ch == ch) return current;
//        current = current->next;
//    }
//    return NULL;
//}
//
//void add_location(key_node* key, char_node* node) {
//    if (!key || !node) return;
//    node->next = key->locations;
//    key->locations = node;
//    key->count++;
//}
//
//void free_memory() {
//    key_node* key = cipher_key;
//    while (key) {
//        char_node* loc = key->locations;
//        while (loc) {
//            char_node* next = loc->next;
//            free(loc);
//            loc = next;
//        }
//        key_node* next_key = key->next;
//        free(key);
//        key = next_key;
//    }
//    cipher_key = NULL;
//    unique_chars = 0;
//    key_text[0] = '\0';
//}
//
//bool generate_cipher_key(const char* text) {
//    if (!text || !*text) return false;
//
//    for (int i = 0; text[i] != '\0'; i++) {
//        if (!is_valid_char(text[i])) {
//            printf("Error: Invalid character: ");
//            show_red(text[i]);
//            printf("\n");
//            return false;
//        }
//    }
//
//    free_memory();
//    strncpy(key_text, text, MAXPASSAGELENGTH);
//
//    key_node* tail = NULL;
//
//    for (int i = 0; text[i] != '\0'; i++) {
//        key_node* existing = find_key_node(text[i]);
//
//        if (!existing) {
//            key_node* new_key = new_key_node(text[i]);
//            if (!new_key) continue;
//
//            if (!cipher_key) cipher_key = tail = new_key;
//            else tail = tail->next = new_key;
//            existing = new_key;
//            unique_chars++;
//        }
//
//        char_node* loc = new_char_node(text[i], i + 1);
//        if (loc) add_location(existing, loc);
//    }
//
//    printf("Key created: %zu chars, %d unique\n", strlen(text), unique_chars);
//    return true;
//}
//
//char* encrypt(const char* text) {
//    if (!text || !cipher_key) return NULL;
//
//    for (int i = 0; text[i] != '\0'; i++) {
//        if (!is_valid_char(text[i])) return NULL;
//    }
//
//    int len = strlen(text);
//    char* result = (char*)malloc(len * (LOCATION_SIZE + 2) + 1);
//    if (!result) return NULL;
//
//    char* ptr = result;
//
//    for (int i = 0; text[i] != '\0'; i++) {
//        if (ptr != result) *ptr++ = ' ';
//
//        key_node* key = find_key_node(text[i]);
//
//        if (key && key->count > 0) {
//            int r = rand() % key->count;
//            char_node* loc = key->locations;
//            for (int j = 0; j < r && loc; j++) loc = loc->next;
//
//            if (loc) {
//                strcpy(ptr, loc->location);
//                ptr += strlen(loc->location);
//            }
//            else {
//                strcpy(ptr, "(0,0)");
//                ptr += 5;
//            }
//        }
//        else {
//            strcpy(ptr, "(0,0)");
//            ptr += 5;
//        }
//    }
//
//    *ptr = '\0';
//    return result;
//}
//
//char* decrypt(const char* enc) {
//    if (!enc || !cipher_key) return NULL;
//
//    int max_len = strlen(enc) / 3 + 1;
//    char* result = (char*)malloc(max_len + 1);
//    if (!result) return NULL;
//
//    char* out = result;
//    const char* ptr = enc;
//
//    while (*ptr) {
//        int row, col;
//        if (sscanf(ptr, " (%d,%d)", &row, &col) == 2) {
//            key_node* key = cipher_key;
//            bool found = false;
//
//            while (key && !found) {
//                char_node* loc = key->locations;
//                while (loc && !found) {
//                    if (loc->row == row && loc->column == col) {
//                        *out++ = key->ch;
//                        found = true;
//                    }
//                    loc = loc->next;
//                }
//                key = key->next;
//            }
//
//            if (!found) *out++ = '?';
//            ptr = strchr(ptr, ')');
//            if (ptr) ptr++;
//        }
//        else {
//            ptr++;
//        }
//    }
//
//    *out = '\0';
//    return result;
//}
//
//char* input_with_hint(const char* prompt, int max_len) {
//    static char buffer[MAXPASSAGELENGTH + 1];
//    int len = 0;
//
//    while (1) {
//        system("cls");
//        printf("%s (max %d chars):\n\n", prompt, max_len);
//
//        printf("Content: ");
//        for (int i = 0; i < len; i++) {
//            if (is_valid_char(buffer[i])) putchar(buffer[i]);
//            else show_red(buffer[i]);
//        }
//        if (len < max_len) printf("█");
//
//        printf("\n\nHint: ");
//
//        bool has_invalid = false;
//        char last_invalid = 0;
//        for (int i = 0; i < len; i++) {
//            if (!is_valid_char(buffer[i])) {
//                has_invalid = true;
//                last_invalid = buffer[i];
//            }
//        }
//
//        if (has_invalid) {
//            printf("'");
//            show_red(last_invalid);
//            printf("' is invalid, please delete. (remain %d)", max_len - len);
//        }
//        else {
//            printf("All chars are valid. (remain %d)", max_len - len);
//        }
//
//        char ch = _getch();
//
//        if (ch == '\r' || ch == '\n') {
//            if (len > 0) break;
//        }
//        else if (ch == 8) {
//            if (len > 0) buffer[--len] = '\0';
//        }
//        else if (ch == 27) {
//            buffer[0] = '\0';
//            return buffer;
//        }
//        else if (len < max_len) {
//            buffer[len++] = ch;
//            buffer[len] = '\0';
//        }
//    }
//
//    return buffer;
//}
//
//char* file_input(const char* prompt) {
//    static char filename[MAX_FILENAME];
//    printf("%s\nEnter filename: ", prompt);
//
//    snprintf(filename, MAX_FILENAME, "E:\\desktop\\Program_and_code\\C-Language-Files\\Visual School\\Basical Program Design\\final work (Program design base)\\Text\\%s", filename);
//    scanf("%255s", filename);
//    clear_buffer();
//
//    char* content = read_from_file(filename);
//    if (!content) {
//        printf("Failed to read file. Press any key to continue...\n");
//        _getch();
//    }
//    return content;
//}
//
//void file_output(const char* prompt, const char* content) {
//    char filename[MAX_FILENAME];
//    printf("%s\nEnter filename to save (or press Enter to skip): ", prompt);
//
//    fgets(filename, MAX_FILENAME, stdin);
//    filename[strcspn(filename, "\n")] = '\0';// string complement span 
//
//    if (strlen(filename) > 0) {
//        char filepath[MAX_FILENAME];
//        snprintf(filepath, MAX_FILENAME, "E:\\desktop\\Program_and_code\\C-Language-Files\\Visual School\\Basical Program Design\\final work (Program design base)\\Text\\%s", filename);
//
//        if (write_to_file(filepath, content)) {
//            printf("Content saved to %s\n", filepath);
//        }
//        else {
//            printf("Failed to save file.\n");
//        }
//    }
//}
//
//void show_key() {
//    if (!cipher_key) {
//        printf("No key loaded.\n");
//        return;
//    }
//
//    printf("\nKey structure:\n\n");
//
//    key_node* key = cipher_key;
//    while (key) {
//        printf("'%c': %d times -> ", key->ch, key->count);
//
//        char_node* loc = key->locations;
//        while (loc) {
//            printf("(%d,%d)", loc->row, loc->column);
//            if (loc->next) printf(" ");
//            loc = loc->next;
//        }
//
//        printf("\n");
//        key = key->next;
//    }
//}
//
//void menu_key() {
//    system("cls");
//    printf("GENERATE KEY\n\n");
//
//    printf("1. Manual input\n");
//    printf("2. Random text\n");
//    printf("3. Read from file\n");
//    printf("4. Save key to file\n");
//    printf("0. Back\n\n");
//    printf("Select: ");
//
//    int choice = get_int(0, 4);
//    if (choice == 0) return;
//
//    char* text = NULL;
//
//    if (choice == 1) {
//        text = input_with_hint("Enter key text", MAXPASSAGELENGTH);
//    }
//    else if (choice == 2) {
//        printf("\nEnter length (10-%d): ", MAXPASSAGELENGTH);
//        int len = get_int(10, MAXPASSAGELENGTH);
//
//        const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
//            "0123456789 .,!?-_";
//        text = (char*)malloc(len + 1);
//        if (text) {
//            for (int i = 0; i < len; i++) {
//                text[i] = charset[rand() % (sizeof(charset) - 1)];
//            }
//            text[len] = '\0';
//            printf("\nGenerated: %s\n", text);
//        }
//    }
//    else if (choice == 3) {
//        text = file_input("Load key from file");
//    }
//    else if (choice == 4) {
//        if (!cipher_key) {
//            printf("No key loaded to save!\n");
//        }
//        else {
//            file_output("Save current key to file", key_text);
//        }
//        printf("\nPress any key...");
//        _getch();
//        return;
//    }
//
//    if (text && *text) {
//        if (generate_cipher_key(text)) {
//            printf("\nKey loaded successfully.\n");
//
//            printf("Save key to file? (y/n): ");
//            char save_choice = _getch();
//            if (save_choice == 'y' || save_choice == 'Y') {
//                file_output("Save key to file", text);
//            }
//        }
//    }
//
//    if (choice == 2 || choice == 3) {
//        if (text) free(text);
//    }
//
//    printf("\nPress any key...");
//    _getch();
//}
//
//void menu_encrypt(int mode) {
//    system("cls");
//    const char* mode_str[] = { "MANUAL", "AUTO", "FILE" };
//    printf("%s ENCRYPTION\n\n", mode_str[mode]);
//
//    if (!cipher_key) {
//        printf("No key loaded!\n");
//        _getch();
//        return;
//    }
//
//    char* text = NULL;
//    char* input_buffer = NULL;
//
//    if (mode == 0) {
//        text = input_with_hint("Enter text to encrypt", MAXTEXTLENGTH);
//    }
//    else if (mode == 1) {
//        printf("Enter length (5-%d): ", MAXTEXTLENGTH);
//        int len = get_int(5, MAXTEXTLENGTH);
//
//        const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,!?";
//        text = (char*)malloc(len + 1);
//        if (text) {
//            for (int i = 0; i < len; i++) {
//                text[i] = charset[rand() % (sizeof(charset) - 1)];
//            }
//            text[len] = '\0';
//            printf("\nText: %s\n", text);
//        }
//    }
//    else if (mode == 2) {
//        input_buffer = file_input("Load text from file for encryption");
//        text = input_buffer;
//    }
//
//    if (!text || !*text) {
//        if (mode == 1 && text) free(text);
//        if (mode == 2 && input_buffer) free(input_buffer);
//        printf("Error: No text!\n");
//        _getch();
//        return;
//    }
//
//    char* enc = encrypt(text);
//    if (!enc) {
//        printf("Error: Encryption failed!\n");
//        if (mode == 1 || mode == 2) {
//            free(text);
//        }
//        _getch();
//        return;
//    }
//
//    printf("\nOriginal: %s\n", text);
//    printf("Encrypted: %s\n", enc);
//
//    printf("\nSave encrypted result to file? (y/n): ");
//    char save_choice = _getch();
//    if (save_choice == 'y' || save_choice == 'Y') {
//        file_output("Save encrypted text to file", enc);
//    }
//
//    free(enc);
//    if (mode == 1 || mode == 2) {
//        free(text);
//    }
//
//    printf("\nPress any key...");
//    _getch();
//}
//
//void menu_decrypt(int mode) {
//    system("cls");
//    const char* mode_str[] = { "MANUAL", "AUTO", "FILE" };
//    printf("%s DECRYPTION\n\n", mode_str[mode]);
//
//    if (!cipher_key) {
//        printf("No key loaded!\n");
//        _getch();
//        return;
//    }
//
//    char* enc = NULL;
//    char* input_buffer = NULL;
//
//    if (mode == 0) {
//        enc = input_with_hint("Enter coordinates (format: (row,col))", MAXTEXTLENGTH * LOCATION_SIZE);
//    }
//    else if (mode == 1) {
//        printf("Enter number of coordinates (5-50): ");
//        int len = get_int(5, 50);
//
//        enc = (char*)malloc(len * (LOCATION_SIZE + 2) + 1);
//        if (enc) {
//            char* ptr = enc;
//            for (int i = 0; i < len; i++) {
//                if (i > 0) *ptr++ = ' ';
//                int row = rand() % ROW;
//                int col = rand() % COL;
//                sprintf(ptr, "(%d,%d)", row, col);
//                ptr += strlen(ptr);
//            }
//            *ptr = '\0';
//            printf("\nEncrypted: %s\n", enc);
//        }
//    }
//    else if (mode == 2) {
//        input_buffer = file_input("Load encrypted text from file for decryption");
//        enc = input_buffer;
//    }
//
//    if (!enc || !*enc) {
//        if (mode == 1 && enc) free(enc);
//        if (mode == 2 && input_buffer) free(input_buffer);
//        printf("Error: No coordinates!\n");
//        _getch();
//        return;
//    }
//
//    char* dec = decrypt(enc);
//    if (!dec) {
//        printf("Error: Decryption failed!\n");
//        if (mode == 1) free(enc);
//        if (mode == 2) free(input_buffer);
//        _getch();
//        return;
//    }
//
//    printf("\nEncrypted: %s\n", enc);
//    printf("Decrypted: %s\n", dec);
//
//    printf("\nSave decrypted result to file? (y/n): ");
//    char save_choice = _getch();
//    if (save_choice == 'y' || save_choice == 'Y') {
//        file_output("Save decrypted text to file", dec);
//    }
//
//    free(dec);
//    if (mode == 1) free(enc);
//    if (mode == 2) free(input_buffer);
//
//    printf("\nPress any key...");
//    _getch();
//}
//
//void show_menu() {
//    system("cls");
//    printf("INTERACTIVE ENCRYPTION SYSTEM\n");
//    printf("==============================\n\n");
//
//    printf("1. Generate/Manage Key\n");
//    printf("2. Manual encryption\n");
//    printf("3. Auto encryption\n");
//    printf("4. File encryption\n");
//    printf("5. Manual decryption\n");
//    printf("6. Auto decryption\n");
//    printf("7. File decryption\n");
//    printf("8. View key\n");
//    printf("9. Exit\n\n");
//
//    if (cipher_key) {
//        printf("Key: LOADED (%d unique chars)\n", unique_chars);
//    }
//    else {
//        printf("Key: NOT LOADED\n");
//    }
//
//    printf("\nSelect (1-9): ");
//}
//
//int main() {
//    srand((unsigned)time(NULL));
//
//    printf("Welcome to Interactive Encryption System\n");
//    printf("\nPress any key to continue...");
//    _getch();
//
//    while (1) {
//        show_menu();
//        int choice = get_int(1, 9);
//
//        switch (choice) {
//        case 1: menu_key(); break;
//        case 2: menu_encrypt(0); break;
//        case 3: menu_encrypt(1); break;
//        case 4: menu_encrypt(2); break;
//        case 5: menu_decrypt(0); break;
//        case 6: menu_decrypt(1); break;
//        case 7: menu_decrypt(2); break;
//        case 8:
//            system("cls");
//            show_key();
//            _getch();
//            break;
//        case 9:
//            free_memory();
//            printf("\nGoodbye!\n");
//            return 0;
//        }
//    }
//
//    return 0;
//}
//
