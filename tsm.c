#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

/***** Globals ******/
int **cityMatrix;  /*the city matrix*/
int numCities;     //number of cities represented in the array
int best;          //the best path
int* arr3;
int flag = 0;
/* Here we retrieve the input specified at the command line
and count line breaks to determine numCities.  Array is stored
in a two dimensional array cityMatrx */
int get_input(char filename[])
{
  
  FILE* fp;
  int i,j;  

  //open file
  fp = fopen(filename, "r");
  
  if(!fp)
    {
      printf("Cannot open file %s\n", filename);
      exit(1);
    }

  //count how many line breaks there are. This is integral so we
  //can access and process the input array
  else
    {
      numCities = 0;
      int c;
      while (c != EOF)
	{
	  c = fgetc(fp);
	  if( c== '\n') 
	    {
	      //each line break '\n' corresponds to a city
	      //because the city matrix is square
	      numCities++;   
	    }

	}
    }
  //close file
  fclose(fp);

  

  //open file
  fp = fopen(filename,"r");
  
  //allocate nxn array for matrix in memory
  cityMatrix = (int**) malloc(numCities * sizeof(int*));
  if (!cityMatrix)
    {
      printf("Cannot allocate matrix!\n");
      exit(1);
    }

  for(i = 0; i < numCities; i++) 
    {
      cityMatrix[i] = (int *) malloc(numCities * sizeof(int)); 
      if(!cityMatrix[i])
	{
	  printf("Cannot allocate matrix[%d]!\n",i);
	  exit(1);
	}
    }
  
  //copy the array into the space allocated above
  for(i = 0; i < numCities; i++)
    {
      for(j = 0; j < numCities; j++)
	{
	  fscanf(fp,"%d ", &cityMatrix[i][j]);
	}
    }

  fclose(fp);
  
  //return value is the number of lines in the array
  return numCities;
}

/*This function calculates all possible permutations of the routes that can
be taken between city one and city(numCities-1).  The cities are numbered starting
at city 0, so city one is the second city.  The distance between city 0 and city 1 is 
calculated prior to this function call.  The initial array passed to this function is always
an array of size numCities-1, with the cities index in chronological order */
int* permutate(int *array, int length) {
  int i, j;
  int interim;
  
  //find first element, starting from the end, that is larger than the one
  //check before it
  i = length - 1;
  while (i > 0 && array[i - 1] >= array[i])
    i--;
  if (i <= 0)
    return 0;
  
  //locate succesor to the element found above 
  j = length - 1;
  while (array[j] <= array[i - 1])
    j--;

  interim = array[i - 1];
  array[i - 1] = array[j];
  array[j] = interim;

  // Reverse suffix
  j = length - 1;
  while (i < j) {
    interim = array[i];
    array[i] = array[j];
    array[j] = interim;
    i++;
    j--;
  }


  
  //this function will return the permutated array to be used by the pathLength() function
  return array;

}

//calculates and returns the distances between the cities specified by the
//specific path, which is the function parameter
int pathLength(int* perm){

  int sum = 0;         //sum of the cost of the citypath
  int x,y,b;           //temporary variables and loop index
  int z = perm[0];     //first city in the array used to calculate distance fro                         m origin to first city
  sum += cityMatrix[0][z];
  arr3 = (int*) calloc(numCities-1,sizeof(int));

  for(b=0; b < numCities - 2; b++){
    x = perm[b];
    y = perm[b+1];

    // printf("x is %d, y is %d, value is %d\n", x,y, cityMatrix[x][y]); 
    //  printf("value at cityMatrix is %d\n", cityMatrix[x][y]);
   
    sum += cityMatrix[x][y];
    if(sum > best){     
         return best;
    }//end if
  }//end for loop

  if(sum == best){
    flag = 1;}
  // else{
    //  flag=0;}
  //  printf("sum here is %d.  best is %d\n", sum, best);
#pragma omp critical 
 if(sum < best && flag == 0){
       best = sum;
       //       flag = 1;
       int u;
       for(u=0; u < numCities - 1; u++){
		 arr3[u] = perm[u];
	 printf(" %d", arr3[u]);
       }
       printf("\n");
  }
  return sum;
  
}

//Calculates (numCities - 1)! which is the number of different routes
//a travelling salesman could take from city 0 visiting each city once
int calculate(){
  int q,result;
  result =1;
  for(q = 1; q < numCities; q++){
    result = result * q;
   }

  //return the result for loop indexing purposes
 return result;
}
 

int main(int argc, char *argv[]){
  int thread_count, my_rank; 
  char* input_file;
  int k,l,t,bound, notStart;

  input_file = argv[1];

  get_input(input_file);

  //used for indexing in various places
  notStart = numCities - 1; 

  int fArr[notStart];

  /*populating the first array (fArr) which values 1 through numCities -1
  this is the array that will be intially sent to permutate and all subsequent
  permutations derived from this array*/ 
  for(k = 0; k < numCities-1; k++){
    fArr[k] = k+1;
  }
 
  best = 1000;
 
  /* assign bound to (numCities - 1)! */
  bound = calculate();

  //  printf("BOUND IS %d\n", bound);

  int* arr2 = (int*) malloc(sizeof(int) * (notStart));
  printf("Best path:0");
  //define the number of threads which will execute the calcuations in parallel
  if(numCities-1 >= 3){
    omp_set_num_threads(3);}
  else{
    omp_set_num_threads(numCities-1);}

  /*BEGIN PARALLEL*/
#pragma omp parallel default(none) private(t,thread_count,my_rank) shared(fArr,arr2,arr3,notStart,bound,best) 
  {
                                                
    int my_rank = omp_get_thread_num();       //assign each thread its unique ID
    int thread_count = omp_get_num_threads(); //total number of threads
    int division = bound / thread_count;      //number of permutations each threa                                              // d calculates

    int e;
  #pragma omp for

  for(e=(my_rank * division); e < ((my_rank * division)+division); e++){
    // printf("my rank %d.....my index is %d\n", my_rank, e);
  
    #pragma omp critical
    arr2 = (permutate(fArr, notStart));

      
   t = pathLength(arr2);
   if(t < best){
       best = t;
        }//end if

  }//end for
 
  }//end parallel



  /*  
  int c,d;
  for(c=0; c<numCities; c++){
    for(d=0; d<numCities;d++){
      printf("%d ", cityMatrix[c][d]);}
	printf("\n");
    }
  */
 
  printf("Distance %d\n",best);      
  
    

}
