/*
interrupt example:
 make a function "happensOnAnInterrupt"
prints something out
link it it up with an 'interrupt pin'
	when interrupt happens, function runs
put an electrical connection on pin 2
	when pin 2 goes from ground to 5v, function runs
attachInterrupt(digitalPinToInterrupt(2), happensOnAnInterupt, RISING)
10
way to make code automatically run on a hardware event
interrupt 'transparent' interrupted function has no idea
that the interrupt happened

where is this used for real:
buttons, want program to respond to buttons
 interrupt used to respond to buttons

 mousePressed()
20 event-driven programming

mouse button--> interrupt to proc-->stops, goes to OS--> OS finds program-->
OS sends event program--> OS sends event to program-->mousePressed() runs

"interval timer"
	set a device to 'ding 'in a few ms when ready
	run an interrupt function
	-autosave, upload, 
	-multitasking
30	run program 1 for 1ms
	run program 2 for 1ms
	run program 1 for 1ms

int 80
 forked, or printed to screen
 system calls run through interrupt call
 kind-of like a function call

'hardware interrupt'
 40timer, button, interrupts program

'software interrupt'
 
'fault/execption'
processor sees the program do something bad, it calls int

divide by zero

segfault:
50	1. if you want memory, ask for it
	2. OS sets up trip wires

	char* var;
	NULL means 0
	printf(var);

why say:
 int 80 instead of OS_call(fork)
 - CP/M called function address 0005
60
 last 40 years, we use an inteerupt instead of func call

 protection: way to allow OS sole control over mem and devices 

 proc has two modes:

-"real or kernel mode": can do everything
 if go to mmemory 10, actually go to 10 can access devices
 DANGEROUS!
70-'protected or user mode': locked down
	if you go to memory 10, actually go to somewhere else
	if go to device, shut down
	limited damage
an interrupt happens
	1. triggering event: int 21
	2. pause program
	3. backup line number (program counter), also regs on stack
	4. switch to kernel mode
	5. go to a special table 'Interrupt Vector Table'
80	6. pick routine out of 21st entry of table
	7. jump to routine
		OS interrupt routine
	8. IRET instrucion
	9. swithc back to user mode
	10. read the line number from stack
	11. resume program
*/
void readFile(char*, char*, int*);
void printChar(char);
void printString(char*);
void readString(char*);
void readSector(char*, int);
void handleInterrupt21(int, int, int, int);
void executeProgram(char*);
void terminate();
void size(char*, int*);
void stringCompare(char*, char*, int, char*);
void random(int);
void writeSector(char*, int);
void deleteFile(char*);
void writeFile(char*,char*,int);
void handleTimerInterrupt(int, int);
void returnFromTimer(int, int);
void kill(int);
int processActive[8];
int processStackPointer[8];
int currentProcess;

void main() {
/*
char line[80];
char buffer[512];
char buffer2[13312];
int sectorsRead;
makeInterrupt21();
// Project C Step 1 test code
interrupt(0x21,3,"messag",buffer2,&sectorsRead);
if(sectorsRead!=0){
interrupt(0x21,0,buffer2,0,0);
}
if(sectorsRead==0){
interrupt(0x21,0,"message not found\r\n",0,0);
}
*/
int setter=0;
char shell[6];
shell[0]='s';
shell[1]='h';
shell[2]='e';
shell[3]='l';
shell[4]='l';
shell[5]='\0';
makeInterrupt21();
//interrupt(6,tester,random_sector,0);
for(setter=0; setter<8; setter++){
processActive[setter]=0;
processStackPointer[setter]=0xff00;
}
currentProcess=-1;
//makeTimerInterrupt();
interrupt(0x21,4,shell,0,0);
makeTimerInterrupt();
/*
makeInterrupt21();
interrupt(0x21,3,"messag",buffer,&sectors);
if(sectors!=0){
	printChar('Z');
}
printChar('E');
//interrupt(0x21,5,0,0,0);
//interrupt(0x21,8,"this a test message","testm",3);
/*
interrupt(0x21,1,line,0,0);
interrupt(0x21,0,line,0,0);
/*
printString("Enter a line: ");
readString(line);
/*printString("HI there");*/
/*
printString(line);
/*int VideoMemoryStart=0xb800;
int VideoOffset=0x0;
int white =0x7;
/*100int red =0x6;*/
/*
int i=0;
char* characters="Hello World\0";
while(characters[i] !=0x0){
putInMemory(VideoMemoryStart, VideoOffset, characters[i]);
VideoOffset++;
/*if(i%2==0){
putInMemory(VideoMemoryStart, VideoOffset, red);
i++;
}110*/
/*
putInMemory(VideoMemoryStart, VideoOffset, white);
i++;
VideoOffset++;
/*characters++;*/
/*
}
*/
while(1);
/*120*/
}
/*step 1 */
void printString(char* a){
int i=0;
while(a[i]!=0x0){
char b=a[i];
interrupt(0x10,0xe*256+b,0,0,0);
i++;
}
}
/*step 2 */
void readString(char* a){
int ah=0x0;
int i=0;
char chara=0x0;
while(chara != 0xd){
/*inside of while loop*/
chara=interrupt(0x16,ah,0,0,0);
if(chara==0x8&&i!=0){
a[i]=0x0;
i--;
printChar(0x20);
printChar(0x8);
/*
printChar(" ");
printChar(0x8);
*/
}
if(chara==0x8&&i==0){
a[i]=0x0;
}
if(chara!=0x8){
a[i]=chara;
i++;
}
printChar(chara);
/*
if(chara==0x8){
chara="";
a[i]="";
printChar(a[i]);
}
else{
printChar(chara);
}
*/
}
/*while loop ends*/
a[i+1]="\r";
a[i+2]="\n";
a[i+3]="\0";
}
/*Step 3 and 4 by Kaue */


void readSector(char* buffer,int sector) 

{ 

int AH = 2; 

int AL = 1; 

int BX = buffer; 

int CH = 0; 

int CL = sector+1; 

int DH = 0; 

int DL = 0x80; 

int AX = AH*256+AL; 

int CX = CH*256+CL; 

int DX = DH*256+DL; 

interrupt(0x13, AX, BX, CX, DX); 

} 
//Step 1 of Part D done by Ryan
void writeSector(char* buffer, int sector){
int AH=3;
int AL=1;
int BX=buffer;
int CH=0;
int CL=sector+1;
int DH=0;
int DL=0x80;
int AX=AH*256+AL;
int CX=CH*256+CL;
int DX=DH*256+DL;
interrupt(0x13,AX,BX,CX,DX);
} 

/*Step 4 of ProjectB and I think other steps of the different projects.
 I honestly forgot what other parts are invovled, but i'll just say Step *
so I hit all of the steps needed here.
*/ 

void handleInterrupt21(int ax, int bx, int cx, int dx) 
/*Step 5 by Ryan Blake*/
{
if(ax==0){
printString("\n");
printString(bx);
} 
if(ax==1){
readString(bx);
}
if(ax==2){
readSector(bx,cx);
}
/*else{
printString("Interrupt has occurred");
}*/
if(ax==3){
readFile(bx,cx,dx);
}
if(ax==4){
executeProgram(bx);
}
if(ax==5){
terminate();
}
if(ax==6){
writeSector(bx,cx);
}
if(ax==7){
deleteFile(bx);
}
if(ax==8){
writeFile(bx,cx,dx);
}
if(ax==9){
kill(bx);
}
if(ax==10){
printChar(bx);
}
if(ax>10){
printString("Interrupt has occurrred"); 
}
} 

void printChar(char a){
interrupt(0x10, 0xe*256+a,0,0,0);
}
void readFile(char* file, char* buffer, int* sectors){
char* theFile;
char directory[512];
int dirsec=0;
int fileEntry=0;
int potentialSectors;
int i;
int filesize=0;
int fileNameParts=0;
*sectors=0;
while(i<6&&file[i]!='\r'){
    char letter=file[i];
    theFile[i]=letter;
    i++;
    filesize++;
}
theFile[i]=0x0;
readSector(directory, 2);
for(i=0;i<512;i=i+32){
//stringCompare(theFile,directory,i,&dirsec);

//printChar(char1);
if(file[0]==directory[0+i]&&file[1]==directory[1+i]&&file[2]==directory[2+i]
	&&file[3]==directory[3+i]&&file[4]==directory[4+i]
	&&file[5]==directory[5+i]){
	for(potentialSectors=0; potentialSectors<26; potentialSectors++){
		if(directory[i+potentialSectors+6]==0x00){
            		break;
		}
		else{
		readSector(buffer, directory[i+potentialSectors+6]); 
		buffer=buffer+512;
		*sectors=*sectors+1;
		}//else

	}//second For loop
i=512;
}//if statement
}
//first for loop
}//method
/*
*/
void executeProgram(char* filename){
char buffer[13312];
int counter=0;
int Sectorsread=0;
int steppingArray=0;
int dataseg, segment;
//int sizeofarray; was part of something else
readFile(filename, buffer, &Sectorsread);
//size(buffer,&sizeofarray); tried to ge the size of the array by making my own little size 
//method
dataseg=setKernelDataSegment();
for(steppingArray=0; steppingArray<8; steppingArray++){
if(processActive[steppingArray]==0){
break;
}
steppingArray++;
}//end of while loop
restoreDataSegment(dataseg);
segment=(steppingArray+2)*0x1000;
for(counter=0; counter<13312;counter++){
putInMemory(segment, counter, buffer[counter]);
//offSet++;
}
//printChar('A');
//launchProgram(0x2000);
initializeProgram(segment);
dataseg=setKernelDataSegment();
processActive[steppingArray]=1;
processStackPointer[steppingArray]=0xff00;
restoreDataSegment(dataseg);
}
void terminate(){
//printChar('S'); testing to see if loop ends
//while(1); For part 3
int dataseg;
dataseg=setKernelDataSegment();
processActive[currentProcess]=0;
restoreDataSegment(dataseg);
while(1);
/*char* shell;
shell[0]='s';
shell[1]='h';
shell[2]='e';
shell[3]='l';
shell[4]='l';
shell[5]='\0';
interrupt(0x21,4,shell,0,0);
*/
}
void writeFile(char* buffer, char* name, int numsect){
char dir[512];
char map[512];
int entry=0;
int fill=0;
int m=3;
int i=0;
readSector(dir,2);
readSector(map,1);
	for(entry=0;entry<512;entry+=32){
		if(dir[entry]==0){
			for(i=0;i<6;i++){
				if(name[i]==0){
				dir[entry+i]='\0';
				}
				else{
				dir[entry+i]=name[i];
				}
			} //second for loop end

		} //first if statement end
	if(i==6){
	break;
	}	//if we found an entry, we only want to do it once, so this breaks
        //the loop
} //end of the first for loop
	for(fill=0;fill<numsect;fill++){
		for(m=3; m<512;m++){
			if(map[m]==0){
			break;
			} //end of second for loop

		}
	map[m]=0xff;
	dir[entry+6+fill]=m;
	writeSector(buffer+512*fill,m);
	} //end of first for loop
writeSector(dir,2);
writeSector(map,1);
}

void deleteFile(char* file){
char directory[512];
char map[512];
int fileExists=0;
int potFile=0;
readSector(directory,2);
readSector(map,1);
	while(potFile<16){
	int tester=0;
	int fileCheck=0;
		while(tester<6){
			if(file[tester]==directory[tester+fileExists]){
			fileCheck++;
			} //if statement end
		tester++;
		} //while loop end
		if(fileCheck==6){
		int marker=0;
		directory[fileExists]='\0';
			while(directory[tester+fileExists+marker]!=0x0){
			char mapmarker=directory[tester+fileExists+marker];
			int mapspot=(int)mapmarker;
			map[mapspot]=0x0;
			marker++;
			} //while loop end
		} //if statement end
	fileExists=fileExists+32;
	potFile++;
	} //while loop end
writeSector(directory,2);
writeSector(map,1);
}
void handleTimerInterrupt(int segment, int sp){
int dataseg;
dataseg=setKernelDataSegment();
if(currentProcess!=-1){
processStackPointer[currentProcess]=sp;
}
currentProcess+=1;
if(currentProcess==8){
currentProcess=0;
}
while(1){
if(processActive[currentProcess]==1){
break;
}
currentProcess+=1;
if(currentProcess==8){
currentProcess=0;
}
} //end of while loop
segment=(currentProcess+2)*0x1000;
sp=processStackPointer[currentProcess];
restoreDataSegment(dataseg);
//printChar('H');
//printChar('I');
returnFromTimer(segment,sp);
}

void kill(int process){
int dataseg;
int counter=0;
int processCheck=0;
dataseg=setKernelDataSegment();
if(processActive[process]==1){
processActive[process]=0;
counter++;
}
processCheck=currentProcess;
restoreDataSegment(dataseg);
/*if(process==processCheck){
printChar('A');
}*/
}
void stringCompare(char* array1, char* array2, int spot, int* checker){
int number=0;

	for(number=0; number<6&&array1[number]!='\r';number++){
		if(array1[number]==array2[number+spot]){
		*checker=*checker+1;
		}
	number++;
	}
}

void size(char* array, int* arraysize){
char buffer[13312];
int Sectors;
int i;
readFile(array, buffer, &Sectors);
while(array[i]!=0x0C){
i++;
*arraysize=*arraysize+1;
}
}
void random(int number){
switch(number/5){
case 0:
number=(number*2)/5;
break;
case 1:
break;
}

}

/*
delete file hints:
change the first byte/bit/whatever you want to call it to 0
change the map entry(s) to 00 instead of FF
Write File hints:
load the dir and map into arrays
iterate through the directory until you find a /0
copy the name of the file to the six bytes of the entry with the entry
being the starting point of the name
look for the entry with the 00 and not FF. Dont start at 0 as that is
the bootloader, so start at the 3rd entry.
Set that one to FF
Add the sector number to the directory
Write 512 bytes from the buffer holding the file to the sector you just
kidnapped from its parents
set all of the remaining entry to 0's
*/

