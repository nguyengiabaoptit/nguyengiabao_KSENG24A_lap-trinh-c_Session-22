#include <stdio.h>
#include <string.h>

struct Account{
    char name[50];
    char password[50];
};

struct Account data[50];

int n;

void loadAccount();

void saveAccount();

void signIn();

void signUp();

int main(){
	int type;
	do{
		printf("\nMENU\n");
		printf("1. Dang nhap\n");
		printf("2. Dang ky\n");
		printf("3. Thoat\n");
		printf("Lua chon cua ban: ");
		scanf("%d",&type);
		fflush(stdin);
		switch(type){
			case 1:
				signIn();
				break;
			case 2:
				signUp();
				break;
		}
	}while(type!=3);
	return 0;
}

void loadAccount(){
    FILE *fptr=fopen("account.bin","rb");
    if(fptr){
        fread(&n,sizeof(int),1,fptr);
        fread(data,sizeof data,n,fptr);
        fclose(fptr);
    }
}

void saveAccount(){
    FILE *fptr=fopen("account.bin","wb");
    fwrite(&n,sizeof(int),1,fptr);
    fwrite(data,sizeof data,n,fptr);
    fclose(fptr);
}

void signIn(){
	loadAccount();
	char name[50],password[50];
	printf("vui long nhap ten tai khoan: ");
	fgets(name,sizeof name,stdin);
	name[strcspn(name,"\n")]='\0';
	int i=0;
	while(i<n){
		if(strcmp(data[i].name,name)==0){
			printf("vui long nhap mat khau tai khoan: ");
			fgets(password,sizeof password,stdin);
			password[strcspn(password,"\n")]='\0';
			if(strcmp(data[i].password,password)==0){
				printf("dang nhap thanh cong\n");
				return;
			}
			printf("sai mat khau\n");
			return;
		}
		i++;
	}
	printf("tai khoan khong ton tai");
}

void signUp(){
	loadAccount();
	char name[50];
	printf("vui long nhap ten tai khoan: ");
	fgets(name,sizeof name,stdin);
	name[strcspn(name,"\n")]='\0';
	int i=0;
	while(i<n){
		if(strcmp(data[i].name,name)==0){
			printf("tai khoan da ton tai");
			return;
		}
		i++;
	}
	strcpy(data[n].name,name);
	printf("vui long nhap mat khau tai khoan: ");
	fgets(data[n].password,sizeof data[n].password,stdin);
	data[n].password[strcspn(data[n].password,"\n")]='\0';
	n++;
	saveAccount();
}
