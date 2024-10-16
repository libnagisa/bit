#pragma once

#include "./environment.h"

NAGISA_BUILD_LIB_DETAIL_BEGIN

template<class T>
constexpr auto bit_of() noexcept { return sizeof(T) * CHAR_BIT; }

NAGISA_BUILD_LIB_DETAIL_END