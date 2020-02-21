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

#pragma once

#include "serialization/keyvalue_serialization.h"
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/version.hpp>
#include <ostream>

namespace cryptonote
{
struct subaddress_index
{
	subaddress_index(uint32_t maj, uint32_t min) { major = maj; minor = min; }
  
	uint32_t major;
	uint32_t minor;
	bool operator==(const subaddress_index &rhs) const { return !memcmp(this, &rhs, sizeof(subaddress_index)); }
	bool operator!=(const subaddress_index &rhs) const { return !(*this == rhs); }
	bool is_zero() const { return major == 0 && minor == 0; }

	BEGIN_SERIALIZE_OBJECT()
	FIELD(major)
	FIELD(minor)
	END_SERIALIZE()

	BEGIN_KV_SERIALIZE_MAP(subaddress_index)
	KV_SERIALIZE(major)
	KV_SERIALIZE(minor)
	END_KV_SERIALIZE_MAP()
};
}

namespace cryptonote
{
inline std::ostream &operator<<(std::ostream &out, const cryptonote::subaddress_index &subaddr_index)
{
	return out << subaddr_index.major << '/' << subaddr_index.minor;
}
}

namespace std
{
template <>
struct hash<cryptonote::subaddress_index>
{
	size_t operator()(const cryptonote::subaddress_index &index) const
	{
		size_t res;
		if(sizeof(size_t) == 8)
		{
			res = ((uint64_t)index.major << 32) | index.minor;
		}
		else
		{
			// https://stackoverflow.com/a/17017281
			res = 17;
			res = res * 31 + hash<uint32_t>()(index.major);
			res = res * 31 + hash<uint32_t>()(index.minor);
		}
		return res;
	}
};
}

BOOST_CLASS_VERSION(cryptonote::subaddress_index, 0)

namespace boost
{
namespace serialization
{
template <class Archive>
inline void serialize(Archive &a, cryptonote::subaddress_index &x, const boost::serialization::version_type ver)
{
	a &x.major;
	a &x.minor;
}
}
}
