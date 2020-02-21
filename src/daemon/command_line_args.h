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

#ifndef DAEMON_COMMAND_LINE_ARGS_H
#define DAEMON_COMMAND_LINE_ARGS_H

#include "common/command_line.h"
#include "cryptonote_config.h"
#include "daemonizer/daemonizer.h"

namespace daemon_args
{
std::string const WINDOWS_SERVICE_NAME = "Ryo Daemon";

const command_line::arg_descriptor<std::string, false, true, 2> arg_config_file = {
	"config-file", "Specify configuration file", (daemonizer::get_default_data_dir() / std::string(CRYPTONOTE_NAME ".conf")).string(), {{&cryptonote::arg_testnet_on, &cryptonote::arg_stagenet_on}}, [](std::array<bool, 2> testnet_stagenet, bool defaulted, std::string val) -> std::string {
      if (testnet_stagenet[0] && defaulted)
        return (daemonizer::get_default_data_dir() / "testnet" /
                std::string(CRYPTONOTE_NAME ".conf")).string();
      else if (testnet_stagenet[1] && defaulted)
        return (daemonizer::get_default_data_dir() / "stagenet" /
                std::string(CRYPTONOTE_NAME ".conf")).string();
      return val; }};
const command_line::arg_descriptor<std::string, false, true, 2> arg_log_file = {
	"log-file", "Specify log file", (daemonizer::get_default_data_dir() / std::string(CRYPTONOTE_NAME ".log")).string(), {{&cryptonote::arg_testnet_on, &cryptonote::arg_stagenet_on}}, [](std::array<bool, 2> testnet_stagenet, bool defaulted, std::string val) -> std::string {
      if (testnet_stagenet[0] && defaulted)
        return (daemonizer::get_default_data_dir() / "testnet" /
                std::string(CRYPTONOTE_NAME ".log")).string();
      else if (testnet_stagenet[1] && defaulted)
        return (daemonizer::get_default_data_dir() / "stagenet" /
                std::string(CRYPTONOTE_NAME ".log")).string();
      return val; }};
const command_line::arg_descriptor<std::string> arg_log_level = {
	"log-level", "Screen log level", ""};
const command_line::arg_descriptor<std::string> arg_log_file_level = {
	"file-log-level", "File log level", ""};
const command_line::arg_descriptor<std::vector<std::string>> arg_command = {
	"daemon_command", "Hidden"};
const command_line::arg_descriptor<bool> arg_os_version = {
	"os-version", "OS for which this executable was compiled"};
const command_line::arg_descriptor<unsigned> arg_max_concurrency = {
	"max-concurrency", "Max number of threads to use for a parallel job", 0};

const command_line::arg_descriptor<std::string> arg_zmq_rpc_bind_ip = {
	"zmq-rpc-bind-ip", "IP for ZMQ RPC server to listen on", "127.0.0.1"};

const command_line::arg_descriptor<std::string, false, true, 2> arg_zmq_rpc_bind_port = {
	"zmq-rpc-bind-port", "Port for ZMQ RPC server to listen on", std::to_string(cryptonote::config<cryptonote::MAINNET>::ZMQ_RPC_DEFAULT_PORT), {{&cryptonote::arg_testnet_on, &cryptonote::arg_stagenet_on}}, [](std::array<bool, 2> testnet_stagenet, bool defaulted, std::string val) -> std::string {
      if (testnet_stagenet[0] && defaulted)
        return std::to_string(cryptonote::config<cryptonote::TESTNET>::ZMQ_RPC_DEFAULT_PORT);
      if (testnet_stagenet[1] && defaulted)
        return std::to_string(cryptonote::config<cryptonote::STAGENET>::ZMQ_RPC_DEFAULT_PORT);
      return val; }};

const command_line::arg_descriptor<bool> arg_display_timestamps = {
	"display-timestamps", "Display screen log with timestamps"};

} // namespace daemon_args

#endif // DAEMON_COMMAND_LINE_ARGS_H
