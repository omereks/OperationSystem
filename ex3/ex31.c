
// Omer Eckstein 312350912

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define IDENTICAL_EXIT 1
#define DIFFERENT_EXIT 2
#define SIMILAR_EXIT 3
#define EXCEPTION_EXIT -1

void WriteMsgWithExec(const char* msg)
{
	write(2, msg, strlen(msg));
	exit(EXCEPTION_EXIT);
}

// case insensitive
int checkSmallCapital(char *c1, char *c2) {
    // if c1 and c2 are both letters
    if ((97 <= *c1 && *c1 <= 122 || 65 <= *c1 && *c1 <= 90) &&
            (97 <= *c2 && *c2 <= 122 || 65 <= *c2 && *c2 <= 90)) {
        if(abs(*c1 - *c2) == 32) {
			return 1;
        }
    }
    return 0;
}

//get path and fill the buffer, if error ecourd will return -1
int fillBuffer(char* buffer , char* path) {
	int fileFD, numBytes = 0, i = 0;
	if ((fileFD = open(path,O_RDONLY)) < 0)
		return -1;
	while (i < 150)
	{
		numBytes += read(fileFD,(numBytes + buffer), 1);
		i++;
	}
	close(fileFD);
	return 1;
	
}
int main(int argc, char* argv[])
{
	char bufferOne[150], bufferTwo[150];
	
	//fill the buffers
	if ( ((fillBuffer(bufferOne, argv[1])) == -1) || (fillBuffer(bufferTwo, argv[2]) == -1) ){
		return -1;
		//WriteMsgWithExec("Error in: read");
	}

	
	 //printf("%s\n", bufferOne);
     //printf("%s\n", bufferTwo);

	int i = 0, offSetOne = 0 , offSetTwo = 0;
	char charFileOne,charFileTwo; 
	int boolIdenticalSimilar = 1;  // 1 for Identical , 0 for similiar
	while (i < 150)
	{
		charFileOne = bufferOne[offSetOne+i];
		charFileTwo = bufferTwo[offSetTwo+i];
		//printf("%d\n", charFileOne);
		//printf("%d\n", charFileTwo);
		
		//end files
		if (!charFileOne && !charFileTwo){
			if(boolIdenticalSimilar)
				return 1;
				//exit(IDENTICAL_EXIT);
			else
				return 3;
				//exit(SIMILAR_EXIT);
		}

		// if there is some differnt
		if (charFileOne != charFileTwo)
		{
			//printf("%c\n", charFileOne);
			boolIdenticalSimilar = 0; // not identical



			if (charFileOne == '\r' || charFileOne == '\n' || charFileOne == 32) {
                offSetTwo--;
				i++;
				continue;
            }
            if  (charFileTwo == '\r' || charFileTwo == '\n' || charFileTwo == 32) {
                offSetOne--;
				i++;
				continue;
            }
			// if charFileOne and charFileTwo are not both letters and differnt in small and capital
			if((charFileOne!=0) && (charFileTwo!=0) && (!checkSmallCapital(&charFileOne, &charFileTwo)))
				return 2;
				//exit(EXCEPTION_EXIT);

		}	
		i++;
	}
	printf("asd");
	if(charFileOne != charFileTwo)
		return 2;
	if(boolIdenticalSimilar)
		return 1;
		//exit(IDENTICAL_EXIT);
	else
		return 3;
		//exit(SIMILAR_EXIT);

}