/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__capabilitydb.cpp
*
* Description  : Manifest manager, capability database implementation
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#include "mman__capabilitydb.hpp"

namespace manifest_manager
{
    /**
    * Capability database
    */
    tCapabilityDatabaseEntry MMAN__astCapabilityDatabase[MMAN__nCapabilityDatabaseSize] =
    {
        /**
         Server services
        */
        // 0x6021, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6021,
        },
        // 0x6021, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6021,
        },
        // 0x6021, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6021,
        },
        // 0x6021, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x6021,
        },
        // 0x6021, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x6021,
        },
        // 0x6021, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x6021,
        },
        // 0x6021, service discovery, outgoing
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6021,
        },


        // 0x6035, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6035,
        },
        // 0x6035, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x6035,
        },
        // 0x6035, service discovery, outgoing
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6035,
        },


        // 0x6034, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6034,
        },
        // 0x6034, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6034,
        },
        // 0x6034, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x6034,
        },
        // 0x6034, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x6034,
        },
        // 0x6034, service discovery, outgoing
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6034,
        },


        // 0x600E, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x600E,
        },
        // 0x600E, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x600E,
        },
        // 0x600E, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x600E,
        },
        // 0x600E, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x600E,
        },
        // 0x600E, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x600E,
        },
        // 0x600E, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x600E,
        },
        // 0x600E, service discovery, outgoing
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x600E,
        },


        // 0x6046, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6046,
        },
        // 0x6046, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6046,
        },
        // 0x6046, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x6046,
        },
        // 0x6046, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x6046,
        },
        // 0x6046, service discovery, outgoing
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6046,
        },

        /**
         Client services
        */
        // 0x6068, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6068,
        },
        // 0x6068, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x6068,
        },
        // 0x6068, notifications, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            42810U,
            nenUDP,
            nenNone,
            0x6068,
        },


        // 0x6069, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6069,
        },
        // 0x6069, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x6069,
        },
        // 0x6069, notifications, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            42810U,
            nenUDP,
            nenNone,
            0x6069,
        },


        // 0x600a, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x10 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x600a,
        },
        // 0x600a, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x10 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenAuthentic,
            0x600a,
        },
        // 0x600a, notifications, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x10 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            42820U,
            nenUDP,
            nenAuthentic,
            0x600a,
        },


        // 0x6017, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6017,
        },
        // 0x6017, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x6017,
        },
        // 0x6017, notifications, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            42810U,
            nenUDP,
            nenNone,
            0x6017,
        },


        // 0x6009, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06 },
            { 0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
            30490U,
            nenUDP,
            nenNone,
            0x6009,
        },
        // 0x6009, service discovery, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            30490U,
            nenUDP,
            nenNone,
            0x6009,
        },
        // 0x6009, notifications, incoming
        {
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06 },
            { 0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 },
            42810U,
            nenUDP,
            nenNone,
            0x6009,
        },
    };
}