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

#include "rpc/core_rpc_server.h"

#include "common/gulps.hpp"



namespace daemonize
{

class t_rpc final
{
	 GULPS_CAT_MAJOR("daemon_rpc");
  public:
	static void init_options(boost::program_options::options_description &option_spec)
	{
		cryptonote::core_rpc_server::init_options(option_spec);
	}

  private:
	cryptonote::core_rpc_server m_server;
	const std::string m_description;

  public:
	t_rpc(
		boost::program_options::variables_map const &vm, t_core &core, t_p2p &p2p, const bool restricted, const cryptonote::network_type nettype, const std::string &port, const std::string &description)
		: m_server{core.get(), p2p.get()}, m_description{description}
	{
		GULPSF_GLOBAL_PRINT("Initializing {} RPC server...", m_description);

		if(!m_server.init(vm, restricted, nettype, port))
		{
			throw std::runtime_error("Failed to initialize " + m_description + " RPC server.");
		}
		GULPSF_GLOBAL_PRINT("{} RPC server initialized OK on port: {}", m_description, m_server.get_binded_port());
	}

	void run()
	{
		GULPSF_GLOBAL_PRINT("Starting {} RPC server...",m_description);
		if(!m_server.run(2, false))
		{
			throw std::runtime_error("Failed to start " + m_description + " RPC server.");
		}
		GULPSF_GLOBAL_PRINT("{} RPC server started ok", m_description);
	}

	void stop()
	{
		GULPSF_GLOBAL_PRINT("Stopping {} RPC server...", m_description);
		m_server.send_stop_signal();
		m_server.timed_wait_server_stop(5000);
	}

	cryptonote::core_rpc_server *get_server()
	{
		return &m_server;
	}

	~t_rpc()
	{
		GULPSF_GLOBAL_PRINT("Deinitializing {} RPC server...", m_description);
		try
		{
			m_server.deinit();
		}
		catch(...)
		{
			GULPSF_ERROR("Failed to deinitialize {} RPC server...", m_description);
		}
	}
};
}
