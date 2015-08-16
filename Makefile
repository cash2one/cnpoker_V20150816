CC = g++
CFLAGS = -g -fPIC -D_FILELINE -Wno-deprecated 
#HOME = /mnt/Shared/moche
HOME = /mnt/share/cnpoker_v20150803

MYSQLINC = /usr/local/mysql/include
MYSQLLIB = -L /usr/lib64/mysql -lmysqlclient -lz -lm

INC = -I $(HOME)/Common -I $(HOME)/Network -I $(HOME)/Utility -I $(HOME)/AgentSrv -I $(HOME)/HyMysql -I $(HOME)/DBSrv -I $(MYSQLINC) 

UtilityObjs 	= Utility/Yond_mutex.o Utility/Yond_ini.o Utility/ObjKeyGenerator.o
CommonObjs 	= Common/InfoParser.o
NetworkObjs 	= Network/Acceptor.o Network/Connector.o Network/IOCPServer.o Network/NetworkObject.o Network/Session.o \
		  Network/SessionList.o Network/SessionPool.o Network/SocketOpt.o Network/SyncHandler.o
AgentServerObjs = AgentSrv/AgentMain.o AgentSrv/AgentFactory.o AgentSrv/AgentServer.o AgentSrv/GameServerSession.o \
		  AgentSrv/ServerSession.o AgentSrv/TempServerSession.o AgentSrv/TempUserSession.o AgentSrv/User.o AgentSrv/UserSession.o \
		  AgentSrv/Handler_FromClient.o AgentSrv/Handler_FromGameServer.o AgentSrv/PacketHandler.o \
		  AgentSrv/GameServerSession.o \
		  AgentSrv/UserManager.o
GameServerObjs 	= GameSrv/AgentServerSession.o GameSrv/DBServerSession.o \
		  GameSrv/GameFactory.o GameSrv/GameMain.o GameSrv/GameServer.o GameSrv/GameUser.o \
		  GameSrv/Handler_FromAgentServer.o GameSrv/Handler_FromDBServer.o GameSrv/PacketHandler.o \
		  GameSrv/ServerSession.o

DBServerObjs 	= HyMysql/HyDatabase.o HyMysql/IDBCInterface.o HyMysql/IMysql.o HyMysql/QueryExecuteProcessor.o HyMysql/QueryResult.o \
		  DBSrv/DBConnectDir.o DBSrv/DBFactory.o \
		  DBSrv/DBMain.o DBSrv/DBServer.o DBSrv/DBUser.o DBSrv/DBUserManager.o \
		  DBSrv/GameServerQuery.o DBSrv/GameServerSession.o DBSrv/Handler_FromGameServer.o DBSrv/Handler_FromLoginServer.o \
		  DBSrv/LoginServerQuery.o DBSrv/PacketHandler.o DBSrv/ServerSession.o DBSrv/TempServerSession.o

LoginServerObjs = LoginSrv/ServerSession.o LoginSrv/AgentServerSession.o LoginSrv/DBServerSession.o LoginSrv/TempServerSession.o \
		  LoginSrv/UserSession.o LoginSrv/User.o LoginSrv/UserManager.o \
		  LoginSrv/LoginFactory.o \
		  LoginSrv/LoginMain.o 
		 # LoginSrv/Handler_FromAgentServer.o LoginSrv/Handler_FromDBServer.o \

BINDIR = bin

all: checkbin $(BINDIR)/AgentServer $(BINDIR)/GameServer $(BINDIR)/DBServer
#$(BINDIR)/LoginServer

$(BINDIR)/AgentServer: $(UtilityObjs) $(CommonObjs) $(NetworkObjs) $(AgentServerObjs)
	$(CC) -g $^ -o $@ -pthread

$(BINDIR)/GameServer: $(UtilityObjs) $(CommonObjs) $(NetworkObjs) $(GameServerObjs)
	$(CC) -g $^ -o $@ -pthread

$(BINDIR)/DBServer: $(UtilityObjs) $(CommonObjs) $(NetworkObjs) $(DBServerObjs)
	$(CC) -g $(MYSQLLIB) $^ -o $@ -pthread

#$(BINDIR)/LoginServer: $(UtilityObjs) $(CommonObjs) $(NetworkObjs) $(LoginServerObjs)
#	$(CC) -g $^ -o $@ -pthread

.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY: checkbin
checkbin:
	test -d "${BINDIR}" || mkdir $(BINDIR)

.PHONY:	clean cleanGame
clean:
	rm -f Common/*.o
	rm -f Network/*.o
	rm -f Utility/*.o
	rm -f AgentSrv/*.o
	rm -f $(BINDIR)/AgentServer

cleanGame:
	rm -f Network/*.o
	rm -f Utility/*.o
	rm -f GameSrv/*.o
	rm -f $(BINDIR)/GameServer
	
cleanLogin:
	rm -f LoginSrv/*.o
	rm -f $(BINDIR)/LoginServer

cleanDB:
	rm -f HyMysql/*.o
	rm -f DBSrv/*.o
	rm -f $(BINDIR)/DBServer	
