// RUN: sair-opt -inline-trivial-sair-ops %s | FileCheck %s

// CHECK-LABEL: @one_map
func @one_map() -> f32 {
  // CHECK: %[[v0:.*]] = constant 1.0
  %0 = constant 1.0 : f32
  // CHECK-NOT: sair.program
  %1 = sair.program {
    // CHECK-NOT: from_scalar
    %2 = sair.from_scalar %0 : !sair.value<(), f32>
    // CHECK-NOT: sair.map
    %3 = sair.map %2 {
    ^bb0(%arg0: f32):
      // CHECK: %[[v3:.*]] = addf %[[v0]], %[[v0]]
      %4 = addf %arg0, %arg0 : f32
      // CHECK-NOT: sair.return
      sair.return %4 : f32
    } : #sair.shape<()>, (f32) -> f32
    // CHECK-NOT: sair.exit
    sair.exit %3 : f32
  } : f32
  // CHECK: return %[[v3]] : f32
  return %1 : f32
}

// CHECK-LABEL: @sequence
func @sequence() -> f32 {
  // CHECK: %[[v0:.*]] = constant 1.0
  %0 = constant 1.0 : f32
  // CHECK-NOT: sair.program
  %6 = sair.program {
    // CHECK-NOT: from_scalar
    %1 = sair.from_scalar %0 : !sair.value<(), f32>
    // CHECK-NOT: sair.map
    %2 = sair.map %1 {
    ^bb0(%arg0: f32):
      // CHECK: %[[v3:.*]] = addf %[[v0]], %[[v0]]
      %3 = addf %arg0, %arg0 : f32
      // CHECK-NOT: sair.return
      sair.return %3 : f32
    } : #sair.shape<()>, (f32) -> f32

    // CHECK-NOT: sair.map_reduce
    %4 = sair.map_reduce %1 reduce %2 {
    ^bb1(%arg1: f32, %arg2: f32):
      // CHECK: %[[v5:.*]] = mulf %[[v0]], %[[v3]]
      %5 = mulf %arg1, %arg2 : f32
      // CHECK-NOT: sair.return
      sair.return %5 : f32
    } : #sair.shape<()>, (f32) -> f32
    // CHECK-NOT: sair.exit
    sair.exit %4 : f32
  } : f32
  // CHECK: return %[[v5]] : f32
  return %6 : f32
}

// CHECK-LABEL: @do_nothing
func @do_nothing() {
  %0 = constant 1.0 : f32
  sair.program {
    %1 = sair.static_range 8 : !sair.range
    %2 = sair.from_scalar %0 : !sair.value<(), f32>
    %3 = sair.map_reduce %2 reduce[d0:%1] {
      ^bb0(%arg0: index, %arg1: f32):
        sair.return %arg1 : f32
    } : #sair.shape<d0:range>, () -> f32
    // The "map" should not be removed unless we can find the scalar value used
    // to construct its operand, which is not available in this case.
    // CHECK: sair.map
    %4 = sair.map %3 {
    ^bb0(%arg1: f32):
      sair.return %arg1 : f32
    } : #sair.shape<()>, (f32) -> f32
    sair.exit
  }
  return
}
