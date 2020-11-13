/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman_task.cpp
*
* Description  : Manifest manager, ACE - tasks
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS dependent
****************************************************************************/

#include "mman_ci.h"
#include "mman_task.hpp"

#define MMAN__nBaseTickCycleTime 10000

namespace manifest_manager
{
    ManifestBroadcasterTask::ManifestBroadcasterTask(SystemFacade &oManifestManager) :
        m_Stop(0), // init locked
        m_oManifestManager(oManifestManager)
    {
    }

    ManifestBroadcasterTask::~ManifestBroadcasterTask(void)
    {
    }

    /* <@QACPP: 2427> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Type of returned object is derived from a declaration in parent class> */
    int ManifestBroadcasterTask::open(void*)
    {
        const char *pacThreadName[] = { SYSCT_sThreadString_MMAN_ManifestBroadcaster };
        size_t StackSize = SYSCT_nStack_MMAN_ManifestBroadcaster;

        int32 i32result = activate(
            /*long flags = */                  THR_JOINABLE | THR_SCHED_FIFO | THR_EXPLICIT_SCHED,
            /*int n_threads = */                1,
            /*int force_active = */             0,
            /*long priority = */                SYSCT_nThreadPrio_MMAN_ManifestBroadcaster,
            /*int grp_id = */                   -1,
            /*ACE_Task_Base *task = */          NULL,
            /*ACE_hthread_t thread_handles[]=*/ NULL,
            /*void *stack[] = */                NULL,
            /*size_t stack_size[] = */          &StackSize,
            /*ACE_thread_t thread_ids[] = */    NULL,
            /*const char* thr_name[] = */       pacThreadName);

        return i32result != -1;
    }

    void ManifestBroadcasterTask::stopTask()
    {
        m_Stop.release();
        wait();
    }

    TCPRequestHandlerTask::TCPRequestHandlerTask(SystemFacade &oManifestManager) :
        m_Stop(0), // init locked
        m_oManifestManager(oManifestManager)
    {
    }

    TCPRequestHandlerTask::~TCPRequestHandlerTask(void)
    {
    }

    /* <@QACPP: 2427> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Type of returned object is derived from a declaration in parent class> */
    int TCPRequestHandlerTask::open(void*)
    {
        const char *pacThreadName[] = { SYSCT_sThreadString_MMAN_TCPRequestHandler };
        size_t StackSize = SYSCT_nStack_MMAN_TCPRequestHandler;

        int32 i32result = activate(
            /*long flags = */                  THR_JOINABLE | THR_SCHED_FIFO | THR_EXPLICIT_SCHED,
            /*int n_threads = */                1,
            /*int force_active = */             0,
            /*long priority = */                SYSCT_nThreadPrio_MMAN_TCPRequestHandler,
            /*int grp_id = */                   -1,
            /*ACE_Task_Base *task = */          NULL,
            /*ACE_hthread_t thread_handles[]=*/ NULL,
            /*void *stack[] = */                NULL,
            /*size_t stack_size[] = */          &StackSize,
            /*ACE_thread_t thread_ids[] = */    NULL,
            /*const char* thr_name[] = */       pacThreadName);

        return i32result != -1;
    }

    void TCPRequestHandlerTask::stopTask()
    {
        m_Stop.release();
        wait();
    }

    TCPRequestProcessorTask::TCPRequestProcessorTask(SystemFacade &oManifestManager) :
        m_Stop(0), // init locked
        m_oManifestManager(oManifestManager)
    {
    }

    TCPRequestProcessorTask::~TCPRequestProcessorTask(void)
    {
    }

    /* <@QACPP: 2427> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Type of returned object is derived from a declaration in parent class> */
    int TCPRequestProcessorTask::open(void*)
    {
        const char *pacThreadName[] = { SYSCT_sThreadString_MMAN_TCPRequestProcessor };
        size_t StackSize = SYSCT_nStack_MMAN_TCPRequestProcessor;

        int32 i32result = activate(
            /*long flags = */                  THR_JOINABLE | THR_SCHED_FIFO | THR_EXPLICIT_SCHED,
            /*int n_threads = */                1,
            /*int force_active = */             0,
            /*long priority = */                SYSCT_nThreadPrio_MMAN_TCPRequestProcessor,
            /*int grp_id = */                   -1,
            /*ACE_Task_Base *task = */          NULL,
            /*ACE_hthread_t thread_handles[]=*/ NULL,
            /*void *stack[] = */                NULL,
            /*size_t stack_size[] = */          &StackSize,
            /*ACE_thread_t thread_ids[] = */    NULL,
            /*const char* thr_name[] = */       pacThreadName);

        return i32result != -1;
    }

    void TCPRequestProcessorTask::stopTask()
    {
        m_Stop.release();
        wait();
    }

    /* <@QACPP: 2427> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Type of returned object is derived from a declaration in parent class> */
    int ManifestBroadcasterTask::svc()
    {
        while (m_Stop.tryacquire() == -1)
        {
            m_oManifestManager.vBroadcastManifest();

            usleep(MMAN__nBroadcastDelay);
        }
        return 0;
    }

    /* <@QACPP: 2427> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Type of returned object is derived from a declaration in parent class> */
    int TCPRequestHandlerTask::svc()
    {
        while (m_Stop.tryacquire() == -1)
        {
            m_oManifestManager.vHandleTCPRequest();

            usleep(MMAN__nBaseTickCycleTime);
        }
        return 0;
    }

    /* <@QACPP: 2427> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Type of returned object is derived from a declaration in parent class> */
    int TCPRequestProcessorTask::svc()
    {
        while (m_Stop.tryacquire() == -1)
        {
            m_oManifestManager.vProcessTCPRequest();

            usleep(MMAN__nBaseTickCycleTime);
        }
        return 0;
    }
}
