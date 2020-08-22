#include <unistd.h>
#include <stdio.h>

int main() {

	int h = 0;
   	int m = 0;
    int s = 0;
   	
   	for ( ; ; ) {

   		sleep(1);   // sleep 1 second
    	s++;
    	
    	if (s / 60 == 1) {
    		s = 0;
    		m++;
    	}
    	
    	if (m / 60 == 1) {
    		m = 0;
    		h++;
    	} 

    	printf("%d:%d:%d\n", h, m, s);
   	
   	}
    
}


/*
<div class="img">

      <img src="" alt="" />

      <h4>Text you want to display on the image</h4>

</div>
*/