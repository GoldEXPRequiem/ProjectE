void enableInterrupts();
void main() 
//Step 4 by Kaue
//Step 5 and 6 by Ryan
{ 	char killCheck[4];
	char shell[6];
	char copyCheck[4];
	char delCheck[4];
	char dirCheck[4];
        char createCheck[6];
	char exeCheck[4]; //array to hold exec
	int filler=0; //number to help fill out exeCheck array
	char buffer[80]; //command line array
	char command[7]; // array to hold the actual command
	int i=0; //
	int exeFlag=0; //number to help see if the command is exec
	char filter;
	int dirFlag=0;
	int delFlag=0;
	int copyFlag=0;
    int createFlag=0;
	int killFlag=0;
	shell[0]='s';
	shell[1]='h';
	shell[2]='e';
	shell[3]='l';
	shell[4]='l';
	shell[5]='\0';
	enableInterrupts();
	while(filler<6){ //start of loop. this adds all of the characters 
			//to exec
	if(filler==0){
	killCheck[filler]='k';
	exeCheck[filler]='e';
	dirCheck[filler]='d';
	delCheck[filler]='d';
	copyCheck[filler]='c';
    createCheck[filler]='c';
	}
	if(filler==1){
	killCheck[filler]='i';
	exeCheck[filler]='x';
	dirCheck[filler]='i';
	delCheck[filler]='e';
	copyCheck[filler]='o';
    createCheck[filler]='r';
	}
	if(filler==2){
	killCheck[filler]='l';
	exeCheck[filler]='e';
	dirCheck[filler]='r';
	delCheck[filler]='l';
	copyCheck[filler]='p';
    createCheck[filler]='e';
	}
	if(filler==3){
	killCheck[filler]='l';
	exeCheck[filler]='c';
	dirCheck[filler]='\0';
	delCheck[filler]='\0';
	copyCheck[filler]='y';
    createCheck[filler]='a';
	}
    if(filler==4){
    createCheck[filler]='t';
    }
    if(filler==5){
    createCheck[filler]='e';
    }
	filler++;
	} //end of loop
        //char buffer[80]; 

        //char command[5]; 

//        char rest[13312];

        //int i = 0; 
	//int exeFlag=0;
  	//depending on how your read/printstring works, you may want to add 
	//these two commands as they will reset the command line so that its at
	//the beginning each time
	syscall(0,"\n");
	syscall(0,"\r");
	//print out shell
        syscall(0,"Shell>"); 
	//read in a line
        syscall(1, buffer); 

        for(i=0; i<6; i++)  
//this loop here puts the command in the command array

        { 

                char compart=buffer[i];
		if(compart==0x20){
		compart='\0';
		break;
		} 
                command[i]=compart; 

        } //end of loop
	//syscall(0,"Print");
  

        command[i]="/0"; //add a null terminator at the end 
//this first block of code is for type
 if(command[0] == 't' &&command[1] == 'y' && command[2] == 'p' && command[3] == 'e') 
 { 
		char* filename; //this is going to be the filename we are looking for
		char filenamepart; //this is going to be how we assemble the file
		int placement=0; //also is going to help us assemble the file
                char buffer2[13312]; //array for the file sectors

                int sectors=0; //the number of sectors
		//this while loop stores the letters of the file inside of
		//filename. Since I doubt we are going to use spaces as a way
		//to name files, there is a if statement that skips those
                while(buffer[i]!=0x0){ 
		if(buffer[i]==0x20){
			i++;
		} //end of if statement
                filenamepart=buffer[i]; 

                filename[placement]=filenamepart; 

                i++; 
		placement++;

        } //end of while loop

   	filename[placement+1]='\0'; //add a null terminator at the end
        syscall(3,filename,buffer2,&sectors);  //call readSector and pass everything required
	syscall(0,"\n");
	syscall(0,"\r");
	if(sectors==0){
	syscall(0,"File not found",0,0);
	}
	else{
        syscall(0,buffer2,0,0); //call printstring and print out contents
	}
}  // type ends
//syscall(0,"Here");
//sets i back to 0
if(i!=0){
i=0;
}
//this loop checks to see if command is exec
while(command[i]!=0x0&&i<6){
filter=exeCheck[i];
	if(command[i]==filter){
	exeFlag++;
	}
filter=dirCheck[i];
	if(command[i]==filter){
	dirFlag++;
	}
filter=delCheck[i];
	if(command[i]==filter){
	delFlag++;
	}
filter=copyCheck[i];
	if(command[i]==filter){
	copyFlag++;
	}
filter=createCheck[i];
    if(command[i]==filter){
    createFlag++;
    }
filter=killCheck[i];
	if(command[i]==filter){
	killFlag++;
	}
i++;
} //while loop ends

//if the command is exec, then do this
if(exeFlag==4){
	char* fileNameArray;
	int sectorsread=0;
	char fileName[6]; //This is going to be the file
	int Placement=0; //helps us place the characters correctly
	char filePart; //helps get each letter
	//same purpose as the type while loop
	while(buffer[i]!=0x0){
		if(buffer[i]==0x20){
		i++;
		}
	filePart=buffer[i]; //get the character
	fileName[Placement]=filePart; //add it to the filename
	i++;
	Placement++;
	} //end of while loop
syscall(3,fileName,fileNameArray, &sectorsread);
if(sectorsread==0){
	syscall(0,"/r");
	syscall(0,"/n");
	syscall(0,"Unknown file",0,0);
}
syscall(4,fileName); //call readFile
} //end of if statement
if(dirFlag==3){
int numofFiles=0;
char directory[512];
int place=0;
syscall(2,directory,2);
	while(numofFiles<16){
	char f_Byte=directory[place];
		if(f_Byte==0){
		int zero=0;
		}
		else{
		char* theFileName;
		theFileName[0]=directory[place];
		theFileName[1]=directory[place+1];
		theFileName[2]=directory[place+2];
		theFileName[3]=directory[place+3];
		theFileName[4]=directory[place+4];
		theFileName[5]=directory[place+5];
		theFileName[6]='\0';
		syscall(0,"\r");
		syscall(0,"\n");
		syscall(0,theFileName);
		} //end of else
	place=place+32;
	numofFiles++;
	}// of while loop
} //end of the dir command
if(delFlag==3){
char* deadFile;
int i=0;
while(i<6){
deadFile[i]=buffer[i+4];
i++;
}
syscall(7,deadFile);
}

if(copyFlag==4){
char* firstFile;
char firstFilesize[13312];
char* newFile;
char newFilesize[13312];
int sectors=0;
char filenamepart;
int check=0;
int linePlace=5;
i++;
	while(buffer[linePlace]!=0x20||check<6){
		if(buffer[linePlace]==0x20){
			break;
		}
	filenamepart=buffer[linePlace];
	syscall(10,filenamepart);
	firstFile[check]=filenamepart;
	i++;
	check++;
	linePlace++;
	}
firstFile[check]='\0';
check=check*0;
	while(buffer[i]!=0x0&&check<6){
		if(buffer[i]==0x20){
		break;
		}
	filenamepart=buffer[i];
	syscall(10,filenamepart);
	newFile[check]=filenamepart;
	i++;
	check++;
	}
newFile[check]='\0';
syscall(3,firstFile,firstFilesize,&sectors);
/*if(sectors>0){
syscall(10,'C');
}*/
//syscall(0,firstFile,0,0);
syscall(8,firstFilesize,newFile,sectors);
} //end of copy command
if(killFlag==4){
char process;
if(buffer[i]==0x20){
i++;
}
process=buffer[i]-'0';
syscall(9,process);
}

if(command[0]=='c'&&command[1]=='r'&&command[2]=='e'&&command[3]=='a'
&&command[4]=='t'&&command[5]=='e')
        {
                //int create;
		int numofEnter=0;
		int placement=0;
                char buffer3[300];
		char buffer4[300];
		int flag=0;
                while(flag!=1)//This while loop should keep running 
                                     //unless user enters an empty line
                {	int enterflag=0;
			int enter=0;
			int Placement=0;
			char firstEnter;
			syscall(0,"\r");
			syscall(0,"\n");
			syscall(1,buffer4);
			/*while(buffer3[placement]!=0x0A||enter!=numofEnter){
				firstEnter=buffer3[placement];
				placement++;
				if(firstEnter==0x0A
				&&firstEnter==buffer3[placement+1]){
				}
			}
			if(buffer3[placement]==0x0A){
				enter++;
				numofEnter=numofEnter+enter;
			}*/
			while(buffer4[Placement]!=0x0){
				char letter;
				letter=buffer4[Placement];
				buffer3[placement]=letter;
				syscall(10,'A');
				Placement++;
				placement++;
			}
			//buffer3[Placement]=='\0';
			syscall(0,buffer3);
                        if(buffer3[i]=='\0')
                        {
                                break;
                        }
		}                        //syscall(1,buffer3);

                        syscall(8,buffer3,command+7,1);
                }


/*
if(createFlag==6){
char buffer3[300];

                //while(buffer[i]!=0x0)//This while loop should keep running unless user enters an empty line
                //{
                        //if(buffer[i]=='\0')
                        //{
                                //break;
                        //}

                        syscall(1,buffer3);

                        syscall(8,buffer3,command+7,1);
                }

}
//if either command fails or unknown command
*/
if(exeFlag!=4&&command[0]!='t'&&dirFlag!=3&&delFlag!=3&&copyFlag!=4&&
createFlag!=6&&killFlag!=4){
	syscall(0,"\r");
	syscall(0,"\n");
	syscall(0,"unknown command",0,0);
}
	syscall(4,shell,0,0);//reload the shell
        while(1); 


} 

