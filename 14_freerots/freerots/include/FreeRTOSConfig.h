/*
FreeRTOS V9.0.0 -版权所有 (C) 2016 Real Time Engineers Ltd.
版权所有
访问 http://www.FreeRTOS.org 以确保您使用的是最新版本。
该文件是 FreeRTOS 发行版的一部分。
FreeRTOS 是免费软件；您可以根据 GNU 通用公共许可证（版本 2）的条款重新分发和/或修改它
自由软件基金会 >>>> 并由 <<<< FreeRTOS 异常进行修改。
********************************************************************************
>>！注意：对 GPL 的修改允许您！<<
>>！分发包含 FreeRTOS 的组合作品而不被 !<<
>>！有义务提供专有组件的源代码！<<
>>！ FreeRTOS 内核之外。 !<<
********************************************************************************
FreeRTOS 发布的目的是希望它有用，但没有任何用处
保修单;甚至没有适销性或适用性的默示保证
出于特定目的。完整的许可证文本可通过以下链接获取：http://www.freertos.org/a00114.html
********************************************************************************
**
*FreeRTOS提供完全免费但专业开发的，*
*坚固、严格的质量控制、支持和交叉*
*平台软件不仅仅是市场领导者，它 *
*是业界事实上的标准。 *
**
*帮助自己快速入门，同时提供帮助 *
*通过购买 FreeRTOS 支持 FreeRTOS 项目 *
*教程书、参考手册或两者：*
*http://www.FreeRTOS.org/Documentation *
**
********************************************************************************
http://www.FreeRTOS.org/FAQHelp.html -有问题吗？从阅读开始
常见问题页面“我的应用程序无法运行，可能出了什么问题？”。你
定义了 configASSERT()？
http://www.FreeRTOS.org/support -作为获得这种顶级品质的回报
免费的嵌入式软件我们请求您通过以下方式帮助我们的全球社区
参加支持论坛。
http://www.FreeRTOS.org/training -投资培训可以让您的团队
尽早提高生产力。现在您可以收到
直接由 Real Time Engineers 首席执行官 Richard Barry 进行 FreeRTOS 培训
有限公司，以及全球领先的实时操作系统的权威。
http://www.FreeRTOS.org/plus -FreeRTOS 生态系统产品精选，
包括FreeRTOS+Trace——不可或缺的生产力工具，一个DOS
兼容的 FAT 文件系统，以及我们的微型线程感知 UDP/IP 堆栈。
http://www.FreeRTOS.org/labs -新的 FreeRTOS 产品孵化的地方。
快来尝试 FreeRTOS+TCP，这是我们针对 FreeRTOS 的全新开源 TCP/IP 堆栈。
http://www.OpenRTOS.com -实时工程师有限公司。将 FreeRTOS 许可为高
诚信系统有限公司以 OpenRTOS 品牌进行销售。低成本 OpenRTOS 许可证提供票据支持、赔偿和商业中间件。
http://www.SafeRTOS.com -高完整性系统还提供安全性
设计并独立 SIL3 认证版本，用于安全和
需要可证明可靠性的关键任务应用程序。
1 个制表符 == 4 个空格！
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
*应用程序特定的定义。
*
*这些定义应根据您的特定硬件进行调整
*申请要求。
*
*这些参数在“配置”部分中进行了描述
*FreeRTOS API 文档可在 FreeRTOS.org 网站上获取。
*
*请参阅http://www.freertos.org/a00110.html。
*----------------------------------------------------------*/
/*configUSE_PREEMPTION  = 1  采用抢占式调度器          configUSE_PREEMPTION = 0 使用协作式调度器（时间片），时间片是默认开启的，相同优先级时使用时间片*/
#define configUSE_PREEMPTION            1

/*configUSE_TICKLESS_IDLE  = 1 使能低功耗模式TICKLESS        configUSE_TICKLESS_IDLE=0  保持系统节拍中断（tick）一直运行*/
#define configUSE_TICKLESS_IDLE         0

/*实际写入的cpu内核频率，也就是cpu指令执行频率*/
#define configCPU_CLOCK_HZ              (SystemCoreClock)

/*系统节拍中断频率，即一秒系统中断的次数*/
#define configTICK_RATE_HZ              ((TickType_t)1000)

/*最大可使用的优先级*/
#define configMAX_PRIORITIES            5

/*空闲任务使用的堆栈大小*/
#define configMINIMAL_STACK_SIZE        ((unsigned short)90)

/*任务名称最大长度*/
#define configMAX_TASK_NAME_LEN         20

/*系统节拍计数器变量类型    =1   表示U16类型    =0表示  U32类型*/
#define configUSE_16_BIT_TICKS          0

/*空闲任务放弃cpu使用权给其他相同优先级任务*/
#define configIDLE_SHOULD_YIELD         1

/*开启任务通知功能，默认开启*/
#define configUSE_TASK_NOTIFICATIONS    1

/*使用互斥信号量*/
#define configUSE_MUTEXES               1

/*使用递归互斥信号量*/
#define configUSE_RECURSIVE_MUTEXES     1

/*configUSE_COUNTING_SEMAPHORES = 1   开启计数信号量*/
#define configUSE_COUNTING_SEMAPHORES   1


/*一般是硬件计算前导指令，硬件选择最高优先级的任务来执行*/
#define   configUSE_PORT_OPTIMISED_TASK_SELECTION   0

#define configUSE_ALTERNATIVE_API       0/*已弃用！*/
#define configQUEUE_REGISTRY_SIZE       8
#define configUSE_QUEUE_SETS            0
#define configUSE_TIME_SLICING          0
#define configUSE_NEWLIB_REENTRANT      0
#define configENABLE_BACKWARD_COMPATIBILITY         0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS     5

/*使用的内存分配（heap x.c）*/
#define configFRTOS_MEMORY_SCHEME                   4
/*Tasks.c 添加（例如线程感知调试功能）*/
#define configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H   1

/*内存分配相关定义。*/
#define configSUPPORT_STATIC_ALLOCATION             0
#define configSUPPORT_DYNAMIC_ALLOCATION            1
#define configTOTAL_HEAP_SIZE                       ((size_t)(10 * 1024))
#define configAPPLICATION_ALLOCATED_HEAP            0

/*钩子函数相关定义。*/
#define configUSE_IDLE_HOOK                         0
#define configUSE_TICK_HOOK                         0
#define configCHECK_FOR_STACK_OVERFLOW              0
#define configUSE_MALLOC_FAILED_HOOK                0
#define configUSE_DAEMON_TASK_STARTUP_HOOK          0

/*运行时间和任务统计信息收集相关定义。*/
#define configGENERATE_RUN_TIME_STATS               0
#define configUSE_TRACE_FACILITY                    1
#define configUSE_STATS_FORMATTING_FUNCTIONS        0

/*任务感知调试。*/
#define configRECORD_STACK_HIGH_ADDRESS             1

/*协同例程相关定义。*/
#define configUSE_CO_ROUTINES                       0
#define configMAX_CO_ROUTINE_PRIORITIES             2

/*软件定时器相关定义。*/
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            (configMINIMAL_STACK_SIZE * 2)

/*定义以捕获开发期间的错误。*/
#define configASSERT(x)         if(( x) == 0) {taskDISABLE_INTERRUPTS(); for (;;);}

/*可选函数 -大多数链接器无论如何都会删除未使用的函数。*/
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     0
#define INCLUDE_xTaskGetIdleTaskHandle          0
#define INCLUDE_eTaskGetState                   0
#define INCLUDE_xTimerPendFunctionCall          1
#define INCLUDE_xTaskAbortDelay                 0
#define INCLUDE_xTaskGetHandle                  0
#define INCLUDE_xTaskResumeFromISR              1

/*Cortex-A 的具体定义。*/
#define configMAX_API_CALL_INTERRUPT_PRIORITY 20

/*Systick 定义*/
#define configSETUP_TICK_INTERRUPT()                                                                                  \
    do                                                                                                                \
    {                                                                                                                 \
        void SystemSetupSystick(uint32_t tickRateHz, void *tickHandler, uint32_t intPriority);                        \
/*设置具有最低优先级的系统杆*/                                                                      \
        SystemSetupSystick(configTICK_RATE_HZ, (void *)FreeRTOS_Tick_Handler, configUNIQUE_INTERRUPT_PRIORITIES - 2); \
    } while (0)
#define configCLEAR_TICK_INTERRUPT()       \
    do                                     \
    {                                      \
        void SystemClearSystickFlag(void); \
        SystemClearSystickFlag();          \
    } while (0)

/*将 FreeRTOS 端口异常处理程序映射到启动处理程序名称的定义。*/
#define FreeRTOS_IRQ_Handler IRQ_Handler
#define FreeRTOS_SWI_Handler SVC_Handler

/*
*如果将configUSE_TASK_FPU_SUPPORT定义为1，则任务将在没有浮动的情况下启动
*点上下文。使用浮点硬件的任务必须调用 vPortTaskUsesFPU()
*在执行任何浮点指令之前。
*/
#ifndef configUSE_TASK_FPU_SUPPORT 
#define configUSE_TASK_FPU_SUPPORT 1
#endif

/*GIC 信息定义。*/
#define configINTERRUPT_CONTROLLER_BASE_ADDRESS 0x00a01000UL
#define configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET 0x1000UL
#define configUNIQUE_INTERRUPT_PRIORITIES 32

#endif/*FREERTOS_CONFIG_H*/
