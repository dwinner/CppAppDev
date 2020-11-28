/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman_task.hpp
*
* Description  : Manifest manager, ACE - tasks
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS dependent
****************************************************************************/

#ifndef MMAN_TASK_HPP_
#define MMAN_TASK_HPP_

extern "C"
{
#include <cdef.h>
}

#include <ace/task.h>
#include <ace/semaphore.h>
#include "mman_systemfacade.hpp"

namespace manifest_manager
{

    /// @brief Task to broadcast manifest digest
    class ManifestBroadcasterTask : public ACE_Task<ACE_MT_SYNCH>
    {
    public:
        /// @brief Default constructor
        explicit ManifestBroadcasterTask(SystemFacade &oManifestManager);
        /// @brief Default destructor
        virtual ~ManifestBroadcasterTask(void);

        /// @brief Opens task
        /* <@QACPP: 2427> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Type of returned object is derived from a declaration in parent class> */
        virtual int open(void*);      
        /// @brief Service method
        /* <@QACPP: 2427> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Type of returned object is derived from a declaration in parent class> */
        virtual int svc();
        /// @brief Stops task
        void stopTask();
    private:		
        /**
        * @brief ManifestBroadcasterTask copy constructor
        */
        ManifestBroadcasterTask(const ManifestBroadcasterTask&);

        /**
        * @brief ManifestBroadcasterTask assignment operator
        */
        ManifestBroadcasterTask& operator=(const ManifestBroadcasterTask&);
		
	    /// @brief Syncronization semaphore to let the thread exit on a signal
        ACE_Semaphore m_Stop;
        /// @brief System facade object
        SystemFacade &m_oManifestManager;
    };

    /// @brief Task to accept TCP connections
    class TCPRequestHandlerTask : public ACE_Task<ACE_MT_SYNCH>
    {
    public:
        /// @brief Default constructor
        explicit TCPRequestHandlerTask(SystemFacade &oManifestManager);
        /// @brief Default destructor
        virtual ~TCPRequestHandlerTask(void);

        /// @brief Opens task
        /* <@QACPP: 2427> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Type of returned object is derived from a declaration in parent class> */
        virtual int open(void*);
        /// @brief Service method
        /* <@QACPP: 2427> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Type of returned object is derived from a declaration in parent class> */
        virtual int svc();
        /// @brief Stops task
        void stopTask();
    private:
        /**
        * @brief TCPRequestHandlerTask copy constructor
        */
        TCPRequestHandlerTask(const TCPRequestHandlerTask&);

        /**
        * @brief TCPRequestHandlerTask assignment operator
        */
        TCPRequestHandlerTask& operator=(const TCPRequestHandlerTask&);
		
	    /// @brief Syncronization semaphore to let the thread exit on a signal
        ACE_Semaphore m_Stop;
        /// @brief System facade object
        SystemFacade &m_oManifestManager;
    };

    /// @brief Task to answer to TCP requests
    class TCPRequestProcessorTask : public ACE_Task<ACE_MT_SYNCH>
    {
    public:
        /// @brief Default constructor
        explicit TCPRequestProcessorTask(SystemFacade &oManifestManager);
        /// @brief Default destructor
        virtual ~TCPRequestProcessorTask(void);

        /// @brief Opens task
        /* <@QACPP: 2427> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Type of returned object is derived from a declaration in parent class> */
        virtual int open(void*);
        /// @brief Service method
        /* <@QACPP: 2427> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Type of returned object is derived from a declaration in parent class> */
        virtual int svc();
        /// @brief Stops task
        void stopTask();
    private:		
        /**
        * @brief TCPRequestProcessorTask copy constructor
        */
        TCPRequestProcessorTask(const TCPRequestProcessorTask&);

        /**
        * @brief TCPRequestProcessorTask assignment operator
        */
        TCPRequestProcessorTask& operator=(const TCPRequestProcessorTask&);
		
	    /// @brief Syncronization semaphore to let the thread exit on a signal
        ACE_Semaphore m_Stop;
        /// @brief System facade object
        SystemFacade &m_oManifestManager;
    };
}

#endif /* MMAN_TASK_HPP_ */
