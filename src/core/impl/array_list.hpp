#ifndef IMPL_ARRAY_LIST_HPP
#define IMPL_ARRAY_LIST_HPP

#include "def.hpp"
#include "list.hpp"

namespace Vessel {

template <typename PType>
concept IsArrayListConfiguration =
    IsListSubTypesAvailable<PType> && IsConfiguration<PType> && requires {
      {
        PType::initial_capacity
      } -> IsSameType<const typename PType::SizeType &>;
    };

template <class PType>
struct DefaultArrayListConfiguration : public Configuration<> {
  using ValueType = PType;
  using KeyType = SizeType;
  static constexpr const SizeType initial_capacity = 16;
};
static_assert(IsArrayListConfiguration<DefaultArrayListConfiguration<Dummy>>);

template <IsArrayListConfiguration PConfigurationType>
class ArrayListImplementation {
public:
  using SizeType = typename PConfigurationType::SizeType;
  using KeyType = typename PConfigurationType::KeyType;
  using ValueType = typename PConfigurationType::ValueType;

private:
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
  explicit ArrayListImplementation(
      SizeType p_initial_capacity = PConfigurationType::initial_capacity) {
    throw UnimplementedException();
  }

  ArrayListImplementation(const ArrayListImplementation &p_list) {
    throw UnimplementedException();
  }

  ArrayListImplementation(ArrayListImplementation &&p_list) {
    throw UnimplementedException();
  }

  auto operator=(const ArrayListImplementation &p_list)
      -> ArrayListImplementation & {
    throw UnimplementedException();
  }

  auto
  operator=(ArrayListImplementation &&p_list) -> ArrayListImplementation & {
    throw UnimplementedException();
  }

  auto operator[](KeyType p_key) -> ValueType & {
    throw UnimplementedException();
  }

  auto operator[](KeyType p_key) const -> const ValueType & {
    throw UnimplementedException();
  }

  auto operator==(const ArrayListImplementation &p_list) const -> Bool {
    throw UnimplementedException();
  }

  auto operator<(const ArrayListImplementation &p_list) const -> Bool {
    throw UnimplementedException();
  }

  auto operator<<(ValueType p_value) -> ArrayListImplementation & {
    throw UnimplementedException();
  }

  auto slice(KeyType p_start, KeyType p_end) const -> ArrayListImplementation {
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

  auto clone() const -> ArrayListImplementation {
    throw UnimplementedException();
  }

  auto get_count() const -> SizeType { throw UnimplementedException(); }

  auto contain(const ValueType &p_value) const -> Bool {
    throw UnimplementedException();
  }

  auto begin() -> Iterator { throw UnimplementedException(); };

  auto end() -> Iterator { throw UnimplementedException(); };

  auto begin() const -> ConstantIterator { throw UnimplementedException(); };

  auto end() const -> ConstantIterator { throw UnimplementedException(); };
};

template <typename PType>
using ArrayList = ArrayListImplementation<DefaultArrayListConfiguration<PType>>;

static_assert(IsList<ArrayList<Dummy>>);

} // namespace Vessel

#endif // IMPL_ARRAY_LIST_HPP