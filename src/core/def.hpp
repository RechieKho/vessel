#ifndef DEF_HPP
#define DEF_HPP

#include <stdint.h>

namespace Ragine
{

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

    template <class = void>
    class Exception
    {
    public:
        using ValueType = const Char *;

    private:
        ValueType message;

    public:
        Exception(ValueType p_message) : message(p_message) {}
        ValueType what() { return message; }
    };

    template <typename Type>
    concept IsTypeAvailable = requires {
        typename Type::Type;
    };

    template <typename Type>
    concept IsKeyTypeAvailable = requires {
        typename Type::KeyType;
    };

    template <typename Type>
    concept IsValueTypeAvailable = requires {
        typename Type::ValueType;
    };

    template <typename Type>
    concept IsValueAvailable = requires {
        Type::value;
    };

    struct Inconstructible
    {
        ~Inconstructible() = delete;
    };

    template <class = void>
    struct Dummy
    {
    };

    constexpr const Dummy<> dummy_value;

    template <typename TargetType>
    struct RemovePointer : public Inconstructible
    {
        using Type = TargetType;
    };

    template <typename TargetType>
    struct RemovePointer<TargetType *> : public Inconstructible
    {
        using Type = TargetType;
    };

    template <typename TargetType>
    struct RemovePointer<TargetType *const> : public Inconstructible
    {
        using Type = TargetType;
    };

    template <typename TargetType>
    struct RemovePointer<TargetType *volatile> : public Inconstructible
    {
        using Type = TargetType;
    };

    template <typename TargetType>
    struct RemovePointer<TargetType *const volatile> : public Inconstructible
    {
        using Type = TargetType;
    };

    static_assert(IsTypeAvailable<RemovePointer<Dummy<>>>);

    template <typename TargetType>
    struct RemoveConstant : public Inconstructible
    {
        using Type = TargetType;
    };

    template <typename TargetType>
    struct RemoveConstant<const TargetType> : public Inconstructible
    {
        using Type = TargetType;
    };

    static_assert(IsTypeAvailable<RemoveConstant<Dummy<>>>);

    template <typename TargetType>
    struct RemoveVolatile : public Inconstructible
    {
        using Type = TargetType;
    };

    template <typename TargetType>
    struct RemoveVolatile<volatile TargetType> : public Inconstructible
    {
        using Type = TargetType;
    };

    static_assert(IsTypeAvailable<RemoveVolatile<Dummy<>>>);

    template <typename TargetType>
    struct RemoveReference : public Inconstructible
    {
        using Type = TargetType;
    };

    template <typename TargetType>
    struct RemoveReference<TargetType &> : public Inconstructible
    {
        using Type = TargetType;
    };

    template <typename TargetType>
    struct RemoveReference<TargetType &&> : public Inconstructible
    {
        using Type = TargetType;
    };

    static_assert(IsTypeAvailable<RemoveReference<Dummy<>>>);

    template <typename TargetType>
    using AsPure = RemoveConstant<typename RemoveVolatile<typename RemoveReference<TargetType>::Type>::Type>::Type;

    template <typename Type, Type Value>
    struct CompileTimeItem : public Inconstructible
    {
        using ValueType = Type;
        static constexpr const ValueType value = Value;
    };

    static_assert(IsValueTypeAvailable<CompileTimeItem<Dummy<>, dummy_value>>);
    static_assert(IsValueAvailable<CompileTimeItem<Dummy<>, dummy_value>>);

    using CompileTimeTrue = CompileTimeItem<Bool, true>;
    using CompileTimeFalse = CompileTimeItem<Bool, false>;

    template <typename FirstType, typename SecondType>
    struct SameType : public CompileTimeFalse
    {
    };

    template <typename Type>
    struct SameType<Type, Type> : public CompileTimeTrue
    {
    };

    template <typename FirstType, typename SecondType>
    concept IsSameType = SameType<FirstType, SecondType>::value;

    template <typename FromType, typename ToType>
    concept IsConvertible = requires(FromType p_object) {
        ToType(p_object);
    };

    template <typename Type>
    concept IsSignedInteger = (IsSameType<AsPure<Type>, Sint8> ||
                               IsSameType<AsPure<Type>, Sint16> ||
                               IsSameType<AsPure<Type>, Sint32> ||
                               IsSameType<AsPure<Type>, Sint64>);

    template <typename Type>
    concept IsUnsignedInteger = (IsSameType<AsPure<Type>, Uint8> ||
                                 IsSameType<AsPure<Type>, Uint16> ||
                                 IsSameType<AsPure<Type>, Uint32> ||
                                 IsSameType<AsPure<Type>, Uint64>);

    template <typename Type>
    concept IsInteger = IsSignedInteger<Type> || IsUnsignedInteger<Type>;

    template <typename Type>
    concept IsFloat = (IsSameType<AsPure<Type>, Float32> || IsSameType<AsPure<Type>, Float64>);

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

    template <typename Type>
    Type &&declval() { throw Exception("`declval` must not be used in evaluated context."); }

    template <typename Type>
    auto move(Type &&p_object) { return static_cast<typename RemoveReference<Type>::Type>(p_object); }

    template <typename Type>
    concept IsForwardIterator = requires(Type p_iterator) {
        IsValueTypeAvailable<Type>;

        { ++p_iterator } -> IsSameType<Type>;
        { *p_iterator } -> IsSameType<typename Type::ValueType>;
        { p_iterator == p_iterator } -> IsSameType<Bool>;
    };

    template <typename Type>
    concept IsBidirectionalIterator = requires(Type p_iterator) {
        IsForwardIterator<Type>;

        { --p_iterator } -> IsSameType<Type>;
    };

    template <typename Type>
    concept IsRandomAccessIterator = requires(Type p_iterator) {
        IsBidirectionalIterator<Type>;
        IsKeyTypeAvailable<Type>;

        { p_iterator[declval<typename Type::KeyType>()] } -> IsSameType<typename Type::ValueType>;
    };

    template <typename Type>
    concept IsContiguousIterator = requires(Type p_iterator) {
        IsRandomAccessIterator<Type>;

        { p_iterator - p_iterator } -> IsSameType<SizeType>;
    };

    template <typename Type>
    concept IsIterable = requires(Type p_iterable) {
        { p_iterable.begin() } -> IsForwardIterator;
        { p_iterable.end() } -> IsForwardIterator;
    };

    template <typename Type>
    concept IsComparable = requires(Type p_object) {
        { p_object == p_object } -> IsSameType<Bool>;
        { p_object < p_object } -> IsSameType<Bool>;
    };

    template <typename Type, typename ReturnType, typename... ArgumentTypes>
    concept IsFunction = requires(Type p_function) {
        { p_function(declval<ArgumentTypes>()...) } -> IsSameType<ReturnType>;
    };

} // namespace Ragine

#endif // DEF_HPP