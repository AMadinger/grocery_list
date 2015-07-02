/*
Grocery_List

PURPOSE - To create, edit, and read an external file holding a list

CURRENT STATUS - v0102
-[1] User can only access a file that already exists. Does not account for edge cases.
-[2.0] Add working, but perhaps not adding the correct way
-[2.1] Delete not working, does not account for fgets() bringing in strings
-[2.2] Read working
-[2.3] End working
-[3] Edge cases accounted for

NOTES
Derek, is it better to have a main function with the basic if(...) for the add, delete, edit, read...
but then have these as seperate functions after main(void) in order to keep things clean?

How's my formatting? I created these comments after decided to send it to you with my current progress.
None of these existed as I was coding it.
*/

#include <stdio.h>
#include <string.h>
FILE *fp;

int main(void){
    
//VARIABLES - declared
    char user_input[100];
    char file_name[100];
    char to_add[100];
    char to_delete[100];
    char read_string[100];
    int ret=0;
    char str[60];

//[1] Direct to file - user specifices file name (assume it exists)    
    printf("file name?: ");
    scanf("%s",file_name);

//[2] Commands: add, delete, read, end - actions on file specified in [1]    
    while(1){
        printf("commands: add, delete, read, end ");
        scanf("%s",user_input);

//[2.0] Add - appends an item to the list       
        if((strcmp(user_input, "add")) == 0){
            printf("What item would you like to add?: ");
            scanf("%s",to_add);
            
            fp = fopen(file_name,"a");
            fprintf(fp,"%s\n", to_add);
            fclose(fp);
            }

//[2.1] Delete - deletes an item from the list
        else if((strcmp(user_input, "delete")) == 0){
            printf("What item would you like to delete?: ");
            scanf("%s",to_delete);
            printf("to_delete: %s\n",to_delete); //debug
            // problem is that to_delete is single line, but all the entries have a \n
            while(1){
              fgets(read_string,100,fp);
              ret = (strcmp(to_delete, "bacon\n"));
              printf("ret: %d\n",ret);
              printf("read string: %s\n",read_string); //debug
              //printf("%d\n",(strcmp(to_delete, read_string))); //debug
              if(ret == 0){
                printf("found it!\n");
                break;
                }
              else if(feof(fp)){
                printf("That item does not exist.\n"); // Once it reaches the end without finding item
                break;
                }
              }
             }

//[2.2] Read - reads the list
        else if((strcmp(user_input, "read")) == 0){
            int i=0;
            fp = fopen(file_name,"r");
            while(1){
                if(fgets(str,60,fp)==NULL) break;
                    i++;
                    printf("%3d: %s\n",i,str);
                    //puts(str);
                    }
            fclose(fp);
            }

//[2.3] End - ends the program
        else if((strcmp(user_input, "end")) == 0)
            break;

//[3] Edge case
        else{
            printf("retry\n");
            }
            
    }
    printf("Program terminated.\n");
    return(0);    
}
