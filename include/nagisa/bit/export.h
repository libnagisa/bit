#pragma once

#include "./detail/basic.h"
#include "./detail/bit_of.h"
#include "./detail/literals.h"
#include "./detail/round.h"
#include "./environment.h"

NAGISA_BUILD_LIB_BEGIN

using details::fixed_width_int_t;
using details::fixed_width_uint_t;
using details::mask;
using details::left_shift;
using details::right_shift;

using details::bit_of;

using details::round_ceil;
using details::round_floor;

namespace literals = details::literals;

NAGISA_BUILD_LIB_END