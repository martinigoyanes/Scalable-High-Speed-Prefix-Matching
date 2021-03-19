#include "io.h"
#include "tools.h"
#include <time.h>

int main(int argc, char **argv){
   /* Init variables */
   char *routingTableName = argv[1];
   char *inputFileName = argv[2];

   int error = OK; 

   uint32_t *IPAddress = (uint32_t *)malloc(sizeof(uint32_t));

   struct timespec *initialTime = (struct timespec*)malloc(sizeof(struct timespec)),
                   *finalTime = (struct timespec*)malloc(sizeof(struct timespec));
   double *searchingTime = (double *)malloc(sizeof(double));
         
   int totalTableAccesses, processedPackets;
   int* numOfTableAccesses = (int *)malloc(sizeof(int));
   double averageTableAccesses, averagePacketProcessingTime,
          totalPacketProcessingTime;
   int* defaultGateway = (int *)malloc(sizeof(int));
   /* Parse input files (routing table and ipaddrs to lookup) */
   if((error = initializeIO(routingTableName, inputFileName)) != OK)
   {
      printIOExplanationError(error);
      return error;
   } 
   
   struct TreeNode* root = NULL;
   /* Create tree with hashtables filled by routingTable*/
   if((error = buildUp(&root, defaultGateway)) != OK &&  error != REACHED_EOF)
   {
      printIOExplanationError(error);
      return error;
   } 
   
   error = OK;
   totalTableAccesses = 0; processedPackets = 0; *numOfTableAccesses = 0;
   *searchingTime = 0;
   while((error = readInputPacketFileLine(IPAddress)) != REACHED_EOF)
   {
      *numOfTableAccesses = 0; *searchingTime = 0;
      /* Read an ipaddr to perform lookup */
      if(error != OK)
      {
         printIOExplanationError(error);
         return error;
      } 

      clock_gettime(CLOCK_MONOTONIC_RAW, initialTime);
      int bmp = lookUp(*IPAddress, root, numOfTableAccesses, defaultGateway);
      clock_gettime(CLOCK_MONOTONIC_RAW, finalTime);

      printOutputLine(*IPAddress, bmp, initialTime, finalTime, searchingTime, *numOfTableAccesses);

      totalTableAccesses = totalTableAccesses + *numOfTableAccesses;
      totalPacketProcessingTime = totalPacketProcessingTime + *searchingTime;
      processedPackets++;

   }
   
   averageTableAccesses = totalTableAccesses/processedPackets;
   averagePacketProcessingTime = totalPacketProcessingTime/processedPackets;
   
   printSummary(processedPackets, averageTableAccesses, averagePacketProcessingTime);
   freeIO();   

   return 0;
}
