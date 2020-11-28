/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__errorhandler.cpp
*
* Description  : Manifest manager, error handler implementation
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

/* System Headerfiles */
#include <string.h>

/* Own Headerfiles */
#include "mman__errorhandler.hpp"
#include "mman__hooks.hpp"

namespace manifest_manager
{
    void ErrorHandler::vReportError(tenErrorId enErrorId, int32 i32Details, const char *pcPath, uint32 u32Line)
    {
        const char *pcFile = pcGetFileName(pcPath);
        if (!pcFile)
        {
            // Fallback in case no file or path was specified
            pcFile = "(null)";
        }

        Hooks::vReportError(pcFile, u32Line, enErrorId, i32Details);
    }

    const char *ErrorHandler::pcGetFileName(const char *pcPath)
    {
        const char *pcFile = NULL;

        if (pcPath)
        {
            if (!pcFile)
            {
                /* <@QACPP: 5029> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Output of __FILE__ macro has a terminating character> */
                const char *pcDelim = strrchr(pcPath, '\\');
                if (pcDelim)
                {
                    pcFile = pcDelim + 1;
                }
            }

            if (!pcFile)
            {
                /* <@QACPP: 5029> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Output of __FILE__ macro has a terminating character> */
                const char *pcDelim = strrchr(pcPath, '/');
                if (pcDelim)
                {
                    pcFile = pcDelim + 1;
                }
            }

            if (!pcFile)
            {
                pcFile = pcPath;
            }
        }

        return pcFile;
    }
}
