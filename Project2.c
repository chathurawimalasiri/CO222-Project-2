/*
 *	E/18/402
 *	WIMALASIRI K.H.C.T.
 *
 *	CO222 PROJECT 2
 *
 *
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*********************************************************** MACROS **********************************************************************************/

#define TOTAL_LENGTH		80
#define TOTAL_SPACES_VBAR	3
#define SPACE			printf(" ")
#define NEW_LINE		printf("\n")
#define MAX_LINE_SIZE		1024
#define NOT_OPEN_FILE		printf("Cannot open one or more given files\n")
#define WRONG_CONTAIN		printf("File/s contain wrong entries.\n")
#define NO_INPUT_FILE		printf("No input files were given\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
#define NOT_CSV_FILE		printf("Only .csv files should be given as inputs.\n");
#define NOT_ENOUGH_L		printf("Not enough options for [-l]\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0])
#define INVALID_OPTION_1	printf("Invalid option [%s]\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[index],argv[0])
#define INVALID_OPTION_2	printf("Invalid options for [-l]\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0])
#define NEGATIVE_NUM_ERROR	printf("Invalid option(negative) for [-l]\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0])
#define MULTI_PARA_ERROR	printf("Cannot plot multiple parameters in same graph.\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0])

/**********************************************************************************************************************************************************/

/*********************************************************** STRUCT VARIABLE **********************************************************************************/

typedef struct analyzeData {

	char memberName[80];
	int numberOfMeeting;
	int durationMinutes;
	int count;
	int csvFileRowNumber;	//for sorting the data
	struct analyzeData * next;

}analyzeData;



/***************************************************************************************************************************************************************/


/*********************************************************** PROTOTYPES **********************************************************************************/

void swap(analyzeData *first, analyzeData *second);
int check_L_flag( int , int);
int checkSubString( char *source, char *search);
int sortedArrayMaxString( analyzeData *source, int );
int participantsConvertToNumber( char *source);
int numberOfDigitsInInteger(int);
void sortArraytoCount( analyzeData *source,int );
void spacePrint(int );
void fillGraphArea( float);
void namePrint( char *name, int );
void finalVerticalLine(int , int );
int sumOfElementCount( analyzeData *source );
void sortArraytoTime( analyzeData *source, int );
int sumOfElementTime( analyzeData *source );
void sortArrayParticipants(analyzeData *source, int);
int sumOfElementParticipant( analyzeData *source );
int findTime(char *source);



/****************************************************************** MAIN **********************************************************************************/

int main(int argc,char **argv ){


	FILE *pointerFile;


	int mFlag = 0, tFlag = 0, pFlag = 0, sFlag=0, lFlag = 10, total = 0, sumOfElement, maxStringLength = 0, csvFileRow = 1, index = 1, size = 0, *filesIndex = NULL, filePlace;

	int plotArea, maxDigits;

	float patternArea;

	//mFlag for -m, tFlag for -t, pFlag for -p and sFlag for --scaled

	char *pBuffer, buffer[MAX_LINE_SIZE], participants[100], timeCell[100];


	analyzeData *pDataset = NULL, *current, dataset ;  //dataset variable for reading the data;



/***************************************************************** ERROR HANDLING ***************************************************************/




	if( argc < 2 ){

		NO_INPUT_FILE;

		return 0;

	}


	else if( argc == 2 ){

                        if( (strcmp( "-m", argv[1]) == 0) || (strcmp( "-p", argv[1]) == 0) || (strcmp( "-t", argv[1]) == 0) || (strcmp( "--scaled", argv[1]) == 0) ){   //not given files

                                 NO_INPUT_FILE;

                                 return 0;

                        }


                        else if( strcmp( "-l", argv[1]) == 0){          //no input a number

                                NOT_ENOUGH_L;

                                return 0;

                        }


                        else if( argv[1][0] == '-' ){           //invalid flag

                                INVALID_OPTION_1;

                                return 0;

                        }

                        else{                   //defualt mode

                                mFlag = 1;
                                sFlag = 0;

                                //input the file index number to array
		

				filesIndex = (int*)malloc(sizeof(int)*(size + 1));

				filesIndex[size] = index;

				size++;	



                        }


	}// 1st if

	else{

		for( ; index < argc ; index++ ){




			if( (strcmp( argv[index], "-l")) == 0) {


				if( index == (argc - 1)  ){			//not give a number after -l

                                	NOT_ENOUGH_L;

                                	return 0;

                        	}



				else if( ( (strcmp( argv[index + 1], "0"))  == 0 ) || ( (strcmp( argv[index + 1], "-0"))  == 0 ) ){	// give number as zero

                                	return 0;

                        	}


				else if( checkSubString( argv[index + 1], ".") == 0  ){        //give float number

                                	INVALID_OPTION_2 ;

                                	return 0;

                        	}


				else if( atoi(argv[ index + 1]) < 0  ){		 //give negative number

                                	NEGATIVE_NUM_ERROR;

                                	return 0;


                        	}


				else if( argv[index + 1][0] == '-' ){        //give invalid flag

                                	INVALID_OPTION_2 ;

                                	return 0;

                        	}


				else if( atoi(argv[index + 1]) > 0 ){		//give correct positive number


					lFlag = atoi(argv[index + 1]);


				}


				else{

					INVALID_OPTION_2 ;

                                	return 0;

				}



			}// -l flag



			else if( strcmp( argv[ index ], "-m" ) == 0 ){		//-m flag


				mFlag = 1;



			} //-m flag



			else if( strcmp( argv[ index ], "-p" ) == 0 ){		//-p flag


				pFlag = 1;


			}// -p flag




			else if( strcmp( argv[ index ], "-t" ) == 0 ){		//-t flag


	  			tFlag = 1;


                	}//-t flag


			else if( strcmp( argv[ index ], "--scaled" ) == 0 ){	//--scaled flag


				sFlag = 1;


			}//--scaled flag




			else if( ( argv[index][0] == '-' ) && ( strcmp( argv[ index], "-l" ) != 0 ) && ( strcmp( argv[ index ], "-m" ) != 0 ) && ( strcmp( argv[ index ], "-t" ) != 0 ) && ( strcmp( argv[ index ], "-p" ) != 0 ) && ( strcmp( argv[ index ], "--scaled" ) != 0 ) ){


				INVALID_OPTION_1 ;

				return 0;



			}// - flag


			else if( strcmp( argv[index - 1], "-l" ) != 0 ){	//find the files and insert the index number of their to linked list

				
				if( size == 0 ){

                                	//input the file index number to array

				
                                	filesIndex = (int*)malloc(sizeof(int)*(size + 1));

                                	filesIndex[size] = index;

                                	size++;

				}


				else{

					//input the file index number to array


                                        filesIndex = (int*)realloc(filesIndex,sizeof(int)*(size + 1));

                                        filesIndex[size] = index;

                                        size++;
				


				}	
				


                	}//search files



		}// main for loop end

	}//else end


	//for the defualt mode and not giving any valid flag
	if( (mFlag + pFlag + tFlag) == 0 ){

		mFlag = 1;

	}



	//check user gives whether one type flags ( -m, -p, -t) or not
	if( (mFlag + pFlag + tFlag) != 1 ){


		MULTI_PARA_ERROR;

		return 0;


	}



	//check user input files or not
        if( size == 0 ){

                NO_INPUT_FILE;

                return 0;


        }



/********************************************************************************************************************************************************/


	if( mFlag == 1){

		//get the files
		for( filePlace = 0; filePlace < size ; filePlace++  ){


			if( checkSubString( argv[filesIndex[filePlace]], ".csv" ) == -1 ){		//check .csv file

				NOT_CSV_FILE;

				return 0;

			}



			pointerFile = fopen( argv[filesIndex[filePlace]] , "r");	//read the file



			if( pointerFile == NULL ){		//if file is wrong gives error message

				NOT_OPEN_FILE ;

				return 0 ;

			}



			while( fgets( buffer, MAX_LINE_SIZE , pointerFile ) ){	//get row information to buffer



				pBuffer = buffer;


				strcpy(dataset.memberName,"\0");
				strcpy(participants,"\0");
				


				//-m flag
				if( sscanf( pBuffer, "%80[^,],%[^,],%8[^\n]", dataset.memberName, participants,timeCell ) != 0 ){  //check empty row


					if(( strcmp(dataset.memberName,"\0") == 0 ) || (strcmp(participants,"\0") == 0) ){	//check the empty cell	of name column and participants

						WRONG_CONTAIN;

						return 0;

					}


					if( total == 0 ){

						current = (analyzeData *)malloc(sizeof(analyzeData));

						*current = dataset;

						current -> count = 1;

						current -> csvFileRowNumber = csvFileRow ;

						current -> next = pDataset;

						pDataset = current;

						total++;

						

					}


					else {

						int checker = 0;

						analyzeData *check;


						for(check = pDataset; check != NULL ; check = check -> next ){

							if( strcmp( check -> memberName,dataset.memberName ) == 0 ){	//check similar members similar names

								checker = 1;

								break;

							}


						}


						if( checker == 1){	//if the input member name is similar to already input name


							check -> count += 1;

						}

						else{			//not equal name

							csvFileRow++ ;

							current = (analyzeData *)malloc(sizeof(analyzeData));

                                        		*current = dataset;

                                        		current -> count = 1;

                                        		current -> csvFileRowNumber = csvFileRow ;

							current -> next = pDataset;

                                        		pDataset = current;

                                        		total++;

							

						}



					}




				}//-m if sscanf


				else{

                                	WRONG_CONTAIN;

                                	return 0;

                        	}


			}//-m while

			fclose(pointerFile);    //close the file

		}//-m for


		analyzeData *temp ;

                int Index;

                lFlag =  check_L_flag( lFlag, total);           //check the lFlag value
		
		sortArraytoCount( pDataset,lFlag );           //sort the linked list

                maxStringLength = sortedArrayMaxString( pDataset, lFlag);       //the maximum length of member name


                maxDigits = numberOfDigitsInInteger( pDataset -> count );               //maximum number of digits in numbers


                plotArea = TOTAL_LENGTH - TOTAL_SPACES_VBAR - maxStringLength - maxDigits;              //graph area


                if( sFlag == 1){


                        NEW_LINE;


                        for( temp = pDataset, Index = 0; Index < lFlag ; temp = temp -> next, Index++ ){


                                patternArea = (temp -> count * plotArea) / (pDataset -> count)  ;

                                //1st row
                                spacePrint(maxStringLength);

                                fillGraphArea( patternArea);

                                NEW_LINE;

                                //2nd row
                                namePrint( temp -> memberName, maxStringLength );

                                fillGraphArea( patternArea);

                                printf("%d", temp -> count);

                                NEW_LINE;

                                //3rd row
                                spacePrint(maxStringLength);

                                fillGraphArea( patternArea);

                                NEW_LINE;

                                //4th row
                                spacePrint(maxStringLength);

                                NEW_LINE;



                        }

                        finalVerticalLine(maxStringLength ,(TOTAL_LENGTH - maxStringLength - TOTAL_SPACES_VBAR) );     //final vertical line



                }



                else if( sFlag == 0 ){


                        sumOfElement = sumOfElementCount( pDataset) ;   //sum of the elements

                        NEW_LINE;

                        for( temp = pDataset, Index = 0; Index < lFlag ; temp = temp -> next, Index++ ){


                                patternArea = (temp -> count * plotArea) / (sumOfElement)  ;

                                //1st row
                                spacePrint(maxStringLength);

                                fillGraphArea( patternArea);

                                NEW_LINE;

                                //2nd row
                                namePrint( temp -> memberName, maxStringLength );

                                fillGraphArea( patternArea);

                                printf("%d", temp -> count);

                                NEW_LINE;

                                //3rd row
                                spacePrint(maxStringLength);

                                fillGraphArea( patternArea);

                                NEW_LINE;

                                //4th row
                                spacePrint(maxStringLength);

                                NEW_LINE;



                        }

                        finalVerticalLine(maxStringLength ,(TOTAL_LENGTH - maxStringLength - TOTAL_SPACES_VBAR) );     //final vertical line


                }



	}// -m if





	else if( pFlag == 1 ){


		//get the files
                for( filePlace = 0; filePlace < size ; filePlace++  ){


                        if( checkSubString( argv[filesIndex[filePlace]] , ".csv" ) == -1 ){         //check .csv file

                        	NOT_CSV_FILE;

                        	return 0;

                        }



                        pointerFile = fopen( argv[filesIndex[filePlace]] , "r");   //read the file



                        if( pointerFile == NULL ){              //if file is wrong gives error message

                                NOT_OPEN_FILE ;

                                return 0 ;

                        }



                        while( fgets( buffer, MAX_LINE_SIZE , pointerFile ) ){  //get row information to buffer



                                pBuffer = buffer;


                                strcpy(dataset.memberName,"\0");
                                strcpy(participants,"\0");
                                



				//-p flag
				if( sscanf( pBuffer, "%80[^,],%[^,],%8[^\n]", dataset.memberName, participants,timeCell ) != 0 ){  //check empty row


                                	if(( strcmp(dataset.memberName,"\0") == 0 ) || (strcmp(participants,"\0") == 0) ){      //check the empty cell  of name column and participants

                                        	WRONG_CONTAIN;

                                        	return 0;

                                	}



                                	dataset.numberOfMeeting =  participantsConvertToNumber( participants );  //convert participants to number




                                	if( total == 0 ){

                                        	current = (analyzeData *)malloc(sizeof(analyzeData));

                                        	*current = dataset;

                                        	current -> csvFileRowNumber = csvFileRow ;

                                        	current -> next = pDataset;

                                        	pDataset = current;

                                        	total++;

                                	}


                                	else {

                                        	int checker = 0;

                                        	analyzeData *check;


                                        	for(check = pDataset; check != NULL ; check = check -> next ){

                                                	if( strcmp( check -> memberName,dataset.memberName ) == 0 ){    //check similar members similar names

                                                        	checker = 1;

                                                        	break;

                                                	}


                                        	}


                                        	if( checker == 1){      //if the input member name is similar to already input name


                                              		check -> numberOfMeeting += dataset.numberOfMeeting;



                                        	}

                                        	else{                   //not equal name

                                                	csvFileRow++ ;

                                                	current = (analyzeData *)malloc(sizeof(analyzeData));

                                                	*current = dataset;

                                                	current -> csvFileRowNumber = csvFileRow ;

                                                	current -> next = pDataset;

                                                	pDataset = current;

                                                	total++;

                                        	}



                                	}




                        	}//-p


				else{

                                	WRONG_CONTAIN;

                                	return 0;

                        	}


			}//while


			fclose(pointerFile);    //close the file


		}//-p for

		analyzeData *temp ;

                int Index;

                lFlag =  check_L_flag( lFlag, total);           //check the lFlag value

		sortArrayParticipants( pDataset, lFlag );      //sort the linked list according number of participants

                maxStringLength = sortedArrayMaxString( pDataset, lFlag);               //find the maximum length of the string

                maxDigits = numberOfDigitsInInteger( pDataset -> numberOfMeeting);      //find the maximum digits of the numbers

                plotArea = TOTAL_LENGTH - TOTAL_SPACES_VBAR  - maxStringLength - maxDigits;                //graph area



                if( sFlag == 1 ){



                        NEW_LINE;


                        for( temp = pDataset, Index = 0; Index < lFlag ; temp = temp -> next, Index++ ){


                                patternArea = (temp -> numberOfMeeting * plotArea) / (pDataset -> numberOfMeeting)  ;

                                //1st row
                                spacePrint(maxStringLength);

                                fillGraphArea( patternArea);

                                NEW_LINE;

                                //2nd row
                                namePrint( temp -> memberName, maxStringLength );

                                fillGraphArea( patternArea);

                                printf("%d", temp -> numberOfMeeting);

                                NEW_LINE;

                                //3rd row
                                spacePrint(maxStringLength);

                                fillGraphArea( patternArea);

                                NEW_LINE;

                                //4th row
                                spacePrint(maxStringLength);

                                NEW_LINE;


                        }

                        finalVerticalLine(maxStringLength ,(TOTAL_LENGTH - maxStringLength - TOTAL_SPACES_VBAR) );     //final vertical line

                }


                else if( sFlag == 0){


                        sumOfElement = sumOfElementParticipant( pDataset );             //get the sum of all the participants

                        NEW_LINE;


                        for( temp = pDataset, Index = 0; Index < lFlag ; temp = temp -> next, Index++ ){


                                patternArea = (temp -> numberOfMeeting * plotArea) / (sumOfElement)  ;

                                //1st row
                                spacePrint(maxStringLength);

                                fillGraphArea( patternArea);

                                NEW_LINE;

                                //2nd row
                                namePrint( temp -> memberName, maxStringLength );

                                fillGraphArea( patternArea);

                                printf("%d", temp -> numberOfMeeting);

                                NEW_LINE;

                                //3rd row
                                spacePrint(maxStringLength);

                                fillGraphArea( patternArea);

                                NEW_LINE;

                                //4th row
                                spacePrint(maxStringLength);

                                NEW_LINE;



                        }

                        finalVerticalLine(maxStringLength ,(TOTAL_LENGTH - maxStringLength - TOTAL_SPACES_VBAR) );     //final vertical line


                }


	}//-p if



	else{ // -t Flag



		//get the files
                for( filePlace = 0; filePlace < size ; filePlace++  ){


                        if( checkSubString( argv[filesIndex[filePlace]] , ".csv" ) == -1 ){         //check .csv file

                                NOT_CSV_FILE;

                                return 0;

                        }



                        pointerFile = fopen( argv[filesIndex[filePlace]] , "r");   //read the file



                        if( pointerFile == NULL ){              //if file is wrong gives error message

                                NOT_OPEN_FILE ;

                                return 0 ;

                        }



                        while( fgets( buffer, MAX_LINE_SIZE , pointerFile ) ){  //get row information to buffer



                                pBuffer = buffer;


                                strcpy(dataset.memberName,"\0");
				strcpy(participants,"\0");
                                strcpy(timeCell,"\0");


				//-t
				if( sscanf( pBuffer, "%80[^,],%[^,],%8[^\n]", dataset.memberName, participants,timeCell ) != 0 ){  //check empty row


                                	if(( strcmp(dataset.memberName,"\0") == 0 ) || (strcmp(participants,"\0") == 0) ){      //check the empty cell  of name column and participants

                                        	WRONG_CONTAIN;

                                        	return 0;

                                	}



                                	if( findTime(timeCell) == -1 ){             //check empty cell of time column and not valid one

                                        	WRONG_CONTAIN;

                                        	return 0;

                                	}



                                	dataset.durationMinutes  =  findTime(timeCell);                         //convert time into minutes


                                	if( total == 0 ){

                                        	current = (analyzeData *)malloc(sizeof(analyzeData));

                                        	*current = dataset;

                                        	current -> csvFileRowNumber = csvFileRow ;

                                        	current -> next = pDataset;

                                        	pDataset = current;

                                        	total++;

                                	}


                                	else {

                                        	int checker = 0;

                                        	analyzeData *check;


                                        	for(check = pDataset; check != NULL ; check = check -> next ){

                                                	if( strcmp( check -> memberName,dataset.memberName ) == 0 ){    //check similar members similar names

                                                        	checker = 1;

                                                        	break;

                                                	}


                                        	}


                                        	if( checker == 1){      //if the input member name is similar to already input name


                                                	check -> durationMinutes += dataset.durationMinutes;

                                        	}

                                        	else{                   //not equal name

                                                	csvFileRow++ ;

                                                	current = (analyzeData *)malloc(sizeof(analyzeData));

                                                	*current = dataset;

                                                	current -> csvFileRowNumber = csvFileRow ;

                                                	current -> next = pDataset;

                                                	pDataset = current;

                                                	total++;

                                        	}



                                	}




                        	}//-t

				else{

                                	WRONG_CONTAIN;

                                	return 0;

                        	}


			}//while

			fclose(pointerFile);    //close the file

		}//-t for


		analyzeData *temp ;

                int Index;

                lFlag =  check_L_flag( lFlag, total);           //check the lFlag value
		
		sortArraytoTime( pDataset,lFlag );            //sort the linked list acording to time

                maxStringLength = sortedArrayMaxString( pDataset, lFlag);       //find the maximum length of the string


                maxDigits = numberOfDigitsInInteger( pDataset -> durationMinutes);      //find the maximum digits of the number


                plotArea = TOTAL_LENGTH - TOTAL_SPACES_VBAR - maxStringLength - maxDigits;                //graph area


                if( sFlag == 1){



                        NEW_LINE;


                        for( temp = pDataset, Index = 0; Index < lFlag ; temp = temp -> next, Index++ ){


                                patternArea = (temp -> durationMinutes * plotArea) / (pDataset -> durationMinutes)  ;

                                //1st row
                                spacePrint(maxStringLength);

                                fillGraphArea( patternArea);

                                NEW_LINE;

                                //2nd row
                                namePrint( temp -> memberName, maxStringLength );

                                fillGraphArea( patternArea);

                                printf("%d", temp -> durationMinutes);

                                NEW_LINE;

                                //3rd row
                                spacePrint(maxStringLength);

                                fillGraphArea( patternArea);

                                NEW_LINE;

                                //4th row
                                spacePrint(maxStringLength);

                                NEW_LINE;



                        }

                        finalVerticalLine(maxStringLength ,(TOTAL_LENGTH - maxStringLength - TOTAL_SPACES_VBAR) );     //final vertical line

                }


                else if( sFlag == 0){


                        sumOfElement = sumOfElementTime( pDataset);     //find the sum of the all the time

                        NEW_LINE;


                        for( temp = pDataset, Index = 0; Index < lFlag ; temp = temp -> next, Index++ ){


                                patternArea = ( temp -> durationMinutes * plotArea) / (sumOfElement)  ;

                                //1st row
                                spacePrint(maxStringLength);

                                fillGraphArea( patternArea);

                                NEW_LINE;

                                //2nd row
                                namePrint( temp -> memberName, maxStringLength );

                                fillGraphArea( patternArea);

                                printf("%d", temp -> durationMinutes);

                                NEW_LINE;

                                //3rd row
                                spacePrint(maxStringLength);

                                fillGraphArea( patternArea);

                                NEW_LINE;

                                //4th row
                                spacePrint(maxStringLength);

                                NEW_LINE;



                        }

                        finalVerticalLine(maxStringLength ,(TOTAL_LENGTH - maxStringLength - TOTAL_SPACES_VBAR) );     //final vertical line



                }


	}//-t

	//free the array

	free(filesIndex);

	return 0;


}

/******************************************************************** MAIN END ***************************************************************************************/



/****************************************************************** OTHER FUCTIONS ************************************************************************************/



//swap the two data set
void swap(analyzeData *first, analyzeData *second){

	analyzeData temp;

	strcpy(temp.memberName ,first -> memberName);
	temp.numberOfMeeting = first -> numberOfMeeting;
	temp.durationMinutes = first -> durationMinutes;
	temp.count = first -> count;
	temp.csvFileRowNumber = first -> csvFileRowNumber;

	strcpy(first -> memberName,second -> memberName);
	first -> numberOfMeeting = second -> numberOfMeeting;
	first -> durationMinutes = second -> durationMinutes;
	first -> count = second -> count;
	first -> csvFileRowNumber = second -> csvFileRowNumber;

	strcpy(second -> memberName,temp.memberName);
	second -> numberOfMeeting = temp.numberOfMeeting;
	second -> durationMinutes = temp.durationMinutes;
	second -> count = temp.count;
	second -> csvFileRowNumber = temp.csvFileRowNumber;


}


//check -l flag number is higher than the maximum number or not
int check_L_flag( int flagValue, int MAX){

	if( flagValue <= MAX ){

		return flagValue;

	}

	return MAX;


}



//check input file subs string
int checkSubString( char *source, char *search){


	char *ptr = strstr( source, search);

	if( ptr != NULL ){

		return 0;

	}

	return -1 ;

}


//find Maximum legth of the name in sorted array
int sortedArrayMaxString( analyzeData *source, int SIZE){

	analyzeData *temp;

	int maxStringLength = 0, index;

	for( temp = source, index = 0; index < SIZE ; temp = temp -> next, index++){

                if( maxStringLength < strlen(temp -> memberName) ){

                        maxStringLength = strlen(temp -> memberName);

                }

        }

	return maxStringLength;

}



//check participants is number or not
int participantsConvertToNumber( char *source){

	int returnValue;

	if( atoi(source) != 0){

		returnValue = atoi(source);

		return returnValue;

	}


	return 0;

}

//convert time into minutes
int findTime(char *source){

	unsigned int hour,minutes,seconds;
	int total;

	if(sscanf(source,"%02u:%02u:%02u",&hour,&minutes,&seconds) == 3){

		total = 60 * hour + minutes;

		return total;

	}

	else{

		return -1;

	}


}



//get the sum of the count
int sumOfElementCount( analyzeData *source ){

	int sum = 0 ;

	analyzeData *temp;

	for(temp = source; temp != NULL; temp = temp -> next){

		sum += temp -> count;

	}

	return sum;


}

//get the sum of the time
int sumOfElementTime( analyzeData *source ){

	int sum = 0;

	analyzeData *temp;

	for(temp = source; temp != NULL; temp = temp -> next){

                sum += temp -> durationMinutes;

        }

        return sum;


}


//get the sum of the participants
int sumOfElementParticipant( analyzeData *source ){

	int sum = 0;

	analyzeData *temp;

        for(temp = source; temp != NULL; temp = temp -> next){

                sum += temp -> numberOfMeeting;

        }

        return sum;


}



//count the digits in the number
int numberOfDigitsInInteger( int number ){

	int count = 0;

	while( number != 0){

		number = number / 10 ;

		count++;

	}

	return count;

}


//sort array according to count

void sortArraytoCount( analyzeData *source, int SIZE ){

	analyzeData *tempData1, *tempData2;

	int counting;

	for( tempData1 = source,counting = 0 ; counting < SIZE; tempData1 = tempData1 -> next, counting++ ){

        	for( tempData2 = tempData1 -> next; tempData2 != NULL ; tempData2 = tempData2 -> next){

                	if( tempData1 -> count < tempData2 -> count){

                        	swap(tempData1, tempData2);

			}


			else if( tempData1 -> count == tempData2 -> count){		//if data equal then sort according to row number

				if( tempData1 -> csvFileRowNumber >  tempData2 -> csvFileRowNumber ){

					swap(tempData1, tempData2);

				}


			}


		}

	}

}



//sort array according to duration time

void sortArraytoTime( analyzeData *source, int SIZE ){


	analyzeData *tempData1, *tempData2;

	int counting;
		
	for( tempData1 = source, counting = 0 ; counting < SIZE ; tempData1 = tempData1 -> next, counting++ ){

		for(tempData2 = tempData1 -> next; tempData2 != NULL ; tempData2 = tempData2 -> next){

			if( tempData1 -> durationMinutes < tempData2 -> durationMinutes){

				swap(tempData1, tempData2);

			}

			else if( tempData1 -> durationMinutes == tempData2 -> durationMinutes){		//if data equal then sort according to row number

				if( tempData1 -> csvFileRowNumber >  tempData2 -> csvFileRowNumber ){

					swap(tempData1, tempData2);

				}

			}


		}

	}

}



//sort according to number of participants
void sortArrayParticipants(analyzeData *source, int SIZE ){


	analyzeData *tempData1, *tempData2;

	int counting;


        for( tempData1 = source, counting = 0 ; counting < SIZE; tempData1 = tempData1 -> next, counting++ ){

                for( tempData2 = tempData1 -> next; tempData2 != NULL ; tempData2 = tempData2 -> next){

                        if( tempData1 -> numberOfMeeting < tempData2 -> numberOfMeeting){

                        	swap(tempData1, tempData2);

                        }

                        else if( tempData1 -> numberOfMeeting == tempData2 -> numberOfMeeting){		//if data equal then sort according to row number

                                if( tempData1 -> csvFileRowNumber >  tempData2 -> csvFileRowNumber ){

                                        swap(tempData1, tempData2);

                                }

                        }


                }

        }


}




/*
 *
 *	GRAPH SYMBOL
 *
 *	─       \u2500
 *	│       \u2502
 *
 *	└       \u2514
 *	░       \u2591
 *
 *
 */


//print space before until meet horizontal line of the graph
void spacePrint(int maxString ){

	int index = 0;

	SPACE ;

	for(index = 0; index < (maxString + 1) ; index++){

		SPACE ;


	}

	printf("\u2502");	// symbol is │


}



//graph filling
void fillGraphArea( float width ){

	int index;

	for( index = 0; index < width; index++){

		printf("\u2591");	//symbol is ░


	}




}


//print the name of the member for the axis
void namePrint( char *name, int MAX ){

	int nameSize, index;

	nameSize = strlen(name);

	printf(" %s",name);

	for( index = 0; index < (MAX - nameSize + 1 ) ; index++ ){

		SPACE ;

	}

	printf("\u2502");	// symbol is │



}


//print last vertical line
void finalVerticalLine(int maxString, int verticalBar){

	int index = 0;

        SPACE ;

        for(index = 0; index < (maxString + 1) ; index++){

                SPACE ;


        }

	printf("\u2514");	//symbol is └


	for( index = 0; index < verticalBar ; index++){

		printf("\u2500");	//symbol is ─

	}

	NEW_LINE;


}




