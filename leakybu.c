#include <stdio.h>
void main() 
{ 
    int in, out, bsize, n, bucket = 0; 
    printf("Enter the bucket size: "); 
    scanf("%d", &bsize); 
    printf("Enter the number of inputs: "); 
    scanf("%d", &n); 
    printf("Enter the packet outgoing rate: "); 
    scanf("%d", &out); 
    while (n != 0) 
    { 
        printf("\nEnter the incoming packet size: "); 
        scanf("%d", &in); 
        printf("Incoming packet size: %d\n", in); 
        if (in <= (bsize - bucket)) 
        {
            bucket += in; 
            printf("Bucket status: %d out of %d\n", bucket, bsize); 
        } 
        else 
        {
            printf("Dropped packets: %d \n", in - (bsize - bucket)); 
            bucket = bsize; 
            printf("Bucket status: %d out of %d\n", bucket, bsize); 
        }
        if (bucket < out) 
        {
            bucket = 0;
        } 
        else 
        {
            bucket -= out; 
        }
        printf("After outgoing, bucket status: %d packets out of %d\n", bucket, bsize); 
        n--; 
    } 
    printf("Simulation complete.\n");

}
