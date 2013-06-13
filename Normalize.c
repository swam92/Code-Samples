int normalize(char *buf, /* The character array containing the string to be normalized*/
              int len    /* the size of the original character array */)
{
  //Print initial array	
  int j=0;
  while(j<len)
    {
      printf("%c", (char)buf[j]);
      j++;
    }
  printf("\n");


  char *write=buf; 							//points to writer
  char *read=buf;  							//points to reader
  int i;           							//array index
  int ctr=0;       							//number of deleted characters
  
	for (i=0; i<len; i++){ 						//for each element in the array
	
       if(isspace(*read)!=0){						//if what read is pointing to is a space
          
       		if(write == buf){					//if nothing has been written yet
    			
      				while(isspace(*read) != 0){		//while read is still pointing to a blank
        			
          				read++;				//increment the location of read
           				ctr++;				//increment the amount of unused characters
        			}
      			*write =getLower((int) *read); 			//break out of loop and assign write its first character
          		}

        	if (isspace(buf[i-1])!=0){				//if there are two consecutive spaces
         
           		while (isspace(*read) != 0){			//while there is more than one consecutive space
          
            		read++;						//increment read pointer
          	  		ctr++;					//increment the amount of unused characters
          		}
          }

          if(buf[i+1]==NULL){          					//if there is one extra trailing space
        		ctr++;						//record it to be deleted
          }
       }

      *write = getLower((int)*read);					//write what is in read

      write++;								//increment write
      read++;								//increment read
    }
  
   int temp = ctr;								
   while(temp > 0)							//for each extra space at the end
    {
     read=NULL;								//assign each extra space null to delete them
     temp--;
   }

  //print normalized array
  int k=0;
  while(k<len)
    {
      printf("%c", (char)buf[k]);
      k++;
    }
  printf("\n");

  return len - ctr; 							//return the size of the normalized array
}
