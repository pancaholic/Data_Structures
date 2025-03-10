#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10

// Struct untuk Chaining(Linked List)
struct node
{
    char data[100];
    struct node *next;
};

// Hash tables
struct node *chainTable[TABLE_SIZE];
char linearTable[TABLE_SIZE][100];
int collisionHandlingMethod = 1;
int selectedHashingMethod = 1;

int occupied[TABLE_SIZE] = {0};

// Mid-Square Hash Function
int midSquareHash(char data[])
{
    int key = 0;
    for (int i = 0; data[i] != '\0'; i++)
    {
        key += data[i];
        printf("%d ", key);
    }
    key = key * key;

    char strKey[20];

    // Ubah int menjadi string
    sprintf(strKey, "%d", key);

    // Ambil digit tengah
    int len = strlen(strKey);

    // index pertama digit tengah
    int midStart = len / 2 - 1;

    // Extract 2 digit tengah
    char midDigits[3] = {strKey[midStart], strKey[midStart + 1], '\0'};

    // Ubah string menjadi int
    int middleValue = atoi(midDigits);

    if (middleValue > TABLE_SIZE)
    {
        return middleValue % TABLE_SIZE;
    }
    else
    {
        return middleValue;
    }
}

// Division Hash Function
int divisionHash(char data[])
{
    int key = 0;
    for (int i = 0; data[i] != '\0'; i++)
    {
        key += data[i];
    }
    return key % TABLE_SIZE;
}

// Folding Hash Function
int foldingHash(char data[])
{
    int key = 0;
    for (int i = 0; data[i] != '\0'; i++)
    {
        key += data[i];
    }

    char strKey[20];

    // Ubah int menjadi string
    sprintf(strKey, "%d", key);

    int sum = 0;
    int len = strlen(strKey);

    // Process the key in parts of size 2
    for (int i = 0; i < len; i += 2)
    {
        char partStr[3];
        // Extract 2 digits
        strncpy(partStr, strKey + i, 2);
        partStr[2] = '\0';

        int partValue = atoi(partStr);
        sum += partValue;
    }

    return sum % TABLE_SIZE;
}

// Digit Extraction Hash Function
int digitExtractionHash(char data[])
{
    int key = 0;
    char strKey[10];

    for (int i = 0; data[i] != '\0'; i++)
        key += data[i];

    sprintf(strKey, "%d", key);

    int extractedKey;
    if (strlen(strKey) >= 4)
    {
        // ambil digit ke 2 dan 4
        extractedKey = (strKey[1] - '0') * 10 + (strKey[3] - '0');
    }
    else
    {
        extractedKey = key % TABLE_SIZE;
    }

    return extractedKey % TABLE_SIZE;
}

// Get the selected hash function
int getHash(char data[])
{
    switch (selectedHashingMethod)
    {
    case 1:
        return midSquareHash(data);
    case 2:
        return divisionHash(data);
    case 3:
        return foldingHash(data);
    case 4:
        return digitExtractionHash(data);
    default:
        return divisionHash(data);
    }
}

// Chaining (Linked List)
void insertChaining(int hashKey, char data[])
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    strcpy(newNode->data, data);
    newNode->next = NULL;

    if (chainTable[hashKey] == NULL)
    {
        chainTable[hashKey] = newNode;
    }
    else
    {
        struct node *curr = chainTable[hashKey];
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

// Linear Probing
void insertLinearProbing(int hashKey, char data[])
{
    int index = hashKey;
    while (strlen(linearTable[index]) > 0)
    {
        index = (index + 1) % TABLE_SIZE;
    }
    strcpy(linearTable[index], data);
}

// Rehashing
int secondHash(char data[])
{
    int key = 0;
    for (int i = 0; data[i] != '\0'; i++)
        key += data[i];
    return 7 - (key % 7);
}

void insertRehashing(int hashKey, char data[])
{
    int index = hashKey;
    int step = secondHash(data);

    int attempts = 0;
    while (occupied[index] && attempts < TABLE_SIZE)
    { 
        index = (index + step) % TABLE_SIZE;
        attempts++;
    }

    if (attempts == TABLE_SIZE)
    {
        printf("Hash table is full. Cannot insert: %s\n", data);
        return;
    }

    strcpy(linearTable[index], data);
    occupied[index] = 1; // Mark as occupied
}

void insertData(char data[])
{
    int hashKey = getHash(data);

    switch (collisionHandlingMethod)
    {
    case 1:
        insertChaining(hashKey, data);
        break;
    case 2:
        insertLinearProbing(hashKey, data);
        break;
    case 3:
        insertRehashing(hashKey, data);
        break;
    }
}

void displayHashTable()
{
    printf("\nHash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Index [%d]: ", i);
        if (collisionHandlingMethod == 1)
        {
            struct node *curr = chainTable[i];
            while (curr)
            {
                printf("%s -> ", curr->data);
                curr = curr->next;
            }
        }
        else
        {
            if (strlen(linearTable[i]) > 0)
                printf("%s", linearTable[i]);
        }
        printf("\n");
    }
}

void showMenu()
{
    printf("Select Hashing Method:\n");
    printf("1. Mid-Square\n2. Division\n3. Folding\n4. Digit Extraction\n5. Exit\n");
    printf("Input: ");
    scanf("%d", &selectedHashingMethod);

    printf("\nSelect Collision Handling:\n");
    printf("1. Chaining (Linked List)\n2. Linear Probing\n3. Double Hashing (Rehashing)\n");
    printf("Input: ");
    scanf("%d", &collisionHandlingMethod);
}

// Free memory
void freeMemory()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct node *curr = chainTable[i];
        while (curr)
        {
            struct node *temp = curr;
            curr = curr->next;
            free(temp);
        }
        chainTable[i] = NULL;
    }
}

int main()
{
    showMenu();

    char data[100];
    while (1)
    {
        printf("Enter data (type 'exit' to stop): ");
        scanf("%s", data);

        if (strcasecmp(data, "exit") == 0)
            break;

        insertData(data);
    }

    displayHashTable();
    freeMemory();

    return 0;
}
