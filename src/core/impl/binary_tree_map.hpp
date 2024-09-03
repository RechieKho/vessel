#ifndef IMPL_BINARY_TREE_MAP_HPP
#define IMPL_BINARY_TREE_MAP_HPP

#include "array_list.hpp"
#include "def.hpp"
#include "list.hpp"
#include "map.hpp"

namespace Vessel {

template <typename PType>
concept IsBinaryTreeMapConfiguration = requires {
  requires IsConfiguration<PType>;
  requires IsMapSubTypesAvailable<PType>;

  {
    PType::max_depth_difference
  } -> IsSameType<const typename PType::SizeType &>;
};

template <class PKeyType, class PValueType>
struct DefaultBinaryTreeMapConfiguration : public Configuration<> {
  using KeyType = PKeyType;
  using ValueType = PValueType;
  using KeyListType = ArrayList<KeyType>;
  using ValueListType = ArrayList<ValueType>;
  static constexpr const SizeType max_depth_difference = 8;
};
static_assert(IsBinaryTreeMapConfiguration<
              DefaultBinaryTreeMapConfiguration<DummyScalar, DummyScalar>>);

template <IsBinaryTreeMapConfiguration PConfigurationType>
class BinaryTreeMapImplementation {
public:
  using SizeType = typename PConfigurationType::SizeType;
  using KeyType = typename PConfigurationType::KeyType;
  using ValueType = typename PConfigurationType::ValueType;
  using KeyListType = typename PConfigurationType::KeyListType;
  using ValueListType = typename PConfigurationType::ValueListType;

private:
  class Pair {
  public:
  private:
  public:
    KeyType key;
    ValueType value;
  };

  class Iterator {
  public:
    using ValueType = Pair &;

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
    using ValueType = const Pair &;

  private:
  public:
    auto operator++() -> ConstantIterator & { throw UnimplementedException(); }

    auto operator*() const -> ValueType { throw UnimplementedException(); }

    auto operator==(const ConstantIterator &p_iterator) const -> Bool {
      throw UnimplementedException();
    }
  };

public:
  explicit BinaryTreeMapImplementation(
      SizeType p_max_depth_difference =
          PConfigurationType::max_depth_difference) {
    throw UnimplementedException();
  }

  BinaryTreeMapImplementation(const BinaryTreeMapImplementation &p_map) {
    throw UnimplementedException();
  }

  BinaryTreeMapImplementation(BinaryTreeMapImplementation &&p_map) {
    throw UnimplementedException();
  }

  auto contain_key(const KeyType &p_key) const -> Bool {
    throw UnimplementedException();
  }

  auto compute_values() const -> ValueListType {
    throw UnimplementedException();
  }

  auto compute_keys() const -> KeyListType { throw UnimplementedException(); }

  auto operator==(const BinaryTreeMapImplementation &p_map) const -> Bool {
    throw UnimplementedException();
  }

  auto operator[](const KeyType &p_key) -> ValueType & {
    throw UnimplementedException();
  }

  auto operator[](const KeyType &p_key) const -> const ValueType & {
    throw UnimplementedException();
  }

  auto insert(const KeyType &p_key, ValueType p_value) -> void {
    throw UnimplementedException();
  }

  auto remove(const KeyType &p_key) -> ValueType {
    throw UnimplementedException();
  }

  auto get_count() const -> SizeType { throw UnimplementedException(); }

  auto contain(const ValueType &p_value) const -> Bool {
    throw UnimplementedException();
  }

  auto begin() -> Iterator { throw UnimplementedException(); }

  auto end() -> Iterator { throw UnimplementedException(); }

  auto begin() const -> ConstantIterator { throw UnimplementedException(); }

  auto end() const -> ConstantIterator { throw UnimplementedException(); }
};

template <typename KeyType, typename ValueType>
using BinaryTreeMap = BinaryTreeMapImplementation<
    DefaultBinaryTreeMapConfiguration<KeyType, ValueType>>;

static_assert(IsMap<BinaryTreeMap<DummyScalar, DummyScalar>>);

} // namespace Vessel

#endif // IMPL_BINARY_TREE_MAP_HPP