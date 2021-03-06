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

#ifndef SAIR_SAIR_TYPES_H_
#define SAIR_SAIR_TYPES_H_

#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Types.h"

namespace sair {

namespace impl {
// Private implementation for sair::RangeType.
class SairShapedTypeStorage;
// Private implementation for sair::ValueType.
class ValueTypeStorage;
}  // end namespace impl

class DomainShapeAttr;

// Base type for Sair objects (values or iteration dimensions) that are defined
// for each point in an iteration domain. This type exposes the shape of the
// domain. Unknown shapes are not supported.
class SairShapedType : public mlir::Type {
 public:
  // This a hook for the MLIR type system.
  using ImplType = impl::SairShapedTypeStorage;
  using Type::Type;

  // Returns the shape of the type.
  DomainShapeAttr Shape() const;
};

// Range type is used for values that define a dimension in a Sair iteration
// domain. A range type may dependent on some number of other iteration
// dimensions. The syntax for the range type is as follows:
//
//   sair-range-type ::= `!` dialect-namespace `.` `range` ('<' dom-shape '>')?
//
class RangeType : public mlir::Type::TypeBase<RangeType, SairShapedType,
                                              impl::SairShapedTypeStorage> {
 public:
  // Constructs RangeType from opaque types in MLIR TypeBase.
  using Base::Base;

  // Constructs an instance of RangeType in the provided context. This is a hook
  // for MLIR Builders.
  static RangeType get(mlir::MLIRContext *context, DomainShapeAttr shape);

  // Returns the name of this type as it appears in the textual format without
  // the dialect prefix.
  static llvm::StringRef Name() { return "range"; }
};

class AccessPatternAttr;

// Types for n-dimensional values produced and consumed by sair operators. A
// value type specifies the shape of the domain of the value and its element
// type. The syntax for this type is the following.
//
//   value-type ::= `!` dialect-namespace `.` `value` `<` dom-shape `,` type `>`
//
class ValueType : public mlir::Type::TypeBase<ValueType, SairShapedType,
                                              impl::ValueTypeStorage> {
 public:
  // Construct ValueType from opaque types in MLIR TypeBase.
  using Base::Base;

  // Construct an instance of ValueType in the provided context. This is a hook
  // for MLIR Builders.
  static ValueType get(mlir::MLIRContext *context, DomainShapeAttr domain,
                       mlir::Type element_type);

  // Construct a 0-dimensional instance of ValueType in the provided context.
  // This is a hook for MLIR Builders.
  static ValueType get(mlir::MLIRContext *context, mlir::Type element_type);

  // Returns the name of this type as it appears in the textual format, without
  // the dialect prefix.
  static llvm::StringRef Name() { return "value"; }

  // Returns the type of the value elements.
  mlir::Type ElementType() const;

  // Converts the type from the use domain to the def domain of the access
  // pattern.
  ValueType AccessedType(AccessPatternAttr access_pattern) const;
};

}  // end namespace sair

#endif  // SAIR_SAIR_TYPES_H_
