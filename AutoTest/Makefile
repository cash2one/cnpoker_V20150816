CC = g++
CFLAGS = -g -fPIC -D_FILELINE -Wno-deprecated 
HOME = /mnt/share/cnpoker_v20150803

INC = -I $(HOME)/Common -I $(HOME)/Network -I $(HOME)/Utility -I $(HOME)/AutoTest

UtilityObjs = ../Utility/Yond_mutex.o ../Utility/Yond_ini.o ../Utility/ObjKeyGenerator.o
CommonObjs 	= ../Common/InfoParser.o
NetworkObjs = ../Network/Acceptor.o ../Network/Connector.o ../Network/IOCPServer.o ../Network/NetworkObject.o ../Network/Session.o \
			  ../Network/SessionList.o ../Network/SessionPool.o ../Network/SocketOpt.o ../Network/SyncHandler.o
		  
AutoTestObjs = ../AutoTest/ServerSession.o ../AutoTest/AutoTest.o ../AutoTest/Main.o ../AutoTest/DBSrv_Test.o	
		  

all: test 
test: $(UtilityObjs) $(CommonObjs) $(NetworkObjs) $(AutoTestObjs)
	$(CC) -g $^ -o $@ -pthread

.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY:	clean
clean:
	rm -f *.o
	rm -f test
	
