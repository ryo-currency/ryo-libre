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

#include <cstddef>
#include <cstring>
#include <functional>

#define CRYPTO_MAKE_COMPARABLE(type)                         \
	namespace crypto                                         \
	{                                                        \
	inline bool operator==(const type &_v1, const type &_v2) \
	{                                                        \
		return std::memcmp(&_v1, &_v2, sizeof(type)) == 0;   \
	}                                                        \
	inline bool operator!=(const type &_v1, const type &_v2) \
	{                                                        \
		return std::memcmp(&_v1, &_v2, sizeof(type)) != 0;   \
	}                                                        \
	}

#define CRYPTO_MAKE_HASHABLE(type)                                                                           \
	CRYPTO_MAKE_COMPARABLE(type)                                                                             \
	namespace crypto                                                                                         \
	{                                                                                                        \
	static_assert(sizeof(std::size_t) <= sizeof(type), "Size of " #type " must be at least that of size_t"); \
	inline std::size_t hash_value(const type &_v)                                                            \
	{                                                                                                        \
		return reinterpret_cast<const std::size_t &>(_v);                                                    \
	}                                                                                                        \
	}                                                                                                        \
	namespace std                                                                                            \
	{                                                                                                        \
	template <>                                                                                              \
	struct hash<crypto::type>                                                                                \
	{                                                                                                        \
		std::size_t operator()(const crypto::type &_v) const                                                 \
		{                                                                                                    \
			return reinterpret_cast<const std::size_t &>(_v);                                                \
		}                                                                                                    \
	};                                                                                                       \
	}
