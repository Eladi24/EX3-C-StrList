#include <stdio.h>
#include <stdlib.h>
#include "StrList.h"
#include <string.h>

int main() {
    int choise;
    StrList* list = StrList_alloc();
    do
    {
        scanf("%d", &choise);

        switch (choise)
        {
        case 1: 
        {
            int numStrings;
            scanf("%d", &numStrings);
            int c;
            // Clear the newline left in the input buffer by scanf()
            while ((c = getchar()) != '\n' && c != EOF)
            {
            
            }
            

            for (int i = 0; i < numStrings; i++)
            {
                char* data = NULL;
                StrList_Scan(&data);
                StrList_insertLast(list, data);
                free(data);
            }
            
            break;
        }    

        case 2:
        {
            int index;
            char* data = NULL;
            scanf("%d", &index);
            // To consume the '\n' left by scanf
            getchar(); 
            StrList_Scan(&data); 
            StrList_insertAt(list, data, index);
            free(data);
            break;
        }
        
        case 3: 
        {
            StrList_print(list);
            break;
        }    

        case 4:
        {
            int size = StrList_size(list);
            printf("%d\n", size);
            break;
        }

        case 5: 
        {
            int index;
            scanf("%d", &index);
            StrList_printAt(list, index);
            break;
        }    

        case 6:
        {
            printf("%d\n", StrList_printLen(list));
            break;
        }

        case 7: 
        {
            char* data = NULL;
            getchar();
            StrList_Scan(&data);
            int count = StrList_count(list, data);
            printf("%d\n", count);
            free(data);
            break;
        }    

        case 8:
        {
            char* data = NULL;
            getchar();
            StrList_Scan(&data);
            StrList_remove(list, data);
            free(data);
            break;
        }

        case 9: 
        {
            int index;
            scanf("%d", &index);
            StrList_removeAt(list, index);
            break;
        }    

        case 10:
        {
            StrList_reverse(list);
            break;
        }

        case 11: 
        {
            int index = 0;
            int size = StrList_size(list);
            while (index < size)
            {
                StrList_removeAt(list, 0);
                index++;
            }
            
            break;
        }    

        case 12:
        {
            StrList_sort(list);
            break;
        }

        case 13: 
        {
            int bool = StrList_isSorted(list);
            if (bool == 1)
            {
                printf("true");
            } else {
                printf("false");
            }
            printf("\n");
            break;
        }

        }
    } while (choise != 0);

    StrList_free(list);
    
}