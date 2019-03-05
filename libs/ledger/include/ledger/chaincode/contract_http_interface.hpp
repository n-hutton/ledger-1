#pragma once
//------------------------------------------------------------------------------
//
//   Copyright 2018-2019 Fetch.AI Limited
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
//------------------------------------------------------------------------------

#include "core/mutex.hpp"
#include "http/module.hpp"
#include "ledger/chaincode/cache.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fetch {
namespace ledger {

class StorageInterface;
class TransactionProcessor;

class ContractHttpInterface : public http::HTTPModule
{

public:
  static constexpr char const *LOGGING_NAME = "ContractHttpInterface";

  // Construction / Destruction
  ContractHttpInterface(StorageInterface &storage, TransactionProcessor &processor);
  ContractHttpInterface(ContractHttpInterface const &) = delete;
  ContractHttpInterface(ContractHttpInterface &&)      = delete;
  ~ContractHttpInterface()                             = default;

  // Operators
  ContractHttpInterface &operator=(ContractHttpInterface const &) = delete;
  ContractHttpInterface &operator=(ContractHttpInterface &&) = delete;

private:
  using Mutex          = mutex::Mutex;
  using ConstByteArray = byte_array::ConstByteArray;

  /**
   * Structure containing status of of multi-transaction submission.
   *
   * The structure is supposed to carry information about how many transactions
   * have been successfully processed and how many transactions have been
   * actually received for processing.
   * The structure is supposed to be used as return value for methods which
   * are dedicated to handle HTTP request for bulk transaction (multi-transaction)
   * reception, giving caller ability to check status of how request has been
   * handled (transaction reception/processing).
   *
   * @see SubmitJsonTx
   * @see SubmitNativeTx
   */
  struct SubmitTxStatus
  {
    std::size_t processed;
    std::size_t received;
  };

  http::HTTPResponse OnQuery(byte_array::ConstByteArray const &contract_name,
                             byte_array::ConstByteArray const &query,
                             http::HTTPRequest const &         request);

  http::HTTPResponse OnTransaction(
      http::ViewParameters const &, http::HTTPRequest const &request,
      byte_array::ConstByteArray const *const expected_contract_name = nullptr);

  SubmitTxStatus SubmitJsonTx(
      http::HTTPRequest const &               request,
      byte_array::ConstByteArray const *const expected_contract_name = nullptr);

  SubmitTxStatus SubmitNativeTx(
      http::HTTPRequest const &               request,
      byte_array::ConstByteArray const *const expected_contract_name = nullptr);

  void RecordTransaction(SubmitTxStatus const &status, http::HTTPRequest const &request);
  void RecordQuery(ConstByteArray const &contract_name, ConstByteArray const &query,
                   http::HTTPRequest const &request);
  void WriteToAccessLog(std::string const &entry);

  StorageInterface &    storage_;
  TransactionProcessor &processor_;
  ChainCodeCache        contract_cache_{};
  Mutex                 access_log_lock_{__LINE__, __FILE__};
  std::ofstream         access_log_;
};

}  // namespace ledger
}  // namespace fetch
