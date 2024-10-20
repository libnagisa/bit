#pragma once

#include "./basic.h"
#include "./environment.h"

NAGISA_BUILD_LIB_DETAIL_BEGIN

template<::std::size_t BitWidth>
constexpr ::std::unsigned_integral auto round_floor(::std::unsigned_integral auto value) noexcept
{
	return static_cast<decltype(value)>(value & ~static_cast<::std::uintptr_t>(details::mask<BitWidth>()));
}

template<::std::size_t BitWidth>
constexpr ::std::unsigned_integral auto round_ceil(::std::unsigned_integral auto value) noexcept
{
	return details::round_floor<BitWidth>(value + static_cast<decltype(value)>(details::mask<BitWidth>()));
}

NAGISA_BUILD_LIB_DETAIL_END