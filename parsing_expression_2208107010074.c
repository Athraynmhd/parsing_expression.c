#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100 // untuk nentuin ukuran maksimum stack

typedef struct // memberikan alias
{
    int top;               // unutk nuntuk index dari elemen teratas
    char *items[MAX_SIZE]; // untuk nyimpan elemen dari stack
} Stack;                   // sekarang stack adalah tipe data

Stack *createStack();
void push(Stack *s, char *item);
char *pop(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
int precedence(char op);
void infix_ke_Postfix(char *infix, char *postfix);
void infix_ke_Prefix(char *infix, char *prefix);
void postfix_ke_Infix(char *postfix, char *infix);
void postfix_ke_Prefix(char *postfix, char *prefix);
void prefix_ke_Infix(char *prefix, char *infix);
void prefix_ke_Postfix(char *prefix, char *postfix);
int cekOperator(char c);
int cekOperand(char c);

int main()
{
    char ekspresi[MAX_SIZE], hasil[MAX_SIZE];
    int opsi;
    printf("\n===================================\n");
    printf("|     Menu Konversi Ekspresi      |\n");
    printf("===================================\n");
    printf("| Pilihan |        Konversi       |\n");
    printf("|=========|=======================|\n");
    printf("|    1    |  Infix ke Postfix     |\n");
    printf("|    2    |  Infix ke Prefix      |\n");
    printf("|    3    |  Postfix ke Infix     |\n");
    printf("|    4    |  Postfix ke Prefix    |\n");
    printf("|    5    |  Prefix ke Infix      |\n");
    printf("|    6    |  Prefix ke Postfix    |\n");
    printf("===================================\n");
    printf("Pilih jenis konversi (1-6) : ");
    scanf("%d", &opsi);
    getchar();

    printf("Masukkan ekspresi: ");
    scanf("%s", ekspresi);

    switch (opsi)
    {
    case 1:
        infix_ke_Postfix(ekspresi, hasil);
        break;
    case 2:
        infix_ke_Prefix(ekspresi, hasil);
        break;
    case 3:
        postfix_ke_Infix(ekspresi, hasil);
        break;
    case 4:
        postfix_ke_Prefix(ekspresi, hasil);
        break;
    case 5:
        prefix_ke_Infix(ekspresi, hasil);
        break;
    case 6:
        prefix_ke_Postfix(ekspresi, hasil);
        break;
    default:
        printf("Pilihan anda tidak valid.\n");
        return 1;
    }

    printf("Hasil konversi: %s\n", hasil);

    return 0;
}

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1; // -1 menandakan bahwa stack kosong
    return stack;    // Mengembalikan pointer stack
}

void push(Stack *s, char *item)
{
    if (!isFull(s))
    {
        s->items[++(s->top)] = item;
    }
}

char *pop(Stack *s)
{
    if (!isEmpty(s))
    {
        return s->items[(s->top)--]; // dengan menaikkan nilai top
    }
    return "";
}

int isEmpty(Stack *s)
{
    return s->top == -1;
}

int isFull(Stack *s)
{
    return s->top == MAX_SIZE - 1; // kalo sama dengan ni tandanya penuh
}

int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

int cekOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; // Melakukan compare
}

int cekOperand(char c)
{
    return isalpha(c) || isdigit(c); // kalo treu 1 kalo false 0
}

void infix_ke_Postfix(char *infix, char *postfix) // Menerima 2 string sebagai argumen
{
    Stack *s = createStack();              // membuat stack baru yang akan digunakan di konversi ini
    int j = 0;                             // untuk melacak posisi berikutnya sehingga kita tau dimna harus menambah karakter berikutnya
    for (int i = 0; infix[i] != '\0'; i++) // Loop ini melakukan pencarian atau screening hingga dapat NULL terminator, batasnya NULL terminator
    {
        char c = infix[i];
        if (cekOperand(c)) // kalau operan maka akan ditambah ke dalam postfix
        {
            postfix[j++] = c; // j akan ditambah dengan 1 untuk memindahkan ke posisi berikutnya dalam string
        }
        else if (c == '(')
        {
            push(s, strdup("(")); // kalau c nya tutup kurung maka akan dilakukan push ke dalam stacknya
        }
        else if (c == ')') // kalau buka kurung, dia akan di pop dari stack
        {
            while (!isEmpty(s) && strcmp(s->items[s->top], "(") != 0)
            {
                postfix[j++] = *pop(s);
            }
            free(pop(s));
        }
        else // kalau c adalah bagian dari operator makan akan dibandingkan dengan presedence
        {
            while (!isEmpty(s) && precedence(c) <= precedence(*s->items[s->top]))
            {
                postfix[j++] = *pop(s);
            }
            char op[2] = {c, '\0'};
            push(s, strdup(op));
        }
    }                   // Loop selesai
    while (!isEmpty(s)) // jika masih ada operator maka akan di tambah ke postfix
    {
        postfix[j++] = *pop(s);
    }
    postfix[j] = '\0'; // NULL terminator untuk menandakan akhir dari string
}

void infix_ke_Prefix(char *infix, char *prefix) // Menerima 2 string
{
    int len = strlen(infix);                        // Menghitung panjang untuk tau berapa banyak karakter yang harus di proses
    char *reversed = (char *)malloc(len + 1);       // untuk nyimpan string infix yang dibalik
    char *infixSementara = (char *)malloc(len + 1); // untuk nyimpan string yang udah di modifikasi
    char *postfix = (char *)malloc(len + 1);        // untuk menampung hasil dari infixsementara ke postfix

    for (int i = 0; i < len; i++)
    {
        reversed[len - i - 1] = infix[i]; // melakukan reverse yang mana
                                          // untuk membalikkan yang belakang ke depan
    }
    reversed[len] = '\0';

    for (int i = 0; i < len; i++) // Mengubah posisi tanda kurung dari "(" ke ")" melalui revers
    {
        if (reversed[i] == '(')
        {
            infixSementara[i] = ')';
        }
        else if (reversed[i] == ')')
        {
            infixSementara[i] = '(';
        }
        else
        {
            infixSementara[i] = reversed[i];
        }
    }
    infixSementara[len] = '\0';

    // Disini notasi prefixnya di ubah dulu ke postfix
    infix_ke_Postfix(infixSementara, postfix);

    int panjangPostfix = strlen(postfix);    // Menghitung panjang, dipake dalam iterasi untuk membalikkan si postfix
    for (int i = 0; i < panjangPostfix; i++) // iterasinya mulai dari index 0 hingga panjang prefix - 1
    {
        prefix[panjangPostfix - i - 1] = postfix[i]; // karena nyimpan terbalik makanya -i -1
    }
    prefix[panjangPostfix] = '\0';

    // Melukukan Pembersihan dari alokasi memori
    free(reversed);
    free(infixSementara);
    free(postfix);
}

void postfix_ke_Infix(char *postfix, char *infix) // Menerima 2 string
{
    Stack *s = createStack(); // Membuat stack baru
    char *a, *b, *c;          // Pointer ini akan nyimpan operand dan hasil penggabungan operand dalam konversi
    char temp[2] = "\0";      // Mendeklarasikan array "temp" dengan panjang 2 untuk nyimpan sementara pas iterasi dngan postfix
    int i, j;                 // variable iterasi dalam loop

    for (i = 0, j = 0; postfix[i]; i++) // melakukan looping untuk screening sampa ke \0 terminator
    {
        if (cekOperand(postfix[i]))
        {
            temp[0] = postfix[i]; // kalau operand salin ke dalam array temp dan melakukan push ke dalam stack
            push(s, strdup(temp));
        }
        else
        {
            a = pop(s);                                    // ambil operand pertama akan jadi operan kedua ketika kita push satu lagi
            b = pop(s);                                    // ambil operand kedua akan jadi operand pertama
            c = (char *)malloc(strlen(a) + strlen(b) + 4); // alokasi memori, panjang operan a dan b + 4 karakter extra untuk kurung dan terminator
            sprintf(c, "(%s%c%s)", b, postfix[i], a);      // sprintf tu untuk membuat string baru, intinya untuk menyisipkan
            push(s, c);                                    // kalau udah sub ekpresi dibentuk, baru di push ke stack untuk lebih komplek
        }
    }
    strcpy(infix, pop(s)); // pop element atas kemudian salin, berarti udah ke di konversi ke infix

    while (!isEmpty(s))
    {
        free(pop(s));
    }
    free(s);
}

void postfix_ke_Prefix(char *postfix, char *prefix)
{
    Stack *s = createStack();
    char *a, *b, *c;
    char temp[2] = "\0";
    int i;

    for (i = 0; postfix[i]; i++)
    {
        if (cekOperand(postfix[i]))
        {
            temp[0] = postfix[i];
            push(s, strdup(temp)); // aka karakter tersebut dimasukkan ke dalam tumpukan menggunakan fungsi push.
        }
        else
        {
            a = pop(s);
            b = pop(s);
            c = (char *)malloc(strlen(a) + strlen(b) + 2);
            sprintf(c, "%c%s%s", postfix[i], b, a);
            push(s, c);
        }
    }
    strcpy(prefix, pop(s));

    while (!isEmpty(s))
    {
        free(pop(s));
    }
    free(s);
}

void prefix_ke_Infix(char *prefix, char *infix)
{
    Stack *s = createStack();
    int length = strlen(prefix);
    char *a, *b, *c;
    char temp[2] = "\0";
    int i;

    for (i = length - 1; i >= 0; i--)
    {
        if (cekOperand(prefix[i]))
        {
            temp[0] = prefix[i];
            push(s, strdup(temp));
        }
        else
        {
            a = pop(s);
            b = pop(s);
            c = (char *)malloc(strlen(a) + strlen(b) + 4);
            sprintf(c, "(%s%c%s)", a, prefix[i], b);
            push(s, c);
        }
    }
    strcpy(infix, pop(s));

    while (!isEmpty(s))
    {
        free(pop(s));
    }
    free(s);
}

void prefix_ke_Postfix(char *prefix, char *postfix)
{
    Stack *s = createStack();
    int length = strlen(prefix);
    char *a, *b, *c;
    char temp[2] = "\0";
    int i;

    for (i = length - 1; i >= 0; i--)
    {
        if (cekOperand(prefix[i]))
        {
            temp[0] = prefix[i];
            push(s, strdup(temp));
        }
        else
        {
            a = pop(s);
            b = pop(s);
            c = (char *)malloc(strlen(a) + strlen(b) + 2);
            sprintf(c, "%s%s%c", a, b, prefix[i]);
            push(s, c);
        }
    }
    strcpy(postfix, pop(s));

    while (!isEmpty(s))
    {
        free(pop(s));
    }
    free(s);
}