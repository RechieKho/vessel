#ifndef DEF_HPP
#define DEF_HPP

#include <stdint.h>

namespace Ragine {

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

template <typename Type> auto declval() -> Type && {
  throw Exception("`declval` must not be used in evaluated context.");
}

template <typename Type>
concept IsTypeAvailable = requires { typename Type::Type; };

template <typename Type>
concept IsKeyTypeAvailable = requires { typename Type::KeyType; };

template <typename Type>
concept IsValueTypeAvailable = requires { typename Type::ValueType; };

template <typename Type>
concept IsValueAvailable = requires { Type::value; };

template <class = void> struct Inconstructible {
  ~Inconstructible() = delete;
};

template <class = void> struct Dummy {};

constexpr const Dummy<> dummy_value;

template <typename TargetType> struct RemovePointer : public Inconstructible<> {
  using Type = TargetType;
};

template <typename TargetType>
struct RemovePointer<TargetType *> : public Inconstructible<> {
  using Type = TargetType;
};

template <typename TargetType>
struct RemovePointer<TargetType *const> : public Inconstructible<> {
  using Type = TargetType;
};

template <typename TargetType>
struct RemovePointer<TargetType *volatile> : public Inconstructible<> {
  using Type = TargetType;
};

template <typename TargetType>
struct RemovePointer<TargetType *const volatile> : public Inconstructible<> {
  using Type = TargetType;
};

static_assert(IsTypeAvailable<RemovePointer<Dummy<>>>);

template <typename TargetType>
struct RemoveConstant : public Inconstructible<> {
  using Type = TargetType;
};

template <typename TargetType>
struct RemoveConstant<const TargetType> : public Inconstructible<> {
  using Type = TargetType;
};

static_assert(IsTypeAvailable<RemoveConstant<Dummy<>>>);

template <typename TargetType>
struct RemoveVolatile : public Inconstructible<> {
  using Type = TargetType;
};

template <typename TargetType>
struct RemoveVolatile<volatile TargetType> : public Inconstructible<> {
  using Type = TargetType;
};

static_assert(IsTypeAvailable<RemoveVolatile<Dummy<>>>);

template <typename TargetType>
struct RemoveReference : public Inconstructible<> {
  using Type = TargetType;
};

template <typename TargetType>
struct RemoveReference<TargetType &> : public Inconstructible<> {
  using Type = TargetType;
};

template <typename TargetType>
struct RemoveReference<TargetType &&> : public Inconstructible<> {
  using Type = TargetType;
};

static_assert(IsTypeAvailable<RemoveReference<Dummy<>>>);

template <typename TargetType>
using AsPure = RemoveConstant<typename RemoveVolatile<
    typename RemoveReference<TargetType>::Type>::Type>::Type;

template <typename Type, Type Value>
struct CompileTimeItem : public Inconstructible<> {
  using ValueType = Type;
  static constexpr const ValueType value = Value;
};

static_assert(IsValueTypeAvailable<CompileTimeItem<Dummy<>, dummy_value>>);
static_assert(IsValueAvailable<CompileTimeItem<Dummy<>, dummy_value>>);

using CompileTimeTrue = CompileTimeItem<Bool, true>;
using CompileTimeFalse = CompileTimeItem<Bool, false>;

template <typename FirstType, typename SecondType>
struct SameType : public CompileTimeFalse {};

template <typename Type>
struct SameType<Type, Type> : public CompileTimeTrue {};

template <typename FirstType, typename SecondType>
concept IsSameType = SameType<FirstType, SecondType>::value;

template <typename FromType, typename ToType>
concept IsConvertible = requires { ToType(declval<FromType>()); };

template <typename Type>
concept IsSignedInteger =
    (IsSameType<AsPure<Type>, Sint8> || IsSameType<AsPure<Type>, Sint16> ||
     IsSameType<AsPure<Type>, Sint32> || IsSameType<AsPure<Type>, Sint64>);

template <typename Type>
concept IsUnsignedInteger =
    (IsSameType<AsPure<Type>, Uint8> || IsSameType<AsPure<Type>, Uint16> ||
     IsSameType<AsPure<Type>, Uint32> || IsSameType<AsPure<Type>, Uint64>);

template <typename Type>
concept IsInteger = IsSignedInteger<Type> || IsUnsignedInteger<Type>;

template <typename Type>
concept IsFloat =
    (IsSameType<AsPure<Type>, Float32> || IsSameType<AsPure<Type>, Float64>);

template <typename Type>
concept IsNumeric = IsFloat<Type> || IsInteger<Type>;

template <typename Type>
concept IsFloatTypeAvailable = requires {
  typename Type::FloatType;
  IsFloat<typename Type::FloatType>;
};

template <typename Type>
concept IsIntTypeAvailable = requires {
  typename Type::IntType;
  IsInteger<typename Type::IntType>;
};

template <typename Type>
concept IsSintTypeAvailable = requires {
  typename Type::SintType;
  IsSignedInteger<typename Type::SintType>;
};

template <typename Type>
concept IsUintTypeAvailable = requires {
  typename Type::UintType;
  IsUnsignedInteger<typename Type::UintType>;
};

template <typename Type>
concept IsSizeTypeAvailable = requires {
  typename Type::SizeType;
  IsUnsignedInteger<typename Type::SizeType>;
};

template <typename Type> auto move(Type &&p_object) {
  return static_cast<typename RemoveReference<Type>::Type &&>(p_object);
}

template <typename Type>
auto forward(typename RemoveReference<Type>::Type &&p_object) {
  return static_cast<Type &&>(p_object);
}

template <typename Type>
auto forward(typename RemoveReference<Type>::Type &p_object) {
  return static_cast<Type &&>(p_object);
}

template <typename Type>
concept IsForwardIterator = IsValueTypeAvailable<Type> && requires {
  { ++declval<Type>() } -> IsSameType<Type &>;
  { *declval<Type>() } -> IsSameType<typename Type::ValueType>;
  { declval<Type>() == declval<const Type &>() } -> IsSameType<Bool>;
};

template <typename Type>
concept IsBidirectionalIterator = IsForwardIterator<Type> && requires {
  { --declval<Type>() } -> IsSameType<Type &>;
};

template <typename Type>
concept IsRandomAccessIterator =
    IsBidirectionalIterator<Type> && IsKeyTypeAvailable<Type> && requires {
      {
        declval<Type>()[declval<typename Type::KeyType>()]
      } -> IsSameType<typename Type::ValueType>;
    };

template <typename Type>
concept IsContiguousIterator = IsRandomAccessIterator<Type> && requires {
  { declval<Type>() - declval<Type>() } -> IsSameType<SizeType>;
};

template <typename Type>
concept IsIterable = requires {
  { declval<Type>().begin() } -> IsForwardIterator;
  { declval<Type>().end() } -> IsForwardIterator;
};

template <typename Type>
concept IsEqualityAvailable = requires {
  { declval<Type>() == declval<Type>() } -> IsSameType<Bool>;
};

template <typename Type>
concept IsOrderingAvailable = requires {
  { declval<Type>() < declval<Type>() } -> IsSameType<Bool>;
};

template <typename Type>
concept IsComparable = requires {
  IsEqualityAvailable<Type>;
  IsOrderingAvailable<Type>;
};

template <typename Type, typename ReturnType, typename... ArgumentTypes>
concept IsCallable = requires {
  { declval<Type>()(declval<ArgumentTypes>()...) } -> IsSameType<ReturnType>;
};

template <typename Type>
concept IsArithmaticAvailable = IsComparable<Type> && requires {
  { declval<Type>() + declval<Type>() } -> IsSameType<Type>;
  { declval<Type>() - declval<Type>() } -> IsSameType<Type>;
  { declval<Type>() * declval<Type>() } -> IsSameType<Type>;
  { declval<Type>() / declval<Type>() } -> IsSameType<Type>;
};

template <typename DerivedType, typename BaseType>
concept IsBaseType = IsConvertible<DerivedType *, BaseType *>;

template <typename Type>
concept IsInconstructible = IsBaseType<Type, Inconstructible<>>;

template <class = void> struct Configuration : public Inconstructible<> {
  using SizeType = Ragine::SizeType;
  using SintType = Ragine::Sint;
  using UintType = Ragine::Uint;
  using FloatType = Ragine::Float;
};

template <typename Type>
concept IsConfiguration = IsBaseType<Type, Configuration<>>;

} // namespace Ragine

#endif // DEF_HPP