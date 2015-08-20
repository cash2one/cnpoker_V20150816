CC = g++
CFLAGS = -g -fPIC -D_FILELINE -Wno-deprecated 
#HOME = /mnt/Shared/moche
HOME = /mnt/share/cnpoker_V20150816

MYSQLINC = /usr/local/mysql/include
MYSQLLIB = -L /usr/lib64/mysql -lmysqlclient -lz -lm

INC = -I $(HOME)/Common  \
	  -I $(HOME)/Network \
	  -I $(HOME)/Utility \
	  -I $(HOME)/Public \
	  -I $(HOME)/AgentSrv \
	  -I $(HOME)/HyMysql \
	  -I $(HOME)/DBSrv \
	  -I $(MYSQLINC) 

PublicObjs 		= Public/Yond_drng.o \
				  Public/InfoParser.o \
				  Public/Poker.o
	  
UtilityObjs 	= Utility/Yond_mutex.o \
				  Utility/Yond_ini.o \
				  Utility/ObjKeyGenerator.o \
				  Utility/Yond_thread.o \
				  Utility/Yond_thread_pool.o

NetworkObjs 	= Network/Acceptor.o \
				  Network/Connector.o \
				  Network/IOCPServer.o \
				  Network/NetworkObject.o \
				  Network/Session.o \
				  Network/SessionList.o \
				  Network/SessionPool.o \
				  Network/SocketOpt.o \
				  Network/SyncHandler.o
		  
AgentServerObjs = AgentSrv/AgentMain.o \
				  AgentSrv/AgentFactory.o \
				  AgentSrv/AgentServer.o \
				  AgentSrv/GameServerSession.o \
				  AgentSrv/LoginServerSession.o \
				  AgentSrv/ServerSession.o \
				  AgentSrv/TempServerSession.o \
				  AgentSrv/TempUserSession.o \
				  AgentSrv/User.o \
				  AgentSrv/UserSession.o \
				  AgentSrv/Handler_FromClient.o \
				  AgentSrv/Handler_FromGameServer.o \
				  AgentSrv/Handler_FromLoginServer.o \
				  AgentSrv/PacketHandler.o \
				  AgentSrv/GameServerSession.o \
				  AgentSrv/UserManager.o
		  
GameServerObjs 	= GameSrv/AgentServerSession.o \
				  GameSrv/DBServerSession.o \
				  GameSrv/GameFactory.o \
				  GameSrv/GameMain.o \
				  GameSrv/GameServer.o \
				  GameSrv/GameUser.o \
				  GameSrv/GameUserManager.o \
				  GameSrv/Handler_FromAgentServer.o \
				  GameSrv/Handler_FromDBServer.o \
				  GameSrv/PacketHandler.o \
				  GameSrv/ServerSession.o

DBServerObjs 	= HyMysql/HyDatabase.o \
				  HyMysql/IDBCInterface.o \
				  HyMysql/IMysql.o \
				  HyMysql/QueryExecuteProcessor.o \
				  HyMysql/QueryResult.o \
				  DBSrv/DBConnectDir.o \
				  DBSrv/DBFactory.o \
				  DBSrv/DBMain.o \
				  DBSrv/DBServer.o \
				  DBSrv/DBUser.o \
				  DBSrv/DBUserManager.o \
				  DBSrv/GameServerQuery.o \
				  DBSrv/GameServerSession.o \
				  DBSrv/Handler_FromGameServer.o \
				  DBSrv/Handler_FromLoginServer.o \
				  DBSrv/LoginServerQuery.o \
				  DBSrv/LoginServerSession.o \
				  DBSrv/PacketHandler.o \
				  DBSrv/ServerSession.o \
				  DBSrv/TempServerSession.o

LoginServerObjs = LoginSrv/ServerSession.o \
				  LoginSrv/TempServerSession.o \
				  LoginSrv/AgentServerSession.o \
				  LoginSrv/DBServerSession.o \
				  LoginSrv/LoginMain.o \
				  LoginSrv/LoginFactory.o \
				  LoginSrv/LoginServer.o \
				  LoginSrv/LoginUser.o \
				  LoginSrv/LoginUserManager.o \
				  LoginSrv/PacketHandler.o \
				  LoginSrv/AllocServer.o \
				  LoginSrv/Handler_FromAgentServer.o \
				  LoginSrv/Handler_FromDBServer.o 
				  
BINDIR = bin

all: checkbin $(BINDIR)/AgentServer $(BINDIR)/GameServer $(BINDIR)/DBServer $(BINDIR)/LoginServer

$(BINDIR)/AgentServer: $(UtilityObjs) $(PublicObjs) $(NetworkObjs) $(AgentServerObjs)
	$(CC) -g $^ -o $@ -pthread

$(BINDIR)/GameServer: $(UtilityObjs) $(PublicObjs) $(NetworkObjs) $(GameServerObjs)
	$(CC) -g $^ -o $@ -pthread

$(BINDIR)/DBServer: $(UtilityObjs) $(PublicObjs) $(NetworkObjs) $(DBServerObjs)
	$(CC) -g $(MYSQLLIB) $^ -o $@ -pthread

$(BINDIR)/LoginServer: $(UtilityObjs) $(PublicObjs) $(NetworkObjs) $(LoginServerObjs)
	$(CC) -g $^ -o $@ -pthread

.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY: checkbin
checkbin:
	test -d "${BINDIR}" || mkdir $(BINDIR)

.PHONY:	clean cleanGame
clean:
	rm -f Network/*.o
	rm -f Utility/*.o
	rm -f Public/*.o
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
