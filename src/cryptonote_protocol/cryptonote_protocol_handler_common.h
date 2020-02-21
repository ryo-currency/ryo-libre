// Copyright (c) 2019, Ryo Currency Project
// Portions copyright (c) 2014-2018, The Monero Project
//
// Portions of this file are available under BSD-3 license. Please see ORIGINAL-LICENSE for details
// All rights reserved.
//
// Ryo changes to this code are in public domain. Please note, other licences may apply to the file.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers

#pragma once

#include "cryptonote_basic/connection_context.h"
#include "cryptonote_protocol/cryptonote_protocol_defs.h"
#include "p2p/net_node_common.h"
namespace cryptonote
{
/************************************************************************/
/*                                                                      */
/************************************************************************/
struct i_cryptonote_protocol
{
	virtual bool relay_block(NOTIFY_NEW_BLOCK::request &arg, cryptonote_connection_context &exclude_context) = 0;
	virtual bool relay_transactions(NOTIFY_NEW_TRANSACTIONS::request &arg, cryptonote_connection_context &exclude_context) = 0;
	//virtual bool request_objects(NOTIFY_REQUEST_GET_OBJECTS::request& arg, cryptonote_connection_context& context)=0;
};

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cryptonote_protocol_stub : public i_cryptonote_protocol
{
	virtual bool relay_block(NOTIFY_NEW_BLOCK::request &arg, cryptonote_connection_context &exclude_context)
	{
		return false;
	}
	virtual bool relay_transactions(NOTIFY_NEW_TRANSACTIONS::request &arg, cryptonote_connection_context &exclude_context)
	{
		return false;
	}
};
}
