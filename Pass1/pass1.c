#include<stdio.h>
#include<string.h>

int main(){
	int locctr,length,len,op, start;
	char label[10], opcode[10], operand[10], code[10];
	FILE *f1, *f2, *f3, *f4;
	f1 = fopen("input.txt","r");
	f2 = fopen("optab.txt","r");
	f3 = fopen("systab.txt","w");
	f4 = fopen("out.txt","w");
	
	fscanf(f1,"%s%s%x",label,opcode,&op);
	
	if(strcmp(opcode,"START") == 0){
		
		start = op;
		locctr = start;
		fprintf(f4,"\t%s\t%s\t%x\n", label, opcode, op);
		fscanf(f1,"%s%s%s",label,opcode,operand);
	}
	else
		locctr = 0;
	
	while(strcmp(opcode,"END") != 0){
		fprintf(f4,"%x\t",locctr);
		
		if(strcmp(label,"-") != 0){
			fprintf(f3,"%s\t%x\n",label, locctr);
		}
		
		rewind(f2);
		
		while(!feof(f2)){
			fscanf(f2,"%s",code);
			if(strcmp(opcode,code) == 0){
				locctr = locctr + 3;
				break;
			}
		}
		
		if(strcmp(opcode,"WORD") == 0){
			locctr = locctr + 3;
		}
		else if(strcmp(opcode,"RESW") == 0){
			locctr = locctr + 3 * atoi(operand);
		}
		else if(strcmp(opcode,"RESB") == 0){
			locctr = locctr + atoi(operand);
		}
		else if(strcmp(opcode,"BYTE") == 0){
			
			if(operand[0] == 'X'){
				locctr = locctr + 1;
			}
			else{
				len = strlen(operand) - 3;
				locctr = locctr + len;
			}
		}
		fprintf(f4,"%s\t%s\t%s\n",label,opcode,operand);
		fscanf(f1,"%s%s%s",label,opcode,operand);
	}
	
	fprintf(f4,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
	printf("\nThe length of the program is:%d\n",(locctr - start));
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
}
