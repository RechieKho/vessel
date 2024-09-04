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

public:
  explicit ArrayListImplementation(SizeType p_capacity = 0)
      : data(null_pointer), count(0), capacity(0) {
    capture(p_capacity);
  }

  ArrayListImplementation(const ArrayListImplementation &p_list)
      : ArrayListImplementation(p_list.count) {
    for (KeyType i = 0; i < p_list.count; ++i)
      push_back(p_list[i]);
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
    for (KeyType i = 0; i < p_list.count; ++i) {
      push_back(p_list[i]);
    }

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

    return *this;
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

    for (KeyType i = 0; i < count; ++i)
      if ((*this)[i] != p_list[i])
        return false;

    return true;
  }

  auto operator<(const ArrayListImplementation &p_list) const -> Bool {
    if (count < p_list.count)
      return true;
    if (count > p_list.count)
      return false;

    for (KeyType i = 0; i < count; ++i) {
      const auto &self_item = (*this)[i];
      const auto &other_item = (p_list)[i];

      if (self_item < other_item)
        return true;
      if (self_item > other_item)
        return false;
    }

    return false;
  }

  auto operator<<(ValueType p_value) -> ArrayListImplementation & {
    push_back(move(p_value));
    return *this;
  }

  auto slice(KeyType p_start, KeyType p_end) const -> ArrayListImplementation {
    if (p_start >= count)
      throw Exception("Out of bound.");
    if (p_end > count)
      throw Exception("Out of bound.");
    if (p_start > p_end)
      throw Exception("Starting index is bigger than ending index.");

    if (p_start == p_end)
      return ArrayListImplementation();

    auto new_list = ArrayListImplementation(p_end - p_start);
    for (KeyType i = p_start; i < p_end; ++i)
      new_list.push_back((*this)[i]);

    return new_list;
  }

  auto insert(KeyType p_key, ValueType p_value) -> void {
    if (p_key > count)
      throw Exception("Out of bound.");

    const auto new_count = count + 1;
    auto new_capacity =
        capacity == 0 ? PConfigurationType::initial_capacity : capacity;
    while (new_capacity < new_count)
      new_capacity *= 2;

    if (new_capacity != capacity) {
      auto new_data = new ValueType[new_capacity];
      for (KeyType i = 0; i < p_key; ++i)
        new_data[i] = move(data[i]);
      for (KeyType i = p_key + 1; i < new_count; ++i)
        new_data[i] = move(data[i - 1]);
      new_data[p_key] = move(p_value);
      delete[] data;
      data = new_data;
    } else {
      for (KeyType i = new_count; i > p_key; --i)
        data[i] = move(data[i - 1]);
      data[p_key] = move(p_value);
    }

    count = new_count;
    capacity = new_capacity;
  }

  auto push_back(ValueType p_value) -> void { insert(count, p_value); }

  auto push_front(ValueType p_value) -> void { insert(0, p_value); }

  auto remove(KeyType p_key) -> ValueType {
    if (p_key >= count)
      throw Exception("Out of bound.");

    const auto popped = move((*this)[p_key]);

    for (KeyType i = p_key; i < count - 1; ++i) {
      (*this)[i] = move((*this)[i + 1]);
    }

    count -= 1;
    return popped;
  }

  auto pop_back() -> ValueType { return remove(count - 1); }

  auto pop_front() -> ValueType { return remove(0); }

  auto get_count() const -> SizeType { return count; }

  auto contain(const ValueType &p_value) const -> Bool {
    for (KeyType i = 0; i < count; ++i)
      if ((*this)[i] == p_value)
        return true;
    return false;
  }

  auto begin() -> Iterator { return Iterator(*this, 0); };

  auto end() -> Iterator { return Iterator(*this, count); };

  auto begin() const -> ConstantIterator { return ConstantIterator(*this, 0); };

  auto end() const -> ConstantIterator { return ConstantIterator(*this, 0); };
};

template <typename PType>
using ArrayList = ArrayListImplementation<DefaultArrayListConfiguration<PType>>;

static_assert(IsList<ArrayList<DummyScalar>>);

} // namespace Vessel

#endif // IMPL_ARRAY_LIST_HPP