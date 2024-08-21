#ifndef DEF_HPP
#define DEF_HPP

#include <stdint.h>

namespace Vessel {

using Sint8 = int8_t;
using Sint16 = int16_t;
using Sint32 = int32_t;
using Sint64 = int64_t;
using Sint = Sint32;

using Char = char;
using Uint8 = uint8_t;
using Uint16 = uint16_t;
using Uint32 = uint32_t;
using Uint64 = uint64_t;
using Uint = Uint32;
using SizeType = Uint64;

using Float32 = float;
using Float64 = double;
using Float = Float32;

using Bool = bool;

constexpr const auto null_pointer = nullptr;
using NullPointer = decltype(null_pointer);

template <typename ReturnType, typename... ArgumentType>
using Function = ReturnType(ArgumentType...);

template <class = void> class Exception {
public:
  using ValueType = const Char *;

private:
  ValueType message;

public:
  Exception(ValueType p_message) : message(p_message) {}
  virtual auto what() const noexcept -> ValueType { return message; }
};

template <class = void> class UnimplementedException : public Exception<> {
public:
  using ExceptionBaseType = Exception<>;

private:
public:
  UnimplementedException() : ExceptionBaseType("Unimplemented.") {}
};

template <typename PType> auto declval() -> PType && {
  throw Exception("`declval` must not be used in evaluated context.");
}

template <typename PType>
concept IsTypeAvailable = requires { typename PType::Type; };

template <typename PType>
concept IsKeyTypeAvailable = requires { typename PType::KeyType; };

template <typename PType>
concept IsValueTypeAvailable = requires { typename PType::ValueType; };

template <typename PType>
concept IsValueAvailable = requires { PType::value; };

template <class = void> struct Inconstructible {
  ~Inconstructible() = delete;
};

using DummyScalar = Sint;
constexpr const DummyScalar dummy_scalar_value = {};

template <class = void> struct DummyClass {};
constexpr const DummyClass<> dummy_class_value = {};

template <typename PType, PType PValue>
struct CompileTimeItem : public Inconstructible<> {
  using ValueType = PType;
  static constexpr const auto value = PValue;
};

static_assert(
    IsValueTypeAvailable<CompileTimeItem<DummyScalar, dummy_scalar_value>>);
static_assert(
    IsValueAvailable<CompileTimeItem<DummyScalar, dummy_scalar_value>>);

using CompileTimeTrue = CompileTimeItem<Bool, true>;
using CompileTimeFalse = CompileTimeItem<Bool, false>;

template <typename PFirstType, typename PSecondType>
struct SameType : public CompileTimeFalse {};

template <typename PType>
struct SameType<PType, PType> : public CompileTimeTrue {};

template <typename PFirstType, typename PSecondType>
concept IsSameType = SameType<PFirstType, PSecondType>::value;

template <typename PTargetType>
struct RemovePointer : public Inconstructible<> {
  using Type = PTargetType;
};

template <typename PTargetType>
struct RemovePointer<PTargetType *> : public Inconstructible<> {
  using Type = PTargetType;
};

template <typename PTargetType>
struct RemovePointer<PTargetType *const> : public Inconstructible<> {
  using Type = PTargetType;
};

template <typename PTargetType>
struct RemovePointer<PTargetType *volatile> : public Inconstructible<> {
  using Type = PTargetType;
};

template <typename PTargetType>
struct RemovePointer<PTargetType *const volatile> : public Inconstructible<> {
  using Type = PTargetType;
};

static_assert(IsTypeAvailable<RemovePointer<DummyScalar>>);

template <typename PTargetType>
struct RemoveConstant : public Inconstructible<> {
  using Type = PTargetType;
};

template <typename PTargetType>
struct RemoveConstant<const PTargetType> : public Inconstructible<> {
  using Type = PTargetType;
};

template <typename PTargetType>
struct RemoveConstant<const PTargetType &> : public Inconstructible<> {
  using Type = PTargetType &;
};

template <typename PTargetType>
struct RemoveConstant<const PTargetType &&> : public Inconstructible<> {
  using Type = PTargetType &&;
};

static_assert(IsTypeAvailable<RemoveConstant<DummyScalar>>);

template <typename PTargetType>
struct RemoveVolatile : public Inconstructible<> {
  using Type = PTargetType;
};

template <typename PTargetType>
struct RemoveVolatile<volatile PTargetType> : public Inconstructible<> {
  using Type = PTargetType;
};

template <typename PTargetType>
struct RemoveVolatile<volatile PTargetType &> : public Inconstructible<> {
  using Type = PTargetType &;
};

template <typename PTargetType>
struct RemoveVolatile<volatile PTargetType &&> : public Inconstructible<> {
  using Type = PTargetType &&;
};

static_assert(IsTypeAvailable<RemoveVolatile<DummyScalar>>);

template <typename PTargetType>
struct RemoveReference : public Inconstructible<> {
  using Type = PTargetType;
};

template <typename PTargetType>
struct RemoveReference<PTargetType &> : public Inconstructible<> {
  using Type = PTargetType;
};

template <typename PTargetType>
struct RemoveReference<PTargetType &&> : public Inconstructible<> {
  using Type = PTargetType;
};

static_assert(IsTypeAvailable<RemoveReference<DummyScalar>>);

template <typename PTargetType>
using AsPure = RemoveConstant<typename RemoveVolatile<
    typename RemoveReference<PTargetType>::Type>::Type>::Type;

template <typename PType>
struct ConstantQualifiedType : public CompileTimeFalse {};

template <typename PType>
struct ConstantQualifiedType<const PType> : public CompileTimeTrue {};

template <typename PType>
struct ConstantQualifiedType<const PType &> : public CompileTimeTrue {};

template <typename PType>
struct ConstantQualifiedType<const PType &&> : public CompileTimeTrue {};

template <typename PType>
concept IsConstantQualifiedType = ConstantQualifiedType<PType>::value;

static_assert(!IsConstantQualifiedType<DummyScalar>);
static_assert(IsConstantQualifiedType<const DummyScalar>);
static_assert(IsConstantQualifiedType<const DummyScalar &>);
static_assert(IsConstantQualifiedType<const DummyScalar &&>);
static_assert(!IsConstantQualifiedType<const DummyScalar *>);
static_assert(IsConstantQualifiedType<const DummyScalar *const>);

template <typename PType>
concept IsDestructible = requires { declval<PType>().~PType(); };

template <typename PType>
concept IsInconstructible = !IsDestructible<PType>;

template <typename PType>
concept IsDefaultConstructible = requires {
  { PType() } -> IsSameType<PType>;
};

template <typename PToType, typename PFromType>
concept IsConstructibleFrom = requires {
  { PToType(declval<PFromType>()) } -> IsSameType<PToType>;
};

template <typename PToType, typename PFromType = PToType>
concept IsMovableFrom = IsConstructibleFrom<PToType, PFromType &&>;

template <typename PToType, typename PFromType = PToType>
concept IsCopyableFrom = IsConstructibleFrom<PToType, const PFromType &&>;

template <typename PType>
concept IsNullPointer = IsSameType<NullPointer, PType>;

template <typename PType>
concept IsSignedInteger =
    (IsSameType<AsPure<PType>, Sint8> || IsSameType<AsPure<PType>, Sint16> ||
     IsSameType<AsPure<PType>, Sint32> || IsSameType<AsPure<PType>, Sint64>);

template <typename PType>
concept IsUnsignedInteger =
    (IsSameType<AsPure<PType>, Uint8> || IsSameType<AsPure<PType>, Uint16> ||
     IsSameType<AsPure<PType>, Uint32> || IsSameType<AsPure<PType>, Uint64>);

template <typename PType>
concept IsInteger = IsSignedInteger<PType> || IsUnsignedInteger<PType>;

template <typename PType>
concept IsFloat =
    (IsSameType<AsPure<PType>, Float32> || IsSameType<AsPure<PType>, Float64>);

template <typename PType>
concept IsNumeric = IsFloat<PType> || IsInteger<PType>;

template <typename PType>
concept IsFloatTypeAvailable = requires {
  typename PType::FloatType;
  IsFloat<typename PType::FloatType>;
};

template <typename PType>
concept IsIntTypeAvailable = requires {
  typename PType::IntType;
  IsInteger<typename PType::IntType>;
};

template <typename PType>
concept IsSintTypeAvailable = requires {
  typename PType::SintType;
  IsSignedInteger<typename PType::SintType>;
};

template <typename PType>
concept IsUintTypeAvailable = requires {
  typename PType::UintType;
  IsUnsignedInteger<typename PType::UintType>;
};

template <typename PType>
concept IsSizeTypeAvailable = requires {
  typename PType::SizeType;
  IsUnsignedInteger<typename PType::SizeType>;
};

template <typename PType> struct MemberPointerType : public CompileTimeFalse {};

template <typename PType, typename PClassType>
struct MemberPointerType<PType PClassType::*> : public CompileTimeTrue {};

template <typename PType>
concept IsMemberPointerType = MemberPointerType<PType>::value;

template <typename PType> struct PointerType : public CompileTimeFalse {};

template <typename PType>
struct PointerType<PType *> : public CompileTimeTrue {};

template <typename PType>
concept IsPointerType = PointerType<PType>::value;

template <typename PType>
concept IsEqualityAvailable = requires {
  { declval<const PType>() == declval<const PType>() } -> IsSameType<Bool>;
};

template <typename PType>
concept IsOrderingAvailable = requires {
  { declval<const PType>() < declval<const PType>() } -> IsSameType<Bool>;
};

template <typename PType>
concept IsComparable = requires {
  IsEqualityAvailable<PType>;
  IsOrderingAvailable<PType>;
};

template <typename PType> auto move(PType &&p_object) {
  return static_cast<typename RemoveReference<PType>::Type &&>(p_object);
}

template <typename PType>
auto forward(typename RemoveReference<PType>::PType &&p_object) {
  return static_cast<PType &&>(p_object);
}

template <typename PType>
auto forward(typename RemoveReference<PType>::PType &p_object) {
  return static_cast<PType &&>(p_object);
}

template <typename PType>
concept IsForwardIterator = IsValueTypeAvailable<PType> &&
                            IsEqualityAvailable<const PType> && requires {
                              { ++declval<PType>() } -> IsSameType<PType &>;
                              {
                                *declval<const PType>()
                              } -> IsSameType<typename PType::ValueType>;
                            };

template <typename PType>
concept IsConstantForwardIterator =
    IsForwardIterator<PType> &&
    IsConstantQualifiedType<typename PType::ValueType>;

template <typename PType>
concept IsBidirectionalIterator = IsForwardIterator<PType> && requires {
  { --declval<PType>() } -> IsSameType<PType &>;
};

template <typename PType>
concept IsConstantBidirectionalIterator =
    IsBidirectionalIterator<PType> &&
    IsConstantQualifiedType<typename PType::ValueType>;

template <typename PType>
concept IsRandomAccessIterator =
    IsBidirectionalIterator<PType> && IsKeyTypeAvailable<PType> && requires {
      {
        declval<PType>()[declval<typename PType::KeyType>()]
      } -> IsSameType<typename PType::ValueType>;
    };

template <typename PType>
concept IsConstantRandomAccessIterator =
    IsRandomAccessIterator<PType> &&
    IsConstantQualifiedType<typename PType::ValueType>;

template <typename PType>
concept IsContiguousIterator = IsRandomAccessIterator<PType> && requires {
  { declval<PType>() - declval<PType>() } -> IsSameType<SizeType>;
};

template <typename PType>
concept IsConstantContiguousIterator =
    IsContiguousIterator<PType> &&
    IsConstantQualifiedType<typename PType::ValueType>;

template <typename PType>
concept IsIterable = requires {
  { declval<PType>().begin() } -> IsForwardIterator;
  { declval<PType>().end() } -> IsForwardIterator;
};

template <typename PType>
concept IsConstantIterable = requires {
  { declval<const PType>().begin() } -> IsConstantForwardIterator;
  { declval<const PType>().end() } -> IsConstantForwardIterator;
};

template <typename PType, typename ReturnType, typename... ArgumentTypes>
concept IsCallable = requires {
  { declval<PType>()(declval<ArgumentTypes>()...) } -> IsSameType<ReturnType>;
};

template <typename PType>
concept IsArithmaticAvailable = IsComparable<PType> && requires {
  { declval<const PType>() + declval<const PType>() } -> IsSameType<PType>;
  { declval<const PType>() - declval<const PType>() } -> IsSameType<PType>;
  { declval<const PType>() * declval<const PType>() } -> IsSameType<PType>;
  { declval<const PType>() / declval<const PType>() } -> IsSameType<PType>;
};

template <typename DerivedType, typename BaseType>
concept IsBaseType = IsConstructibleFrom<BaseType *, DerivedType *>;

template <typename PType>
concept IsConfiguration =
    IsSizeTypeAvailable<PType> && IsSintTypeAvailable<PType> &&
    IsUintTypeAvailable<PType> && IsFloatTypeAvailable<PType>;

template <class = void> struct Configuration : public Inconstructible<> {
  using SizeType = Vessel::SizeType;
  using SintType = Vessel::Sint;
  using UintType = Vessel::Uint;
  using FloatType = Vessel::Float;
};
static_assert(IsConfiguration<Configuration<>>);

} // namespace Vessel

#endif // DEF_HPP