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

#ifndef THIRD_PARTY_SAIR_TRANSFORMS_LOWERING_PASS_CLASSES_H_
#define THIRD_PARTY_SAIR_TRANSFORMS_LOWERING_PASS_CLASSES_H_

#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/SCF/SCF.h"
#include "mlir/Dialect/StandardOps/IR/Ops.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/TypeID.h"
#include "sair_dialect.h"

namespace sair {

#define GEN_PASS_CLASSES
#include "transforms/lowering.h.inc"

}  // namespace sair

#endif  // THIRD_PARTY_SAIR_TRANSFORMS_LOWERING_PASS_CLASSES_H_
