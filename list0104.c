/*
Grocery_List

PURPOSE - To create, edit, and read an external file holding a list

CURRENT STATUS - v0104
-[1] User can access a file that already exists or create a new one.
-[2.0] Add working
-[2.1] Delete working
-[2.2] Read working
-[2.3] End working
-[3] Edge cases accounted for

NOTES
Not all edge cases accounted for. Limitations on length of entries, number of entries, and space for entries.
No error message if an item sought to be deleted is not in the list.
Confirmation for deletion, however.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fp;

int main ( void )
{

	//VARIABLES - declared
	char user_input[ 100 ];
	char file_name[ 100 ];
	char file_yn[100]; //used as yes/no for file
	char to_add[ 100 ];
	char to_delete[ 100 ];
	char str[ 60 ];
	
	/*ERRORS - return values delcared
	1-file_yn error
	*/
	
	//[1] Direct to file - user specifices file name (assume it exists)    
    printf ( "\nWelcome to List!\nDo you already have a file to write to? (y/n): " );
    scanf ( "%s", file_yn );

	/*do{
	    printf ( "Do you already have a file? Please type in only y/n: " );
	    scanf ( "%s", file_yn );
	    }
	    while((strcmp ( file_yn, "y" ) ) != 0) || (strcmp ( file_yn, "n" ) != 0));
	    */

	if(strcmp ( file_yn, "y" )  == 0){
	    printf ( "\nWhat is the file's name (w/ extension)?: " );
	    scanf ( "%s", file_name );
	    }
	else if(strcmp ( file_yn, "n" )  == 0){
	    printf ( "\nI'll create one for you. What would you like to name the file (w/ extension)?: " );
	    scanf ( "%s", file_name );
	    fp = fopen ( file_name, "w" );
	    fclose ( fp );
	    }
	else
	    return (1); //file_yn error

	//[2] Commands: add, delete, read, instructions, end - actions on file specified in [1]    
	while ( 1 )
	{
		printf ( "\nCommands: add, delete, read, instructions, end " );
		scanf ( "%s", user_input );

		//[2.0] Add - appends an item to the list       
		if ( ( strcmp ( user_input, "add" ) ) == 0 )
		{
			printf ( "What item would you like to add?: " );
			scanf ( "%s", to_add );

			fp = fopen ( file_name, "a" );
			fprintf ( fp, "%s\n", to_add );
			fclose ( fp );
		}

		//[2.1] Delete - deletes an item from the list
		else if ( ( strcmp ( user_input, "delete" ) ) == 0 )
		{
			printf ( "what do you want to delete?: " );
			scanf ( "%s", to_delete);
			const int to_delete_length = strlen ( to_delete );
			to_delete[ to_delete_length ] = '\n';
			to_delete[ to_delete_length+1 ] = '\0';

			int i = 0;
			char** delete_array = ( char** )malloc ( sizeof ( char* ) * 20 );
			for ( i = 0; i < 20; ++i ) delete_array[ i ] = NULL;

			i = 0;
			fp = fopen ( file_name, "r" );
			while ( 1 )
			{
				if ( fgets ( str, 60, fp ) == NULL ) break; //terminating condition
				if ( ( strcmp ( to_delete, str ) ) != 0 )
				{
					delete_array[ i ] = ( char* )malloc ( sizeof ( char ) * 60 );
					memcpy ( delete_array[ i ], str, 60 );
				}
				else
				{
					delete_array[ i ] = NULL;
					printf("\nfound and deleted\n");
				}
				i++;
			}
			fclose( fp );
			fp = fopen ( file_name, "w" );
			for ( i = 0; i < 20; i++ )
			{
				if ( delete_array[ i ] != NULL )
				{
					fputs ( delete_array[ i ],fp );
				}
			}
			// free every line
			for ( i = 0; i < 20; ++i ) free ( delete_array[ i ] ); //can't free memory you don't own, but we did, with NULL
			free ( delete_array );

			fclose ( fp );
		}

		//[2.2] Read - reads the list
		else if ( ( strcmp ( user_input, "read" ) ) == 0 )
		{
			int i = 0;
			fp = fopen ( file_name, "r" );
			while ( 1 )
			{
				if ( fgets ( str, 60, fp ) == NULL ) break;
				i++;
				printf ( "%3d: %s\n", i, str );
				//puts(str);
			}
			fclose ( fp );
		}

		//[2.3] Instructions - prints out instructions
		else if ( ( strcmp ( user_input, "instructions" ) ) == 0 ){
			printf ( "This program can add items to a file, delete them, or let you read the file.\n");
			printf ( "The file being written to is %s\n",file_name);
			printf ( "Type a command and hit enter. Then type/enter the item for that command.\n");
			printf ( "Entered items cannot have spaces.\n");
			printf ( "The file is updated after every action.\n");
			printf ( "Please keep an item's characters below 60, and the number of items in the list < 19.\n");
			printf ( "If no confirmation about item being deleted, item not found.\n");
			}
		
		//[2.4] End - ends the program
		else if (  strcmp ( user_input, "end" )  == 0 ){
			break;
			}

		//[3] Edge case
		else
		{
			printf ( "retry\n" );
		}

	}
	printf ( "Program terminated.\n" );
	return( 0 );
}
