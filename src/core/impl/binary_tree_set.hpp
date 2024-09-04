#ifndef IMPL_BINARY_TREE_SET_HPP
#define IMPL_BINARY_TREE_SET_HPP

#include "def.hpp"
#include "set.hpp"

namespace Vessel {

template <typename PType>
concept IsBinaryTreeSetConfiguration = requires {
  requires IsConfiguration<PType>;
  requires IsSetSubTypesAvailable<PType>;
};

template <class PType>
struct DefaultBinaryTreeSetConfiguration : public Configuration<> {
  using ValueType = PType;
  using FindType = ValueType;
};
static_assert(IsBinaryTreeSetConfiguration<
              DefaultBinaryTreeSetConfiguration<DummyScalar>>);

template <IsBinaryTreeSetConfiguration PConfigurationType>
class BinaryTreeSetImplementation {
public:
  using SizeType = typename PConfigurationType::SizeType;
  using ValueType = typename PConfigurationType::ValueType;
  using FindType = typename PConfigurationType::FindType;

private:
  class Iterator {
  public:
    using ContainerType = BinaryTreeSetImplementation;
    using ValueType = typename ContainerType::ValueType &;

  private:
  public:
    explicit Iterator() { throw UnimplementedException(); }
    auto operator++() -> Iterator & { throw UnimplementedException(); }
    auto operator*() const -> ValueType { throw UnimplementedException(); }
    auto operator==(const Iterator &p_iterator) const -> Bool {
      throw UnimplementedException();
    }
  };

  class ConstantIterator {
  public:
    using ContainerType = BinaryTreeSetImplementation;
    using ValueType = const typename ContainerType::ValueType &;

  private:
  public:
    explicit ConstantIterator() { throw UnimplementedException(); }
    auto operator++() -> ConstantIterator & { throw UnimplementedException(); }
    auto operator*() const -> ValueType { throw UnimplementedException(); }
    auto operator==(const ConstantIterator &p_iterator) const -> Bool {
      throw UnimplementedException();
    }
  };

public:
  explicit BinaryTreeSetImplementation() { throw UnimplementedException(); }

  BinaryTreeSetImplementation(const BinaryTreeSetImplementation &p_set) {
    throw UnimplementedException();
  }

  BinaryTreeSetImplementation(BinaryTreeSetImplementation &&p_set) {
    throw UnimplementedException();
  }

  ~BinaryTreeSetImplementation() {}

  auto operator=(const BinaryTreeSetImplementation &p_set)
      -> BinaryTreeSetImplementation & {
    throw UnimplementedException();
  }

  auto operator=(BinaryTreeSetImplementation &&p_set)
      -> BinaryTreeSetImplementation & {
    throw UnimplementedException();
  }

  auto operator==(const BinaryTreeSetImplementation &p_set) const -> Bool {
    throw UnimplementedException();
  }

  auto find(const FindType &p_finder) -> ValueType & {
    throw UnimplementedException();
  }

  auto find(const FindType &p_finder) const -> const ValueType & {
    throw UnimplementedException();
  }

  auto insert(ValueType p_value) -> void { throw UnimplementedException(); }

  auto remove(const FindType &p_finder) -> void {
    throw UnimplementedException();
  }

  auto contain(const ValueType &p_value) const -> Bool {
    throw UnimplementedException();
  }

  auto get_count() const -> SizeType { throw UnimplementedException(); }

  auto begin() -> Iterator { throw UnimplementedException(); }

  auto end() -> Iterator { throw UnimplementedException(); }

  auto begin() const -> ConstantIterator { throw UnimplementedException(); }

  auto end() const -> ConstantIterator { throw UnimplementedException(); }
};

template <typename PType>
using BinaryTreeSet =
    BinaryTreeSetImplementation<DefaultBinaryTreeSetConfiguration<PType>>;

static_assert(IsSet<BinaryTreeSet<DummyScalar>>);

} // namespace Vessel

#endif // IMPL_BINARY_TREE_SET_HPP