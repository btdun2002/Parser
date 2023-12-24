#include <stdio.h>

extern void compile(char * );

int	main(int argc, char * argv[]){
	if (argc != 2){
		printf("Syntax error:\n\nC:\\>pl0.exe filename.pl0\n\n");
	}else{
  		compile(argv[1]);
  		printf("\n\nThanh cong\n\n");
	}

	return 0;
}
