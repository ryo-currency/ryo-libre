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
namespace cryptonote
{
/************************************************************************/
/*                                                                      */
/************************************************************************/
struct tx_verification_context
{
	bool m_should_be_relayed;
	bool m_verifivation_failed;		//bad tx, should drop connection
	bool m_verifivation_impossible; //the transaction is related with an alternative blockchain
	bool m_added_to_pool;
	bool m_low_mixin;
	bool m_double_spend;
	bool m_invalid_input;
	bool m_invalid_output;
	bool m_too_big;
	bool m_overspend;
	bool m_fee_too_low;
	bool m_not_rct;
};

struct block_verification_context
{
	bool m_added_to_main_chain;
	bool m_verifivation_failed; //bad block, should drop connection
	bool m_marked_as_orphaned;
	bool m_already_exists;
	bool m_partial_block_reward;
};
}
