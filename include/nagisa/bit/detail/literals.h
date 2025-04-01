#pragma once

#include "./environment.h"

NAGISA_BUILD_LIB_DETAIL_BEGIN

namespace literals
{
	constexpr auto operator ""_b(unsigned long long int x) noexcept { return x * (1ull << 0); }

	constexpr auto operator ""_kb(unsigned long long int x) noexcept { return x * (1ull << 10); }

	constexpr auto operator ""_mb(unsigned long long int x) noexcept { return x * (1ull << 20); }

	constexpr auto operator ""_gb(unsigned long long int x) noexcept { return x * (1ull << 30); }

	constexpr auto operator ""_tb(unsigned long long int x) noexcept { return x * (1ull << 40); }

	constexpr auto operator ""_pb(unsigned long long int x) noexcept { return x * (1ull << 50); }

	constexpr auto operator ""_byte(unsigned long long int x) noexcept { return ::std::byte{ x }; }
}

NAGISA_BUILD_LIB_DETAIL_END