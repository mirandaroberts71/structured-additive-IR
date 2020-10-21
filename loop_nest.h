// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef THIRD_PARTY_SAIR_LOOP_NEST_H_
#define THIRD_PARTY_SAIR_LOOP_NEST_H_

#include "llvm/ADT/DenseMap.h"
#include "mlir/IR/Attributes.h"
#include "mlir/Support/LogicalResult.h"
#include "sair_op_interfaces.h"
#include "sair_ops.h"

namespace sair {

// Verifies loop nest attributes of operations nested in the
// sair.program operation.
mlir::LogicalResult VerifyLoopNests(SairProgramOp program);

// Analysis that keeps track of the loop nest of operations.
class LoopNestAnalysis {
 public:
  explicit LoopNestAnalysis(SairProgramOp program_op);

  // Computes or retrieves the loop nest of the given operation.
  mlir::ArrayAttr GetLoopNest(SairOp op) const;

  // Computes or retrieves the loop nest associated to a value. The value must
  // be defined by a sair operation.
  mlir::ArrayAttr GetLoopNest(mlir::Value value) const;

 private:
  // Computes the loop nest for the given operation.
  mlir::ArrayAttr ComputeLoopNest(mlir::Operation *operation);

  llvm::DenseMap<mlir::Operation *, mlir::ArrayAttr> loop_nests_;
};

}  // namespace sair

#endif  // THIRD_PARTY_SAIR_LOOP_NEST_H_
