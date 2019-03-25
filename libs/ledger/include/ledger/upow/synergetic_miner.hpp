#pragma once

#include "vm/analyser.hpp"
#include "vm/typeids.hpp"

#include "vm/compiler.hpp"
#include "vm/module.hpp"
#include "vm/vm.hpp"

#include "synergetic_vm_module.hpp"
#include "synergetic_contract.hpp"
#include "work.hpp"

namespace fetch
{
namespace consensus
{

class SynergeticMiner {
public:
  using ScoreType = Work::ScoreType;

  SynergeticMiner(fetch::ledger::DAG &dag)
  : dag_(dag)
  {
    CreateConensusVMModule(module_);

    // Preparing VM & compiler
    vm_       = new fetch::vm::VM(&module_);
    vm_->RegisterGlobalPointer(&dag_);
  }

  ~SynergeticMiner() 
  {
    delete vm_;
  }

  bool DefineProblem(SynergeticContract contract) 
  { 
    assert(contract != nullptr);
    text_output_ = "";

    // Defining problem
    if (!vm_->Execute(contract->script, contract->problem_function, error_, text_output_, problem_))
    {
      // TODO: LOG
      return false;
    }
    return true;
  }

  ScoreType ExecuteWork(SynergeticContract contract, Work work) 
  { 
    text_output_ = "";

    if(work.contract_name != contract.contract_name)
    {
      throw std::runtime_error("Contract name between work and used contract differs.");
    }

    // Executing the work function
    int64_t nonce = work();

    if (!vm_->Execute(contract->script, contract->work_function, error_,  text_output_, solution_, problem_, nonce))
    {
      std::cerr << "Runtime error: " << error_ << std::endl;
      return std::numeric_limits< ScoreType >::max();
    }

    // Computing objective function
    if (!vm_->Execute(contract->script, contract->objective_function, error_, text_output_, score_,  problem_, solution_))
    {
      std::cerr << "Runtime error: " << error_ << std::endl;
      return std::numeric_limits< ScoreType >::max();
    }
    
    return score_.primitive.f64; // TODO: Migrate to i64 and fixed points
  }
private:
  fetch::ledger::DAG  &dag_;
  fetch::vm::Module    module_;
  fetch::vm::VM *      vm_;

  std::string        error_;
  fetch::vm::Variant problem_;
  fetch::vm::Variant solution_; 
  fetch::vm::Variant score_;  
  std::string text_output_;
};


}
}