/*
 * This the code by Anthony Prajwal P
 * 
 * Implementation of one-pass Macroprocessor
 * Input is taken form input.txt, and creates macro.txt and output.txt files.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char label[10], opcode[10], operand[10], maclabel[10];
	char label1[10], opcode1[10], operand1[10];
	char l1[10];
	int count;
	FILE *f1, *f2, *f3;
	f1 = fopen("input.txt", "r");
	f2 = fopen("macro.txt", "w");
	f3 = fopen("output.txt", "w");
	
	while(fscanf(f1,"%s%s%s",label, opcode, operand) != EOF){
		if(strcmp(opcode, "MACRO") == 0){
			strcpy(maclabel,label);
			fscanf(f1, "%s%s%s", label, opcode, operand);
			while(strcmp(opcode, "MEND") != 0){
				fprintf(f2,"%s\t%s\t%s\t\n",label, opcode, operand);
				fscanf(f1, "%s%s%s", label, opcode, operand);
			}
		}
	}
	
	rewind(f1);
	fclose(f2);
	
	while(fscanf(f1,"%s%s%s",label, opcode, operand) != EOF){
		if(strcmp(opcode,"MACRO") == 0){
			while(strcmp(opcode, "MEND") != 0){
				fscanf(f1, "%s%s%s", label, opcode, operand);
			}
		}
		else if(strcmp(opcode,"END") == 0){
			break;
		}
		else if(strcmp(opcode,maclabel) == 0){
			strcpy(l1,label);
			count = 1;
			f2 = fopen("macro.txt","r");
			while(fscanf(f2,"%s%s%s",label1, opcode1, operand1) != EOF){
				if(count == 1){
					fprintf(f3,"%s\t%s\t%s\n",l1,opcode1,operand1);
					count = 0;
				}
				else 
					fprintf(f3,"%s\t%s\t%s\n",label1,opcode1,operand1);
			}
			fclose(f2);
		}
		else if(strcmp(opcode,"MACRO") != 0 && strcmp(opcode, "MEND") != 0){
			fprintf(f3,"%s\t%s\t%s\n",label,opcode,operand);
		}
		
	}
	fclose(f1);
	fclose(f3);
}
