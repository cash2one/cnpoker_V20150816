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
	
	struct sRESULT {
		unsigned int uiScore;
		unsigned int uiFaileds;
		unsigned int uiWons;
		unsigned int uiEscape;
		sRESULT() {
			uiScore	  = 0;
			uiFaileds = 0;
			uiWons    = 0;
			uiEscape  = 0;
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
		_BINDING_COLUMN(0, uiScore)
		_BINDING_COLUMN(1, uiFaileds)
		_BINDING_COLUMN(2, uiWons)
		_BINDING_COLUMN(3, uiEscape)
	_END_BINDING_DATA()
	
	struct tag_LOGIN {
		unsigned int uiRootID;
	} pParam[1];
	
	_BEGIN_PARAM_DATA(tag_LOGIN, pParam, PARAM_COL_NUL)
		_BINDING_PARAM(0, uiRootID,  SQL_PARAM_INPUT)
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
		
		unsigned int uiRootID;
		
		sRESULT() {
			uiRootID = 0;
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
		_BINDING_COLUMN(0, uiRootID)
	_END_BINDING_DATA()
	
	struct tag_LOGIN {
		unsigned int uiRootID;
		unsigned int uiScore;
		unsigned int uiFaileds;
		unsigned int uiWons;
		unsigned int uiEscape;
	} pParam[1];
	
	_BEGIN_PARAM_DATA(tag_LOGIN, pParam, PARAM_COL_NUL)
		_BINDING_PARAM(0, uiRootID,  	SQL_PARAM_INPUT)
		_BINDING_PARAM(1, uiScore,  	SQL_PARAM_INPUT)
		_BINDING_PARAM(2, uiFaileds,  	SQL_PARAM_INPUT)
		_BINDING_PARAM(3, uiWons,  		SQL_PARAM_INPUT)
		_BINDING_PARAM(4, uiEscape,  	SQL_PARAM_INPUT)
	_END_PARAM_DATA()
};

#endif