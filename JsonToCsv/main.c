#include "cJSON.h"
#include <stdio.h>
#include "lines.h"

void MakeFields(cJSON *head,FILE *f)
{
    int flag = 0;
    if(head->child !=NULL)
    {
        flag = 1;
        MakeFields(head->child,f);
    }
    if(head->next!=NULL)
        MakeFields(head->next,f);
    if(!flag)
        fprintf(f,"%s,",head->string);
}

void MakeCsv(cJSON *head,FILE *f)
{
    int flag = 0;
    if(head->child !=NULL)
    {
        flag = 1;
        MakeCsv(head->child,f);
    }
    if(head->next!=NULL)
        MakeCsv(head->next,f);
    if(!flag)
    {
        if(head->type == cJSON_String)
            fprintf(f,"%s,",head->valuestring);
        else if(head->type == cJSON_Number)  
            fprintf(f,"%g,",head->valuedouble);
    }
}

int main()
{
    puts("Enter filename:");
    char *s = ReadLine();

    FILE *f = fopen(s,"r");
    free(s);
    if(f == NULL)
    {
        puts("File is not founded!");
        return 0;
    }
    
    char c;
    char *fileStr = (char *)calloc(1,sizeof(char));
    while ((c = fgetc(f)) != EOF)
        PushLine(&fileStr,c);
    fclose(f);
    cJSON *json = cJSON_Parse(fileStr);

    if(json == NULL)
    {
        puts("Parce panic!");
        return 0;
    }

    if(!cJSON_IsArray(json))
    {
        puts("Error! JSON is incorrect!");
        return 0;
    }

    int size = cJSON_GetArraySize(json);
    cJSON **data = (cJSON **) malloc(size * sizeof(cJSON*));
    cJSON *buffer;
    for (int i = 0; i < size; i++) 
    {
        buffer = cJSON_GetArrayItem(json, i);
        data[i] = buffer;
    }

    f = fopen("output.csv","w");

    MakeFields(data[0]->child,f);

    fputc('\n',f);

    for(int i =0;i<size;i++)
    {
        MakeCsv(data[i]->child,f);
        fputc('\n',f);
    } 

    fclose(f);
    puts("Complete!");
    return 0;
}

//Рекурсия выход так как cjson указывает в массиве на child а потом от child на next в массиве

//Попытки сделать без рекурсии

// for(cJSON *prev = data[0];prev!=NULL;prev = prev->child)
//     {
//         if(prev->string != NULL)
//             printf("%s,",prev->child->string);
//     }

//     for(int i =0;i<size;i++)
//     {
//         for(cJSON *prev = data[i]->child;prev!=NULL;prev = prev->next)
//         {
//             if(prev->type == cJSON_String)
//                 printf("%s ",prev->valuestring);
//             else if(prev->type == cJSON_Number);
//                 printf("%g ",prev->valuedouble);
//         }
//         putchar('\n');
//     }



// for(cJSON *prev = data[0]->child;prev!=NULL;prev = prev->next)
//     {
//         if(prev->string != NULL)
//             printf("%s,",prev->string);
//     }
//     putchar('\n');
//     for(int i =0;i<size;i++)
//     {
//         for(cJSON *prev = data[i]->child;prev!=NULL;prev = prev->next)
//         {
//             if(prev->type == cJSON_String)
//                 printf("%s,",prev->valuestring);
//             else if(prev->type == cJSON_Number);
//                 printf("%g,",prev->valuedouble);
//         }
//         putchar('\n');
//     }



// cJSON *last;

//     for(cJSON *prev = data[0]->child;prev!=NULL;prev = prev->next)
//     {
//         last = prev;
//     }

//     for(cJSON *prev = last;prev!=data[0]->child;prev = prev->prev)
//     {
//         if(prev->string != NULL)
//             printf("%s,",prev->string);
//     }
//     printf("%s,",data[0]->child->string);

// for(int i =0;i<size;i++)
    // {
    //     for(cJSON *prev = data[i]->child;prev!=NULL;prev = prev->next)
    //     {   
    //         for(cJSON *head = prev;head != NULL;head = head->child)
    //         {
    //             if(head->type == cJSON_String)
    //                 printf("%s,",head->valuestring);
    //             else if(head->type == cJSON_Number)
    //                 printf("%g,",head->valuedouble);
    //             else if(head->type == cJSON_NULL)
    //                 puts("NULL,");
    //         }
    //     }
    //     putchar('\n');
    // }