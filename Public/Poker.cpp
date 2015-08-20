#include "Poker.h"

/**********  出牌算法 **********/

int Poker::Than(ePK_TYPE _my, char _myValue, char _myCount, ePK_TYPE _other, char _otherValue, char _otherCount)
{
	if ( _my != _other ) {
		if ( _my == PH_MAX )
			return (PH_AGAIN);
		
		if ( _my == PH_4 )
			return (PH_THAN);
		
		return (PH_INVALID);
	}
	
	if ( !(_myValue > PH_C1 && _myValue < PH_End) ) 
		return (PH_INVALID);
	
	if ( _myValue > _otherValue )
		return (PH_THAN);
	
	return (PH_INVALID);
}

int Poker::Pick(unsigned char * PK_Group, unsigned int PK_Size, char & thanValue, char & thanCount)
{
	if ( PK_Size <= 0 || PK_Group == NULL ) {
		return (PH_0);
	}
	
	thanCount = 0;
	thanValue = PK_Group[0]; // 取第一个牌为比较值
	
	// (高击中 + 低复杂度) 判断区
	if ( PK_Size == 1 ) {
		return (PH_1); // 单牌
	}
	else if ( PK_Size == 2) {
		if ( PK_Group[0] == PK_Group[1] ) {
			return (PH_2); // 对子
		}
		if ( (PK_Group[0] == 14) && (PK_Group[1] == 15) ) {
			return (PH_MAX); // 王炸
		}
		return -1;
	}
	
	short _Max_Value = 0; 	// PK最大面值
	short _Min_Value = 15; 	// PK最小面值
	short _Max_Count = 0; 	// PK计量最多
	short _Min_Count = 0; 	// PK计量最少
	short _Min_Index = 0; 	// PK计量需要一个下标位来判断	
	
	const short CS_SLOT = 15; // PK的下标最大常量数
	short _PK_Slot[CS_SLOT] = {0}; // PK的SLOT容器
	
	short _idx = 0;
	short _val = 0;
	for ( short i=0; i<(short)PK_Size; ++i)
	{
		_idx = PK_Group[i];
		if ( _idx >= 15 ) {
			return (PH_0);
		}
		
		_PK_Slot[_idx]++;
		_val = _PK_Slot[_idx];
		
		_Max_Value = (_idx >  _Max_Value) ? _idx : _Max_Value; 	// 高位置获取
		_Min_Value = (_idx <= _Min_Value) ? _idx : _Min_Value; 	// 低位置获取
		_Max_Count = (_val >  _Max_Count) ? _val : _Max_Count; 	// 高计量获取
	}
	
	if ( (_Max_Value == _Min_Value) ) { // PK 大小面值都相等时
		if ( PK_Size == 3 ) {
			return (PH_3); // 3个
		}
		if ( PK_Size == 4 ) {
			return (PH_4); // 炸弹
		}
		return (PH_0);
	}
	
	if ( _Max_Count > 4) {
		return (PH_0);
	}
	
	// 得出最小面值的牌
	for (short i=0; i<(short)PK_Size; ++i)
	{
		_idx = PK_Group[i];
		_val = _PK_Slot[_idx];
		_Min_Count = (_val <= _Min_Count) ? _val : _Min_Count; // 低计量获取		
	}
	
	thanValue = _Max_Value; // 到这里取最大值为比较值
	if ( _Max_Count == _Min_Count ) { // PK 数量都相等时
		thanCount = PK_Size / _Max_Count;
		short _Div_0 = PK_Size / (_Max_Value - _Min_Value + 1);
		short _Div_1 = PK_Size % (_Max_Value - _Min_Value + 1);
		short _Div_2 = PK_Size / _Max_Count;
		short _Div_3 = PK_Size % _Max_Count;
		if ( (_Max_Count == _Div_0) && (_Div_1 == 0) ) {
			if ( _Max_Count == 1 ) {
				if ( (_Div_2 >= 5) && (_Div_3 == 0) )
					return (PH_4); // 顺子
				else
					return (PH_0); // 顺不起来
			}
			if ( _Max_Count == 2 ) {
				if ( (_Div_2 >= 3) && (_Div_3 == 0) ) 
					return 0; // 连对
				else
					return (PH_0); // 连不起来
			}
			if ( _Max_Count == 3 ) {
				if ( (_Div_2 >= 2) && (_Div_3 == 0) )
					return 0; // 飞机
				else
					return (PH_0); // 飞不起来
			}
		}
		return (PH_0);		
	}
	
	_idx = 0;
	for (short i=0; i<(short)PK_Size; ++i)
	{
		_idx = PK_Group[i];
		if ( _PK_Slot[_idx] == _Max_Count ) {
			break;
		}
	}
	
	thanValue = _idx; // 到这里取最多牌面值为比较值:
	if ( _Max_Count == 3 ) {
		thanCount = 1;
		if ( (_Min_Count == 1) && (PK_Size == 4) ) {
			return (PH_31); // 三带一
		}
		if ( (_Min_Count == 2) && (PK_Size == 5) ) {
			return (PH_32); // 三带二
		}
		
		// 是否三个连起来了
		short _Three_Max_Value 	= 0; 	// 3同位最大面值
		short _Three_Min_Value 	= 15; 	// 3同位最小面值
		short _Three_Count 		= 0; 	// 3同位个数
		short _Two_Count 		= 0; 	// 2同位个数
		short _One_Count 		= 0; 	// 1同位个数
		for (short i=0; i<(short)CS_SLOT; ++i)
		{
			_idx = _PK_Slot[i];
			if ( _idx == 3 ) {
				_Three_Max_Value = (i >  _Three_Max_Value) ? i : _Three_Max_Value; // 高位置获取
				_Three_Min_Value = (i <= _Three_Min_Value) ? i : _Three_Min_Value; // 低位置获取
				_Three_Count++;
			}
			else if ( _idx == 2 ) {
				_Two_Count++;
			}
			else if ( _idx == 1 ) {
				_One_Count++;
			}
		}
		
		short _Div_0 = (_Three_Max_Value - _Three_Min_Value + 1) / _Three_Count;
		short _Div_1 = (_Three_Max_Value - _Three_Min_Value + 1) % _Three_Count;
		if ( (_Div_0 == 1) && (_Div_1 == 0) ) {
			thanCount = _Three_Count;
			if ( _Three_Count == (_Two_Count * 2 + _One_Count) ) {
				return (PH_31); // 三带一
			}
			return (PH_0);
		}
		return (PH_0);
	}
	
	if ( _Max_Count == 4 ) {
		if ( _Min_Count == 1 ) {
			if ( PK_Size == 5 )
				return (PH_41); // 四带一
			if ( PK_Size == 6 )
				return (PH_411); // 四带二
			return (PH_0);			
		}
		if ( _Min_Count == 2 ) {
			if ( PK_Size == 6 )
				return (PH_42); // 四带一对
			if ( PK_Size == 8 )
				return (PH_422); // 四带两对
			return (PH_0);
		}
		return (PH_0);		
	}
	
	return (PH_0);	
}

//int Poker::OneTimes(unsigned char * szPK1, char iSizePK1, unsigned char * szPK2, char iSizePK2)
int Poker::OneTimes(unsigned char * szPK1, char iSizePK1, ePK_TYPE _other, char _otherValue, char _otherCount)
{
	char iThanValue1 = 0;
	char iThanCount1 = 0;
	char iThanValue2 = 0;
	char iThanCount2 = 0;
	
	int e1 = Pick(szPK1, iSizePK1, iThanValue1, iThanCount1);
	if ( e1 != PH_0 )
	{
		return Than((ePK_TYPE)e1, iThanValue1, iThanCount1, _other, _otherValue, _otherCount);
	}
	return PH_0;
	
	//int e1, e2;
	//e1 = Pick(szPK1, iSizePK1, iThanValue1, iThanCount1);
	//e2 = Pick(szPK2, iSizePK2, iThanValue2, iThanCount2);
	//return Than((ePK_TYPE)e1, iThanValue1, iThanCount1, (ePK_TYPE)e2, iThanValue2, iThanCount2);
}

/**********  end of 出牌算法 **********/
