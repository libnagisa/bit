#pragma once

#include "./environment.h"

NAGISA_BUILD_LIB_DETAIL_BEGIN

template<auto BitWidth, class UnderlyingType>
concept expressable = ::std::unsigned_integral<decltype(BitWidth)> && requires
{
	{ ::std::numeric_limits<UnderlyingType>::digits } -> ::std::integral;
	requires (::std::numeric_limits<UnderlyingType>::digits >= BitWidth);
};

enum storage
{
	byte,
	word,
	double_word,
	quad,
};

constexpr auto storage_of(::std::uint_least8_t bit_width) noexcept
{
#if (__cpp_if_consteval >= 202106L)
	if consteval
#else
	if (::std::is_constant_evaluated())
#endif
	{
		if (bit_width > ::std::numeric_limits<::std::uintmax_t>::digits)
		{
			//::std::abort();
		}
	}
	return static_cast<storage>(::std::countr_zero(::std::bit_ceil(bit_width / 8u + static_cast<bool>(bit_width % 8u))));
}

using uint_sequence_t = stl_freestanding::tuples::static_tuple<::std::uint8_t, ::std::uint16_t, ::std::uint32_t, ::std::uint64_t>;
using int_sequence_t = stl_freestanding::tuples::static_tuple<::std::int8_t, ::std::int16_t, ::std::int32_t, ::std::int64_t>;

template<::std::uint_least8_t Digits>
using fixed_width_uint_t = stl_freestanding::tuples::tuple_element_t<static_cast<::std::uint_least8_t>(details::storage_of(Digits)), uint_sequence_t>;

template<::std::uint_least8_t Digits>
using fixed_width_int_t = stl_freestanding::tuples::tuple_element_t<static_cast<::std::uint_least8_t>(details::storage_of(Digits + 1)), int_sequence_t>;

template<bool Signed, ::std::uint_least8_t Digits>
using fixed_width_switch_signed = ::std::conditional_t<Signed, fixed_width_int_t<Digits>, fixed_width_uint_t<Digits>>;


template<::std::unsigned_integral T>
consteval auto mask() noexcept
{
	return static_cast<T>(~static_cast<T>(0));
}

template<::std::integral T, auto BitWidth>
	requires expressable<BitWidth, T>
consteval auto mask() noexcept
{
	using unsigned_type = ::std::make_unsigned_t<T>;

	/// make sure diff in range [0, numeric_limits<unsigned_type>::digits)
	if constexpr (BitWidth == 0)
	{
		return static_cast<T>(0);
	}
	else
	{
		constexpr auto diff = ::std::numeric_limits<unsigned_type>::digits - BitWidth;
		return static_cast<T>(details::mask<unsigned_type>() >> diff);
	}
}

template<::std::uint_least8_t BitWidth>
	requires (BitWidth <= ::std::numeric_limits<::std::uintmax_t>::digits)
consteval auto mask() noexcept
{
	return details::mask<fixed_width_uint_t<BitWidth>, BitWidth>();
}

template<bool Signed, ::std::uint_least8_t Digits>
	requires (Digits <= ::std::numeric_limits<::std::uintmax_t>::digits)
consteval auto mask() noexcept
{
	return details::mask<fixed_width_switch_signed<Signed, Digits>, Digits>();
}


template<::std::int8_t Shift>
constexpr auto left_shift(::std::integral auto value) noexcept
{

	if constexpr (Shift > 0)
	{
		if constexpr (Shift >= ::std::numeric_limits<decltype(value)>::digits)
		{
			return 0;
		}
		else
		{
			return value << Shift;
		}
	}
	else if constexpr (Shift < 0)
	{
		if constexpr (-Shift >= ::std::numeric_limits<decltype(value)>::digits)
		{
			return 0;
		}
		else
		{
			return value >> -Shift;
		}
	}
	else
	{
		return value;
	}
}

template<::std::int8_t Shift>
constexpr decltype(auto) right_shift(::std::integral auto value) noexcept
{
	return details::left_shift<-Shift>(value);
}

NAGISA_BUILD_LIB_DETAIL_END