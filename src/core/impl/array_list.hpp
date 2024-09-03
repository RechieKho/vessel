#ifndef IMPL_ARRAY_LIST_HPP
#define IMPL_ARRAY_LIST_HPP

#include "def.hpp"
#include "list.hpp"

namespace Vessel {

template <typename PType>
concept IsArrayListConfiguration = requires {
  requires IsListSubTypesAvailable<PType>;
  requires IsConfiguration<PType>;
  { PType::initial_capacity } -> IsSameType<const typename PType::SizeType &>;
  requires PType::initial_capacity > 0;
};

template <class PType>
struct DefaultArrayListConfiguration : public Configuration<> {
  using ValueType = PType;
  using KeyType = SizeType;
  static constexpr const SizeType initial_capacity = 16;
};
static_assert(
    IsArrayListConfiguration<DefaultArrayListConfiguration<DummyScalar>>);

template <IsArrayListConfiguration PConfigurationType>
class ArrayListImplementation {
public:
  using SizeType = typename PConfigurationType::SizeType;
  using KeyType = typename PConfigurationType::KeyType;
  using ValueType = typename PConfigurationType::ValueType;

private:
  ValueType *data;
  SizeType count;
  SizeType capacity;

  class Iterator {
  public:
    using ContainerType = ArrayListImplementation;
    using KeyType = typename ContainerType::KeyType;
    using ValueType = typename ContainerType::ValueType &;

  private:
    ContainerType &container;
    KeyType index;

  public:
    explicit Iterator(ContainerType &p_container, KeyType p_index)
        : container(p_container), index(p_index) {}

    auto operator++() -> Iterator & {
      ++index;
      return *this;
    }

    auto operator*() const -> ValueType { return container[index]; }

    auto operator==(const Iterator &p_iterator) const -> Bool {
      return container == p_iterator.container && index == p_iterator.index;
    }
  };

  class ConstantIterator {
  public:
    using ContainerType = ArrayListImplementation;
    using KeyType = typename ContainerType::KeyType;
    using ValueType = const ContainerType::ValueType &;

  private:
    const ContainerType &container;
    KeyType index;

  public:
    explicit ConstantIterator(const ContainerType &p_container, KeyType p_index)
        : container(p_container), index(p_index) {}

    auto operator++() -> ConstantIterator & {
      ++index;
      return *this;
    }

    auto operator*() const -> ValueType { return container[index]; }

    auto operator==(const ConstantIterator &p_iterator) const -> Bool {
      return container == p_iterator.container && index == p_iterator.index;
    }
  };

  auto release() -> void {
    if (capacity != 0 && data != null_pointer)
      delete[] data;

    capacity = 0;
    count = 0;
  }

  auto capture(SizeType p_capacity) -> void {
    release();
    if (p_capacity == 0)
      return;

    capacity = p_capacity;
    data = new ValueType[p_capacity];
  }

  auto reserve(KeyType p_minimum_capacity) -> void {
    if (capacity > p_minimum_capacity)
      return;

    auto new_capacity =
        capacity == 0 ? PConfigurationType::initial_capacity : capacity;
    while (new_capacity < p_minimum_capacity)
      new_capacity *= 2;

    auto new_list = ArrayListImplementation(new_capacity);
    for (const auto item : *this)
      new_list.push_back(item);

    *this = move(new_list);
  }

public:
  explicit ArrayListImplementation(SizeType p_capacity = 0)
      : data(null_pointer), count(0), capacity(0) {
    capture(p_capacity);
  }

  ArrayListImplementation(const ArrayListImplementation &p_list)
      : ArrayListImplementation(p_list.count) {
    for (const auto item : p_list)
      push_back(item);
  }

  ArrayListImplementation(ArrayListImplementation &&p_list)
      : data(p_list.data), count(p_list.count), capacity(p_list.capacity) {
    p_list.data = null_pointer;
    p_list.count = 0;
    p_list.capacity = 0;
  }

  ~ArrayListImplementation() { release(); }

  auto operator=(const ArrayListImplementation &p_list)
      -> ArrayListImplementation & {
    capture(p_list.count);
    for (const auto item : p_list)
      push_back(item);

    return *this;
  }

  auto
  operator=(ArrayListImplementation &&p_list) -> ArrayListImplementation & {
    release();
    data = p_list.data;
    capacity = p_list.capacity;
    count = p_list.count;

    p_list.data = null_pointer;
    p_list.capacity = 0;
    p_list.count = 0;
  }

  auto operator[](KeyType p_key) -> ValueType & {
    if (p_key >= count)
      throw Exception("Out of bound.");
    return data[p_key];
  }

  auto operator[](KeyType p_key) const -> const ValueType & {
    if (p_key >= count)
      throw Exception("Out of bound.");
    return data[p_key];
  }

  auto operator==(const ArrayListImplementation &p_list) const -> Bool {
    if (count != p_list.count)
      return false;
    // TODO: Check each element.
    return true;
  }

  auto operator<(const ArrayListImplementation &p_list) const -> Bool {
    if (count < p_list.count)
      return true;
    if (count > p_list.count)
      return false;
    // TODO: Compare each element.
    return true;
  }

  auto operator<<(ValueType p_value) -> ArrayListImplementation & {
    push_back(move(p_value));
    return *this;
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

static_assert(IsList<ArrayList<DummyScalar>>);

} // namespace Vessel

#endif // IMPL_ARRAY_LIST_HPP