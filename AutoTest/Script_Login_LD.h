#ifndef _SERVERSESSION_H_INCLUDED_
#define _SERVERSESSION_H_INCLUDED_


class Script_Login_LD0001 : public DBSrv_TEST
{
	void InitTest()
	{
		Step = 0;
		m_1.username = "sylar"
		m_1.password = "123qwe";
		
		m_2.rootid = 10; 
	}
	void ParsePacket(MSG_BASE * pMsg)
	{
	    if (Step == 0)
	    {
		pMsg = m_2;
		Step = 1;
		IsRet = TRUE;
		
		this->AutoTest();
	    }
	    
            if(Step == 1){
		
	    }

	}
};


class Script_Login_LD0002 : public DBSrv_TEST
{
	void InitTest()
	{
		Step = 0;
		m_1.username = "kim"
		m_1.password = "123qwe";
		
		m_2.rootid = 0; 
	}

	void ParsePacket(MSG_BASE * pMsg)
	{
	    if (Step == 0)
	    {
		pMsg = m_2;
		Step = 1;
		IsRet = TRUE;
		
		this->AutoTest();
	    }
	    
            if(Step == 5)
	    {
		
	    }

	}
};


#endif // _AGENTPLAYER_H_INCLUDED_
