#ifndef __GAMESERVERQUERY_H_INCLUDED__
#define __GAMESERVERQUERY_H_INCLUDED__

#include <dbCommon.h>

class Query_GamePackage_select : public QueryResult
{
	_DECLARE_QUERY_POOL(Query_GamePackage_select);
	
public:
	
	enum
	{
		RESULT_COL_NUM = 4,
		PARAM_COL_NUL = 1,
	};
	
	struct sRESULT
	{
		unsigned int m_uiScore; 		// 分数
		unsigned int m_uiFaileds; 		// 失败次数
		unsigned int m_uiWons; 			// 赢的次数
		unsigned int m_uiEscape; 		// 逃跑次数
		sRESULT() 
		{
			m_uiScore	  = 0;
			m_uiFaileds = 0;
			m_uiWons    = 0;
			m_uiEscape  = 0;
		}
	};
	
	ULONG uLength[RESULT_COL_NUM]; // 4
	
	vector<sRESULT> vctRes;
	
	void AllocData()
	{
		sRESULT m_RESULT;
		memset(&m_RESULT, 0, sizeof( m_RESULT) );
		vctRes.push_back( m_RESULT );
	}
	
	void InitData() { vctRes.clear(); }
	void dealData() { vctRes.pop_back(); }
	
	_BEGIN_BINDING_DATA( sRESULT, vctRes, uLength, 1, RESULT_COL_NUM )
		_BINDING_COLUMN(0, m_uiScore)
		_BINDING_COLUMN(1, m_uiFaileds)
		_BINDING_COLUMN(2, m_uiWons)
		_BINDING_COLUMN(3, m_uiEscape)
	_END_BINDING_DATA()
	
	struct tag_LOGIN 
	{
		unsigned int m_uiRootID;
	} pParam[1];
	
	_BEGIN_PARAM_DATA( tag_LOGIN, pParam, PARAM_COL_NUL )
		_BINDING_PARAM(0, m_uiRootID,  SQL_PARAM_INPUT)
	_END_PARAM_DATA()
};


class Query_GamePackage_update : public QueryResult
{
	_DECLARE_QUERY_POOL(Query_GamePackage_update);
	
public:
	
	enum
	{
		RESULT_COL_NUM = 1,
		PARAM_COL_NUL = 4,
	};
	
	struct sRESULT {
		
		unsigned int m_uiRootID;
		
		sRESULT() {
			m_uiRootID = 0;
		}
	};
	
	ULONG uLength[RESULT_COL_NUM];
	
	vector<sRESULT> vctRes;
	
	void AllocData()
	{
		sRESULT m_RESULT;
		memset(&m_RESULT, 0, sizeof( m_RESULT) );
		vctRes.push_back( m_RESULT );
	}
	
	void InitData() { vctRes.clear(); }
	void dealData() { vctRes.pop_back(); }
	
	_BEGIN_BINDING_DATA( sRESULT, vctRes, uLength, 1, RESULT_COL_NUM)
		_BINDING_COLUMN(0, m_uiRootID)
	_END_BINDING_DATA()
	
	struct tag_LOGIN {
		unsigned int m_uiRootID;
		unsigned int m_uiScore;
		unsigned int m_uiFaileds;
		unsigned int m_uiWons;
		unsigned int m_uiEscape;
	} pParam[1];
	
	_BEGIN_PARAM_DATA(tag_LOGIN, pParam, PARAM_COL_NUL)
		_BINDING_PARAM(0, m_uiRootID,  	SQL_PARAM_INPUT)
		_BINDING_PARAM(1, m_uiScore,  	SQL_PARAM_INPUT)
		_BINDING_PARAM(2, m_uiFaileds,  SQL_PARAM_INPUT)
		_BINDING_PARAM(3, m_uiWons,  	SQL_PARAM_INPUT)
		_BINDING_PARAM(4, m_uiEscape,  	SQL_PARAM_INPUT)
	_END_PARAM_DATA()
};

#endif