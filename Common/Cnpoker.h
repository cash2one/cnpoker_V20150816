#ifndef _CNPOKER_H_INCLUDED_
#define _CNPOKER_H_INCLUDED_


// 出牌的类型
enum ePK_TYPE
{
	PH_0 	= 0    , 		// 无效
	PH_1 	= 100  , 		// 单牌
	PH_2 	       , 		// 对子
	PH_3 	       ,		// 三个
	PH_31 	       ,		// 三带一
	PH_32 	       ,		// 三带二
	PH_4 	       ,		// 炸弹
	PH_41 	       ,		// 四带一
	PH_411 	       ,		// 四带两单
	PH_42 	       ,		// 四带一对
	PH_422 	       ,		// 四带两对
	PH_MAX 	       ,		// 王炸
	
	
	PH_C1 	= 200  , 		// 顺子
	PH_C2 	       ,		// 连对
	PH_C3 	       ,		// 飞机
	PH_End 	= 1000 ,		// 无效	
};

enum ePK_POWER
{
	PH_INVALID = 0 , 		// 无效牌集
	PH_PASS    = 10, 		// 转出牌权
	PH_AGAIN       , 		// 再出牌权
	PH_THAN        , 		// 等待比较
};

#endif // _CNPOKER_H_INCLUDED_
