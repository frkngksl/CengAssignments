from socket import *
import sys
import time
from hashlib import blake2b
from hmac import compare_digest

downloadFileNameTCP = "transfer_file_TCP.txt"
downloadFileNameUDP = "transfer_file_UDP.txt"
lengthOfTimestamp = 17
averageArrayTCP = []
averageArrayUDP = []
totalTransmissionTimeTCP = 0
totalTransmissionTimeUDP = 0

#READ ONLY variables for states
DATATYPE = 0
ACKTYPE = 1
FINTYPE = 2
WAITFOR0 = 10
WAITFOR1 = 11
stateOfFSM = WAITFOR0

"""
Packet Format For UDP
1-64 --> hashValue
65. Byte --> Sequence Number (1)
66. Byte --> Packet Type (1)
67-83. Bytelar --> Timestamp (17)
84-1000. Bytelar --> Data

convention:
datapacket = 0
ackpacket = 1
finpacket = 2
"""
#In this function, I just first extract checksum (hash) value from givenpacket and compare it with recalculated value to check the corruption. Identical to client
def checkChecksumEqual(givenMessage):
    givenHashValue = givenMessage[:64]
    calculatedHashValueInput = givenMessage[64:]
    #Remainingpart is hashed
    calculatedHashValue = getHashingValue(calculatedHashValueInput)
    #getHashingValue is a function that gives hash value
    return compare_digest(calculatedHashValue,givenHashValue)
    #Compare digests

#Function for create ACK packets based on sequenceNumber
def makeACKPacket(sequenceNumber):
    global ACKTYPE
    seqNumAndFlag = str(sequenceNumber)+str(ACKTYPE)
    timeStampValue = getTimeInfo()
    #No need to implement ACK packets timestamp, if needed can be implemented easily
    hexOfChecksum = getHashingValue(seqNumAndFlag.encode()+timeStampValue.encode())
    sendingPacket = hexOfChecksum +(seqNumAndFlag+timeStampValue).encode()
    return sendingPacket

#Finite state machine for receiving UDP packets
def takePacketWithFSM(givenSocket):
    global stateOfFSM
    global FINTYPE
    global WAITFOR0
    global WAITFOR1
    while True:
        #Wait for ACK 0
        if(stateOfFSM == WAITFOR0):
            receivedMessage, clientAddress = givenSocket.recvfrom(1000)
            #Recieve Message and check for corruption
            if(not checkChecksumEqual(receivedMessage) ):
                sendedPacket = makeACKPacket(1)
                #Send NACK (NACK Free protocol)
                givenSocket.sendto(sendedPacket,clientAddress)
            else:
                #Decode and check sequence Number
                temp = receivedMessage[64:66]
                sequenceNumber = int(temp.decode()[0])
                if(sequenceNumber == 1):
                    #Send ACK for broken ACK cases (just refer to FSM in lecture slides)
                    sendedPacket = makeACKPacket(1)
                    givenSocket.sendto(sendedPacket,clientAddress)
                else:
                    #Correct packet, change state and return
                    sendedPacket = makeACKPacket(0)
                    givenSocket.sendto(sendedPacket,clientAddress)
                    stateOfFSM = WAITFOR1
                    return receivedMessage
        #Identical to WAITFOR0
        elif(stateOfFSM == WAITFOR1):
            receivedMessage, clientAddress = givenSocket.recvfrom(1000)
            #Check corruption
            if(not checkChecksumEqual(receivedMessage)):
                #NACK packet send
                sendedPacket = makeACKPacket(0)
                givenSocket.sendto(sendedPacket,clientAddress)
            else:
                temp = receivedMessage[64:66]
                sequenceNumber = int(temp.decode()[0])
                if(sequenceNumber == 0):
                    #Send ACK for broken ACK cases (refer to FSM)
                    sendedPacket = makeACKPacket(0)
                    givenSocket.sendto(sendedPacket,clientAddress)
                else:
                    #Correct packet, change state and return
                    sendedPacket = makeACKPacket(1)
                    givenSocket.sendto(sendedPacket,clientAddress)
                    stateOfFSM = WAITFOR0
                    return receivedMessage

#Main function for file receive over UDP
def receiveFileOverUDP(givenSocket):
    global DATATYPE
    global FINTYPE
    global averageArrayUDP
    global totalTransmissionTimeUDP
    chunks = []
    firstPacketFlag = True
    firstTimeFromClient = None
    while True:
        #Take packet
        receiveCorrectPacket = takePacketWithFSM(givenSocket)
        temp = receiveCorrectPacket[64:66]
        receivedPacketType = int(temp.decode()[1])
        #Extract type
        if(receivedPacketType == DATATYPE):
            #Handle timestamp and save data to chunks
            sendedTime = float(receiveCorrectPacket[66:83].decode())
            receiveTime = float(getTimeInfo())
            if(firstPacketFlag):
                firstPacketFlag = False
                firstTimeFromClient = sendedTime
            averageArrayUDP.append(receiveTime-sendedTime)
            chunks.append(receiveCorrectPacket[83:])
        elif(receivedPacketType == FINTYPE):
            #FIN case break
            break
    #Write all received chunks
    finishTime = float(getTimeInfo())
    totalTransmissionTimeUDP = (finishTime-firstTimeFromClient)*1000
    fileDescriptor = open(downloadFileNameUDP,"wb")
    for chunk in chunks:
        fileDescriptor.write(chunk)
    fileDescriptor.close()
    #calculate total time in ms

#Identical to client, jut get hash function
def getHashingValue(givenInput):
    hashObj = blake2b(digest_size=64)
    hashObj.update(givenInput)
    return hashObj.digest()

#Print run information
def printCorrectUsage():
    print("python3 "+sys.argv[0]+" <server UDP port> <server TCP port>")

#Identical to one that is in client.py. Get epoch time
def getTimeInfo():
    takenTime = str(time.time())
    pointIndex = takenTime.find(".")
    temp = takenTime[pointIndex+1:]
    precisionInfo = ""
    if(len(temp)<6):
        precisionInfo = temp+"0"*(6-len(temp))
    else:
        precisionInfo = temp[:6]
    return takenTime[:pointIndex]+"."+precisionInfo
    #It is length is fixed 17 -> [10].[6]

#Simple Average calculation  function
def calculateAverage(listOfTransmission):
    sumOflist = 0
    lengthOfList = len(listOfTransmission)
    for element in listOfTransmission:
        sumOflist+=element
    return sumOflist/lengthOfList

#Main function for receiving file over TCP
def receiveFileOverTCP(connectionTCPSocket):
    global averageArrayTCP
    global totalTransmissionTimeTCP
    chunks = []
    closeFlag = False
    firstPacketFlag = True
    firstTimeFromClient = None
    #Check for closed connection
    while(not closeFlag):
        tempChunk =  bytearray()
        while(len(tempChunk) != 1000):
            #Buffer loop mentioned in README, sometimes buffer reads less than 1000 bytes, fix it with buffer
            bufferForTCP = connectionTCPSocket.recv(1000-len(tempChunk))
            if(not bufferForTCP):
                closeFlag = True
                break
            tempChunk+=bufferForTCP
        #Time difference and add chunk
        sendedTime = float(tempChunk[:17].decode())
        receiveTime = float(getTimeInfo())
        if(firstPacketFlag):
            firstTimeFromClient = sendedTime
            firstPacketFlag = False
        averageArrayTCP.append(receiveTime-sendedTime)
        chunks.append(tempChunk[17:])
    #Calculate time in ms
    finishTime = float(getTimeInfo())
    totalTransmissionTimeTCP = (finishTime-firstTimeFromClient)*1000
    connectionTCPSocket.close()
    #Write received chunks to file
    fileDescriptor = open(downloadFileNameTCP,"wb")
    for chunk in chunks:
        fileDescriptor.write(chunk)
    fileDescriptor.close()

if(__name__ == "__main__"):
    if(len(sys.argv) != 3):
        printCorrectUsage()
        exit(0)
    serverUDPPort = sys.argv[1]
    serverTCPPort = sys.argv[2]
    #Create and bind sockets
    serverUDPSocket = socket(AF_INET,SOCK_DGRAM)
    serverUDPSocket.bind(('',int(serverUDPPort)))
    serverTCPSocket = socket(AF_INET,SOCK_STREAM)
    serverTCPSocket.bind(('',int(serverTCPPort)))
    serverTCPSocket.listen(1)
    #Receive UDP
    receiveFileOverUDP(serverUDPSocket)
    serverUDPSocket.close()
    connectionTCPSocket, addr = serverTCPSocket.accept()
    #Start send TCP
    receiveFileOverTCP(connectionTCPSocket)
    serverTCPSocket.close()
    stringAverageTCP = str(calculateAverage(averageArrayTCP)*1000)
    stringAverageUDP = str(calculateAverage(averageArrayUDP)*1000)
    stringTCPTotal = str(totalTransmissionTimeTCP)
    stringUDPTotal = str(totalTransmissionTimeUDP)
    print("TCP Packets Average Transmission Time:",stringAverageTCP[:stringAverageTCP.find(".")+3],"ms")
    print("UDP Packets Average Transmission Time:",stringAverageUDP[:stringAverageUDP.find(".")+3],"ms")
    print("TCP Communication Total Transmission Time:",stringTCPTotal[:stringTCPTotal.find(".")+3],"ms")
    print("UDP Communication Total Transmission Time:",stringUDPTotal[:stringUDPTotal.find(".")+3],"ms")
    #That's all :)
