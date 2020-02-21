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

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "hash-ops.h"

#ifdef _MSC_VER
#include <malloc.h>
#elif !defined(__FreeBSD__) && !defined(__OpenBSD__) && !defined(__DragonFly__)
#include <alloca.h>
#else
#include <stdlib.h>
#endif

/*** 
* Round to power of two, for count>=3 and for count being not too large (as reasonable for tree hash calculations)
*/
size_t tree_hash_cnt(size_t count)
{
	// This algo has some bad history but all we are doing is 1 << floor(log2(count))
	// There are _many_ ways to do log2, for some reason the one selected was the most obscure one,
	// and fixing it made it even more obscure.
	//
	// Iterative method implemented below aims for clarity over speed, if performance is needed
	// then my advice is to use the BSR instruction on x86
	//
	// All the paranoid asserts have been removed since it is trivial to mathematically prove that
	// the return will always be a power of 2.
	// Problem space has been defined as 3 <= count <= 2^28. Of course quarter of a billion transactions
	// is not a sane upper limit for a block, so there will be tighter limits in other parts of the code

	assert(count >= 3);			 // cases for 0,1,2 are handled elsewhere
	assert(count <= 0x10000000); // sanity limit to 2^28, MSB=1 will cause an inf loop

	size_t pow = 2;
	while(pow < count)
		pow <<= 1;
	return pow >> 1;
}

void tree_hash(const char (*hashes)[HASH_SIZE], size_t count, char *root_hash)
{
	assert(count > 0);
	if(count == 1)
	{
		memcpy(root_hash, hashes, HASH_SIZE);
	}
	else if(count == 2)
	{
		cn_fast_hash(hashes, 2 * HASH_SIZE, root_hash);
	}
	else
	{
		size_t i, j;

		size_t cnt = tree_hash_cnt(count);

		char(*ints)[HASH_SIZE];
		size_t ints_size = cnt * HASH_SIZE;
		ints = alloca(ints_size);
		memset(ints, 0, ints_size); // allocate, and zero out as extra protection for using uninitialized mem

		memcpy(ints, hashes, (2 * cnt - count) * HASH_SIZE);

		for(i = 2 * cnt - count, j = 2 * cnt - count; j < cnt; i += 2, ++j)
		{
			cn_fast_hash(hashes[i], 64, ints[j]);
		}
		assert(i == count);

		while(cnt > 2)
		{
			cnt >>= 1;
			for(i = 0, j = 0; j < cnt; i += 2, ++j)
			{
				cn_fast_hash(ints[i], 64, ints[j]);
			}
		}

		cn_fast_hash(ints[0], 64, root_hash);
	}
}
