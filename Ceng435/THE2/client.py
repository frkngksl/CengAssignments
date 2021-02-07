from socket import *
import time
import sys
from hashlib import blake2b
from hmac import compare_digest

uploadFileNameTCP = "transfer_file_TCP.txt"
uploadFileNameUDP = "transfer_file_UDP.txt"

lengthOfTimestamp = 17

udpRetransmissionCount = 0

sequenceNumber = 0

DATATYPE = 0
ACKTYPE = 1
FINTYPE = 2
WAITFORCALL0 = 10
WAITFORACK0 = 11
WAITFORCALL1 = 12
WAITFORACK1 = 13
#Global variables for FSM, they are constant


CLOSETIMEOUT = 3
#Close connection timeout
stateOfFSM = WAITFORCALL0
#StateOfFSM holds state of machine


"""
Just a remainder
Packet Format For UDP
1-64 --> hashValue
65. Byte --> Sequence Number (1)
66. Byte --> Packet Type (1)
67-83. Byte --> Timestamp (17)
84-1000. Byte --> Data

convention:
datapacket = 0
ackpacket = 1
finpacket = 2
"""

#In this function, I just first extract checksum (hash) value from givenpacket and compare it with recalculated value to check the corruption
def checkChecksumEqual(givenMessage):
    givenHashValue = givenMessage[:64]
    calculatedHashValueInput = givenMessage[64:]
    #Remainingpart is hashed
    calculatedHashValue = getHashingValue(calculatedHashValueInput)
    #getHashingValue is a function that gives hash value
    return compare_digest(calculatedHashValue,givenHashValue)
    #Compare digests

#Send packets using a Finite State Machine
def sendAndReceiveWithFSM(givenSocket,givenServerName,givenServerPort,givenPacket,isFIN):
    global stateOfFSM
    global WAITFORCALL0
    global WAITFORACK0
    global WAITFORCALL1
    global WAITFORACK1
    global sequenceNumber
    global udpRetransmissionCount
    receivedMessage = None
    returnedServerAddress = None
    sendedData = givenPacket[83:]
    #Extract data that will be sent again
    while(True):
        #If we waits for sequence 0
        if(stateOfFSM == WAITFORCALL0):
            givenSocket.sendto(givenPacket,(givenServerName, givenServerPort))
            stateOfFSM = WAITFORACK0
            #send and update the FSM state
        elif(stateOfFSM == WAITFORACK0):
            #If we sent FIN packet
            if(isFIN):
                try:
                    givenSocket.settimeout(CLOSETIMEOUT)
                    #Set timeout
                    receivedMessage, returnedServerAddress = givenSocket.recvfrom(1000)
                    #Try to receive an ACK package, if it can't receive message and time is up, it goes to except case
                    givenSocket.settimeout(None)
                except timeout:
                    return
                    #Return for connection
            #Otherwise, just receive a regular ACK for DATA type message
            else:
                receivedMessage, returnedServerAddress = givenSocket.recvfrom(1000)
            #If the packet is corrupted
            if(not checkChecksumEqual(receivedMessage)):
                temp = givenPacket[64:66]
                givenSeqNumber = int(temp.decode()[0])
                givenPacketType = int(temp.decode()[1])
                #Parse sequence number and type from resended packet
                seqNumAndFlag = str(givenSeqNumber)+str(givenPacketType)
                newTimeStampValue = getTimeInfo()
                #Retake the timestamp
                newHash = getHashingValue(seqNumAndFlag.encode()+newTimeStampValue.encode()+sendedData)
                #Get hash
                newPacketForResend = (newHash+seqNumAndFlag.encode()+newTimeStampValue.encode()+sendedData)
                givenSocket.sendto(newPacketForResend,(givenServerName,givenServerPort))
                #Resend newly created packet and increase retransmissionCount
                udpRetransmissionCount+=1
            else:
                #No corruption but check sequence number
                temp = receivedMessage[64:66]
                givenSeqNumber = int(temp.decode()[0])
                givenPacketType = int(temp.decode()[1])
                if(givenSeqNumber == 1):
                    #If 1, it is NACK because we use a NACK-free protocol so resend the packet
                    temp = givenPacket[64:66]
                    givenSeqNumber = int(temp.decode()[0])
                    givenPacketType = int(temp.decode()[1])
                    #Parse sequence number and type from resended packet
                    seqNumAndFlag = str(givenSeqNumber)+str(givenPacketType)
                    newTimeStampValue = getTimeInfo()
                    #Retake the timestamp
                    newHash = getHashingValue(seqNumAndFlag.encode()+newTimeStampValue.encode()+sendedData)
                    #Get hash
                    newPacketForResend = (newHash +seqNumAndFlag.encode()+newTimeStampValue.encode()+sendedData)
                    givenSocket.sendto(newPacketForResend,(givenServerName,givenServerPort))
                    #Resend newly created packet and increase retransmissionCount
                    udpRetransmissionCount+=1
                else:
                    #No corruption and it is ACK so change state and return
                    stateOfFSM = WAITFORCALL1
                    break

        #Send 1 sequence numbered packet
        elif(stateOfFSM == WAITFORCALL1):
            givenSocket.sendto(givenPacket,(givenServerName, givenServerPort))
            stateOfFSM = WAITFORACK1
            #Change state again

        #Exactly identical steps for 1
        elif(stateOfFSM == WAITFORACK1):
            if(isFIN):
                #Again timeout for FIN or receive normally
                try:
                    givenSocket.settimeout(CLOSETIMEOUT)
                    receivedMessage, returnedServerAddress = givenSocket.recvfrom(1000)
                    givenSocket.settimeout(None)
                except timeout:
                    return
            else:
                receivedMessage, returnedServerAddress = givenSocket.recvfrom(1000)
            #Check and resend for corrupted packet
            if(not checkChecksumEqual(receivedMessage)):
                temp = givenPacket[64:66]
                givenSeqNumber = int(temp.decode()[0])
                givenPacketType = int(temp.decode()[1])
                seqNumAndFlag = str(givenSeqNumber)+str(givenPacketType)
                newTimeStampValue = getTimeInfo()
                newHash = getHashingValue(seqNumAndFlag.encode()+newTimeStampValue.encode()+sendedData)
                newPacketForResend = (newHash+seqNumAndFlag.encode()+newTimeStampValue.encode()+sendedData)
                givenSocket.sendto(newPacketForResend,(givenServerName,givenServerPort))
                udpRetransmissionCount+=1

            else:
                temp = receivedMessage[64:66]
                givenSeqNumber = int(temp.decode()[0])
                givenPacketType = int(temp.decode()[1])
                #Handle NACK
                if(givenSeqNumber == 0):
                    temp = givenPacket[64:66]
                    givenSeqNumber = int(temp.decode()[0])
                    givenPacketType = int(temp.decode()[1])
                    seqNumAndFlag = str(givenSeqNumber)+str(givenPacketType)
                    newTimeStampValue = getTimeInfo()
                    newHash = getHashingValue(seqNumAndFlag.encode()+newTimeStampValue.encode()+sendedData)
                    newPacketForResend = (newHash +seqNumAndFlag.encode()+newTimeStampValue.encode()+sendedData)
                    givenSocket.sendto(newPacketForResend,(givenServerName,givenServerPort))
                    udpRetransmissionCount+=1
                else:
                    #It is regular ACK change your state
                    stateOfFSM = WAITFORCALL0
                    break
#Main function for sending file UDP
def sendFileOverUDP(givenSocket,givenServerName,givenServerPort):
    global FINTYPE
    global DATATYPE
    global ACKTYPE
    global sequenceNumber
    startFirstTimer = ""
    timeInfoLast = ""
    #Open file in binary mode to read file as chunks
    fileDescriptor = open(uploadFileNameUDP,"rb")
    #Readed data for each chunk (refer to package header)
    maximumReadedData = 1000-1-1-64-17
    receiveMessage = None
    #1000 max size , 1 sequence Number, 1 packet type (fin-ack-data), 32 hashValue (checksum), 17 timestamp. Remaining is for data.
    while True:
        #Read chunk
        readChunk = fileDescriptor.read(maximumReadedData)
        #If not readChunk, it means that whole file was sent. So, send FIN packet
        if(not readChunk):
            seqNumAndFlag = str(sequenceNumber)+str(FINTYPE)
            timeStampValue = getTimeInfo()
            hexOfChecksum = getHashingValue(seqNumAndFlag.encode()+timeStampValue.encode())
            #Create header for FIN Case
            sendingPacket = (hexOfChecksum +seqNumAndFlag.encode()+timeStampValue.encode())
            if(sequenceNumber):
                sequenceNumber = 0
            else:
                sequenceNumber = 1
            #Send FIN packet and break the loop
            sendAndReceiveWithFSM(givenSocket,givenServerName,givenServerPort,sendingPacket,True)
            break
        #Create and send new data packet
        seqNumAndFlag = str(sequenceNumber)+str(DATATYPE)
        timeStampValue = getTimeInfo()
        hexOfChecksum = getHashingValue(seqNumAndFlag.encode()+timeStampValue.encode()+readChunk)
        sendingPacket = (hexOfChecksum +seqNumAndFlag.encode()+timeStampValue.encode()+readChunk)
        #Ugly sequence Number toggling
        if(sequenceNumber):
            sequenceNumber = 0
        else:
            sequenceNumber = 1
        sendAndReceiveWithFSM(givenSocket,givenServerName,givenServerPort,sendingPacket,False)
    fileDescriptor.close()

#For convention
def printCorrectUsage():
    print("python3 "+sys.argv[0]+" <server IP> <server UDP port> <server TCP port> <client UDP sender port> <client TCP sender port>")

#Tıme parsing function from time.time() output (epoch). Extracted version is [10].[6]
def getTimeInfo():
    takenTime = str(time.time())
    pointIndex = takenTime.find(".")
    temp = takenTime[pointIndex+1:]
    precisionInfo = ""
    if(len(temp)<6):
        #Expand floating point precision to 6 to ensure fixed size.
        precisionInfo = temp+"0"*(6-len(temp))
    else:
        precisionInfo = temp[:6]
    return takenTime[:pointIndex]+"."+precisionInfo


#TCP sending function
def sendFileOverTCP(givenSocket):
    fileDescriptor = open(uploadFileNameTCP,"rb")
    while True:
        #Read chunk set max size 1000
        readChunk = fileDescriptor.read(1000-lengthOfTimestamp)
        if(not readChunk):
            #Close socket
            givenSocket.shutdown(SHUT_RDWR)
            break
        timeStringSend = getTimeInfo().encode()
        givenSocket.send(timeStringSend+readChunk)
    fileDescriptor.close()

#Get hash value for given input
def getHashingValue(givenInput):
    hashObj = blake2b(digest_size=64)
    hashObj.update(givenInput)
    return hashObj.digest()


if(__name__ == "__main__"):
    if(len(sys.argv) != 6):
        getTimeInfo()
        printCorrectUsage()
        exit(0)
    #Parse arguments
    serverIP = sys.argv[1]
    serverUDPPort = sys.argv[2]
    serverTCPPort = sys.argv[3]
    clientUDPPort = sys.argv[4]
    clientTCPPort = sys.argv[5]
    #Create Sockets
    clientUDPSocket = socket(AF_INET,SOCK_DGRAM)
    clientUDPSocket.bind(('',int(clientUDPPort)))
    clientTCPSocket = socket(AF_INET,SOCK_STREAM)
    clientTCPSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    clientTCPSocket.bind(('',int(clientTCPPort)))
    #Start sending UDP
    sendFileOverUDP(clientUDPSocket,serverIP,int(serverUDPPort))
    clientUDPSocket.close()
    #Try to connect until server accepts, maybe client tries to connect before server accepts the incoming connections
    connectFlag = False
    while not connectFlag:
        try:
            clientTCPSocket.connect((serverIP,int(serverTCPPort)))
            connectFlag = True
        except:
            pass
    sendFileOverTCP(clientTCPSocket)
    clientTCPSocket.close()
    print("UDP Transmission Re-transferred Packets:",udpRetransmissionCount)
    #Done :)
