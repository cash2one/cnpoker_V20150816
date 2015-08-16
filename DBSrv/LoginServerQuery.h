#ifndef __LOGINSERVERQUERY_H_INCLUDED__
#define __LOGINSERVERQUERY_H_INCLUDED__

#include <dbCommon.h>

class Query_Login_update : public QueryResult
{
	_DECLARE_QUERY_POOL(Query_Login_update);
	
public:
	
	enum
	{
		RESULT_COL_NUM = 1,
		PARAM_COL_NUL = 2,
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
		BYTE byUsername[32];
		BYTE byPassword[32];
	} pParam[1];
	
	_BEGIN_PARAM_DATA(tag_LOGIN, pParam, PARAM_COL_NUL)
		_BINDING_PARAM_PTR(0, byUsername,  SQL_PARAM_INPUT)
		_BINDING_PARAM_PTR(1, byPassword,  SQL_PARAM_INPUT)
	_END_PARAM_DATA()
};


#endif