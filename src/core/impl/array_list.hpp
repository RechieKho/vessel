#ifndef IMPL_ARRAY_LIST_HPP
#define IMPL_ARRAY_LIST_HPP

#include "def.hpp"
#include "list.hpp"

namespace Vessel {

template <typename Type>
concept IsArrayListConfiguration = requires {
  { Type::initial_capacity } -> IsSameType<const typename Type::SizeType &>;
} && IsConfiguration<Type>;

template <class = void>
struct DefaultArrayListConfiguration : public Configuration<> {
  static constexpr const SizeType initial_capacity = 16;
};
static_assert(IsArrayListConfiguration<DefaultArrayListConfiguration<>>);

template <typename Type, IsArrayListConfiguration ConfigurationType =
                             DefaultArrayListConfiguration<>>
class ArrayList {
public:
  using SizeType = ConfigurationType::SizeType;
  using KeyType = SizeType;
  using ValueType = Type;

private:
  ValueType *values;
  SizeType count;
  SizeType capacity;

  auto reserve(SizeType p_minimum_capacity) -> void {
    throw UnimplementedException();
  }

  class Iterator {
  public:
    using ValueType = ValueType &;

  private:
  public:
    auto operator++() -> Iterator & { throw UnimplementedException(); }

    auto operator*() const -> ValueType { throw UnimplementedException(); }

    auto operator==(const Iterator &p_iterator) const -> Bool {
      throw UnimplementedException();
    }
  };

  class ConstantIterator {
  public:
    using ValueType = const ValueType &;

  private:
  public:
    auto operator++() -> ConstantIterator & { throw UnimplementedException(); }

    auto operator*() const -> ValueType { throw UnimplementedException(); }

    auto operator==(const ConstantIterator &p_iterator) const -> Bool {
      throw UnimplementedException();
    }
  };

public:
  explicit ArrayList(
      SizeType p_initial_capacity = ConfigurationType::initial_capacity) {
    throw UnimplementedException();
  }

  ArrayList(const ArrayList &p_list) { throw UnimplementedException(); }

  ArrayList(ArrayList &&p_list) { throw UnimplementedException(); }

  auto operator=(const ArrayList &p_list) -> ArrayList & {
    throw UnimplementedException();
  }

  auto operator=(ArrayList &&p_list) -> ArrayList & {
    throw UnimplementedException();
  }

  auto operator[](KeyType p_key) -> ValueType & {
    throw UnimplementedException();
  }

  auto operator[](KeyType p_key) const -> const ValueType & {
    throw UnimplementedException();
  }

  auto operator==(const ArrayList &p_list) const -> Bool {
    throw UnimplementedException();
  }

  auto operator<(const ArrayList &p_list) const -> Bool {
    throw UnimplementedException();
  }

  auto operator<<(ValueType p_value) -> ArrayList & {
    throw UnimplementedException();
  }

  auto slice(KeyType p_start, KeyType p_end) const -> ArrayList {
    throw UnimplementedException();
  }

  auto insert(KeyType p_key, ValueType p_value) -> void {
    throw UnimplementedException();
  }

  auto push_back(ValueType p_value) -> void { throw UnimplementedException(); }

  auto push_front(ValueType p_value) -> void { throw UnimplementedException(); }

  auto remove(KeyType p_key) -> ValueType { throw UnimplementedException(); }

  auto pop_back() -> ValueType { throw UnimplementedException(); }

  auto pop_front() -> ValueType { throw UnimplementedException(); }

  auto clone() const -> ArrayList { throw UnimplementedException(); }

  auto get_count() const -> SizeType { throw UnimplementedException(); }

  auto contain(const ValueType &p_value) const -> Bool {
    throw UnimplementedException();
  }

  auto begin() -> Iterator { throw UnimplementedException(); };

  auto end() -> Iterator { throw UnimplementedException(); };

  auto begin() const -> ConstantIterator { throw UnimplementedException(); };

  auto end() const -> ConstantIterator { throw UnimplementedException(); };
};
static_assert(IsList<ArrayList<Dummy<>>>);

} // namespace Vessel

#endif // IMPL_ARRAY_LIST_HPP