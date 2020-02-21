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

#include "wipeable_string.h"
#include <atomic>
#include <boost/optional/optional.hpp>
#include <string>

namespace tools
{
class password_container
{
  public:
	static constexpr const size_t max_password_size = 1024;

	//! Empty password
	password_container() noexcept;

	//! `password` is used as password
	password_container(std::string &&password) noexcept;

	//! \return A password from stdin TTY prompt or `std::cin` pipe.
	static boost::optional<password_container> prompt(bool verify, const char *mesage = "Password");
	static std::atomic<bool> is_prompting;

	password_container(const password_container &) = delete;
	password_container(password_container &&rhs) = default;

	//! Wipes internal password
	~password_container() noexcept;

	password_container &operator=(const password_container &) = delete;
	password_container &operator=(password_container &&) = default;

	const epee::wipeable_string &password() const noexcept { return m_password; }

  private:
	epee::wipeable_string m_password;
};

struct login
{
	login() = default;

	/*!
       Extracts username and password from the format `username:password`. A
       blank username or password is allowed. If the `:` character is not
       present, `password_container::prompt` will be called by forwarding the
       `verify` and `message` arguments.

       \param userpass Is "consumed", and the memory contents are wiped.
       \param verify is passed to `password_container::prompt` if necessary.
       \param message is passed to `password_container::prompt` if necessary.

       \return The username and password, or boost::none if
         `password_container::prompt` fails.
     */
	static boost::optional<login> parse(std::string &&userpass, bool verify, const std::function<boost::optional<password_container>(bool)> &prompt);

	login(const login &) = delete;
	login(login &&) = default;
	~login() = default;
	login &operator=(const login &) = delete;
	login &operator=(login &&) = default;

	std::string username;
	password_container password;
};
}
