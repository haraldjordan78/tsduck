//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2005-2017, Thierry Lelegard
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.
//
//----------------------------------------------------------------------------
//!
//!  @file
//!  Command line arguments for the class TablesLogger.
//!
//----------------------------------------------------------------------------

#pragma once
#include "tsTablesDisplayArgs.h"
#include "tsMPEG.h"

namespace ts {
    //!
    //! Command line arguments for the class TablesLogger.
    //!
    class TSDUCKDLL TablesLoggerArgs: public TablesDisplayArgs
    {
    public:
        //!
        //! Explicit reference to superclass.
        //!
        typedef TablesDisplayArgs SuperClass;

        //!
        //! Constructor.
        //!
        TablesLoggerArgs();

        //!
        //! Virtual destructor.
        //!
        virtual ~TablesLoggerArgs() {}

        //!
        //! Type of logging destination.
        //!
        enum Mode {
            TEXT,    //!< Formatted human-readable tables.
            BINARY,  //!< Save binary sections.
            UDP      //!< Send sections using UDP/IP.
        };

        // Public fields, by options.
        Mode         mode;            //!< Type of destination.
        std::string  destination;     //!< Destination name (file, host, etc).
        bool         multi_files;     //!< Multiple binary output files (one per section).
        bool         flush;           //!< Flush output file.
        std::string  udp_local;       //!< Name of outgoing local address (empty if unspecified).
        int          udp_ttl;         //!< Time-to-live socket option.
        bool         udp_raw;         //!< UDP messages contain raw sections, not structured messages.
        bool         all_sections;    //!< Collect all sections, as they appear.
        uint32_t     max_tables;      //!< Max number of tables to dump.
        bool         time_stamp;      //!< Display time stamps with each table.
        bool         packet_index;    //!< Display packet index with each table.
        bool         diversified;     //!< Payload must be diversified.
        bool         logger;          //!< Table logger.
        size_t       log_size;        //!< Size of table to log.
        bool         negate_tid;      //!< Negate tid filter (exclude selected tids).
        bool         negate_tidext;   //!< Negate tidext filter (exclude selected tidexts).
        PIDSet       pid;             //!< PID values to filter.
        bool         add_pmt_pids;    //!< Add PMT PID's when one is found.
        std::set<uint8_t>  tid;       //!< TID values to filter.
        std::set<uint16_t> tidext;    //!< TID-ext values to filter.

        //!
        //! Default table log size.
        //! With option -\-log, specify how many bytes are displayed at the
        //! beginning of the table payload (the header is not displayed).
        //! The default is 8 bytes.
        //!
        static const size_t DEFAULT_LOG_SIZE = 8;

        //!
        //! Check if standard output shall be used.
        //! @return True if standard output shall be used.
        //!
        bool useCout() const
        {
            return mode == TEXT && destination.empty();
        }

        //!
        //! Define command line options in an Args.
        //! @param [in,out] args Command line arguments to update.
        //!
        virtual void defineOptions(Args& args) const;

        //!
        //! Add help about command line options in an Args.
        //! @param [in,out] args Command line arguments to update.
        //!
        virtual void addHelp(Args& args) const;

        //!
        //! Load arguments from command line.
        //! Args error indicator is set in case of incorrect arguments.
        //! @param [in,out] args Command line arguments.
        //!
        virtual void load(Args& args);
    };
}