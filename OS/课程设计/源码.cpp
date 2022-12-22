#include <iostream>
#include <string>
#include <string>
#include <stdlib.h>
#include <vector>
using namespace std;
#define PIECE_NUM 50 // 内存块数
#define ORDER_NUM 10 // 指令集大小
#define PAGE_NUM 5   // 驻留集大小
#define BLOCK_TIME 3 // 阻塞时间
// 暂定每个进程 页表长10，驻留集5块，5个进程，也就需要25块
// 0-19内存块分给系统，20-50内存块分给用户进程,每个连续的分5块

// 指令
typedef struct ORder
{
    char orderType; // 输入i，输出o，查询q，修改c
    int orderNum;   // 要执行的页面号
} ORDER;

// 页表项
typedef struct PageTab
{
    int pageNum;  // 页号
    int blockNum; // 块号
    int flag;     // 0:在外存,1:在内存中,是否在内存中
    int access;   // 最近一次被访问的时间，LRU算法
} PAGETAB;

typedef struct Pcb
{
    int id;                  // 进程号
    string name;             // 进程名
    int priority;            // 优先级，抢占式的优先级调度，运行的进程每次-3，就绪队列的每次+3
    int status;              // 进程状态 0：就绪 1：运行 2：阻塞
    int runTime;             // 运行时间
    int blockTime;           // 阻塞时间
    int curOrder;            // 指令集指针
    ORDER orders[ORDER_NUM]; // 指令集
    int startBlock;          // 起始块号
    vector<PAGETAB> pageTab; // 页表,长度和进程指令集长度一样
    int pageTabSize;         // 在内存中的页表大小
} PCB;

int memory[PIECE_NUM];  // 内存块 -1：空闲 0：系统 其他数字：进程号
vector<PCB> readyQueue; // 就绪队列
vector<PCB> runProcess; // 运行进程
vector<PCB> blockQueue; // 阻塞队列
Pcb P1, P2, P3, P4, P5; // 进程
vector<string> REMIND;  // 提示信息
int finishNum = 0;      // 已完成进程数
int time = 0; // 时间片

void showTime()
{
    cout << "\033[35m------------------------------------------------------------------------------" << endl;
    cout << "\n==========================当前时间片  " << time << "\t===============================\n"
         << endl;
    cout << "-------------------------------------------------------------------------------\033[0m\n"
         << endl;
}
void showTime(string s)
{
    cout << "\033[35m\n\n------------------------------------------------------------------------------" << endl;
    cout << "\n==========================当前时间片:  " << time << "  " << s << "\t===============================\n"
         << endl;
    cout << "-------------------------------------------------------------------------------\033[0m\n"
         << endl;
}
// 初始化内存
void initMemory()
{
    int i = 0;
    for (; i <= 19; i++)
    {
        memory[i] = 0;
    }
    // 20-24 给进程1，25-29给进程2，30-34给进程3，35-39给进程4，40-44给进程5
    int j = 0;
    for (; i < 45; i++)
    {
        if (i % 5 == 0)
            j++;
        memory[i] = j;
    }
    for (; i < PIECE_NUM; i++)
    {
        memory[i] = -1;
    }
}

// 展示内存
void showMemory()
{
    cout << "\033[35m\n============内存表============\033[0m\n"
         << endl;
    for (int i = 0; i < PIECE_NUM; i++)
    {
        printf("%3d", memory[i]);
        if (i % 10 == 9)
        {
            cout << endl;
        }
    }
    cout << endl;
}

// 展示就绪队列
void showReadyQueue()
{
    cout << "\033[32m\n==============================就绪进程表====================================\033[0m\n"
         << endl;
    cout << "进程号\t进程名\t优先级\t状态\t运行时间" << endl;
    for (int i = 0; i < readyQueue.size(); i++)
    {
        cout << readyQueue[i].id << "\t"
             << readyQueue[i].name << "\t"
             << readyQueue[i].priority << "\t";
        cout << "就绪\t";
        cout << readyQueue[i].runTime << endl;
    }
    cout << "\033[32m\n=================================================================================\033[0m\n";
}

// 展示运行进程
void showRunProcess()
{
    cout << "\033[37m\n==============================运行进程====================================\033[0m\n"
         << endl;
    cout << "进程号\t进程名\t优先级\t状态\t运行时间" << endl;
    for (int i = 0; i < runProcess.size(); i++)
    {
        cout << runProcess[i].id << "\t"
             << runProcess[i].name << "\t"
             << runProcess[i].priority << "\t";
        cout << "运行\t";
        cout << runProcess[0].runTime << endl;
        cout << "\033[37m\n=================================================================================\033[0m\n";
        // 展示运行进程的页表
        cout << "\033[37m\n==============================运行进程页表====================================\033[0m\n"
             << endl;
        cout << "页号\t是否在内存\t块号\t访问字段" << endl;
        for (int i = 0; i < runProcess[0].pageTab.size(); i++)
        {
            cout << runProcess[0].pageTab[i].pageNum << "\t";
            if (runProcess[0].pageTab[i].flag == 1)
                cout << "    是\t\t";
            else
                cout << "    否\t\t";
            if (runProcess[0].pageTab[i].blockNum != -1)
                cout << runProcess[0].pageTab[i].blockNum << "\t\t";
            else
                cout << "\t\t";
            if (runProcess[0].pageTab[i].access)
                cout << runProcess[0].pageTab[i].access << endl;
            else
                cout << "" << endl;
        }
        cout << "\033[37m\n=================================================================================\033[0m\n";
    }
}

// 展示阻塞队列
void showBlockQueue()
{
    cout << "\033[31m\n==============================阻塞进程表====================================\033[0m\n"
         << endl;
    cout << "进程号\t进程名\t优先级\t状态\t阻塞时间" << endl;
    for (int i = 0; i < blockQueue.size(); i++)
    {
        cout << blockQueue[i].id << "\t"
             << blockQueue[i].name << "\t"
             << blockQueue[i].priority << "\t";
        cout << "阻塞\t";

        cout << blockQueue[i].blockTime << endl;
    }
    cout << "\033[31m\n=================================================================================\033[0m\n";
}

bool isShowStartTime = true;
void showTable()
{
    system("cls");
    if (time > 0 && isShowStartTime)
        showTime("开始"), isShowStartTime = false;
    else
        showTime("结束"), isShowStartTime = true;
    showReadyQueue();
    cout << endl;
    showRunProcess();
    cout << endl;
    showBlockQueue();
}

void showRemind()
{
    if (REMIND.empty())
        return;
    // 展示REMIND
    cout << "\033[35m\n==============================REMIND====================================\033[0m\n"
         << endl;
    for (auto c : REMIND)
    {
        cout << c << endl;
    }
    REMIND.clear();
    cout << "\033[35m\n=================================================================================\033[0m\n";
}

// 抢占式优先级调度
void prioritySchedule()
{
    // 1. 从就绪队列中找到优先级最高的进程
    int maxPriority = -1;
    int maxPriorityIndex = 0;
    for (int i = 0; i < readyQueue.size(); i++)
    {
        if (readyQueue[i].priority > maxPriority)
        {
            maxPriority = readyQueue[i].priority;
            maxPriorityIndex = i;
        }
    }
    // 2. 如果没有进程在运行或者该进程的优先级比运行进程的高，将该进程从就绪队列中移除，放入运行队列中
    if (runProcess.size() == 0)
    {
        // 2.1 将就绪队列中的进程放入运行队列中，更改一下状态
        runProcess.push_back(readyQueue[maxPriorityIndex]);
        runProcess[0].status = 1;
        readyQueue.erase(readyQueue.begin() + maxPriorityIndex);
    }
    else if (maxPriority > runProcess[0].priority)
    {
        // 2.1 将运行队列中的进程放入就绪队列中，更改一下状态
        runProcess[0].status = 0;
        readyQueue.push_back(runProcess[0]);
        runProcess.clear();
        // 2.2 将就绪队列中的进程放入运行队列中，更改一下状态
        runProcess.push_back(readyQueue[maxPriorityIndex]);
        runProcess[0].status = 1;
        readyQueue.erase(readyQueue.begin() + maxPriorityIndex);
    }
}

// 读取运行进程的指令
void readOrder()
{
    int curOrder = runProcess[0].curOrder;
    int pageNum = runProcess[0].orders[curOrder].orderNum;
    int startBlock = runProcess[0].startBlock;
    char orderType = runProcess[0].orders[curOrder].orderType;
    runProcess[0].curOrder++;
    // 在内存中的页的access加1
    for (int i = 0; i < runProcess[0].pageTab.size(); i++)
    {
        // 如果在内存中
        if (runProcess[0].pageTab[i].flag == 1)
            runProcess[0].pageTab[i].access++;
    }
    bool isShouldClear = false;
    if (orderType == 'i' || orderType == 'o')
    {
        // 如果是输入输出指令，这时候需要将进程放入阻塞队列中
        runProcess[0].status = 2;
        runProcess[0].blockTime = BLOCK_TIME; // 阻塞时间
        blockQueue.push_back(runProcess[0]);
        // runProcess.clear();
        isShouldClear = true;
        string s = "进程" + runProcess[0].name + "执行了" + orderType + "指令，进入阻塞队列";
        REMIND.push_back(s);
    }
    // 查询修改
    // 该页在内存中，直接操作
    if (runProcess[0].pageTab[pageNum - 1].flag == 1)
    {
        // 这里具体操作省略没写，直接到执行完毕之后操作
        runProcess[0].pageTab[pageNum - 1].access = 1;
        if (runProcess[0].curOrder == ORDER_NUM)
        {
            // 进程执行完最后一个命令，执行完毕
            finishNum++;
            runProcess.clear();
            string s = "进程" + runProcess[0].name + "执行完毕";
            REMIND.push_back(s);
        }
        return;
    }
    // 到这里说明该页不在内存中
    // 1. 如果内存中有空闲块，直接分配
    if (runProcess[0].pageTabSize < PAGE_NUM)
    {
        // 页表中还有空位，从内存中分配一个块
        runProcess[0].pageTab[pageNum - 1].blockNum = startBlock + runProcess[0].pageTabSize;
        runProcess[0].pageTab[pageNum - 1].flag = 1;
        runProcess[0].pageTab[pageNum - 1].access = 1;
        runProcess[0].pageTabSize++;
    }
    else
    {
        // 2. 如果内存中没有空闲块，需要进行页面置换
        // 2.1 找到最近最久未使用的页
        int maxAccess = -0x3f3f3f;
        int maxAccessIndex = -1;
        for (int i = 0; i < runProcess[0].pageTab.size(); i++)
        {
            if (runProcess[0].pageTab[i].access > maxAccess)
            {
                maxAccess = runProcess[0].pageTab[i].access;
                maxAccessIndex = i;
            }
        }
        // 2.2 这里不写回磁盘，直接进行替换
        int t = runProcess[0].pageTab[maxAccessIndex].pageNum;
        runProcess[0].pageTab[pageNum - 1].access = 1;
        runProcess[0].pageTab[pageNum - 1].blockNum = runProcess[0].pageTab[maxAccessIndex].blockNum;
        runProcess[0].pageTab[pageNum - 1].flag = 1;
        runProcess[0].pageTab[maxAccessIndex].access = 0;
        runProcess[0].pageTab[maxAccessIndex].blockNum = -1;
        runProcess[0].pageTab[maxAccessIndex].flag = 0;
        string s = "进程" + runProcess[0].name + "执行了" + orderType + "指令，发生页表缺页，进行LRU页面置换";
        s += "，页号" + to_string(t) + "所在块换成页号" + to_string(pageNum);
        REMIND.push_back(s);
    }
    if (isShouldClear)
        runProcess.clear();
    if (runProcess[0].curOrder == ORDER_NUM)
    {
        // 进程执行完毕
        finishNum++;
        runProcess.clear();
        string s = "进程" + runProcess[0].name + "执行完毕";
        REMIND.push_back(s);
    }
}

void check()
{
    for (int i = 0; i < blockQueue.size(); i++)
    {
        blockQueue[i].blockTime--;
        if (blockQueue[i].blockTime == 0)
        {
            // 从阻塞队列中移除
            blockQueue[i].status = 0;
            readyQueue.push_back(blockQueue[i]);
            blockQueue.erase(blockQueue.begin() + i);
            i--;
        }
    }
}

// 运行时间片
void run()
{
    while (true)
    {
        if (finishNum == 5)
        {
            printf("所有进程执行完毕\n");
            system("pause");
            exit(0);
        }
        time++;
        // 先用抢占式优先级调度选出一个进程
        prioritySchedule();
        showTable();
        system("pause");
        // 1. 运行进程的优先度-3,就绪队列的优先度+3
        runProcess[0].priority = runProcess[0].priority - 3 ? runProcess[0].priority - 3 : 0;
        runProcess[0].runTime++;
        for (int i = 0; i < readyQueue.size(); i++)
        {
            readyQueue[i].priority += 3;
        }
        // 2. 读取指令
        readOrder();
        check();
        showTable();
        showRemind();
        system("pause");
    }
}

void initProcess()
{
    // 20-24 给进程1，25-29给进程2，30-34给进程3，35-39给进程4，40-44给进程5
    // P1用来演示缺页中断和页面置换，P2用来演示进程切换
    P1.id = 0, P1.name = "P1", P1.priority = 80, P1.status = 0, P1.startBlock = 20, P1.curOrder = 0, P1.blockTime = 0;
    P2.id = 1, P2.name = "P2", P2.priority = 30, P2.status = 0, P2.startBlock = 25, P2.curOrder = 0, P2.blockTime = 0;
    P3.id = 2, P3.name = "P3", P3.priority = 10, P3.status = 0, P3.startBlock = 30, P3.curOrder = 0, P3.blockTime = 0;
    P4.id = 3, P4.name = "P4", P4.priority = 20, P4.status = 0, P4.startBlock = 35, P4.curOrder = 0, P4.blockTime = 0;
    P5.id = 4, P5.name = "P5", P5.priority = 15, P5.status = 0, P5.startBlock = 40, P5.curOrder = 0, P5.blockTime = 0;
    P1.orders[0].orderType = 'q', P1.orders[0].orderNum = 1;  // 查询页号1
    P1.orders[1].orderType = 'c', P1.orders[1].orderNum = 2;  // 修改页号2
    P1.orders[2].orderType = 'q', P1.orders[2].orderNum = 3;  // 查询页号3
    P1.orders[3].orderType = 'c', P1.orders[3].orderNum = 4;  // 修改页号4
    P1.orders[4].orderType = 'q', P1.orders[4].orderNum = 5;  // 查询页号5
    P1.orders[5].orderType = 'c', P1.orders[5].orderNum = 1;  // 修改页号1
    P1.orders[6].orderType = 'q', P1.orders[6].orderNum = 2;  // 查询页号2
    P1.orders[7].orderType = 'c', P1.orders[7].orderNum = 8;  // 修改页号8，这里会发生页面置换
    P1.orders[8].orderType = 'q', P1.orders[8].orderNum = 9;  // 查询页号9
    P1.orders[9].orderType = 'c', P1.orders[9].orderNum = 10; // 修改页号10
    // 初始化页表
    for (int i = 0; i < ORDER_NUM; i++)
    {
        PAGETAB p;
        p.pageNum = i + 1;
        p.blockNum = -1;
        p.flag = 0;
        p.access = 0;
        P1.pageTab.push_back(p);
    }
    cout << "DEBUG2" << endl;
    P2.orders[0].orderType = 'q', P2.orders[0].orderNum = 1; // 查询页号1
    P2.orders[1].orderType = 'i', P2.orders[1].orderNum = 2; // 输入，这里发生中断，进入阻塞队列
    P2.orders[2].orderType = 'q', P2.orders[2].orderNum = 2; // 查询页号2
    P2.orders[3].orderType = 'o', P2.orders[3].orderNum = 4; // 输出页号4
    P2.orders[4].orderType = 'q', P2.orders[4].orderNum = 3; // 查询页号3
    P2.orders[5].orderType = 'c', P2.orders[5].orderNum = 4; // 修改页号4
    P2.orders[6].orderType = 'i', P2.orders[6].orderNum = 7; // 输入，中断
    P2.orders[7].orderType = 'c', P2.orders[7].orderNum = 5; // 修改页号5
    P2.orders[8].orderType = 'q', P2.orders[8].orderNum = 1; // 查询页号1
    P2.orders[9].orderType = 'c', P2.orders[9].orderNum = 2; // 修改页号2
    for (int i = 0; i < ORDER_NUM; i++)
    {
        PAGETAB p;
        p.pageNum = i + 1;
        p.blockNum = -1;
        p.flag = 0;
        p.access = 0;
        P2.pageTab.push_back(p);
    }
    P3.orders[0].orderType = 'q', P3.orders[0].orderNum = 1;
    P3.orders[1].orderType = 'c', P3.orders[1].orderNum = 2;
    P3.orders[2].orderType = 'q', P3.orders[2].orderNum = 3;
    P3.orders[3].orderType = 'c', P3.orders[3].orderNum = 4;
    P3.orders[4].orderType = 'q', P3.orders[4].orderNum = 5;
    P3.orders[5].orderType = 'c', P3.orders[5].orderNum = 1;
    P3.orders[6].orderType = 'q', P3.orders[6].orderNum = 2;
    P3.orders[7].orderType = 'c', P3.orders[7].orderNum = 6;
    P3.orders[8].orderType = 'q', P3.orders[8].orderNum = 7;
    P3.orders[9].orderType = 'c', P3.orders[9].orderNum = 3;
    for (int i = 0; i < ORDER_NUM; i++)
    {
        PAGETAB p;
        p.pageNum = i + 1;
        p.blockNum = -1;
        p.flag = 0;
        p.access = 0;
        P3.pageTab.push_back(p);
    }
    P4.orders[0].orderType = 'q', P4.orders[0].orderNum = 1;
    P4.orders[1].orderType = 'c', P4.orders[1].orderNum = 2;
    P4.orders[2].orderType = 'q', P4.orders[2].orderNum = 3;
    P4.orders[3].orderType = 'c', P4.orders[3].orderNum = 4;
    P4.orders[4].orderType = 'q', P4.orders[4].orderNum = 5;
    P4.orders[5].orderType = 'q', P4.orders[5].orderNum = 1;
    P4.orders[6].orderType = 'q', P4.orders[6].orderNum = 2;
    P4.orders[7].orderType = 'c', P4.orders[7].orderNum = 3;
    P4.orders[8].orderType = 'q', P4.orders[8].orderNum = 4;
    P4.orders[9].orderType = 'c', P4.orders[9].orderNum = 5;
    for (int i = 0; i < ORDER_NUM; i++)
    {
        PAGETAB p;
        p.pageNum = i + 1;
        p.blockNum = -1;
        p.flag = 0;
        p.access = 0;
        P4.pageTab.push_back(p);
    }
    P5.orders[0].orderType = 'q', P5.orders[0].orderNum = 1;
    P5.orders[1].orderType = 'c', P5.orders[1].orderNum = 2;
    P5.orders[2].orderType = 'q', P5.orders[2].orderNum = 3;
    P5.orders[3].orderType = 'c', P5.orders[3].orderNum = 4;
    P5.orders[4].orderType = 'q', P5.orders[4].orderNum = 5;
    P5.orders[5].orderType = 'q', P5.orders[5].orderNum = 1;
    P5.orders[6].orderType = 'q', P5.orders[6].orderNum = 2;
    P5.orders[7].orderType = 'c', P5.orders[7].orderNum = 3;
    P5.orders[8].orderType = 'q', P5.orders[8].orderNum = 4;
    P5.orders[9].orderType = 'c', P5.orders[9].orderNum = 5;
    for (int i = 0; i < ORDER_NUM; i++)
    {
        PAGETAB p;
        p.pageNum = i + 1;
        p.blockNum = -1;
        p.flag = 0;
        p.access = 0;
        P5.pageTab.push_back(p);
    }
}

// 初始化
void init()
{
    // 1.初始化内存
    initMemory();
    // 2.初始化进程
    initProcess();
    // 3.把五个进程都放进就绪队列
    readyQueue.push_back(P1);
    readyQueue.push_back(P2);
    readyQueue.push_back(P3);
    readyQueue.push_back(P4);
    readyQueue.push_back(P5);
}
int main()
{
    bool isInit = false;
    while (true)
    {
        cout << "先选择初始化，再运行" << endl;
        cout << "1.初始化(仅需一次)" << endl;
        cout << "2.运行" << endl;
        int choose;
        cin >> choose;
        switch (choose)
        {
        case 1:
            if (!isInit)
            {
                isInit = true;
                init();
                showTable();
                showMemory();
            }
            break;
        case 2:
            run();
            break;
        }
    }
    return 0;
}