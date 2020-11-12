#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <limits.h>
#include "logging.h"
#include "message.h"
#include <poll.h>
#include <string.h>
#include<sys/wait.h>
#include<sys/types.h>
#define PIPE(fd) socketpair(AF_UNIX, SOCK_STREAM, PF_UNIX, fd)

void bidderStarter(char *inputLine,pid_t* pidList, int* fileDescriptorList,int pidIndex){
    char *c;
    char *newArguments;
    size_t length;
    int lengthForCounter;
    int tokenIndex = 0;
    char *pathOfExecutable;
    int numberOfArguments = 0;
    char **argumentList = NULL;
    size_t gettedSize=getline(&inputLine,&length,stdin);
    int temporaryFileDescriptor[2];
    if(gettedSize == -1){
        return;
    }
    c=inputLine;
    lengthForCounter =0;
    newArguments = malloc(sizeof(char));
    while(*c != '\n'){
        if(*c == ' '){
            newArguments[lengthForCounter] = '\0';
            if(tokenIndex == 0){
                pathOfExecutable = newArguments;
            }
            else if(tokenIndex == 1){
                numberOfArguments = atoi(newArguments);
                argumentList = (char **) malloc(sizeof(char *)*(numberOfArguments+2));
                argumentList[0] = pathOfExecutable;
                argumentList[numberOfArguments+1] = NULL;
            }
            else if(tokenIndex == numberOfArguments+1){
                argumentList[tokenIndex-1] = newArguments;
                break;
            }
            else{
                argumentList[tokenIndex-1] = newArguments;
            }
            //free(newArguments);
            newArguments = malloc(sizeof(char)); //fazla malloc
            lengthForCounter = 0;
            c++;
            tokenIndex++;
            continue;
        }
        newArguments[lengthForCounter++] = *c;
        c++;
        newArguments = realloc(newArguments,lengthForCounter+1);
    }
    newArguments[lengthForCounter] = '\0';
    if(numberOfArguments == 0 && argumentList == NULL){
        argumentList = (char **) malloc(sizeof(char *)*2);
        argumentList[0] = pathOfExecutable;
        argumentList[1] = NULL;
    }
    else{
        argumentList[tokenIndex-1] = newArguments;
    }
    PIPE(temporaryFileDescriptor);
    if((pidList[pidIndex] = fork()) > 0){
        close(temporaryFileDescriptor[1]); //SERVER 0'ı kullansın
        fileDescriptorList[pidIndex] = temporaryFileDescriptor[0];
        pathOfExecutable = NULL;
        c = NULL;
        newArguments = NULL;
        for(int i=0;i<numberOfArguments+1;i++){
            free(argumentList[i]);
            argumentList[i] = NULL;
        }
        free(argumentList);
        argumentList = NULL;
    }
    else{

        close(temporaryFileDescriptor[0]); //CLIENT 1'i kullansın.
        dup2(temporaryFileDescriptor[1],0);
        dup2(temporaryFileDescriptor[1],1);
        close(temporaryFileDescriptor[1]);
        execvp(pathOfExecutable,argumentList);
    }
}

int firstMessageReceiver(cm *comingMessage,int fileDescriptor,pid_t pidOfBidder,int client_id){
    //cm comingMessage;
    //read(fileDescriptor,&comingMessage,sizeof(cm));
    ii forPrint;
    forPrint.pid = pidOfBidder;
    forPrint.type = comingMessage->message_id;
    forPrint.info = comingMessage->params;
    print_input(&forPrint,client_id);
    return comingMessage->params.delay;
}

void firstMessageSender(int fileDescriptor,pid_t pidOfBidder,int client_id,int starting_bid,int current_bid,int minimum_increment){
    sm serverResponse;
    oi outputMessage;
    serverResponse.message_id = SERVER_CONNECTION_ESTABLISHED;
    serverResponse.params.start_info.client_id = client_id;
    serverResponse.params.start_info.starting_bid = starting_bid;
    serverResponse.params.start_info.current_bid = current_bid;
    serverResponse.params.start_info.minimum_increment = minimum_increment;
    outputMessage.type = SERVER_CONNECTION_ESTABLISHED;
    outputMessage.pid = pidOfBidder;
    outputMessage.info = serverResponse.params;
    print_output(&outputMessage,client_id);
    write(fileDescriptor,&serverResponse,sizeof(sm));
}

void bidResponseHandler(int fileDescriptor,pid_t pidOfBidder, int client_id,int result,int current_bid){
    sm serverResponse;
    oi outputMessage;
    serverResponse.message_id = SERVER_BID_RESULT;
    serverResponse.params.result_info.result = result;
    serverResponse.params.result_info.current_bid = current_bid;
    outputMessage.type = SERVER_BID_RESULT;
    outputMessage.pid = pidOfBidder;
    outputMessage.info = serverResponse.params;
    print_output(&outputMessage,client_id);
    write(fileDescriptor,&serverResponse,sizeof(sm));
}

void pollInitiater(struct pollfd* pfd,int* fileDescriptorList,int numberOfBidders){
    for(int i=0;i<numberOfBidders;i++){
        pfd[i].fd = fileDescriptorList[i];
        pfd[i].events = POLLIN;
        pfd[i].revents = 0;
    }
}

int newDelayDecider(int *delaysOfBidders,int *activeBidderList,int numberOfBidders){
    int minDelay = INT_MAX;
    for(int i=0;i<numberOfBidders;i++){
        if(activeBidderList[i] == 1 && delaysOfBidders[i] < minDelay){
            minDelay = delaysOfBidders[i];
        }
    }
    return minDelay;
}

void bidRequestHandler(cm *clientMessageReceived,pid_t pidOfBidder, int client_id){
    ii requestPrint;
    requestPrint.pid = pidOfBidder;
    requestPrint.type = clientMessageReceived->message_id;
    requestPrint.info = clientMessageReceived->params;
    print_input(&requestPrint,client_id);
}

void finishRequestHandler(cm *clientMessageReceived,pid_t pidOfBidder,int client_id){
    ii requestPrint;
    requestPrint.pid = pidOfBidder;
    requestPrint.type = clientMessageReceived->message_id;
    requestPrint.info = clientMessageReceived->params;
    print_input(&requestPrint,client_id);
}

void sendWinnerToAllBidders(int *fileDescriptorList, pid_t *pidList,int numberOfBidders,int winner_id,int winner_bid){
    sm serverResponse;
    oi outputMessage;
    for(int i=0;i<numberOfBidders;i++){
        memset(&serverResponse,0x00,sizeof(sm));
        memset(&outputMessage,0x00,sizeof(oi));
        serverResponse.message_id = SERVER_AUCTION_FINISHED;
        serverResponse.params.winner_info.winner_id = winner_id;
        serverResponse.params.winner_info.winning_bid = winner_bid;
        outputMessage.type = SERVER_AUCTION_FINISHED;
        outputMessage.pid = pidList[i];
        outputMessage.info = serverResponse.params;
        print_output(&outputMessage,i);
        write(fileDescriptorList[i],&serverResponse,sizeof(sm));
    }
}

void reapeAllBidders(int *fileDescriptorList,pid_t *pidList,int *exitStatusOfBidders,int numberOfBidders){
    int statusFromWait;
    for(int i=0;i<numberOfBidders;i++){
        close(fileDescriptorList[i]);
        statusFromWait = 0;
        waitpid(pidList[i],&statusFromWait,0);
        print_client_finished(i,statusFromWait,statusFromWait == exitStatusOfBidders[i]);
    }
}

int main(){
        char *inputLine = NULL;
        size_t length=0;
        getline(&inputLine,&length,stdin);
        int starting_bid = 0;
        int minimum_increment = 0;
        int numberOfBidders = 0;
        int minimumDelay = INT_MAX;
        int activeBidders;
        int currentHighestBidder;
        int current_bid;
        int returningDelay;
        int readedBufferSize;
        int bidderOffer =0;
        cm clientMessageReceived;
        int resultForBidRequest = 0;
        sscanf(inputLine," %d %d %d",&starting_bid,&minimum_increment,&numberOfBidders);
        //printf("Starting bid: %d, minimum_increment: %d, numberOfBidders: %d\n",starting_bid,minimum_increment,numberOfBidders); // Silincek
        current_bid = starting_bid;
        activeBidders = numberOfBidders;
        pid_t pidList[numberOfBidders];
        int fileDescriptorList[numberOfBidders];
        int activeBidderList[numberOfBidders];
        struct pollfd pfd[numberOfBidders];
        int delaysOfBidders[numberOfBidders];
        int exitStatusOfBidders[numberOfBidders];
        for(int i=0;i<numberOfBidders;i++){
            if(inputLine != NULL){
                free(inputLine);
                inputLine = NULL;
            }
            bidderStarter(inputLine,pidList,fileDescriptorList,i);
            activeBidderList[i] = 1;
        }
        if(inputLine != NULL){
            free(inputLine);
            inputLine = NULL;
        }
        pollInitiater(pfd,fileDescriptorList,numberOfBidders);
        while(activeBidders>0){
            for(int j=0;j<numberOfBidders;j++){
                pfd[j].revents = 0; // Clear revents
            }
            poll(pfd,numberOfBidders,minimumDelay);
            for(int j=0;j<numberOfBidders;j++){ //Bu kısım sorulacak
                if ((pfd[j].revents & POLLIN) && (activeBidderList[j] == 1)) {
                    memset(&clientMessageReceived,0x00,sizeof(clientMessageReceived));
                    readedBufferSize = read(fileDescriptorList[j],&clientMessageReceived,sizeof(clientMessageReceived));
                    if(readedBufferSize == 0){
                        //TODO I Dont understand
                        continue;
                    }
                    else{
                        switch(clientMessageReceived.message_id){
                            case CLIENT_CONNECT:
                                //printf("It shouldn't happen right?\n");
                                returningDelay = firstMessageReceiver(&clientMessageReceived,fileDescriptorList[j],pidList[j],j);
                                delaysOfBidders[j] = returningDelay;
                                if(returningDelay < minimumDelay){
                                    minimumDelay = returningDelay;
                                }
                                firstMessageSender(fileDescriptorList[j],pidList[j],j,starting_bid,current_bid,minimum_increment);
                                break;
                            case CLIENT_BID:
                                bidderOffer = clientMessageReceived.params.bid;
                                //printf("wants to bid %d,pidi bu %d bid value is %d \n", j,pidList[j],bidderOffer);
                                bidRequestHandler(&clientMessageReceived,pidList[j],j);
                                if(bidderOffer < starting_bid){
                                    resultForBidRequest = BID_LOWER_THAN_STARTING_BID;
                                }
                                else if(bidderOffer < current_bid){
                                    resultForBidRequest = BID_LOWER_THAN_CURRENT;
                                }
                                else if(bidderOffer-current_bid < minimum_increment){
                                    resultForBidRequest = BID_INCREMENT_LOWER_THAN_MINIMUM;
                                }
                                else{
                                    resultForBidRequest = BID_ACCEPTED;
                                    currentHighestBidder = j;
                                    current_bid = bidderOffer;
                                }
                                bidResponseHandler(fileDescriptorList[j],pidList[j],j,resultForBidRequest,current_bid);
                                break;
                            case CLIENT_FINISHED:
                                //printf("Wants to exit :%d,pidi de bu: %d \n",j,pidList[j]);
                                activeBidders--;
                                activeBidderList[j] = 0;
                                exitStatusOfBidders[j] = clientMessageReceived.params.status;
                                pfd[j].fd = -1; //Poll için
                                finishRequestHandler(&clientMessageReceived,pidList[j],j);
                                minimumDelay = newDelayDecider(delaysOfBidders,activeBidderList,numberOfBidders);
                                break;
                        }
                    }
                }
            }
        }
        //printf("Kazananın client idsi: %d pidi: %d tutar: %d\n",currentHighestBidder,pidList[currentHighestBidder],current_bid);
        print_server_finished(currentHighestBidder,current_bid);
        sendWinnerToAllBidders(fileDescriptorList,pidList,numberOfBidders,currentHighestBidder,current_bid);
        reapeAllBidders(fileDescriptorList,pidList,exitStatusOfBidders,numberOfBidders);
    return 0;
}
