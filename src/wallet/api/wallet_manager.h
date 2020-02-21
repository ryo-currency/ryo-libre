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

#include "net/http_client.h"
#include "wallet/api/wallet2_api.h"
#include <string>

namespace Ryo
{

class WalletManagerImpl : public WalletManager
{
  public:
	Wallet *createWallet(const std::string &path, const std::string &password,
						 const std::string &language, NetworkType nettype);
	Wallet *openWallet(const std::string &path, const std::string &password, NetworkType nettype);
	virtual Wallet *recoveryWallet(const std::string &path,
								   const std::string &password,
								   const std::string &mnemonic,
								   NetworkType nettype,
								   uint64_t restoreHeight);
	virtual Wallet *createWalletFromKeys(const std::string &path,
										 const std::string &password,
										 const std::string &language,
										 NetworkType nettype,
										 uint64_t restoreHeight,
										 const std::string &addressString,
										 const std::string &viewKeyString,
										 const std::string &spendKeyString = "");
	// next two methods are deprecated - use the above version which allow setting of a password
	virtual Wallet *recoveryWallet(const std::string &path, const std::string &mnemonic, NetworkType nettype, uint64_t restoreHeight);
	// deprecated: use createWalletFromKeys(..., password, ...) instead
	virtual Wallet *createWalletFromKeys(const std::string &path,
										 const std::string &language,
										 NetworkType nettype,
										 uint64_t restoreHeight,
										 const std::string &addressString,
										 const std::string &viewKeyString,
										 const std::string &spendKeyString = "");
	virtual bool closeWallet(Wallet *wallet, bool store = true);
	bool walletExists(const std::string &path);
	bool verifyWalletPassword(const std::string &keys_file_name, const std::string &password, bool no_spend_key) const;
	std::vector<std::string> findWallets(const std::string &path);
	std::string errorString() const;
	void setDaemonAddress(const std::string &address);
	bool connected(uint32_t *version = NULL);
	uint64_t blockchainHeight();
	uint64_t blockchainTargetHeight();
	uint64_t networkDifficulty();
	double miningHashRate();
	uint64_t blockTarget();
	bool isMining();
	bool startMining(const std::string &address, uint32_t threads = 1, bool background_mining = false, bool ignore_battery = true);
	bool stopMining();

  private:
	WalletManagerImpl() {}
	friend struct WalletManagerFactory;
	std::string m_daemonAddress;
	epee::net_utils::http::http_simple_client m_http_client;
	std::string m_errorString;
};

} // namespace
