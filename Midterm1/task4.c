#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>



int str_to_int(char *str){
    int result;
    int x;

        result = 0;
        x = 1;
        while ((*str >= '0') && (*str <= '9'))
        {
            result = (result * 10) + ((*str) - '0');
            str++;
        }
        return (result * x);
}

char* int_to_str(int value){
    
}

int isNum(char c){

	int ascii = (int)c;

	if(ascii >= (int)'0' && ascii <= (int)'9'){
		return ascii;
	}
	return 0;
}

int main(int argc, char *argv[])
{
    char buffer;
    char buffer2;
    char buffer3;
    int counter = 0;
    int InFileDes;
    int OutFileDes2, OutFileDes3, OutFileDes4, OutFileDes5;
    
    umask(0);
    InFileDes = open(argv[1], O_RDONLY);
    OutFileDes2 = open(argv[2], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR | S_IRGRP|S_IWGRP | S_IROTH|S_IWOTH);
    OutFileDes3 = open(argv[3], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR | S_IRGRP|S_IWGRP | S_IROTH|S_IWOTH);
    OutFileDes4 = open(argv[4], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR | S_IRGRP|S_IWGRP | S_IROTH|S_IWOTH);
    OutFileDes5 = open(argv[5], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR | S_IRGRP|S_IWGRP | S_IROTH|S_IWOTH);

    //Fills file with numbers from input file
    while ((read(InFileDes, &buffer, 1) > 0)){
        if(isNum(buffer) || buffer == ' ' || buffer == '\n'){
            write(OutFileDes3, &buffer, 1);
        }
        else {
            write(OutFileDes3, " ", 1);
        }
    }

    lseek(InFileDes, 0, SEEK_SET);
    // Fills file with charcters from input file
    while ((read(InFileDes, &buffer, 1) > 0)){
        if(buffer >= 'a' && buffer <= 'z' || buffer >= 'A' && buffer <= 'Z' || buffer == ' ' || buffer == '\n'){
            write(OutFileDes2, &buffer, 1);
        }
        else {
            write(OutFileDes2, " ", 1);
        }
    }
    
    lseek(InFileDes, 0, SEEK_SET);
    // Fills file with special charcters from input file
    while ((read(InFileDes, &buffer, 1) > 0)){
        if(buffer >= 33 && buffer <= 47 || buffer >= 58 && buffer <= 64 || buffer >= 91 && buffer <= 96 || buffer == '\n'){
            write(OutFileDes4, &buffer, 1);
        }
        else{
            write(OutFileDes4, " ", 1);
        }
    }

    // Sets the file descriptors back to the beginning of each outputfile
    lseek(OutFileDes2, 0, SEEK_SET);
    lseek(OutFileDes3, 0, SEEK_SET);
    lseek(OutFileDes4, 0, SEEK_SET);
    // Replicates inputfile with the output files writing to the copy file
    while ((read(OutFileDes2, &buffer, 1) && read(OutFileDes3, &buffer2, 1) && read(OutFileDes4, &buffer3, 1) > 0)){
        if(buffer >= 'a' && buffer <= 'z' || buffer >= 'A' && buffer <= 'Z'){
            write(OutFileDes5, &buffer, 1);
            continue;
        }
        else if(isNum(buffer2)){
            write(OutFileDes5, &buffer2, 1);
            continue;
        }
        else if(buffer3 >= 33 && buffer3 <= 47 || buffer3 >= 58 && buffer3 <= 64 || buffer3 >= 91 && buffer3 <= 96 || buffer3 == '\n'){
            write(OutFileDes5, &buffer3, 1);
            continue;
        }
        else if(buffer == '\n' && buffer2 == '\n' && buffer3 == '\n'){
            write(OutFileDes5, &buffer, 1);
            continue;
        }
        else if(buffer == ' ' && buffer2 == ' ' && buffer3 == ' '){
            write(OutFileDes5, &buffer, 1);
            continue;
        }
        else{
            write(OutFileDes5, &buffer, 1);
            continue;
        }
    }
    

    close (InFileDes);
    close (OutFileDes2);
    close (OutFileDes3);
    close (OutFileDes4);
    close (OutFileDes5);

    
    exit (0);
}