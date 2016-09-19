#include <iostream>
using namespace std;

int count=0;
int sign=0;
void printchar(unsigned char input){
	for (int i = 0; i < 8; i++) {
	      printf("%d", !!((input << i) & 0x80));
	  }  
	printf("\n");
}
int eight(unsigned char a, unsigned char b, unsigned char c ){
	if(b==255){count++;return 1;}

	unsigned char D=~(a|b|c);
	while(D){
		unsigned char bit= D&-D;
		D-=bit;
		// unsigned int output=(unsigned int) ~D;
		// printf("%d\n",output );
		// if(int(D)!=-1)	printchar(~D);
		eight((a|bit)<<1,b|bit,(c|bit)>>1);
			// sign=0;
		
	}

	return count;
}

int main(){
	
	printf("%d\n",eight(0,0,0));
	return 0;
}

