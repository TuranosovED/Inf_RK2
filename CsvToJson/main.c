#include "cJSON.h"
#include "lines.h"
#include <stdio.h>
#include <ctype.h>

int main()
{
    puts("Enter fileName:");
    char *s = ReadLine();
    FILE *f = fopen(s,"r");
    free(s);

    if(f == NULL)
    {
        puts("File is not founded!");
        return 0;
    }

    char c;
    char *bufferStr = (char *)calloc(1,sizeof(char));
    char fileStr[1024];
    int size = 0;

    while((c = fgetc(f)) != '\n')
    {
        if(c == ',')
            size++;
        PushLine(&bufferStr,c);
    }
        
    //fgetc(f);
    int cvsSize = 0;

    FILE *f1 = fopen("output.json","w");

    char **Fields = (char **)calloc(size,sizeof(char*));
    char *buffer = strtok(bufferStr,",");

    for(int i =0;i<size;i++)
    {
        Fields[i] = buffer;
        buffer = strtok(NULL,",");
    }
    
    
    fputs("[\n\t", f1);
    int counter = 0;
    int trigger = 1;
    while(fgets(fileStr, 1024, f) != NULL)
    {
        if(!trigger)
        {
            fputs("},", f1);
        }
        fputs("\n{\n",f1);
        buffer = strtok(fileStr, ",");
        while(buffer != NULL)
        {
            if(counter<size && buffer != NULL)
                fprintf(f1,"\"%s\": \"%s\"",Fields[counter++],buffer);
            buffer = strtok(NULL, ",");
            
            if(counter <size)
                fputc(',',f1);
            fputc('\n',f1);
        }
        counter = 0;
        trigger = 0;
    }

    fputs("}\n]\n\t", f1);

    fclose(f);
    fclose(f1);
    return 0;
}

// if(scobka)
//         {
//             fputs("{\n",f);
//             scobka = 0;
//         }
//         if(fileStr[i] == ',')
//         {
//             counter++;
//             if(covachka == 1)
//             {
//                 fputc('"',f);
//                 covachka = 0;
//             }
//             if((counter <(size)))
//                 fputs(",\n",f);
//             trigger = 1;
//         }
//         else
//         {
//             if(trigger)
//             {
//                 if(counter<size)
//                     fprintf(f,"\"%s\":",Fields[counter]);
//                 trigger = 0;
//             }
//             if(!isdigit(fileStr[i]) && !covachka && fileStr[i] != '\n')
//             {
//                 fputc('"',f);
//                 covachka = 1;
//             }
                
//             fputc(fileStr[i],f);
//         }
//         if(fileStr[i] == '\n')
//         {
//             fputs("\n},\n",f);
//             scobka = 1;
//             counter = 0;
//             covachka = 0;
//             trigger = 1;
//         }