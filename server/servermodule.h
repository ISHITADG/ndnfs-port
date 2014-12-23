/*
 * Copyright (c) 2014 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * This is the ported ndnfs(https://github.com/wentaoshang/NDNFS.git)
 * to ndn-cpp(CCL) and NFD.
 *
 * Author: Zhehao Wang, based on the work of
 * Qiuhan Ding <dingqiuhan@gmail.com>, Wentao Shang <wentao@cs.ucla.edu>
 */

#ifndef __SERVER_MODULE_H__
#define __SERVER_MODULE_H__

#define NDNFS_DEBUG

#include <string>

#include <ndn-cpp/face.hpp>
#include <ndn-cpp/common.hpp>
#include <ndn-cpp/name.hpp>
#include <ndn-cpp/interest.hpp>
#include <ndn-cpp/security/key-chain.hpp>
#include <ndn-cpp/security/identity/osx-private-key-storage.hpp>
#include <ndn-cpp/security/identity/memory-private-key-storage.hpp>
#include "dir.pb.h"
#include "file.pb.h"

#include <sqlite3.h>

#define FULLLEN 100

extern const char *db_name;
extern sqlite3 *db;
extern ndn::KeyChain keyChain;
extern ndn::Name certificateName;

extern std::string global_prefix;
extern const char* fs_path;

void onInterest(const ndn::ptr_lib::shared_ptr<const ndn::Name>& prefix, const ndn::ptr_lib::shared_ptr<const ndn::Interest>& interest, ndn::Transport& transport, uint64_t registeredPrefixId);

void onRegisterFailed(const ndn::ptr_lib::shared_ptr<const ndn::Name>& prefix);

void parseName(const ndn::Name& name, int &version, int &seg, std::string &path);

void processInterest(const ndn::Name& interest_name, ndn::Transport& transport);

void sendDir(const std::string& path, int mtime, ndn::Transport& transport);

void sendFile(const std::string& path, int version, int sizef, int totalseg, ndn::Transport& transport);

#endif // __SERVER_MODULE_H__
