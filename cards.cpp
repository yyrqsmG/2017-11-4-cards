#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

#define PLAYER_NUM 4 //4名玩家
#define COLOR_NUM 4  //4种颜色
#define CARD_NUM 13  //13个牌数
#define ALL_NUM (COLOR_NUM * CARD_NUM)   //52张牌
#define PLAYER_CARD_NUM (ALL_NUM / PLAYER_NUM) //玩家手牌数

char card_type(int m_type);
char* card_name(int m_num);

class NODE{
public:
    int m_type;
    int m_num;
};

class CARD{
private:
    NODE m_cards[ALL_NUM];
    NODE player_cards[PLAYER_NUM][PLAYER_CARD_NUM];
public:
    CARD();//构造函数

	class NODE get_card();
    void init_player_cards();//随机将牌组中的牌发到用户手牌上
    void sort_palyer_cards();//为玩家手牌排序
    void show_cards();//显示牌
};

CARD::CARD()
{
    int i, j, x;
    for(i = 0; i < COLOR_NUM; i++)//设置花色
    {
        for(j = 0; j < CARD_NUM; j++)//设置牌号
        {
            x = i * CARD_NUM + j;
            m_cards[x].m_type = i;
            m_cards[x].m_num = j;
        }
    }
}

void CARD::init_player_cards()
{
    int i, j;
    for(i = 0; i < PLAYER_NUM; i++)
    {
        for(j = 0; j < PLAYER_CARD_NUM; j++)
        {
            player_cards[i][j] = get_card();//随机发牌
        }
    }
}

void CARD::sort_palyer_cards()
{
    int i, j, x;
    NODE a;
    //遍历所有玩家手牌
    for (x = 0; x < PLAYER_NUM; x++)
    {
        //使用冒泡排序
        for (i = 0; i < PLAYER_CARD_NUM - 1; i++) 
        {
            for (j = i + 1; j < PLAYER_CARD_NUM; j++) 
            {
                //比较数字，数字一样大时比较花色（牌面大的放在前面）
                if (player_cards[x][j].m_num > player_cards[x][i].m_num ||
                    (player_cards[x][j].m_num == player_cards[x][i].m_num && player_cards[x][j].m_type > player_cards[x][i].m_type)) 
                {
                    a = player_cards[x][i];
                    player_cards[x][i] = player_cards[x][j];
                    player_cards[x][j] = a;
                }
            }
        }
    }
}

void CARD::show_cards()
{
    int i, j;
    //遍历所有玩家的手牌然后转化花色和牌号进行输出
    for (i = 0; i < PLAYER_NUM; i++) 
    {
        for (j = 0; j < PLAYER_CARD_NUM; j++) 
        {
            cout<<card_type(player_cards[i][j].m_type)<<card_name(player_cards[i][j].m_num)<<' ';
        }
        cout<<endl;
    }
}

NODE CARD::get_card()//从牌组中随机获取一张牌，并将该位置的牌置为不可用，防止重复取到同一张牌
{
    NODE a;
    int i = rand() % ALL_NUM;//随机一个数
    while(m_cards[i].m_num == -1)//判断该位置是否有效
    {
        i++;
        i %= ALL_NUM;//如果超过数组则从头开始
    }
    a = m_cards[i];
    m_cards[i].m_type = -1;
    m_cards[i].m_num = -1;
    return a;
}

char card_type(int type)
{
    switch(type){
        case 0:
            return 4;//方块
        case 1:
            return 5;//梅花
        case 2:
            return 3;//红桃
        case 3:
            return 6;//黑桃
    }
}

char* card_name(int num)
{
    //定义牌号
    //static 
	char* card_nums[CARD_NUM] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
    //从牌号数组中取出牌号
    return card_nums[num];
}


int main(void)
{
    srand(time(NULL));
    CARD acard;
    acard.init_player_cards();//发牌
    acard.sort_palyer_cards();//手牌排序
    acard.show_cards();//显示手牌
}
