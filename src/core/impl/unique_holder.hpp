#ifndef IMPL_UNIQUE_HOLDER_HPP
#define IMPL_UNIQUE_HOLDER_HPP

#include "def.hpp"
#include "holder.hpp"

namespace Vessel {

template <typename PType>
concept IsUniqueHolder = requires {
  requires IsHolder<PType>;
  requires !IsCopyableFrom<PType>;
  requires IsMovableFrom<PType>;
};

template <typename PType, IsReleaser PReleaserType = Releaser<PType>>
class UniqueHolder {
public:
  using ValueType = PType;
  using ReleaserType = PReleaserType;

private:
public:
  UniqueHolder(ValueType *p_pointer) { throw UnimplementedException(); }

  UniqueHolder(const UniqueHolder &p_holder) = delete;

  UniqueHolder(UniqueHolder &&p_holder) { throw UnimplementedException(); }

  auto operator->() -> ValueType * { throw UnimplementedException(); }

  auto operator->() const -> const ValueType * {
    throw UnimplementedException();
  }

  auto operator*() -> ValueType & { throw UnimplementedException(); }

  auto operator*() const -> const ValueType & {
    throw UnimplementedException();
  }
};
static_assert(IsUniqueHolder<UniqueHolder<DummyScalar>>);

} // namespace Vessel

#endif // IMPL_UNIQUE_HOLDER_HPP